//
// Created by mrbgn on 4/13/21.
//

#ifndef PRODUCER_CONSUMER_WRITER_HPP
#define PRODUCER_CONSUMER_WRITER_HPP

#include <string>
#include <iostream>
#include <fstream>

class Writer
{
 public:
  Writer(std::string fileName);
  void Write(std::string toFile);

 private:
  std::string _fileName;

};


#endif  // PRODUCER_CONSUMER_WRITER_HPP
