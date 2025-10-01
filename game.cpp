#include "game.h"
#include <random>

Game::Game()
{
    grid = Grid();
    blocks = GetAllBlocks();
    currentBlock = GetRamdomBlock();
    nextBlock = GetRamdomBlock();
    gameOver = false;
    score = 0;
    InitAudioDevice(); // Configrações de audio
    music = LoadMusicStream("Sounds/music.mp3");
    PlayMusicStream(music);
    rotateSound = LoadSound("Sounds/rotate.mp3");
    clearSound = LoadSound("Sounds/clear.mp3");
}

Game::~Game() // Libera os recursos de audio ao fechar o jogo
{
    UnloadSound(rotateSound);
    UnloadSound(clearSound);
    UnloadMusicStream(music);
    CloseAudioDevice();
}

Block Game::GetRamdomBlock() // Retorna um bloco aleatorio da lista e o remove dela
{
    if (blocks.empty()) // Se acabou a lista, reinicia com todos blocos
    {
        blocks = GetAllBlocks();
    }
    int ramdomIndex = rand() % blocks.size();
    Block block = blocks[ramdomIndex];
    blocks.erase(blocks.begin() + ramdomIndex);
    return block;
}

std::vector<Block> Game::GetAllBlocks() // Cria uma lista com todos os blocos do game
{
    return {IBlock(), JBlock(), LBlock(), OBlock(), SBlock(), TBlock(), ZBlock()};
}

void Game::Draw()
{
    grid.draw();
    currentBlock.Draw(11, 11);
    switch (nextBlock.id) // Ajuste nas posições dos boloco 3 e 4
    {
    case 3:
        nextBlock.Draw(255,290);
        break;
    case 4:
        nextBlock.Draw(255,280);
        break;    
    default:
    nextBlock.Draw(270,270);
        break;
    }
}

void Game::HandleInput() // Entrada do teclado
{
    int keyPressed = GetKeyPressed();
    if (gameOver && keyPressed != 0)
    {
        gameOver = false;
        Reset();
    }
    switch (keyPressed) // Movimentos com as teclas no teclado 
    {
    case KEY_LEFT:
        MoveBlockLeft();
        break; 
    case KEY_RIGHT:
        MoveBlockRight();
        break;
    case KEY_DOWN:
        MoveBlockDown();
        UpdateScore(0,1); // Ao mover para baixo ganha 1 ponto
        break;
    case KEY_UP:
        RotateBlock();
        break;
    }
}

void Game:: MoveBlockLeft() //Move o bloco para a esquerta
{
    if(!gameOver)
    {
        currentBlock.Move(0, -1);
        if (IsBlockOutside() || BlockFits() == false)
        {
            currentBlock.Move(0, 1);
        }
    }
}

void Game:: MoveBlockRight() //Move o bloco para a direita
{
    if(!gameOver)
    {
        currentBlock.Move(0,1);
        if (IsBlockOutside() || BlockFits() == false)
        {
            currentBlock.Move(0, -1);
        }
    }
}

void Game:: MoveBlockDown() //Move o bloco para baixo
{
    if(!gameOver)
    {
        currentBlock.Move(1,0);
        if (IsBlockOutside() || BlockFits() == false)
        {
            currentBlock.Move(-1, 0);
            LockBlock(); // faz o bloco fixar parado quando chega ao final do tabuleiro
        }
    }
}

bool Game::IsBlockOutside() // Verifica se alguma célula do bloco saiu fora da grade
{
    std::vector<Position> titles = currentBlock.GetCellPositions();
    for (Position item: titles)
    {
        if (grid.IsCellOutside(item.row, item.column))
        {
            return true;
        }
    }
    return false;
}

void Game::RotateBlock() // Rotaciona o bloco
{
    if(!gameOver)
    {
        currentBlock.Rotate();
        if (IsBlockOutside() || BlockFits() == false) // Ira verificar se o bloco não esta rodando para fora da janela
        {
            currentBlock.UndoRotation();
        }
        else
        {
            PlaySound(rotateSound);
        }
    }
}

void Game::LockBlock() // Fixa o bloco no fundo do tabuleiro ou quando enconsta em outro
{
    std::vector<Position> tiles = currentBlock.GetCellPositions();
    for (Position item: tiles)
    {
        grid.grid[item.row][item.column] = currentBlock.id;
    }
    currentBlock = nextBlock;
    if (BlockFits() == false) // Se o bloco não couber 'GameOver'
    {
        gameOver = true;
    }
    
    nextBlock = GetRamdomBlock();
    int rowsCleared = grid.ClearFullRows(); // Limpa as linhas cheias e atualiza o score
    if (rowsCleared > 0)
    {
        PlaySound(clearSound);
        UpdateScore(rowsCleared, 0);
    }
}

bool Game::BlockFits() // Verifica se o bloco pode ocupar a posição atual
{
    std::vector<Position> tiles = currentBlock.GetCellPositions();
    for (Position item: tiles)
    {
        if (grid.IsCellEmpty(item.row, item.column) == false)
        {
            return false;
        }
    }
    return true;
}

void Game::Reset() // Reinicia o game
{
    grid.Initialize();
    blocks = GetAllBlocks();
    currentBlock = GetRamdomBlock();
    nextBlock = GetRamdomBlock();
    score = 0;
}

void Game::UpdateScore(int LinesCleared, int moveDownPoints) // Atualiza o score baseado nas linhas eliminadas ou movimentos para baixo
{
    switch (LinesCleared)
    {
    case 1:
        score += 50;
        break;
    case 2:
        score += 200;
        break;
    case 3:
        score += 400;
        break;
    case 4:
        score += 600;
        break;
    default:
        break;
    }
    score += moveDownPoints; // Pontos extras por mover para baixo manualmente
}
