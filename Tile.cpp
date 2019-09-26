//
// Created by Daniela Vertiz on 4/17/19.
//

#include "Tile.h"



Tile:: Tile(){}

Tile:: Tile(sf::Vector2f& coordinates, bool isMine){
    sprite.setPosition(coordinates);
    numAdjacentMines = 0;
    isConcealed = true;
    isFlagged = false;
    this->isMine = isMine;
    this->coordinates = coordinates;
}




void Tile:: Render(sf::RenderWindow &window){


    if (isConcealed){

        sprite.setTexture(textureMap["images/tile_hidden.png"]);
        window.draw(sprite);

        if (isFlagged || gameState == 2){
            sprite.setTexture(textureMap["images/flag.png"]);
            window.draw(sprite);
        }
        if (debugOn){
            if(isMine){
                sprite.setTexture(textureMap["images/mine.png"]);
                window.draw(sprite);
            }
        }
    }

    else {

        sprite.setTexture(textureMap["images/tile_revealed.png"]);
        window.draw(sprite);

        if (isMine){
            sprite.setTexture(textureMap["images/mine.png"]);
            window.draw(sprite);
        }
        else{
            switch (numAdjacentMines){

                default:{
                    break;
                }
                case 1:{
                    sprite.setTexture(textureMap["images/number_1.png"]);
                    window.draw(sprite);
                    break;
                }

                case 2:{
                    sprite.setTexture(textureMap["images/number_2.png"]);
                    window.draw(sprite);
                    break;
                }

                case 3:{
                    sprite.setTexture(textureMap["images/number_3.png"]);
                    window.draw(sprite);
                    break;
                }

                case 4:{
                    sprite.setTexture(textureMap["images/number_4.png"]);
                    window.draw(sprite);
                    break;
                }

                case 5:{
                    sprite.setTexture(textureMap["images/number_5.png"]);
                    window.draw(sprite);
                    break;
                }

                case 6:{
                    sprite.setTexture(textureMap["images/number_6.png"]);
                    window.draw(sprite);
                    break;
                }

                case 7:{
                    sprite.setTexture(textureMap["images/number_7.png"]);
                    window.draw(sprite);
                    break;
                }

                case 8:{
                    sprite.setTexture(textureMap["images/number_8.png"]);
                    window.draw(sprite);
                    break;
                }
            }
        }
    }
}




void Tile:: Reveal(){

    // ONLY DO SHIT IF IT'S HIDDEN
    if(isConcealed) {

        // THIS TILE'S NO LONGER HIDDEN
        isConcealed = false;

        // IF THERE ARE NO MINES AROUND
        if(numAdjacentMines == 0){

            // AND IF IT'S NOT A MINE ITSELF
            if(!isMine) {

                // CASCADE REVEAL ALL SURROUNDING TILES
                for (Tile *tile: adjacentTiles) {
                    if(!tile->isFlagged){
                        tile->Reveal();
                    }
                }
            }
        }
    }
}