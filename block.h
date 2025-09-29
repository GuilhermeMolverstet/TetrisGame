#pragma once
#include <vector>
#include <map>
#include "position.h"
#include "colors.h"

class Block
{
    public:
        Block();
        void Draw(int offsetX, int offsetY);
        void Move(int rows, int columns); // Movimento dos blocos
        std::vector<Position> GetCellPositions();
        void Rotate(); // Rotação dos blocos
        void UndoRotation();
        int id;
        std::map<int, std::vector<Position>> cells;
private:
    int cellSize;
    int rotationState;
    std::vector<Color> colors;
    int rowOffset;
    int columnOffset;
};
