//
// Created by mrbgn on 4/13/21.
//

#include "Writer.hpp"

Writer::Writer(std::string fileName) : _fileName(fileName){}

void Writer::Write(std::string toFile) {
  std::ofstream out;
  out.open(_fileName, std::ios::app);
  if (out.is_open())
  {
    out << toFile << std::endl;
  }
  out.close();
}
