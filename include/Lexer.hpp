#pragma once
#include <string>
#include <variant>
#include <vector>
#include <expected>

enum class TokenType {
  NUMBER,
  OPERATOR,
  INVALID,
  END_TOKEN
};

class Token {
  public:
    TokenType m_type;
    std::variant<std::string,double> m_value;
    Token(TokenType type,std::variant<std::string,double> value);
};

class Lexer {
  private:
    std::string_view source;
    size_t cursor = 0;

    bool isAtEnd() const; //controlla se la stringa e' finita
    char advance(); // legge il carattere attuale e avanza
    char peek() const;    // guarda il carattere attuale senza avanzare
    char peekNext() const; // guarda il carattere dopo quello attuale
    bool match(char expected); // avanza solo se il carattere e' quello cercato
    Token generate_token(std::string str);
    public:
    Lexer(std::string_view src);
    std::vector<Token> parse();
};