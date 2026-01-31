#include "Parser.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <variant>


int main() {
  std::string input = "223+5 6 6-3";
  //std::getline(std::cin, input);
  Lexer lexer(input);
  std::vector<Token> tokens = lexer.parse();
  for (Token t : tokens){
    std::visit([](auto&& arg){
      std::cout << arg <<std::endl;
    },t.m_value);
  }
  return 0;
}
