#include <atomic>
#include <boost/asio.hpp>
#include <iostream>
#include <memory>
#include <thread>

class Service {
public:
    Service() {}

    void HandleClient(boost::asio::ip::tcp::socket& sock) {
        try {
            boost::asio::streambuf request;
            boost::asio::read_until(sock, request, '\n');
            // Emulate request processing.
            int i = 0;
            while (i != 1000000) i++;
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
            // Sending response.
            std::string response = "Response\n";
            boost::asio::write(sock, boost::asio::buffer(response));
        } catch (boost::system::system_error& e) {
            std::cout << "Error occured! Error code = " << e.code() << ". Message: " << e.what();
        }
    }
};

class Acceptor {
public:
    Acceptor(boost::asio::io_service& ios, unsigned short port_num) : m_ios(ios), m_acceptor(m_ios, boost::asio::ip::tcp::endpoint(boost::asio::ip::address_v4::any(), port_num)) { m_acceptor.listen(); }

    void Accept() {
        boost::asio::ip::tcp::socket sock(m_ios);
        m_acceptor.accept(sock);
        Service svc;
        svc.HandleClient(sock);
    }

private:
    boost::asio::io_service& m_ios;
    boost::asio::ip::tcp::acceptor m_acceptor;
};

class Server {
public:
    Server() : m_stop(false) {}

    void Start(unsigned short port_num) {
        m_thread.reset(new std::thread([this, port_num]() { Run(port_num); }));
    }

    void Stop() {
        m_stop.store(true);
        m_thread->join();
    }

private:
    void Run(unsigned short port_num) {
        Acceptor acc(m_ios, port_num);
        while (!m_stop.load()) {
            acc.Accept();
        }
    }

private:
    std::unique_ptr<std::thread> m_thread;
    std::atomic<bool> m_stop;
    boost::asio::io_service m_ios;
};

int main() {
    unsigned short port_num = 3333;
    try {
        Server srv;
        srv.Start(port_num);
        std::this_thread::sleep_for(std::chrono::seconds(60));
        srv.Stop();
    } catch (boost::system::system_error& e) {
        std::cout << "Error occured! Error code = " << e.code() << ". Message: " << e.what();
    }

    return 0;
}
