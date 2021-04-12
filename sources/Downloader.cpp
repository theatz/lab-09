//
// Created by mrbgn on 4/5/21.
//

#include <Downloader.hpp>

Downloader::Downloader(size_t depth) : _depth(depth) {}

PageToParse Downloader::Download(UrlToDownload url) {
  try {
    //    std::lock_guard<std::mutex> lk(_)
    auto const host = DefineHost(url.url);

    auto const port = "80";                     // https - 443, http - 80
    auto const target = DefineTarget(url.url);  //
    int version = 10;
    // The io_context is required for all I/O
    boost::asio::io_context ioc;

    // These objects perform our I/O
    tcp::resolver resolver{ioc};
    tcp::socket socket{ioc};

    // Look up the domain name
    auto const results = resolver.resolve(host, port);

    // Make the connection on the IP address we get from a lookup
    boost::asio::connect(socket, results.begin(), results.end());

    // Set up an HTTP GET request message
    http::request<http::string_body> req{http::verb::get, target, version};
    req.set(http::field::host, host);
    req.set(http::field::user_agent, BOOST_BEAST_VERSION_STRING);

    // Send the HTTP request to the remote host
    http::write(socket, req);

    // This buffer is used for reading and must be persisted
    boost::beast::flat_buffer buffer;

    // Declare a container to hold the response
    http::response<http::dynamic_body> res;

    // Receive the HTTP response
    http::read(socket, buffer, res);

    // Write the message to standard out
    std::cout << boost::beast::buffers_to_string(res.body().data())
              << std::endl;

    // Gracefully close the socket
    boost::system::error_code ec;
    socket.shutdown(tcp::socket::shutdown_both, ec);

    // not_connected happens sometimes
    // so don't bother reporting it.
    //
    if (ec && ec != boost::system::errc::not_connected)
      throw boost::system::system_error{ec};

    // If we get here then the connection is closed gracefully
    //    return PageToParse {
    //      boost::beast::buffers_to_string(res.body().data()), url.depth
    //    }
  }
  //}
  catch (std::exception const& e) {
//    std::cerr << "Error: " << e.what() << ":" << url << std::endl;
//    return PageToParse{"error" url.depth};
  }
}

std::string Downloader::DefineTarget(std::string url) {
  size_t found = url.find("/");
  if (found != std::string::npos) return url.substr(url.find("/"));
  return "/";
}
std::string Downloader::DefineHost(std::string url) {
  size_t found = url.find("/");
  if (found != std::string::npos) return url.substr(0, url.find("/"));
  return url;
}
