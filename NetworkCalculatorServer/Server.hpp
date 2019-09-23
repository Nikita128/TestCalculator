#ifndef SERVER_HPP_INCLUDED
#define SERVER_HPP_INCLUDED

#include <cstdlib>
#include <string>
#include <iostream>
#include <memory>
#include <utility>
#include <boost/asio.hpp>
#include <boost/algorithm/string.hpp>
#include "Calculation.hpp"

using namespace std;
using boost::asio::ip::tcp;

enum class Progress_type { login = 1, password, calculate, logout };

class Server
{
public:
  Server(boost::asio::io_context& io_context, short port)
    : acceptor_(io_context, tcp::endpoint(tcp::v4(), port))
  {
    do_accept();
  }

private:
  void do_accept();

  tcp::acceptor acceptor_;
};

class Session
  : public std::enable_shared_from_this<Session>
{
public:
    Session(tcp::socket socket)
    : socket_(std::move(socket))
    {
    }

    void start();
    void stop();

private:
    void do_read();

    void do_write(std::size_t length);
    string process_response();
    bool check_login(string login);
    bool check_password(string login, string password);

    tcp::socket socket_;
    enum { max_length = 1024 };
    char data_[max_length];
    string str_data {};
    stringstream sstr;

    map<string, short> command_dictionary {};
    Progress_type progress { Progress_type::logout };
    string current_login {};
    Calculation::Token_stream token_stream{};
    Calculation::Calculator calculator{};
};

#endif // SERVER_HPP_INCLUDED
