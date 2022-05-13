#include <atomic>
#include <boost/asio.hpp>
#include <boost/date_time.hpp>
#include <iostream>
#include <memory>
#include <thread>
#include <sstream>

class Service
{
public:
    Service(std::shared_ptr<boost::asio::ip::tcp::socket> sock) : m_sock(sock)
    {
        std::cout << "Service.Service()" << std::endl;
    }

    void StartHandling()
    {
        std::cout << "Service.StartHandling()" << std::endl;
        std::cout << "Current System Time = " << boost::posix_time::second_clock::local_time() << std::endl;
        boost::asio::async_read_until(*m_sock.get(), m_request, '\n', [this](const boost::system::error_code &ec, std::size_t bytes_transferred)
                                      { onRequestReceived(ec, bytes_transferred); });
    }

private:
    void onRequestReceived(const boost::system::error_code &ec, std::size_t bytes_transferred)
    {
        std::cout << "Service.onRequestReceived()" << std::endl;
        if (ec.value() != 0)
        {
            std::cout << "Error occured! Error code = " << ec.value() << ". Message: " << ec.message();
            onFinish();
            return;
        }
        // Process the request.
        m_response = ProcessRequest(m_request);
        // Initiate asynchronous write operation.
        boost::asio::async_write(*m_sock.get(), boost::asio::buffer(m_response), [this](const boost::system::error_code &ec, std::size_t bytes_transferred)
                                 { onResponseSent(ec, bytes_transferred); });
    }

    void onResponseSent(const boost::system::error_code &ec, std::size_t bytes_transferred)
    {
        std::cout << "Service.onResponseSent()" << std::endl;
        if (ec.value() != 0)
        {
            std::cout << "Error occured! Error code = " << ec.value() << ". Message: " << ec.message();
        }
        onFinish();
    }

    // Here we perform the cleanup.
    void onFinish()
    {
        std::cout << "Service.onFinish()" << std::endl;
        delete this;
    }

    std::string ProcessRequest(boost::asio::streambuf &request)
    {
        std::cout << "Service.ProcessRequest()" << std::endl;
        // In this method we parse the request, process it
        // and prepare the request.
        // Emulate CPU-consuming operations.
        int i = 0;
        while (i != 1000000)
            i++;
        // Emulate operations that block the thread
        // (e.g. synch I/O operations).
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        // Prepare and return the response message.
        std::ostringstream oss;
        oss << boost::posix_time::second_clock::local_time() << std::endl;
        return oss.str();
    }

private:
    std::shared_ptr<boost::asio::ip::tcp::socket> m_sock;
    std::string m_response;
    boost::asio::streambuf m_request;
};

class Acceptor
{
public:
    Acceptor(boost::asio::io_service &ios, unsigned short port_num) : m_ios(ios), m_acceptor(m_ios, boost::asio::ip::tcp::endpoint(boost::asio::ip::address_v4::any(), port_num)), m_isStopped(false)
    {
        std::cout << "Acceptor.Acceptor()" << std::endl;
    }

    // Start accepting incoming connection requests.
    void Start()
    {
        std::cout << "Acceptor.Start()" << std::endl;
        m_acceptor.listen();
        InitAccept();
    }

    // Stop accepting incoming connection requests.
    void Stop()
    {
        std::cout << "--- Acceptor.Stop()" << std::endl;
        m_isStopped.store(true);
    }

private:
    void InitAccept()
    {
        std::cout << "Acceptor.InitAccept()" << std::endl;
        std::shared_ptr<boost::asio::ip::tcp::socket> sock(new boost::asio::ip::tcp::socket(m_ios));
        m_acceptor.async_accept(*sock.get(), [this, sock](const boost::system::error_code &error)
                                { onAccept(error, sock); });
    }

    void onAccept(const boost::system::error_code &ec, std::shared_ptr<boost::asio::ip::tcp::socket> sock)
    {
        std::cout << "\nAcceptor.onAccept()" << std::endl;
        if (ec.value() == 0)
        {
            std::cout << "[ before ]m_acceptor.accept()" << std::endl;
            (new Service(sock))->StartHandling();
            std::cout << "[ after ]m_acceptor.accept()" << std::endl;
        }
        else
        {
            std::cout << "Error occured! Error code = " << ec.value() << ". Message: " << ec.message();
        }
        // Init next async accept operation if
        // acceptor has not been stopped yet.
        if (!m_isStopped.load())
        {
            InitAccept();
        }
        else
        {
            // Stop accepting incoming connections
            // and free allocated resources.
            m_acceptor.close();
        }
    }

private:
    boost::asio::io_service &m_ios;
    boost::asio::ip::tcp::acceptor m_acceptor;
    std::atomic<bool> m_isStopped;
};

class Server
{
public:
    Server()
    {
        std::cout << "Server.Server()" << std::endl;
        m_work.reset(new boost::asio::io_service::work(m_ios));
    }

    // Start the server.
    void Start(unsigned short port_num, unsigned int thread_pool_size)
    {
        std::cout << "Server.Start()" << std::endl;
        assert(thread_pool_size > 0);
        // Create and start Acceptor.
        acc.reset(new Acceptor(m_ios, port_num));
        acc->Start();
        // Create specified number of threads and
        // add them to the pool.
        for (unsigned int i = 0; i < thread_pool_size; i++)
        {
            std::unique_ptr<std::thread> th(new std::thread([this]()
                                                            { m_ios.run(); }));
            m_thread_pool.push_back(std::move(th));
        }
    }

    // Stop the server.
    void Stop()
    {
        std::cout << "Server.Stop()" << std::endl;
        acc->Stop();
        m_ios.stop();
        for (auto &th : m_thread_pool)
        {
            th->join();
        }
    }

private:
    boost::asio::io_service m_ios;
    std::unique_ptr<boost::asio::io_service::work> m_work;
    std::unique_ptr<Acceptor> acc;
    std::vector<std::unique_ptr<std::thread>> m_thread_pool;
};

const unsigned int DEFAULT_THREAD_POOL_SIZE = 2;

int main()
{
    unsigned short port_num = 8000;
    try
    {
        Server srv;
        unsigned int thread_pool_size = std::thread::hardware_concurrency() * 2;
        if (thread_pool_size == 0)
            thread_pool_size = DEFAULT_THREAD_POOL_SIZE;
        srv.Start(port_num, thread_pool_size);
        std::this_thread::sleep_for(std::chrono::seconds(60));
        srv.Stop();
    }
    catch (boost::system::system_error &e)
    {
        std::cout << "Error occured! Error code = " << e.code() << ". Message: " << e.what();
    }

    return 0;
}
