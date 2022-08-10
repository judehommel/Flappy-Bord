#include <iostream>
#include <string>
#include "random.h"
#include <SFML/Graphics.hpp>

using namespace std;

double pipeX1 = 1200.f;
double pipeY1 = random <int> (250, 650);
double pipeX2 = 1800.f;
double pipeY2 = random <int> (250, 650);
double pipeAccel = 5.f;
double bordY = 200.f;

void bord(sf::RenderWindow &window)
{
    sf::CircleShape bord(30.f);
    bord.setFillColor(sf::Color(200, 200, 70));
    bord.setPosition(70.f, bordY);
    bord.setOrigin(15.f, 15.f);
    window.draw(bord);
}


void pipe1(sf::RenderWindow &window)
{
    sf::RectangleShape pipeBottom(sf::Vector2f(100.f, 400.f));
    sf::RectangleShape pipeTop(sf::Vector2f(100.f, 400.f));
    pipeBottom.setSize(sf::Vector2f(100.f, 800.f));
    pipeTop.setSize(sf::Vector2f(100.f, 800.f));
    pipeBottom.setPosition(pipeX1, pipeY1);
    pipeTop.setPosition(pipeX1, pipeY1-1000);
    pipeBottom.setFillColor(sf::Color(100, 200, 70));
    pipeTop.setFillColor(sf::Color(100, 200, 70));
    pipeX1-=pipeAccel;
    window.draw(pipeTop);
    window.draw(pipeBottom);
}

void pipe2(sf::RenderWindow &window)
{
    sf::RectangleShape pipeBottom(sf::Vector2f(100.f, 400.f));
    sf::RectangleShape pipeTop(sf::Vector2f(100.f, 400.f));
    pipeBottom.setSize(sf::Vector2f(100.f, 800.f));
    pipeTop.setSize(sf::Vector2f(100.f, 800.f));
    pipeBottom.setPosition(pipeX2, pipeY2);
    pipeTop.setPosition(pipeX2, pipeY2-1000);
    pipeBottom.setFillColor(sf::Color(100, 200, 70));
    pipeTop.setFillColor(sf::Color(100, 200, 70));
    pipeX2-=pipeAccel;
    window.draw(pipeTop);
    window.draw(pipeBottom);
}

