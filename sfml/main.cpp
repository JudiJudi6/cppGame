#include <SFML/Graphics.hpp>
#include "Tank.h"
#include "Bullet.h"
#include "EnemyTank.h"
#include "playerTank.h"
#include "StatsWindow.h"
#include "renderHelpers.h"
#include "enemyIntelligence.h"
#include "Wall.h"
#include "Brick.h"
#include "Box.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

int main()
{
    sf::RenderWindow window(sf::VideoMode(1100, 800), "Tanks 2D", sf::Style::Close);
    sf::RectangleShape map;
    sf::RectangleShape panel;
   // sf::Texture texture;
    //texture.loadFromFile("enemy.png");
    
    std::srand(std::time(0));
    sf::Clock clock;
    clock.restart();
   // int newDirection = std::rand() % 4;
    //sf::Clock clock;
    //clock.restart();

    const int tanksInGame = 3;
    const int wallsInGame = 30;
    const int bricksInGame = 3;
    const int boxesInGame = 1;
    std::vector<Tank> enemyTanks;
    std::vector<Bullet> enemyBullets;

    //stats
    //sf::Text killsCounter;
    //int destroyedTanks = 0;

    // Gracz
    Tank playerTank(sf::Vector2f(450, 400), 5.0f, "player.png", "playerHitted.png");
    Bullet playerBullet;

   // enemyTanks.push_back(Tank(getRandomCordsForEnemySpawn(), 0.9f, "enemy.png", "enemyHitted.png"));

    
    for (int i = 0; i < tanksInGame; i++) {
        enemyTanks.push_back(Tank(getRandomCordsForEnemySpawn(), 1.5f, "enemy.png", "enemyHitted.png"));
        enemyBullets.push_back(Bullet());
       // std::cout << enemyTanks.size();
    }

    for (int i = 0; i < wallsInGame; i++) {
        walls.push_back(Wall(getRandomCordsForWalls(), "wall.png"));
    }

    for (int i = 0; i < bricksInGame; i++) {
        bricks.push_back(Brick(getRandomCordsForWalls(), "Bricks.png"));
    }

    for (int i = 0; i < boxesInGame; i++) {
        boxes.push_back(Box(getRandomCordsForWalls(), "box.png"));
    }
    
    /*
    //enemy 1
    Tank enemy1Tank(getRandomCordsForEnemySpawn(), 0.9f, "enemy.png", "enemyHitted.png");
    //Bullet enemy1bullet;
    
    //enemy2
    Tank enemy2Tank(getRandomCordsForEnemySpawn(), 0.9f, "enemy.png", "enemyHitted.png");

    //enemy3
    Tank enemy3Tank(getRandomCordsForEnemySpawn(), 0.9f, "enemy.png", "enemyHitted.png");

    */

    sf::Texture mapTexture;
    map.setSize(sf::Vector2f(900, 800));
    mapTexture.loadFromFile("map.jpg");
    map.setTexture(&mapTexture);

    sf::Texture panelTexture;
    panel.setSize(sf::Vector2f(200, 800));
    panelTexture.loadFromFile("panel.png");
    panel.setTexture(&panelTexture);
    panel.setPosition(900, 0);
    //map.setPosition(100, 50);

    //Stats gameStats;

            startGameTime();


    while (window.isOpen()) {
        sf::Event evnt;


        while (window.pollEvent(evnt)) {
            switch (evnt.type)
            {
            case sf::Event::Closed:
                window.close();
                break;
                /*case sf::Event::TextEntered:
                    if (evnt.text.unicode < 128) {
                        printf("%c", evnt.text.unicode);
                    }
                    break; */
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            playerTank.moveTop();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            playerTank.moveLeft();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            playerTank.moveBottom();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            playerTank.moveRight();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
            playerBullet.shot(playerTank.getBulletDirection(), playerTank.body.getPosition().x, playerTank.body.getPosition().y);
        } 


        playerBullet.updateBullet();

        countGameTime();


        window.clear();
        window.draw(map);
        playerBullet.drawBullet(window);
        window.draw(playerTank.body); 
        /*
        window.draw(enemy1Tank.body);
        window.draw(enemy2Tank.body);
        window.draw(enemy3Tank.body);
        */
        for(int i = 0; i < tanksInGame; i++) {
            enemyTanks[i].getHitted(playerBullet);
            enemyTanks[i].getHittedAnimation();
            playerTank.getHitted(enemyBullets[i]);
            enemyBullets[i].drawBullet(window);
            enemyBullets[i].updateBullet();
            enemyTanks[i].drawTank(window);
            enemyTanks[i].enemyIntelligence(playerTank, enemyBullets[i], clock);
        }

        for (int i = 0; i < bricksInGame; i++) {
            window.draw(bricks[i].body);
            bricks[i].SetWallTexture();
            for (int j = 0; j < enemyBullets.size(); j++) {
                bricks[i].GetHitted(enemyBullets[j]);
            }
                bricks[i].GetHitted(playerBullet);
        }

        for (int i = 0; i < boxesInGame; i++) {
            window.draw(boxes[i].body);
            boxes[i].SetWallTexture();
            for (int j = 0; j < enemyBullets.size(); j++) {
                boxes[i].GetHitted(enemyBullets[j]);
            }
            boxes[i].GetHitted(playerBullet);
        }

        for (int i = 0; i < wallsInGame; i++) {
            window.draw(walls[i].body);
            walls[i].SetWallTexture();
            for (int j = 0; j < enemyBullets.size(); j++) {
                walls[i].GetHitted(enemyBullets[j]);
            }
                walls[i].GetHitted(playerBullet);
        }

        playerTank.getHittedAnimation();
        window.draw(panel);
        
        //draw stats
        //std::cout << destroyedTanks;
        drawText(window, "Kills: ", destroyedTanks, sf::Vector2f(950, 200));
        drawText(window, "Game time: ", gameTime, sf::Vector2f(950, 300));
        drawText(window, "Player HP: ", playerTank.getHealthPoints(), sf::Vector2f(950, 400));

        //addKill();

        window.display();

    }

    return 0;
}