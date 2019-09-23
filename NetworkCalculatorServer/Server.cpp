#include "Server.hpp"

void Server::do_accept()
{
    acceptor_.listen();
    acceptor_.async_accept(
        [this](boost::system::error_code ec, tcp::socket socket)
        {
            if (!ec)
            {
                std::make_shared<Session>(std::move(socket))->start();
            }

            do_accept();
        });
}

void Session::do_read()
{
    auto self(shared_from_this());

    socket_.async_read_some(boost::asio::buffer(data_, max_length),
        [this, self](boost::system::error_code ec, std::size_t length)
        {
            if (!ec)
            {
                str_data = process_response();
                do_write(length);
            }
        });
}

void Session::do_write(std::size_t length)
{
    auto self(shared_from_this());

    boost::asio::async_write(socket_, boost::asio::buffer(str_data),
        [this, self](boost::system::error_code ec, std::size_t length)
        {
            if (!ec)
            {
                if (str_data == "logout")
                {
                    stop();
                    return;
                }
                do_read();
            }
        });
}

void Session::start()
{
    command_dictionary["login"] = 1;
    command_dictionary["password"] = 2;
    command_dictionary["calculate"] = 3;
    command_dictionary["logout"] = 4;
    do_read();
}

void Session::stop()
{
    socket_.shutdown(boost::asio::ip::tcp::socket::shutdown_both);
    socket_.close();
}

string Session::process_response()
{
    string response = data_;
    vector<string> answers;
    boost::algorithm::split(answers, response, boost::algorithm::is_space());

    if (answers.size() != 2 && response != "logout")
        response = "Unable to process your command. Please enter it again.";

    short current_command { (answers.size() == 2)? command_dictionary[answers[0]] : command_dictionary[response] };

    switch (current_command)
    {
        case 1:
            if (progress == Progress_type::logout)
            {
                if (check_login(answers[1]))
                {
                    current_login = answers[1];
                    response = "Your login is '" + current_login + "'. Now enter your password: ";
                    progress = Progress_type::login;
                }
                else
                    response = "Wrong login. Try again: ";
            }
            else
            {
                response = "Wrong command. I know your login is " + current_login +
                    ((progress == Progress_type::login)? "Now you're supposed to write the password: " : "Now you're supposed to write an expression: ");
            }
            break;

        case 2:
            if (progress == Progress_type::login)
            {
                if (check_password(current_login, answers[1]))
                {
                    response = "Your password is correct!\nProceed with your expression (calculate <\"expr\">): ";
                    progress = Progress_type::password;
                }
                else
                    response = "Wrong password. Bruh (long and nasty burp follows). Try again: ";
            }
            else
            {
                response = (progress == Progress_type::password)? "You've already done this. You can enter your expression now." : "Now you're supposed to write an expression: ";
            }
            break;

        case 3:
            if (progress == Progress_type::password || progress == Progress_type::calculate)
            {
                token_stream.set_input(new istringstream{answers[1].substr(1, answers[1].size()-2)});
                calculator.set_token_stream(token_stream);
                if (progress == Progress_type::password)
                {
                    progress = Progress_type::calculate;
                }
                istringstream* iss = static_cast<istringstream*>(token_stream.ip);
// TODO (nikita#1#): сделать по-нормальному очищение строкового стрима
                iss->str(iss->str().substr(0, iss->str().find("\"")));

                response = "Result:\n" + calculator.calculate() + "Please enter another expression: ";
            }
            break;

        case 4:
            cerr << "logiut case ";
            if (progress != Progress_type::logout)
                response = "logout";

            break;

        default:
            response = "Unknown command. Try ";
            if (progress == Progress_type::logout)
                response += "(login <your_username>) ";
            if (progress == Progress_type::login)
                response += "(password <your_password>) ";
            if (progress == Progress_type::password)
                response += "(calculate <\"expr\">) ";
            if (progress == Progress_type::calculate)
                response += "(calculate <\"expr\">) or (logout) ";

            break;
    }
    return response;
}

bool Session::check_login(string login)
{
    return (login == "Stan")? "Ok" : "WHY NO";
}

bool Session::check_password(string login, string password)
{
    return password == "duh";
}
