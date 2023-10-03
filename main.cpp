#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
using namespace std;
#include "Random.h"

void chainReveal (int x, int width, int what[], sf::Sprite img, sf::RenderWindow& win) {
    what[x] = 4;
    if (what[x - width] == 2) {
        what[x - width] = 4;
        chainReveal((x - width), width, what, img, win);
    }
    if (what[x + width] == 2) {
        what[x + width] = 4;
        chainReveal((x + width), width, what, img, win);
    }
    if (what[x - 1] == 2) {
        what[x - 1] = 4;
        chainReveal((x - 1), width, what, img, win);
    }
    if (what[x + 1] == 2) {
        what[x + 1] = 4;
        chainReveal((x + 1), width, what, img, win);
    }
}

void digitalFunc(string val, int width, sf::Sprite digits, int heightPos, sf::RenderWindow& gameWindow) {
    if (val == "0") {
        digits.setPosition(width, heightPos);
        digits.setTextureRect(sf::IntRect(0, 0, 21, 32));
        gameWindow.draw(digits);
    }
    if (val == "1") {
        digits.setPosition(width, heightPos);
        digits.setTextureRect(sf::IntRect(21, 0, 21, 32));
        gameWindow.draw(digits);
    }
    if (val == "2") {
        digits.setPosition(width, heightPos);
        digits.setTextureRect(sf::IntRect(42, 0, 21, 32));
        gameWindow.draw(digits);
    }
    if (val == "3") {
        digits.setPosition(width, heightPos);
        digits.setTextureRect(sf::IntRect(63, 0, 21, 32));
        gameWindow.draw(digits);
    }
    if (val == "4") {
        digits.setPosition(width, heightPos);
        digits.setTextureRect(sf::IntRect(84, 0, 21, 32));
        gameWindow.draw(digits);
    }
    if (val == "5") {
        digits.setPosition(width, heightPos);
        digits.setTextureRect(sf::IntRect(105, 0, 21, 32));
        gameWindow.draw(digits);
    }
    if (val == "6") {
        digits.setPosition(width, heightPos);
        digits.setTextureRect(sf::IntRect(126, 0, 21, 32));
        gameWindow.draw(digits);
    }
    if (val == "7") {
        digits.setPosition(width, heightPos);
        digits.setTextureRect(sf::IntRect(147, 0, 21, 32));
        gameWindow.draw(digits);
    }
    if (val == "8") {
        digits.setPosition(width, heightPos);
        digits.setTextureRect(sf::IntRect(186, 0, 21, 32));
        gameWindow.draw(digits);
    }
    if (val == "9") {
        digits.setPosition(width, heightPos);
        digits.setTextureRect(sf::IntRect(189, 0, 21, 32));
        gameWindow.draw(digits);
    }
}

