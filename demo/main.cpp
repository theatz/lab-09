#include <gumbo.h>

#include <boost/program_options.hpp>
#include <fstream>
#include <iostream>
#include <string>

#include "Manager.hpp"

using namespace boost::program_options;

int main(int argc, char** argv) {
  std::string url;
  uint32_t depth;
  uint32_t network_threads;
  uint32_t parser_threads;
  std::string output;

  options_description desc("General options");
  std::string task_type;
  desc.add_options()
      ("url", value(&url), "url to download")
      ("depth", value(&depth), "recursion depth")
      ("network_threads", value(&network_threads), "network_threads")
      ("parser_threads", value(&parser_threads), "parser_threads")
      ("output", value(&output), "output file");
  variables_map vm;
  try {
    parsed_options parsed = command_line_parser(argc, argv).options(desc).allow_unregistered().run();
    store(parsed, vm);
    std::cout << vm["url"].as<std::string>() << std::endl << vm["depth"].as<uint32_t>() << std::endl << vm["network_threads"].as<uint32_t>() << std::endl << vm["parser_threads"].as<uint32_t>() << std::endl << vm["output"].as<std::string>() << std::endl;
  }
  catch(std::exception& ex) {
    std::cout << desc << std::endl;
  }
  /*
  uint32_t x = 4;
  uint32_t z = 4;
  uint32_t y = 4;

  Manager man(x, y, z);
  */
}
