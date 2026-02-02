#include "Parser.hpp"
#include <iostream>
#include <string>


int main() {
  std::string input ;//= "23+5-20";
  std::getline(std::cin,input);
  Parser parser(input);
  std::cout<<parser.parse()<<std::endl;
  return 0;
}
