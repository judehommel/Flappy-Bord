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
    int scoreTimer = 10;
    int score = 0;
    float fallSpeed = 2.f;
    float gravity = 0.2f;
    string s;
    sf::Text death;
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
                gravity-=7.f;
                fallSpeed = 1.5f;
                jumpDelay = 3;
            }
            else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
            {
                jumpDelay--;
                gravity = 0.2f;
            }
            else
            {
                gravity = 0.2f;
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
            cout<<s;
            scoreTimer = 10;
            pipeAccel+=0.5f;
        }
        else if(pipeX2 < 50.f && pipeX2 > 40.f && scoreTimer < 1)
        {
            score++;
            s = to_string(score);
            cout<<s;
            scoreTimer = 10;
            pipeAccel+=0.5f;
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
            scoreTxt.setPosition(500.f, 20.f);
            window.draw(scoreTxt);
        }

        //Death Checks
        bordIsDead = (bordY > 700) ? true : bordIsDead;
        bordIsDead = (pipeX1 < 100.f && pipeX1 > 0.f && bordY < pipeY1-210 || pipeX1 < 100.f && pipeX1 > 0.f && bordY > pipeY1) ? true : bordIsDead;
        bordIsDead = (pipeX2 < 100.f && pipeX2 > 0.f && bordY < pipeY2-210 || pipeX2 < 100.f && pipeX2 > 0.f && bordY > pipeY2) ? true : bordIsDead;
        if(bordIsDead)
        {
            window.clear(sf::Color(50, 50, 50));
            death.setFont(arial);
            death.setString("You Died!");
            death.setCharacterSize(70);
            death.setFillColor(sf::Color::Red);
            death.setStyle(sf::Text::Bold);
            death.setPosition(430.f, 210.f);
            bordY+=bordY;
            pipeX1+=pipeX1;
            pipeX2+=pipeX2;
            window.draw(death);
        }
        // end the current frame
        window.display();
    }

    return 0;
}
