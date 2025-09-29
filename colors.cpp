#include "colors.h"

const Color cinzaEscuro = {26,31,40, 255};
const Color verde = {47,230,23, 255};
const Color vermelho = {232,18,18, 255};
const Color laranja = {226,116,17, 255};
const Color amarelo = {237,234,4, 255};
const Color roxo = {166,0,247, 255};
const Color ciano = {21,204,209, 255};
const Color azul = {13,64,216, 255};
const Color azulClaro = {59,85,162, 255};
const Color azulEscuro = {44,44,127, 255};

std::vector<Color> GetCellColors()
{
    return {cinzaEscuro, verde, vermelho, laranja, amarelo, roxo, ciano, azul};
}