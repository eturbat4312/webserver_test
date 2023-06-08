#include <iostream>
#include <string>

#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <boost/asio/ip/tcp.hpp>

namespace http = boost::beast::http;
using tcp = boost::asio::ip::tcp;

// Perform an HTTP GET request
void performGetRequest(const std::string& host, const std::string& target) {
    try {
        boost::asio::io_context io;
        tcp::resolver resolver(io);
        tcp::socket socket(io);
        auto const results = resolver.resolve(host, "80");
        boost::asio::connect(socket, results.begin(), results.end());

        http::request<http::string_body> req{ http::verb::get, target, 11 };
        req.set(http::field::host, host);
        req.set(http::field::user_agent, BOOST_BEAST_VERSION_STRING);

        http::write(socket, req);

        boost::beast::flat_buffer buffer;
        http::response<http::dynamic_body> res;
        http::read(socket, buffer, res);

        std::cout << res << std::endl;
    }
    catch (std::exception const& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

// Perform an HTTP POST request
void performPostRequest(const std::string& host, const std::string& target, const std::string& data) {
    try {
        boost::asio::io_context io;
        tcp::resolver resolver(io);
        tcp::socket socket(io);
        auto const results = resolver.resolve(host, "80");
        boost::asio::connect(socket, results.begin(), results.end());

        http::request<http::string_body> req{ http::verb::post, target, 11 };
        req.set(http::field::host, host);
        req.set(http::field::user_agent, BOOST_BEAST_VERSION_STRING);
        req.set(http::field::content_type, "text/plain");
        req.body() = data;
        req.prepare_payload();

        http::write(socket, req);

        boost::beast::flat_buffer buffer;
        http::response<http::dynamic_body> res;
        http::read(socket, buffer, res);

        std::cout << res << std::endl;
    }
    catch (std::exception const& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

// Perform an HTTP DELETE request
void performDeleteRequest(const std::string& host, const std::string& target) {
    try {
        boost::asio::io_context io;
        tcp::resolver resolver(io);
        tcp::socket socket(io);
        auto const results = resolver.resolve(host, "80");
        boost::asio::connect(socket, results.begin(), results.end());

        http::request<http::string_body> req{ http::verb::delete_, target, 11 };
        req.set(http::field::host, host);
        req.set(http::field::user_agent, BOOST_BEAST_VERSION_STRING);

        http::write(socket, req);

        boost::beast::flat_buffer buffer;
        http::response<http::dynamic_body> res;
        http::read(socket, buffer, res);

        std::cout << res << std::endl;
    }
    catch (std::exception const& e) {
        std::cerr << "Error: " << e.what() << std::endl;
	}
}