int main() {
    int count = 1;
    int mouseCount = 1;

    int width;
    int height;
    int mines;

    ifstream currentFile("boards/config.cfg");
    if (currentFile.is_open()) {
        currentFile >> width;
        currentFile >> height;
        currentFile >> mines;
    }
    currentFile.close();

    int mineArray [mines][2]; //location of mines
    int totalTiles = height * width;
    int whatArray[totalTiles]; // 0 = number, 1 = mine, 2 = empty tile
    int numArray[totalTiles]; // track number(adjacent to bomb) in ever tile , bomb or empty tile = 0
    vector<int> whatVector; //stores ever left click position
    vector<int> chainTile;
    vector<vector<int>> hiddenVec;
    int flagArray[totalTiles];
    int flagPos[totalTiles][2];
    int whatFlag[totalTiles];
    int stringNum = mines;
    int winCount = 1;
    int bcon = 0;
    vector<string> board;
    vector<int> testb;
    int anotherVar = 0;

    int hchange;
    int wchange;
    int numin;
    int ifmine = 0;

    sf::Texture hiddenTile;
    hiddenTile.loadFromFile("images/tile_hidden.png");
    sf::Sprite hiddenT(hiddenTile);

    sf::Texture revealTile;
    revealTile.loadFromFile("images/tile_revealed.png");
    sf::Sprite revealT(revealTile);

    sf::Texture smileNorm;
    smileNorm.loadFromFile("images/face_happy.png");
    sf::Sprite smileN(smileNorm);

    sf::Texture debugBomb;
    debugBomb.loadFromFile("images/debug.png");
    sf::Sprite debugB(debugBomb);

    sf::Texture testOne;
    testOne.loadFromFile("images/test_1.png");
    sf::Sprite test1(testOne);

    sf::Texture testTwo;
    testTwo.loadFromFile("images/test_2.png");
    sf::Sprite test2(testTwo);

    sf::Texture testThree;
    testThree.loadFromFile("images/test_3.png");
    sf::Sprite test3(testThree);

    sf::Texture flagPic;
    flagPic.loadFromFile("images/flag.png");
    sf::Sprite flag(flagPic);

    sf::Texture minePic;
    minePic.loadFromFile("images/mine.png");
    sf::Sprite mine(minePic);

    sf::Texture onePic;
    onePic.loadFromFile("images/number_1.png");
    sf::Sprite one(onePic);

    sf::Texture twoPic;
    twoPic.loadFromFile("images/number_2.png");
    sf::Sprite two(twoPic);

    sf::Texture threePic;
    threePic.loadFromFile("images/number_3.png");
    sf::Sprite three(threePic);

    sf::Texture fourPic;
    fourPic.loadFromFile("images/number_4.png");
    sf::Sprite four(fourPic);

    sf::Texture fivePic;
    fivePic.loadFromFile("images/number_5.png");
    sf::Sprite five(fivePic);

    sf::Texture sixPic;
    sixPic.loadFromFile("images/number_6.png");
    sf::Sprite six(sixPic);

    sf::Texture sevenPic;
    sevenPic.loadFromFile("images/number_7.png");
    sf::Sprite seven(sevenPic);

    sf::Texture eightPic;
    eightPic.loadFromFile("images/number_8.png");
    sf::Sprite eight(eightPic);

    sf::Texture smileLose;
    smileLose.loadFromFile("images/face_lose.png");
    sf::Sprite smileL(smileLose);

    sf::Texture digitsTot;
    digitsTot.loadFromFile("images/digits.png");
    sf::Sprite digits(digitsTot);

    sf::Texture smileWin;
    smileWin.loadFromFile("images/face_win.png");
    sf::Sprite smileW(smileWin);


    sf::RenderWindow gameWindow(sf::VideoMode((width * 32), ((height * 32) + 100)), "Minesweeper");

    sf::Event event;
    while (gameWindow.isOpen()) {
        while (gameWindow.pollEvent(event)) {
            if (event.type == sf::Event::EventType::Closed) {
                gameWindow.close();
            }
        }

        gameWindow.clear();

        int heightPos;
        int widthPos;
        int loc;

        //Executes once placing bombs and numbers values and empty tiles
        if (count == 1) {
            //drawing Hidden Tiles
            stringNum = mines;
            heightPos = 0;
            widthPos = 0;
            vector<int> v;
            for (int i = 0 ; i < height ; i++) {
                for (int j = 0 ; j < width ; j++) {
                    v.push_back(widthPos);
                    v.push_back(heightPos);
                    hiddenVec.push_back(v);
                    v.clear();
                    widthPos = widthPos + 32;
                }
                widthPos = 0;
                heightPos = heightPos + 32;
            }
            //intializing all values to 0
            for (int i = 0 ; i < totalTiles ; i++) {
                whatArray[i] = 0;
            }
            for (int i = 0 ; i < totalTiles ; i++) {
                flagArray[i] = 0;
            }
            for (int i = 0 ; i < totalTiles ; i++) {
                whatFlag[i] = 0;
            }
            for (int i = 0 ; i < totalTiles ; i++) {
                flagPos[i][0] = 0;
                flagPos[i][1] = 0;
            }
            //Bombs
            for (int i = 0 ; i < mines ; i++) {
                int randomX = Random::IntRan(0, width * 32);
                int randomY = Random::IntRan(0, height * 32);
                randomX = (randomX / 32) * 32;
                randomY = (randomY / 32) * 32;
                mineArray[i][0] = randomX;
                mineArray[i][1] = randomY;
                int numTile = (randomX / 32) + ((randomY / 32) * width);
                if (whatArray[numTile] == 1) {
                    i = i - 1;
                }
                else whatArray[numTile] = 1;
            }
            /*
            if (ifmine != 1) {

            }
            else {
                for (int i = 0 ; i < wchange * hchange ; i++) {
                    whatArray[i] = testb[i];
                    mineArray[i][0] = (i % wchange) * 32;
                    mineArray[i][1] = (i / wchange) * 32;
                }
                totalTiles = wchange * hchange;
            } */
            //numbers
            for (int i = 0 ; i < totalTiles ; i++) {
                int flagnum = 0;
                if (whatArray[i] == 0) { //lookinbg at all values with no bomb
                    if (whatArray[i - width - 1] == 1) flagnum++;
                    if (whatArray[i - width] == 1) flagnum++;
                    if (whatArray[i - width + 1] == 1) flagnum++;
                    if (whatArray[i - 1] == 1) flagnum++;
                    if (whatArray[i + 1] == 1) flagnum++;
                    if (whatArray[i + width - 1] == 1) flagnum++;
                    if (whatArray[i + width] == 1) flagnum++;
                    if (whatArray[i + width + 1] == 1) flagnum++;
                    if ((i + 1) % width == 0) {
                        flagnum = 0;
                        if (whatArray[i - width - 1] == 1) flagnum++;
                        if (whatArray[i - width] == 1) flagnum++;
                        if (whatArray[i - 1] == 1) flagnum++;
                        if (whatArray[i + width - 1] == 1) flagnum++;
                        if (whatArray[i + width] == 1) flagnum++;
                    }
                    if ((i + 1) % width == 1) {
                        flagnum = 0;
                        if (whatArray[i - width] == 1) flagnum++;
                        if (whatArray[i - width + 1] == 1) flagnum++;
                        if (whatArray[i + 1] == 1) flagnum++;
                        if (whatArray[i + width] == 1) flagnum++;
                        if (whatArray[i + width + 1] == 1) flagnum++;
                    }
                }
                else {
                    flagnum = 0;
                }
                numArray[i] = flagnum; //number value for each tile
            }
            //each empty tile = 2
            for (int i = 0 ; i < totalTiles ; i++) {
                if (numArray[i] == 0 & whatArray[i] == 0) {
                    whatArray[i] = 2;
                }
            }
            count = 2;
        }

        //drawing face and buttons
        float smiley = ((width / 2.0f) - 1) * 32.0f;
        smileN.setPosition(sf::Vector2f(smiley, heightPos));
        gameWindow.draw(smileN);
        debugB.setPosition(sf::Vector2f(smiley + (4 * 32), heightPos));
        gameWindow.draw(debugB);
        test1.setPosition(sf::Vector2f(smiley + (6 * 32), heightPos));
        gameWindow.draw(test1);
        test2.setPosition(sf::Vector2f(smiley + (8 * 32), heightPos));
        gameWindow.draw(test2);
        test3.setPosition(sf::Vector2f(smiley + (10 * 32), heightPos));
        gameWindow.draw(test3);

        //find location of left mouse click
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            int xCoord;
            int yCoord;
            int hiddenLoc;
            bool alr = false;
            auto mousePos = sf::Mouse::getPosition(gameWindow);
            if (mouseCount == 1) {
                if (mousePos.y < (height * 32) && mousePos.y > 0 && mousePos.x < (width * 32) && mousePos.x > 0) {
                    xCoord = mousePos.x / 32;
                    yCoord = mousePos.y / 32;
                    hiddenLoc = (yCoord * width) + (xCoord);
                    for (int i = 0; i < whatVector.size(); i++) {
                        if (whatVector[i] == hiddenLoc) alr = true;
                    }
                    if (alr == false) whatVector.push_back(hiddenLoc); //stores tile number position of ev ery left click
                }
                if (mousePos.y > heightPos && mousePos.y < (heightPos + 64) && mousePos.x > (smiley + 128) && mousePos.x < (smiley + 192) ) {
                    int once = 0;
                    for (int i = 0 ; i < totalTiles ; i++) {
                        if (whatArray[i] == 1 && once == 0) {
                            whatVector.push_back(i);
                            once++;
                        }
                    }
                    anotherVar = 1;
                }
            }
            if (mousePos.y > heightPos && mousePos.y < (heightPos + 64) && mousePos.x > smiley && mousePos.x < (smiley + 64)) {
                for (int i = 0 ; i < mines ; i++) {
                    mineArray[i][0] = 0;
                    mineArray[i][1] = 0;
                }
                for (int i = 0 ; i < totalTiles ; i++) {
                    whatArray[i] = 0;
                }
                for (int i = 0 ; i < totalTiles ; i++) {
                    numArray[i] = 0;
                }
                for (int i = 0 ; i < totalTiles ; i++) {
                    flagPos[i][0] = 0;
                    flagPos[i][1] = 0;
                }
                for (int i = 0 ; i < totalTiles ; i++) {
                    flagArray[i] = 0;
                }
                for (int i = 0 ; i < totalTiles ; i++) {
                    whatFlag[i] = 0;
                }
                whatVector.clear();
                chainTile.clear();
                hiddenVec.clear();
                count = 1;
                mouseCount = 1;
                winCount = 1;
                ifmine = 0;
                anotherVar = 0;
            }
            /*
            if (mousePos.y > heightPos && mousePos.y < (heightPos + 64) && mousePos.x > (smiley + 192) && mousePos.x < (smiley + 256) && bcon == 0) {
                vector<string> board;
                vector<int> testb;
                string info;
                ifstream file("testboard1.brd");
                numin = 0;
                if (file.is_open()) {
                    while (file >> info) {
                        board.push_back(info);
                    }
                    hchange = board.size();
                    wchange = board[0].size();
                    for (int i = 0 ; i < board.size() ; i++) {
                        for (int j = 0 ; j < board[i].size() ; j++) {
                            if (board[i][j] == '1') {
                                numin++;
                                testb.push_back(1);
                            }
                            else testb.push_back(0);
                        }
                    }
                }
                for (int i = 0 ; i < testb.size() ; i++) {
                    cout << testb[i] << endl;
                }
                ifmine = 1;
                count = 1;
            }
            if (mousePos.y > heightPos && mousePos.y < (heightPos + 64) && mousePos.x > (smiley + 256) && mousePos.x < (smiley + 320)) {

            }
            if (mousePos.y > heightPos && mousePos.y < (heightPos + 64) && mousePos.x > (smiley + 320) && mousePos.x < (smiley + 384)) {

            }*/
        }

        for (int i = 0 ; i < totalTiles ; i++) {
            hiddenT.setPosition(sf::Vector2f(hiddenVec[i][0], hiddenVec[i][1]));
            gameWindow.draw(hiddenT);
        }

        for (int i = 0 ; i < whatVector.size() ; i++) {
            if (anotherVar == 1) {
                if (whatArray[whatVector[i]] == 1) {
                    for (int j = 0 ; j < mines ; j++) {
                        revealT.setPosition(mineArray[j][0], mineArray[j][1]);
                        gameWindow.draw(revealT);
                        mine.setPosition(mineArray[j][0], mineArray[j][1]);
                        gameWindow.draw(mine);
                    }
                }
            }
            else {
                //bomb placement
                if (whatArray[whatVector[i]] == 1) {
                    for (int j = 0 ; j < mines ; j++) {
                        revealT.setPosition(mineArray[j][0], mineArray[j][1]);
                        gameWindow.draw(revealT);
                        mine.setPosition(mineArray[j][0], mineArray[j][1]);
                        gameWindow.draw(mine);
                    }
                    smileL.setPosition(sf::Vector2f(smiley, heightPos));
                    gameWindow.draw(smileL);
                    mouseCount = 2;
                }
            }
            //number placement
            if (whatArray[whatVector[i]] == 0) {
                revealT.setPosition((whatVector[i] % width) * 32, (whatVector[i] / width) * 32);
                gameWindow.draw(revealT);
                whatFlag[whatVector[i]] = 1;
                if (numArray[whatVector[i]] == 1) {
                    one.setPosition((whatVector[i] % width) * 32, (whatVector[i] / width) * 32);
                    gameWindow.draw(one);
                }
                if (numArray[whatVector[i]] == 2) {
                    two.setPosition((whatVector[i] % width) * 32, (whatVector[i] / width) * 32);
                    gameWindow.draw(two);
                }
                if (numArray[whatVector[i]] == 3) {
                    three.setPosition((whatVector[i] % width) * 32, (whatVector[i] / width) * 32);
                    gameWindow.draw(three);
                }
                if (numArray[i] == 4) {
                    four.setPosition((whatVector[i] % width) * 32, (whatVector[i] / width) * 32);
                    gameWindow.draw(four);
                }
                if (numArray[i] == 5) {
                    five.setPosition((whatVector[i] % width) * 32, (whatVector[i] / width) * 32);
                    gameWindow.draw(five);
                }
                if (numArray[i] == 6) {
                    six.setPosition((whatVector[i] % width) * 32, (whatVector[i] / width) * 32);
                    gameWindow.draw(six);
                }
                if (numArray[i] == 7) {
                    seven.setPosition((whatVector[i] % width) * 32, (whatVector[i] / width) * 32);
                    gameWindow.draw(seven);
                }
                if (numArray[i] == 8) {
                    eight.setPosition((whatVector[i] % width) * 32, (whatVector[i] / width) * 32);
                    gameWindow.draw(eight);
                }
            }
            //empty tile placement
            if (whatArray[whatVector[i]] == 2) {
                int smth = whatVector[i];
                chainReveal(smth, width, whatArray, revealT, gameWindow);
                for (int j = 0 ; j < totalTiles ; j++) {
                    if (whatArray[j] == 4) {
                        whatFlag[j] = 1;
                    }
                }
            }
        }

        for (int i = 0 ; i < totalTiles ; i++) {
            if (whatArray[i] == 4) {
                revealT.setPosition((i % width) * 32, (i / width) * 32);
                gameWindow.draw(revealT);
            }
        }

        //location of every right click
        if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
            if (winCount == 1) {
                int xCoord;
                int yCoord;
                int flagloc;
                auto mousePos = sf::Mouse::getPosition(gameWindow);
                xCoord = (mousePos.x / 32) * 32;
                yCoord = (mousePos.y / 32) * 32;
                flagloc = ((yCoord / 32) * width) + (xCoord / 32);
                if (mouseCount == 1) {
                    if (flagArray[flagloc] == 0 && whatFlag[flagloc] == 0) {
                        flagArray[flagloc] = 1;
                        flagPos[flagloc][0] = xCoord;
                        flagPos[flagloc][1] = yCoord;
                        stringNum--;
                    }
                    else if (flagArray[flagloc] == 1) {
                        flagArray[flagloc] = 0;
                        stringNum++;
                    }
                }
            }
        }

        if (stringNum == 0) {
            bool win = true;
            for (int i = 0 ; i < totalTiles ; i++) {
                if (whatArray[i] == 1) {
                    if (whatArray[i] == flagArray[i]) {
                        win = true;
                    }
                    else win = false;
                }
            }
            if (win == true) {
                smileW.setPosition(sf::Vector2f(smiley, heightPos));
                gameWindow.draw(smileW);
                winCount = 2;
                for (int i = 0 ; i < totalTiles ; i++) {
                    if (whatArray[i] == 2) {
                        int smth = i;
                        chainReveal(smth, width, whatArray, revealT, gameWindow);
                        for (int j = 0 ; j < totalTiles ; j++) {
                            if (whatArray[j] == 4) {
                                whatFlag[j] = 1;
                            }
                        }
                    }
                }
                for (int i = 0 ; i < totalTiles ; i++) {
                    if (whatArray[i] == 0) {
                        revealT.setPosition((i % width) * 32, (i / width) * 32);
                        gameWindow.draw(revealT);
                        whatFlag[i] = 1;
                        if (numArray[i] == 1) {
                            one.setPosition((i % width) * 32, (i / width) * 32);
                            gameWindow.draw(one);
                        }
                        if (numArray[i] == 2) {
                            two.setPosition((i % width) * 32, (i / width) * 32);
                            gameWindow.draw(two);
                        }
                        if (numArray[i] == 3) {
                            three.setPosition((i % width) * 32, (i / width) * 32);
                            gameWindow.draw(three);
                        }
                        if (numArray[i] == 4) {
                            four.setPosition((i % width) * 32, (i / width) * 32);
                            gameWindow.draw(four);
                        }
                        if (numArray[i] == 5) {
                            five.setPosition((i % width) * 32, (i / width) * 32);
                            gameWindow.draw(five);
                        }
                        if (numArray[i] == 6) {
                            six.setPosition((i % width) * 32, (i / width) * 32);
                            gameWindow.draw(six);
                        }
                        if (numArray[i] == 7) {
                            seven.setPosition((i % width) * 32, (i / width) * 32);
                            gameWindow.draw(seven);
                        }
                        if (numArray[i] == 8) {
                            eight.setPosition((i % width) * 32, (i / width) * 32);
                            gameWindow.draw(eight);
                        }
                    }
                }
            }
        }

        //print flag locations
        for (int i = 0 ; i < totalTiles ; i++) {
            if (flagArray[i] == 1) {
                flag.setPosition(sf::Vector2f(flagPos[i][0], flagPos[i][1]));
                gameWindow.draw(flag);
            }
        }

        string number = to_string(stringNum);
        string val = number + '$';
        string pass;
        if (val[0] == '-') {
            digits.setPosition(0, heightPos);
            digits.setTextureRect(sf::IntRect(210, 0, 21, 32));
            gameWindow.draw(digits);
            if (val[2] == '$') {
                digits.setPosition(21, heightPos);
                digits.setTextureRect(sf::IntRect(0, 0, 21, 32));
                gameWindow.draw(digits);
                digits.setPosition(42, heightPos);
                digits.setTextureRect(sf::IntRect(0, 0, 21, 32));
                gameWindow.draw(digits);
                pass = val[1];
                digitalFunc(pass, 63, digits, heightPos, gameWindow);
            }
            if (val[3] == '$') {
                digits.setPosition(21, heightPos);
                digits.setTextureRect(sf::IntRect(0, 0, 21, 32));
                gameWindow.draw(digits);
                pass = val[1];
                digitalFunc(pass, 42, digits, heightPos, gameWindow);
                pass = val[2];
                digitalFunc(pass, 63, digits, heightPos, gameWindow);

            }
            if (val[4] == '$') {
                pass = val[1];
                digitalFunc(pass, 21, digits, heightPos, gameWindow);
                pass = val[2];
                digitalFunc(pass, 42, digits, heightPos, gameWindow);
                pass = val[3];
                digitalFunc(pass, 63, digits, heightPos, gameWindow);
            }
        }
        else {
            if (val[1] == '$') {
                digits.setPosition(21, heightPos);
                digits.setTextureRect(sf::IntRect(0, 0, 21, 32));
                gameWindow.draw(digits);
                digits.setPosition(42, heightPos);
                digits.setTextureRect(sf::IntRect(0, 0, 21, 32));
                gameWindow.draw(digits);
                pass = val[0];
                digitalFunc(pass, 63, digits, heightPos, gameWindow);
            }
            if (val[2] == '$') {
                digits.setPosition(21, heightPos);
                digits.setTextureRect(sf::IntRect(0, 0, 21, 32));
                gameWindow.draw(digits);
                pass = val[0];
                digitalFunc(pass, 42, digits, heightPos, gameWindow);
                pass = val[1];
                digitalFunc(pass, 63, digits, heightPos, gameWindow);

            }
            if (val[3] == '$') {
                pass = val[0];
                digitalFunc(pass, 21, digits, heightPos, gameWindow);
                pass = val[1];
                digitalFunc(pass, 42, digits, heightPos, gameWindow);
                pass = val[2];
                digitalFunc(pass, 63, digits, heightPos, gameWindow);
            }
        }

        gameWindow.display();
    }
    return 0;
}
