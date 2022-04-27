#include <boost/asio.hpp>
#include <iostream>

std::string readFromSocketDelim(boost::asio::ip::tcp::socket &sock)
{
	boost::asio::streambuf buf;

	// Synchronously read data from the socket until
	// '\n' symbol is encountered.
	boost::asio::read_until(sock, buf, '\n');

	std::string message;

	// Because buffer 'buf' may contain some other data
	// after '\n' symbol, we have to parse the buffer and
	// extract only symbols before the delimiter.
	std::istream input_stream(&buf);
	std::getline(input_stream, message);

	return message;
}

std::string readFromSocketEnhanced(boost::asio::ip::tcp::socket &sock)
{
	const unsigned char MESSAGE_SIZE = 7;
	char buf[MESSAGE_SIZE];
	boost::asio::read(sock, boost::asio::buffer(buf, MESSAGE_SIZE));
	return std::string(buf, MESSAGE_SIZE);
}

std::string readFromSocket(boost::asio::ip::tcp::socket &sock)
{
	const unsigned char MESSAGE_SIZE = 7;
	char buf[MESSAGE_SIZE];
	std::size_t total_bytes_read = 0;

	while (total_bytes_read != MESSAGE_SIZE)
	{
		total_bytes_read += sock.read_some(boost::asio::buffer(buf + total_bytes_read, MESSAGE_SIZE - total_bytes_read));
	}

	return std::string(buf, total_bytes_read);
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
		readFromSocket(sock);
	}
	catch (boost::system::system_error &e)
	{
		std::cout << "Error occured! Error code = " << e.code() << ". Message: " << e.what();
		return e.code().value();
	}

	return 0;
}
