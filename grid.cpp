#include "grid.h"
#include <iostream>
#include "colors.h"

Grid::Grid()
{
    numRows = 20; // altura do tabuleiro - numero de linhas
    numCols = 10; // largura do tabuleiro - numeros de colunas
    cellSize = 30; // tamanho de cada célula em pixels
    Initialize();
    colors = GetCellColors();
}

void Grid::Initialize() // Ira inicializar a grade preenchendo todas as células com 0 (vazio)
{
    for (int row = 0; row < numRows; row++)
    {
        for (int column = 0; column < numCols; column++)
        {
            grid[row][column] = 0; // 0 representa o quadrado vazio
        }
    }
}

void Grid::print() // Um debug para imprimir a grade no console
{
    for (int row = 0; row < numRows; row++)
    {
        for (int column = 0; column < numCols; column++)
        {
            std::cout << grid[row][column] << " ";
        }
        std::cout << std::endl;
    }
}

void Grid::draw() // Ira desenhar a grade na tela (usando o Raylib)
{
    for (int row = 0; row < numRows; row++)
    {
        for (int column = 0; column < numCols; column++)
        {
            int cellValue = grid[row][column]; // valor da célula (0 = vazio, >0 = cor da peça)
            DrawRectangle(column * cellSize + 11, row * cellSize + 11, cellSize -1, cellSize -1, colors[cellValue]); // Desenha cada célula ajustada pelo tamanho e cor correspondente
        }
    }
}

bool Grid::IsCellOutside(int row, int column) // Vai verificar se a célula está fora dos limites do tabuleiro
{
    if (row >= 0 && row < numRows && column>= 0 && column<numCols)
    {
        return false;
    }
    return true;
}

bool Grid::IsCellEmpty(int row, int column) // Verifica se a célula está vazia
{
    if (grid[row][column] == 0)
    {
        return true;
    }
    return false;
}

int Grid::ClearFullRows() // Ira as linhas completas e retorna quantas foram removidas 
{
    int completed = 0; // Contador de linhas completas
    for (int row = numRows-1; row >= 0; row--) // Percorre da última linha para cima
    {
        if (IsRowFull(row))
        {
            ClearRow(row);
            completed++;
        }
        else if (completed > 0)
        {
            MoveRowDown(row, completed); // Move a linha atual para baixo
        }
    }
    return completed;
}

bool Grid::IsRowFull(int row) // Ira vericar se uma linha está cheia "sem espaços vazios"
{
    for (int column = 0; column < numCols; column++)
    {
        if (grid[row][column] == 0)
        {
            return false;
        }
    }
    return true;    
}

void Grid::ClearRow(int row) // Limpa uma linha, preenchenado com zero
{
    for (int column = 0; column < numCols; column ++)
    {
        grid[row][column] = 0;
    }
}

void Grid::MoveRowDown(int row, int numRows) // Move uma linha para baixo 
{
    for (int column = 0; column < numCols; column++)
    {
        grid[row + numRows][column] = grid[row][column]; //Copia valores para a nova posição
        grid[row][column] = 0;
    }
    
}
