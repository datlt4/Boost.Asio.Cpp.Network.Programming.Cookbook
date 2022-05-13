#include <boost/asio.hpp>
#include <iostream>

int main()
{
	// Step 1. Here we assume that the server application has
	// already obtained the protocol port number.
	unsigned short port_num = 8000;

	// Step 2. Creating an endpoint.
	boost::asio::ip::udp::endpoint ep(boost::asio::ip::address_v4::any(), port_num);

	// Used by 'socket' class constructor.
	boost::asio::io_service ios;

	// Step 3. Creating and opening a socket.
	boost::asio::ip::udp::socket sock(ios, ep.protocol());
	boost::system::error_code ec;

	// Step 4. Binding the socket to an endpoint.
	sock.bind(ep, ec);

	// Handling errors if any.
	if (ec.value() != 0)
	{
		// Failed to bind the socket. Breaking execution.
		std::cout << "Failed to bind the socket."
				  << "Error code = " << ec.value() << ". Message: " << ec.message();
		return ec.value();
	}

	return 0;
}