int main()
{
    srand(time(0));

    bool bordIsDead = false;
    float jumpDelay = 3;
    int scoreTimer = 5;
    int score = 0;
    float fallSpeed = 2.f;
    float gravity = 0.2f;
    string s = "0";
    sf::Text death;
    sf::Text respawnTxt;
    sf::Text scoreTxt;
    sf::Font arial;
    arial.loadFromFile("arial.ttf");
    if (!arial.loadFromFile("arial.ttf"))
    {
        cout<<"error";
    }

    // create the window
    sf::RenderWindow window(sf::VideoMode(1200, 700), "Flappy Bord");

    window.setFramerateLimit(60);

    // run the program as long as the window is open
    while (window.isOpen())
    {
        beginning:
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                window.close();
        }

        // Background
        window.clear(sf::Color(150, 160, 230));

        bord(window);

        //Jump function
        if(bordY>0)
        {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && jumpDelay < 0)
            {
                gravity-=9.f;
                fallSpeed = 1.5f;
                jumpDelay = 3;
            }
            else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
            {
                jumpDelay--;
                gravity = 0.25f;
            }
            else
            {
                gravity = 0.25f;
            }
        }
        bordY+=fallSpeed;
        fallSpeed+=gravity;

        pipe1(window);
        pipe2(window);


        if(pipeX1 < 50.f && pipeX1 > 40.f && scoreTimer < 1)
        {
            score++;
            s = to_string(score);
            cout<<s + " ";
            scoreTimer = 5;
            pipeAccel+=0.2f;
        }
        else if(pipeX2 < 50.f && pipeX2 > 40.f && scoreTimer < 1)
        {
            score++;
            s = to_string(score);
            cout<<s + " ";
            scoreTimer = 5;
            pipeAccel+=0.2f;
        }
        else
        {
            scoreTimer--;
        }

        if(pipeX1 < -100.f)
        {
            pipeX1 = 1200.f;
        }
        else if(pipeX2 < -100.f)
        {
            pipeX2 = 1200.f;
        }

        if(pipeX1 > 1199.f)
        {
            pipeY1 = random <int> (250, 650);
        }
        else if(pipeX2 > 1199.f)
        {
            pipeY2 = random <int> (250, 650);
        }

        if (!bordIsDead)
        {
            //Displays Score
            scoreTxt.setFont(arial);
            scoreTxt.setString("Score: " + s);
            scoreTxt.setCharacterSize(50);
            scoreTxt.setFillColor(sf::Color(255, 255, 255, 170));
            scoreTxt.setStyle(sf::Text::Bold);
            scoreTxt.setPosition(510.f, 20.f);
            window.draw(scoreTxt);
        }

        //Death Checks
        bordIsDead = (bordY > 700) ? true : bordIsDead;
        bordIsDead = (pipeX1 < 100.f && pipeX1 > 0.f && bordY < pipeY1-200.f || pipeX1 < 100.f && pipeX1 > 0.f && bordY > pipeY1-10.f) ? true : bordIsDead;
        bordIsDead = (pipeX2 < 100.f && pipeX2 > 0.f && bordY < pipeY2-200.f || pipeX2 < 100.f && pipeX2 > 0.f && bordY > pipeY2-10.f) ? true : bordIsDead;
        if(bordIsDead)
        {
            window.clear(sf::Color(70, 70, 70));
            death.setFont(arial);
            death.setString("You Died!");
            death.setCharacterSize(70);
            death.setFillColor(sf::Color::Red);
            death.setStyle(sf::Text::Bold);
            death.setPosition(430.f, 180.f);
            scoreTxt.setFont(arial);
            scoreTxt.setString("Score: " + s);
            scoreTxt.setCharacterSize(50);
            scoreTxt.setFillColor(sf::Color(255, 255, 255, 170));
            scoreTxt.setStyle(sf::Text::Bold);
            scoreTxt.setOrigin(40.f, 10.f);
            scoreTxt.setPosition(510.f, 330.f);
            respawnTxt.setFont(arial);
            respawnTxt.setString("Respawn");
            respawnTxt.setCharacterSize(40);
            respawnTxt.setFillColor(sf::Color(190, 190, 190));
            respawnTxt.setPosition(500.f, 500);
            sf::RectangleShape respawnButton;
            respawnButton.setOutlineColor(sf::Color::Black);
            respawnButton.setOutlineThickness(10);
            respawnButton.setSize(sf::Vector2f(230.f, 100.f));
            respawnButton.setPosition(470.f, 480.f);
            if(sf::Mouse::getPosition().x < 1490 && sf::Mouse::getPosition().x > 1240 && sf::Mouse::getPosition().y < 1200 && sf::Mouse::getPosition().y > 1090)
            {
                respawnButton.setFillColor(sf::Color(130, 130, 130));
                if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
                {
                    respawnButton.setFillColor(sf::Color(80, 80, 80));
                    pipeX1 = 1200.f;
                    pipeY1 = random <int> (250, 650);
                    pipeX2 = 1800.f;
                    pipeY2 = random <int> (250, 650);
                    pipeAccel = 5.f;
                    bordY = 200.f;
                    bordIsDead = false;
                    fallSpeed = 1.5f;
                    score = 0;
                    s = "0";
                    goto beginning;
                }
            }
            else
            {
                respawnButton.setFillColor(sf::Color(100, 100, 100));
            }
            bordY+=bordY;
            pipeX1+=pipeX1;
            pipeX2+=pipeX2;
            window.draw(respawnButton);
            window.draw(respawnTxt);
            window.draw(scoreTxt);
            window.draw(death);
        }
        // end the current frame
        window.display();
    }

    return 0;
}
