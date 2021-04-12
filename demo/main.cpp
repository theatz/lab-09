#include <gumbo.h>

#include <boost/program_options.hpp>
#include <fstream>
#include <iostream>
#include <string>

#include "Manager.hpp"

namespace po = boost::program_options;

int main(int argc, char** argv) {
  /*
  std::string url;
  std::size_t depth;
  std::size_t network_threads;
  std::size_t parser_threads;
  std::string output;

  po::options_description desc("General options");
  std::string task_type;
  desc.add_options()
      ("help,h", "Show help")
      ("url,u", po::value<std::string>(&url), "url to download")
      ("depth,d", po::value<std::size_t>(&depth), "recursion depth")
      ("network_threads,n", po::value<std::size_t>(&network_threads), "network_threads")
      ("parser_threads,p", po::value<std::size_t>(&parser_threads), "parser_threads")
      ("output,o", po::value<std::string>(&output), "outputFile");
  po::variables_map vm;
  try {
    po::parsed_options parsed = po::command_line_parser(argc, argv).options(desc).allow_unregistered().run();
    po::store(parsed, vm);
  }
  catch(std::exception& ex) {
    std::cout << desc << std::endl;
  }
   */
}
