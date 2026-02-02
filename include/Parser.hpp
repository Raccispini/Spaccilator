#include "Lexer.hpp"
class Parser {
    private:
        std::string_view source;
        std::vector<Token> tokens;
        int cursor = 0;
        
        bool match(TokenType type); //controlla se l'attuale token e' di quel tipo
        Token previous(); // restituisce il token precedente
        Token advance(); // manda avanti il cursore dei token
        
        double parseTerm();
        double parseExpression();
        double parseFactor();        

    public:
        Parser(std::string);
        double parse();
};