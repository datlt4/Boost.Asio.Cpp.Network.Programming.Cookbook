#include <boost/predef.h> // Tools to identify the OS.

// We need this to enable cancelling of I/O operations on
// Windows XP, Windows Server 2003 and earlier.
// Refer to "http://www.boost.org/doc/libs/1_58_0/
// doc/html/boost_asio/reference/basic_stream_socket/
// cancel/overload1.html" for details.
#ifdef BOOST_OS_WINDOWS
#define _WIN32_WINNT 0x0501

#if _WIN32_WINNT <= 0x0502 // Windows Server 2003 or earlier.
#define BOOST_ASIO_DISABLE_IOCP
#define BOOST_ASIO_ENABLE_CANCELIO
#endif
#endif

#include <boost/asio.hpp>
#include <iostream>
#include <thread>

int main()
{
	std::string raw_ip_address = "127.0.0.1";
	unsigned short port_num = 8001;

	try
	{
		boost::asio::io_service ios;
		boost::asio::ip::tcp::endpoint ep(boost::asio::ip::address::from_string(raw_ip_address), port_num);
		std::shared_ptr<boost::asio::ip::tcp::socket> sock(new boost::asio::ip::tcp::socket(ios, ep.protocol()));

		sock->async_connect(ep,
							[sock](const boost::system::error_code &ec)
							{
								// If asynchronous operation has been
								// cancelled or an error occured during
								// executon, ec contains corresponding
								// error code.
								if (ec.value() != 0)
								{
									if (ec == boost::asio::error::operation_aborted)
									{
										std::cout << "Operation cancelled!";
									}
									else
									{
										std::cout << "Error occured!"
												  << " Error code = " << ec.value()
												  << ". Message: " << ec.message();
									}
									return;
								}
								// At this point the socket is connected and
								// can be used for communication with
								// remote application.
							});

		// Starting a thread, which will be used
		// to call the callback when asynchronous
		// operation completes.
		std::thread worker_thread([&ios]()
								  {
			try {
				ios.run();
			}
			catch (boost::system::system_error &e) {
				std::cout << "Error occured!"
					<< " Error code = " << e.code()
					<< ". Message: " << e.what();
			} });

		// Emulating delay.
		std::cout << "Emulating delay\n";
		for (int i = 1; i < 6; ++i)
		{
			std::this_thread::sleep_for(std::chrono::seconds(1));
			std::cout << i << std::endl;
		}
		std::cout << "after Emulating delay\n";

		// Cancelling the initiated operation.
		sock->cancel();
		std::cout << "sock->cancel()\n";

		// Waiting for the worker thread to complete.
		worker_thread.join();
	}
	catch (boost::system::system_error &e)
	{
		std::cout << "Error occured! Error code = " << e.code()
				  << ". Message: " << e.what();

		return e.code().value();
	}

	return 0;
}
