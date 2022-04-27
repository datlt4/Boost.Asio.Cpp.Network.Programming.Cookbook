#include <boost/asio.hpp>
#include <iostream>

void writeToSocketEnhanced(boost::asio::ip::tcp::socket &sock)
{
	// Allocating and filling the buffer.
	std::string buf = "Hello";

	// Write whole buffer to the socket.
	boost::asio::write(sock, boost::asio::buffer(buf));
}

void writeToSocket(boost::asio::ip::tcp::socket &sock)
{
	// Allocating and filling the buffer.
	std::string buf = "Hello";
	std::size_t total_bytes_written = 0;

	// Run the loop until all data is written
	// to the socket.
	while (total_bytes_written != buf.length())
	{
		total_bytes_written += sock.write_some(boost::asio::buffer(buf.c_str() + total_bytes_written, buf.length() - total_bytes_written));
	}
}

int main()
{
	std::string raw_ip_address = "127.0.0.1";
	unsigned short port_num = 8001;

	try
	{
		boost::asio::io_service ios;
		boost::asio::ip::tcp::endpoint ep(boost::asio::ip::address::from_string(raw_ip_address), port_num);
		boost::asio::ip::tcp::socket sock(ios, ep.protocol());
		sock.connect(ep);
		writeToSocket(sock);
	}
	catch (boost::system::system_error &e)
	{
		std::cout << "Error occured! Error code = " << e.code() << ". Message: " << e.what();
		return e.code().value();
	}

	return 0;
}
