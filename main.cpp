#include <raylib.h>
#include "game.h"
#include "colors.h"
#include <iostream>

double lastUpdateTime = 0;

bool EventTriggered(double interval)
{
    double currentTime = GetTime();
    if (currentTime - lastUpdateTime >= interval)
    {
        lastUpdateTime = currentTime;
        return true;
    }
    return false;
}

int main () 
{
    InitWindow(500, 620, "Tetris C++"); // Janela com 500x620 e rodando a 60 quadros por segundo
    SetTargetFPS(60);

    Font font = LoadFontEx("Font/monogram.ttf", 64, 0, 0);

    Game game = Game();

    while (WindowShouldClose() == false) // Loop do jogo, fica aberto ate o usario fechar a janela
    {
        UpdateMusicStream(game.music);
        game.HandleInput(); // Entrada do teclado
        if (EventTriggered(0.2))
        {
            game.MoveBlockDown(); // Faz o bloco de mover para baixo "OBS: como esta marcado para 60fps, o bloco cai mt rapido. Sera feito um metedo para o bloco cair mais lento"
        }
        
        BeginDrawing();
        ClearBackground(azulEscuro);
        DrawTextEx(font, "Score", {365, 15}, 38, 2, WHITE);
        DrawTextEx(font, "Next", {370, 175}, 38, 2, WHITE);
        if (game.gameOver)
        {        
            DrawTextEx(font, "GAME OVRER", {320, 450}, 38, 2, WHITE);
        }
        DrawRectangleRounded({320,55,170,60}, 0.3, 6, azulClaro);

        char scoreText[10];
        sprintf(scoreText, "%d", game.score);
        Vector2 textSize = MeasureTextEx(font, scoreText, 38, 2);

        DrawTextEx(font, scoreText, {320 + (170 - textSize.x) / 2, 65}, 38, 2, WHITE);
        DrawRectangleRounded({320,215,170,180}, 0.3, 6, azulClaro);
        game.Draw(); // Desenho do tabuleiro e peças
        EndDrawing();
    }
    
    CloseWindow();
}