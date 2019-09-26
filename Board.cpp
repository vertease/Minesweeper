//
// Created by Daniela Vertiz on 4/17/19.
//

#include "Board.h"


Board:: Board(int test){

    string lines[16];

    if (test != 0) {

        string fileName = "boards/testboard";

        if (test == 1){
            fileName.append("1.brd");
        }
        else if (test == 2){
            fileName.append("2.brd");
        }
        else if (test == 3){
            fileName.append("3.brd");
        }

        fstream file(fileName, ios_base::in);

        for (int i = 0; i < 16; i++){
            getline(file, lines[i], '\n');
        }
    }



    // CREATE BLANK TILE COORDINATES
    sf::Vector2f tileVector;

    // FILL IN 2D TILE CONTAINER
    for (int i = 0; i < 16; i++) {

        for (int j = 0; j < 25; j++) {

            // ONE BY ONE, CONSTRUCT A TILE @ CORRESPONDING COORDS

            if (test != 0 && lines[i][j] == '1'){
                tiles[j][i] = Tile(tileVector, true);
                minesPlaced++;
            }
            else{
                tiles[j][i] = Tile(tileVector, false);
            }

            // SHIFT THE X COORDS TO THE RIGHT
            tileVector.x += 32;
        }

        // SHIFT DOWN, THEN ALL THE WAY TO THE LEFT AGAIN
        tileVector.y += 32;
        tileVector.x -= 800;
    }


    // SET MINES
    if (test == 0){
        minesPlaced = SetMines();
    }

    // SET ADJACENT TILES
    SetAdjacentTiles();

    gameState = 0;
}



void Board:: Render(sf::RenderWindow& window){
    for (int i = 0; i < 25; i++){
        for (int j = 0; j < 16; j++){
            tiles[i][j].Render(window);
        }
    }
}



void Board:: RevealMines(sf::RenderWindow &window){

    // LOOP THRU ALL TILES
    // REVEAL THE MINES

    for (int i = 0; i < 25; i++){
        for (int j = 0; j < 16; j++){

            if(tiles[i][j].isMine){
                tiles[i][j].Reveal();
            }
        }
    }
}



void Board:: SetAdjacentTiles(){
    for (int i = 0; i < 16; i++) {

        for (int j = 0; j < 25; j++) {

            // TOP
            if (i != 0){
                tiles[j][i].adjacentTiles.push_back(&tiles[j][i-1]);

                if(tiles[j][i-1].isMine){
                    tiles[j][i].numAdjacentMines++;
                }
            }

            // BOTTOM
            if (i != 15){
                tiles[j][i].adjacentTiles.push_back(&tiles[j][i + 1]);

                if(tiles[j][i + 1].isMine){
                    tiles[j][i].numAdjacentMines++;
                }
            }

            // RIGHT
            if (j != 24){
                tiles[j][i].adjacentTiles.push_back(&tiles[j+1][i]);

                if(tiles[j+1][i].isMine){
                    tiles[j][i].numAdjacentMines++;
                }
            }

            // LEFT
            if (j != 0) {
                tiles[j][i].adjacentTiles.push_back(&tiles[j - 1][i]);

                if(tiles[j - 1][i].isMine){
                    tiles[j][i].numAdjacentMines++;
                }
            }

            // TOP RIGHT
            if (i!=0 && j!=24) {
                tiles[j][i].adjacentTiles.push_back(&tiles[j + 1][i - 1]);

                if(tiles[j + 1][i - 1].isMine){
                    tiles[j][i].numAdjacentMines++;
                }
            }

            // TOP LEFT
            if (i!=0 && j!=0) {
                tiles[j][i].adjacentTiles.push_back(&tiles[j - 1][i - 1]);

                if(tiles[j - 1][i - 1].isMine){
                    tiles[j][i].numAdjacentMines++;
                }
            }

            // BOTTOM RIGHT
            if (i!=15 && j!=24) {
                tiles[j][i].adjacentTiles.push_back(&tiles[j+1][i+1]);

                if(tiles[j+1][i+1].isMine){
                    tiles[j][i].numAdjacentMines++;
                }
            }

            // BOTTOM LEFT
            if (i!=15 && j!=0) {
                tiles[j][i].adjacentTiles.push_back(&tiles[j-1][i+1]);

                if(tiles[j-1][i+1].isMine){
                    tiles[j][i].numAdjacentMines++;
                }
            }
        }
    }
}



int Board:: BoardClicked(bool left, int x, int y){

    // ONLY CHANGE SHIT IF THE TILE HASN'T BEEN REVEALED
    if (tiles[x/32][y/32].isConcealed){



        // IF YOU CLICKED TO REVEAL
        if (left){


            // ONLY CHANGE THE TILE IF THERE ISN'T A FLAG ON IT
            if(!tiles[x/32][y/32].isFlagged){

                tiles[x/32][y/32].Reveal();

                // CHECK TO SEE IF YOU CLICKED ON A MINE
                if (tiles[x/32][y/32].isMine){

                    // GAME OVER!
                    return 1;
                }
                else {

                    int freeTiles = 400 - minesPlaced;

                    for (int i = 0; i < 25; i++){
                        for (int j = 0; j < 16; j++){
                            if(!tiles[i][j].isConcealed){
                                freeTiles--;
                            }
                        }
                    }

                    if(freeTiles == 0){
                        return 2;
                    }

                    // STILL PLAYING
                    return 0;
                }

            }
        }

            // IF YOU CLICKED TO FLAG
        else{

            if( tiles[x/32][y/32].isFlagged){
                tiles[x/32][y/32].isFlagged = false;
                flagsPlaced--;
            }
            else{
                tiles[x/32][y/32].isFlagged = true;
                flagsPlaced++;
            }
        }
    }

}



int Board:: SetMines(){
    srand(time(NULL));

    for (int minesPlaced = 0; minesPlaced < 50; minesPlaced++){
        int x = (rand() % 25);
        int y = (rand() % 16);

        if(tiles[x][y].isMine) {
            minesPlaced--;
        }

        tiles[x][y].isMine = true;
    }

    int mines = 0;

    for (int i = 0; i < 25; i++){
        for (int j = 0; j < 16; j++){

            if(tiles[i][j].isMine){
                mines++;
            }
        }
    }

    return mines;
}



int Board:: MineCounter(){
    return minesPlaced - flagsPlaced;
}