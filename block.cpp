#include "block.h"

Block::Block()
{
    cellSize = 30;
    rotationState = 0;
    colors = GetCellColors();
    rowOffset = 0;  // Deslocamento da peça em relação à linha inicial
    columnOffset = 0; // Deslocamento da peça em relação à coluna inicial
}

void Block::Draw(int offsetX, int offsetY)
{
    std::vector<Position> tiles = GetCellPositions();
    for (Position item : tiles) 
    {                   // Posiçãp X                            Posição Y                Largura         Altura
        DrawRectangle(item.column * cellSize + offsetX, item.row * cellSize + offsetY, cellSize - 1, cellSize -1, colors[id]);
    }
}

void Block::Move(int rows, int columns) // Alteraçã da posição dos blocos movendo linhas e colunas
{
    rowOffset += rows;
    columnOffset += columns;
}

std::vector<Position> Block::GetCellPositions()
{
    std::vector<Position> tiles = cells[rotationState]; // Pega as células correspondentes ao estado atual da rotação
    std::vector<Position> movedTiles;
    for (Position item: tiles) // Deslogamento em cada celula
    {
        Position newPos = Position(item.row + rowOffset, item.column + columnOffset); // Deslocamento da peça
        movedTiles.push_back(newPos);
    }
    return movedTiles;
}

void Block::Rotate() // Rotaciona o bloco em sentido horario
{
    rotationState ++;
    if (rotationState == (int)cells.size())
    {
        rotationState = 0;
    }
    
}

void Block::UndoRotation() // Desfaz a última rotação "So vai ser usado quando a rotação causaria uma colisão"
{
    rotationState --;
    if (rotationState == -1)
    {
        rotationState = cells.size() -1;
    }
}