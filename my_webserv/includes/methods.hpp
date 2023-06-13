#pragma once

#include <iostream>
#include <string>

#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <boost/asio/ip/tcp.hpp>

void performGetRequest(const std::string& host, const std::string& target);
void performPostRequest(const std::string& host, const std::string& target, const std::string& data);
void performDeleteRequest(const std::string& host, const std::string& target);
