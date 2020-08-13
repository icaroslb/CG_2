#include "algebra_vetor.h"

int main () {

    Vec_2f vetor(1.0f, 1.0f);

    std::cout << produto_escalar( vetor, vetor ) << std::endl;
    std::cout << produto_vetorial( vetor, vetor ) << std::endl;
    std::cout << norma_quadrada( vetor ) << std::endl;
    std::cout << norma( vetor ) << std::endl;

    return 0;
    
}