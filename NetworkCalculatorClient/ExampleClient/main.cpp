#include <cstdlib>
#include <cstring>
#include <iostream>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

enum { max_length = 1024 };

int main(int argc, char* argv[])
{
  try
  {
    if (argc != 3)
    {
      std::cerr << "Usage: blocking_tcp_echo_client <host> <port>\n";
      return 1;
    }

    boost::asio::io_context io_context;

    tcp::socket s(io_context);
    tcp::resolver resolver(io_context);
    boost::asio::connect(s, resolver.resolve(argv[1], argv[2]));
    std::cout << "Enter your username (login <username>):\n";
    for (;;)
    {
        char request[max_length];
        memset(request, 0, max_length);
        std::cout << "-> ";
        std::cin.getline(request, max_length);
        size_t request_length = std::strlen(request);
        boost::asio::write(s, boost::asio::buffer(request, request_length));

        char reply[max_length];
        memset(reply, 0, max_length);
        size_t reply_length = s.read_some(boost::asio::buffer(reply));

        if (std::string{reply} == "quit")
        {
            std::cout << "You've successfully disconnected from the server! Client application shutting down...\n";
            s.close();
            break;
        }

        std::cout.write(reply, reply_length);
        std::cout << "\n";
    }
  }
  catch (std::exception& e)
  {
    std::cerr << "Exception: " << e.what() << "\n";
  }

  return 0;
}
