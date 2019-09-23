#include <cstdlib>
#include <iostream>
#include <thread>
#include <utility>
#include <boost/asio.hpp>
#include <chrono>
#include <ctime>
#include <boost/algorithm/string.hpp>
#include <string>
#include "Server.hpp"

using namespace std;
using boost::asio::ip::tcp;

int main(int argc, char* argv[])
{
  try
  {
    if (argc != 2)
    {
      std::cerr << "Usage: async_tcp_echo_server <port>\n";
      return 1;
    }

    boost::asio::io_context io_context;

    Server s(io_context, std::atoi(argv[1]));

    io_context.run();
  }
  catch (std::exception& e)
  {
    std::cerr << "Exception: " << e.what() << "\n";
  }

  return 0;
}

// BLOCKING SYNC SERVER

//const int MAX_LENGTH = 1024;
//
//enum class Progress_type { login = 1, password, calculate, logout };
//
//bool check_login(string login)
//{
//    return (login == "Stan")? "Ok" : "WHY NO";
//}
//
//bool check_password(string login, string password)
//{
//    return password == "duh";
//}
//
//void session(tcp::socket sock)
//{
//    map<string, short> command_dictionary {};
//    command_dictionary["login"] = 1;
//    command_dictionary["password"] = 2;
//    command_dictionary["calculate"] = 3;
//    command_dictionary["logout"] = 4;
//
//    string current_login {};
//
//    Progress_type progress { Progress_type::logout };
//
//    try
//    {
//        for (;;)
//        {
//            char data[MAX_LENGTH];
//            string s {""};
//            boost::system::error_code error;
//            memset(data, 0, static_cast<size_t>(MAX_LENGTH));
//            //size_t length =
//            sock.read_some(boost::asio::buffer(data), error);
//            //boost::asio::read(sock, boost::asio::buffer(s, 10), error);
//            s = data;
//            if (error == boost::asio::error::eof)
//            {
//                cout << "Connection closed." << endl;
//                break;
//            }
//            else if (error)
//                throw boost::system::system_error(error);
//
//            string my_message {};
//
//            vector<string> answers;
//            boost::algorithm::split(answers, s, boost::algorithm::is_space());
//
//            if (answers.size() != 2)
//                my_message = "Unable to process your command. Please enter it again.";
//            else
//                my_message = "Write something else";
//
//            short current_command { command_dictionary[answers[0]] };
//
//            switch (current_command)
//            {
//                case 1:
//                    if (progress == Progress_type::logout)
//                    {
//                        if (check_login(answers[1]))
//                        {
//                            current_login = answers[1];
//                            my_message = "Your login is '" + current_login + "'. Now enter your password: ";
//                            progress = Progress_type::login;
//                        }
//                        else
//                            my_message = "Wrong login. Try again: ";
//                    }
//                    else
//                    {
//                        my_message = "Wrong command. I know your login is " + current_login +
//                            ((progress == Progress_type::login)? "Now you're supposed to write the password: " : "Now you're supposed to write an expression: ");
//                    }
//                    break;
//
//                case 2:
//                    if (progress == Progress_type::login)
//                    {
//                        if (check_password(current_login, answers[1]))
//                        {
//                            my_message = "Your password is correct! Proceed with your expression: ";
//                            progress = Progress_type::password;
//                        }
//                        else
//                            my_message = "Wrong password. Bruh (long and nasty burp follows). Try again: ";
//                    }
//                    else
//                    {
//                        my_message = (progress == Progress_type::password)? "You've already done this. You can enter your expression now." : "Now you're supposed to write an expression: ";
//                    }
//                    break;
//            }
//
//            boost::asio::write(sock, boost::asio::buffer(my_message), error);
//            cout << "PLEASE" << endl;
//        }
//    }
//    catch (std::exception& e)
//    {
//        std::cerr << "Exception in thread: " << e.what() << "\n";
//    }
//}
//
//void server(boost::asio::io_context& io_context, unsigned short port)
//{
//    tcp::acceptor a(io_context, tcp::endpoint(tcp::v4(), port));
//    a.listen();
//    for (;;)
//    {
//        cout << "woah";
//        std::thread(session, a.accept()).detach();
//    }
//}
//
//int main(int argc, char* argv[])
//{
//    try
//    {
//        if (argc != 2)
//        {
//            std::cerr << "Usage: blocking_tcp_echo_server <port>\n";
//            return 1;
//        }
//
//        boost::asio::io_context io_context;
//
//        server(io_context, std::atoi(argv[1]));
//    }
//    catch (std::exception& e)
//    {
//        std::cerr << "Exception: " << e.what() << "\n";
//    }
//
//    return 0;
//}
