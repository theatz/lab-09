//
// Created by mrbgn on 4/6/21.
//

#include <gumbo.h>

#include <Downloader.hpp>
#include <Structs.hpp>
#include <atomic>
#include <fstream>
#include <iostream>

#ifndef PRODUCER_CONSUMER_PARSER_HPP
#define PRODUCER_CONSUMER_PARSER_HPP

class Parser {
 public:
  Parser(std::size_t depth);
  PageOutput Parse(PageToParse page);
  bool DefineLink(std::string link);
  void SearchForLinks(GumboNode* node, PageOutput& pageOutput);

 private:
  size_t _depth;
};

#endif  // PRODUCER_CONSUMER_PARSER_HPP
