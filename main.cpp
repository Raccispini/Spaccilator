#include "Parser.hpp"
#include <iostream>
#include <string>


int main() {
  std::string input = "223+5 6 6-3";
  Parser parser(input);
  std::cout<<parser.parse()<<std::endl;
  return 0;
}
