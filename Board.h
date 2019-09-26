//
// Created by Daniela Vertiz on 4/17/19.
//

#ifndef MINESWEEPER_BOARD_H
#define MINESWEEPER_BOARD_H

#include "Tile.h"

class Board
{
private:
    Tile tiles[25][16];
    int flagsPlaced;
    int minesPlaced;


public:

    //CONSTRUCTOR
    Board(int test);

    //METHODS
    void Render(sf::RenderWindow& window);
    void RevealMines(sf::RenderWindow &window);
    void SetAdjacentTiles();
    int BoardClicked(bool left, int x, int y);
    int SetMines();
    int MineCounter();
};

#endif //MINESWEEPER_BOARD_H
