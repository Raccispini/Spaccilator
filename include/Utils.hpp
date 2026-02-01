#include <iostream>
#include <cstdlib>

// Macro per gesione dei colori del terminale
#define DEBUG_RED "\033[31m"
#define DEBUG_YELLOW "\033[33m"
#define DEBUG_RESET "\033[0m"

#define TODO(message)\
    std::cout<< DEBUG_YELLOW<< "[TODO] "<< __FILE__ << ": " << __LINE__ \
    << " - " << message << DEBUG_RESET <<std::endl;

#define UNIMPLEMENTED(message)\
    do {\
        std::cerr<<DEBUG_RED<<"[FATAL] Funzione "<< message << " non ancora implementata at "<<__FILE__<<":"<<__LINE__<<std::endl;\
        std::abort();\
    }while(0)