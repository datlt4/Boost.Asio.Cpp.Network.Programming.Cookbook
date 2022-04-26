#include <boost/asio.hpp>
#include <iostream>

int main()
{
	// Step 1. Assume that the client application has already
	// obtained the IP address and protocol port number of the
	// target server.
	std::string raw_ip_address = "127.0.0.1";
	unsigned short port_num = 8001;

	try
	{
		// Step 2. Creating an endpoint designating
		// a target server application.
		boost::asio::ip::tcp::endpoint ep(boost::asio::ip::address::from_string(raw_ip_address), port_num);
		boost::asio::io_service ios;

		// Step 3. Creating and opening a socket.
		boost::asio::ip::tcp::socket sock(ios, ep.protocol());

		// Step 4. Connecting a socket.
		sock.connect(ep);
	}
	// Overloads of boost::asio::ip::address::from_string() and
	// boost::asio::ip::tcp::socket::connect() used here throw
	// exceptions in case of error condition.
	catch (boost::system::system_error &e)
	{
		std::cout << "Error occured! Error code = " << e.code() << ". Message: " << e.what();
		return e.code().value();
	}

	return 0;
}
