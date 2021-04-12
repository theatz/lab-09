//
// Created by mrbgn on 4/5/21.
//

#include <Structs.hpp>
#include <atomic>
#include <boost/asio/connect.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <fstream>
#include <iostream>
#include <queue>

using tcp = boost::asio::ip::tcp;     // from <boost/asio/ip/tcp.hpp>
namespace http = boost::beast::http;  // from <boost/beast/http.hpp>

#ifndef PRODUCER_CONSUMER_DOWNLOADER_HPP
#define PRODUCER_CONSUMER_DOWNLOADER_HPP

class Downloader {
 public:
  Downloader(size_t depth);
  PageToParse Download(UrlToDownload url);
  std::string DefineTarget(std::string url);
  std::string DefineHost(std::string url);

 private:
  size_t _depth;
};

#endif  // PRODUCER_CONSUMER_DOWNLOADER_HPP
