//
// Created by Daniela Vertiz on 4/17/19.
//

#ifndef MINESWEEPER_TILE_H
#define MINESWEEPER_TILE_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <map>
#include <math.h>
using namespace std;
using namespace sf;


extern map<string, sf::Texture> textureMap;
extern int gameState;
extern bool debugOn;


struct Tile
{
    static map<string, sf::Texture> textures;
    Sprite sprite;
    Vector2f coordinates;

    vector<Tile*> adjacentTiles;
    int numAdjacentMines;

    bool isConcealed;
    bool isFlagged;
    bool isMine;

    //CONSTRUCTOR
    Tile();
    Tile(sf::Vector2f& coordinates, bool isMine);

    void Reveal();
    void Render(sf::RenderWindow &window);
};

#endif //MINESWEEPER_TILE_H
