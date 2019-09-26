#include <SFML/Graphics.hpp>
#include "Board.h"







// MAKE GLOBAL MAP OF TEXTURES
map<string, sf::Texture> textureMap;

// DEBUG MODE
bool debugOn;

// GAME STATE
//      gameState 0 = playing
//      gameState 1 = lost
//      gameState 2 = won
int gameState;







int main() {




    // CREATE VECTOR OF TEXTURE FILES
    vector<string> images = {"images/debug.png",    "images/digits.png",    "images/face_happy.png",
                             "images/face_lose.png", "images/face_win.png",  "images/flag.png",
                             "images/mine.png",      "images/number_1.png",  "images/number_2.png",
                             "images/number_3.png",  "images/number_4.png",  "images/number_5.png",
                             "images/number_6.png",  "images/number_7.png",  "images/number_8.png",
                             "images/test_1.png",    "images/test_2.png",    "images/Test_3.png",
                             "images/tile_hidden.png", "images/tile_revealed.png"};

    // PASS THEM IN AND LOAD THE MAP
    sf::Texture current;
    for (unsigned int i = 0; i < images.size(); i++){
        current.loadFromFile(images[i]);
        textureMap[images[i]] = current;
    }






    // COUNTER BUTTON
    sf::Sprite digits;
    digits.setTexture(textureMap["images/digits.png"]);

    // RESET BUTTON
    sf::Sprite reset;
    reset.setTexture(textureMap["images/face_happy.png"]);
    reset.setPosition(Vector2f(400 - 32, 16 * 32));

    // WIN BUTTON
    sf::Sprite win;
    win.setTexture(textureMap["images/face_win.png"]);
    win.setPosition(Vector2f(400 - 32, 16 * 32));

    // LOSE BUTTON
    sf::Sprite lose;
    lose.setTexture(textureMap["images/face_lose.png"]);
    lose.setPosition(Vector2f(400 - 32, 16 * 32));

    // DEBUG BUTTON
    sf::Sprite debug;
    debug.setTexture(textureMap["images/debug.png"]);
    debug.setPosition(Vector2f(400 + (3*32), 16 * 32));

    // TEST 1 BUTTON
    sf::Sprite test1;
    test1.setTexture(textureMap["images/test_1.png"]);
    test1.setPosition(Vector2f(400 + (5*32), 16 * 32));

    // TEST 2 BUTTON
    sf::Sprite test2;
    test2.setTexture(textureMap["images/test_2.png"]);
    test2.setPosition(Vector2f(400 + (7*32), 16 * 32));

    // TEST 3 BUTTON
    sf::Sprite test3;
    test3.setTexture(textureMap["images/Test_3.png"]);
    test3.setPosition(Vector2f(400 + (9*32), 16 * 32));

    // BOARD
    Board *board = new Board(0);

    // DEBUG MODE
    debugOn = false;

    int counter = 0;







    sf::RenderWindow window(sf::VideoMode(800,600),"Minesweeper");

    while(window.isOpen()) {



        sf::Event event;

        while (window.pollEvent(event)) {



            switch (event.type) {



                default: {
                    break;
                }



                case sf::Event::Closed: {
                    window.close();
                    break;
                }



                case sf::Event::MouseButtonPressed: {


                    // RECORD COORDINATES
                    int x = event.mouseButton.x;
                    int y = event.mouseButton.y;


                    // RESET CLICKED
                    if ((x > (400 - 32)) && (x < (400 + 32)) && (y > (600 - (32 * 3))) && (y < (600 - 32))) {
                        board = new Board(0);
                    }


                    // DEBUG CLICKED
                    if ((x > (400 + (3 * 32))) && (x < (400 + (5 * 32))) && (y > (600 - (32 * 3))) && (y < (600 - 32))) {
                        debugOn = !debugOn;
                    }

                    // TEST 1 CLICKED
                    if ((x > (400 + (5 * 32))) && (x < (400 + (7 * 32))) && (y > (600 - (32 * 3))) && (y < (600 - 32))) {
                        board = new Board(1);
                    }

                    // TEST 2 CLICKED
                    if ((x > (400 + (7 * 32))) && (x < (400 + (9 * 32))) && (y > (600 - (32 * 3))) && (y < (600 - 32))) {
                        board = new Board(2);
                    }

                    // TEST 3 CLICKED
                    if ((x > (400 + (9 * 32))) && (x < (400 + (11 * 32))) && (y > (600 - (32 * 3))) && (y < (600 - 32))) {
                        board = new Board(3);
                    }

                    if (gameState == 0) {

                        // TILE CLICKED
                        if (x > 0 && x < 800 && y > 0 && y < (600 - (32 * 3))) {

                            // CLICK TO REVEAL
                            if (event.mouseButton.button == sf::Mouse::Left) {
                                gameState = board->BoardClicked(true, x, y);
                            }
                            // CLICK TO FLAG
                            if (event.mouseButton.button == sf::Mouse::Right) {
                                gameState = board->BoardClicked(false, x, y);
                            }
                        }
                    }


                    break;
                }
            }
        }


        // DRAW BOARD
        board->Render(window);



        // DRAW COUNTER
        counter = board->MineCounter();

//        int ones = abs(counter%10);
//        digits.setTextureRect(sf::IntRect(ones*21, 0, 21, 32));
//        digits.setPosition(Vector2f(42, 16 * 32));
//        window.draw(digits);
//
//        int tens = abs(counter/10);
//        digits.setTextureRect(sf::IntRect(tens*21, 0, 21, 32));
//        digits.setPosition(Vector2f(21, 16 * 32));
//        window.draw(digits);
//
//        if(counter < 0){
//            digits.setTextureRect(sf::IntRect(210, 0, 21, 32));
//            digits.setPosition(Vector2f(0, 16 * 32));
//            window.draw(digits);
//        }
//        else{
//            digits.setTextureRect(sf::IntRect(0, 0, 21, 32));
//            digits.setPosition(Vector2f(0, 16 * 32));
//            window.draw(digits);
//        }

        if(counter < 0){
            digits.setTextureRect(sf::IntRect(210, 0, 21, 32));
            digits.setPosition(Vector2f(0, 16 * 32));
            window.draw(digits);
        }

        int hundreds = counter/100;
        digits.setTextureRect(sf::IntRect(hundreds*21, 0, 21, 32));
        digits.setPosition(Vector2f(21, 16 * 32));
        window.draw(digits);
        counter -= hundreds*100;

        int tens = counter/10;
        digits.setTextureRect(sf::IntRect(tens*21, 0, 21, 32));
        digits.setPosition(Vector2f(42, 16 * 32));
        window.draw(digits);
        counter -= tens*10;

        int ones = counter/1;
        digits.setTextureRect(sf::IntRect(counter*21, 0, 21, 32));
        digits.setPosition(Vector2f(42, 16 * 32));
        window.draw(digits);



        // DRAW SMILEY
        if (gameState == 0){
            window.draw(reset);
        }
        else if (gameState == 1){
            window.draw(lose);
            board->RevealMines(window);
        }
        else if (gameState == 2){
            window.draw(win);
        }

        // DRAW THE REST
        window.draw(debug);
        window.draw(test1);
        window.draw(test2);
        window.draw(test3);


        window.display();

    }

    return 0;

}