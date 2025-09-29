# TetrisGame

Bem-vindo ao repositório **TetrisGame**! Este projeto é uma implementação do clássico jogo Tetris, desenvolvida para fins de aprendizado, aprimoramento de habilidades em programação na linguagem C++.

## Sobre o Projeto

O TetrisGame tem como objetivo recriar o famoso jogo de quebra-cabeças, onde peças de diferentes formatos caem em um tabuleiro e devem ser organizadas para formar linhas completas, que então são eliminadas. O jogo termina quando não há mais espaço para novas peças.

## Funcionalidades

- Peças tetromino com rotação
- Sistema de pontuação baseado em linhas eliminadas
- Detecção de fim de jogo
- Interface gráfica simples e intuitiva
- Controle de movimentos (esquerda, direita, baixo, girar)
- Velocidade progressiva
  
## Pré-requisitos para rodar o jogo
Compilador C++ (g++ ou similar)
Biblioteca Raylib instalada em seu sistema (usada para gráficos e áudio)
Possuir as dependências do projeto (fontes, áudio, etc.)

## Passos para Execução

Clone o repositório:
- git clone https://github.com/GuilhermeMolverstet/TetrisGame.git
- cd TetrisGame

## Compile o projeto:

- g++ main.cpp game.cpp block.cpp grid.cpp blocks.cpp -o TetrisGame -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
Certifique-se que os arquivos do Raylib estejam em seu PATH ou inclua o caminho com -I e -L se necessário.

## Para executar o jogo:

./TetrisGame ou na tecla F5
