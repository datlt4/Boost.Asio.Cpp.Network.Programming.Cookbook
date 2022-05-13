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
    Service()
    {
        std::cout << "Service.Service()" << std::endl;
    }

    void HandleClient(boost::asio::ip::tcp::socket &sock)
    {
        std::cout << "Service.HandleClient()" << std::endl;
        std::cout << "Current System Time = " << boost::posix_time::second_clock::local_time() << std::endl;
        try
        {
            boost::asio::streambuf request;
            boost::asio::read_until(sock, request, '\n');
            // Emulate request processing.
            int i = 0;
            while (i != 1000000)
                i++;
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
            // Sending response.
            std::ostringstream oss;
            oss << boost::posix_time::second_clock::local_time() << std::endl;
            boost::asio::write(sock, boost::asio::buffer(oss.str()));
            // Get current system time
        }
        catch (boost::system::system_error &e)
        {
            std::cout << "Error occured! Error code = " << e.code() << ". Message: " << e.what();
        }
    }
};

class Acceptor
{
public:
    Acceptor(boost::asio::io_service &ios, unsigned short port_num) : m_ios(ios), m_acceptor(m_ios, boost::asio::ip::tcp::endpoint(boost::asio::ip::address_v4::any(), port_num))
    {
        std::cout << "Acceptor.Acceptor()" << std::endl;
        m_acceptor.listen();
    }

    void Accept()
    {
        std::cout << "Acceptor.Accept()" << std::endl;
        boost::asio::ip::tcp::socket sock(m_ios);
        m_acceptor.accept(sock);
        std::cout << "[ before ]m_acceptor.accept()" << std::endl;
        Service svc;
        svc.HandleClient(sock);
        std::cout << "[ after ] m_acceptor.accept()" << std::endl;
    }

private:
    boost::asio::io_service &m_ios;
    boost::asio::ip::tcp::acceptor m_acceptor;
};

class Server
{
public:
    Server() : m_stop(false)
    {
        std::cout << "Server.Server()" << std::endl;
    }

    void Start(unsigned short port_num)
    {
        std::cout << "Server.Start()" << std::endl;
        m_thread.reset(new std::thread([this, port_num]()
                                       { Run(port_num); }));
    }

    void Stop()
    {
        std::cout << "--- Server.Stop()" << std::endl;
        m_stop.store(true);
        m_thread->join();
    }

private:
    void Run(unsigned short port_num)
    {
        std::cout << "Server.Run()" << std::endl;
        Acceptor acc(m_ios, port_num);
        while (!m_stop.load())
        {
            std::cout << "\n";
            acc.Accept();
        }
    }

private:
    std::unique_ptr<std::thread> m_thread;
    std::atomic<bool> m_stop;
    boost::asio::io_service m_ios;
};

int main()
{
    unsigned short port_num = 8000;
    try
    {
        Server srv;
        srv.Start(port_num);
        std::this_thread::sleep_for(std::chrono::seconds(60));
        srv.Stop();
    }
    catch (boost::system::system_error &e)
    {
        std::cout << "Error occured! Error code = " << e.code() << ". Message: " << e.what();
    }

    return 0;
}
