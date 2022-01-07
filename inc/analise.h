#include <iostream>
#include "registro.h"

class Analise
{
public:
    Analise(){};
    ~Analise(){};
    //M B N(registros)
    //Passar registro pra arvore
    static void processAVP(int, int, Registro *);
    void processAB(int, int, Registro);
};