#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
float mov(int j)
{
    if (j>15)
        return -mov(31-j);
    return 15/std::sqrt(j);
}
bool ver(sf::Vector2f di,sf::Vector2f ca)
{
    int dix=di.x+18,diy=di.y+56;
    if (dix+13<ca.x||dix>ca.x+24||diy<ca.y)
        return 0;
    else
        return 1;
}
int main()
{
    int jump=0,vx=0,mos=5,mom=5;
    bool gov=0;
    sf::RenderWindow window(sf::VideoMode(600,200),"Joculet"/*,sf::Style::Titlebar|sf::Style::Close*/); //fereastra cu marime fixa
    sf::View view;
    sf::Texture dino,cacti,dinov;
    dino.loadFromFile("dino.bmp");
    cacti.loadFromFile("cacti.bmp");
    dinov.loadFromFile("dinov.bmp");
    sf::Clock clock;
    sf::Font font;
    font.loadFromFile("arial.ttf");
    sf::Text text("Game over!",font);
    text.setCharacterSize(30);
    text.setFillColor(sf::Color::Red);
    sf::Vector2f pocac(576,187);
    sf::RectangleShape din(sf::Vector2f(66,56)),cac(sf::Vector2f(24,13));
    din.setTexture(&dino);
    din.setPosition(0,144);
    cac.setTexture(&cacti);
    cac.setPosition(pocac);
    while (clock.getElapsedTime().asSeconds()<1); //timp de asteptare o secunda
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            //inchidem fereastra la semnal
            if (event.type == sf::Event::Closed)
                window.close();
        }
        while (clock.getElapsedTime().asMilliseconds()<33.3); //limitat la 30fps
        clock.restart();
        if (!gov)
        {
            din.move(mos,0); //miscare orizontala continua a dinozaurului
            if (mom!=mos)
            {
                din.move(-1,0);
                mom=mos;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)&&!jump)
                jump=1;
            if (jump)
            {
                din.move(0,-mov(jump));
                jump++;
            }
            if (jump==31)
                jump=0;
            if (din.getPosition().x>200) //mentinem dinozaurul pe aceasi pozitie in ecran miscandu-l odata cu el dupa o anumita perioada
            {
                view.reset(sf::FloatRect(vx,0,600,200));
                window.setView(view);
                vx+=mos;
            }
            if (pocac.x+24<vx) //plasam un nou obstacol daca cel prezent fuge de tot din peisaj
            {
                pocac.x=vx+600;
                cac.setPosition(pocac);
                mos++; //crestem viteza cu fiecare nou obstacol
            }
        }
        window.clear();
        window.draw(din);
        window.draw(cac);
        if (gov)
            window.draw(text);
        window.display();
        if (ver(din.getPosition(),pocac))
        {
            din.setTexture(&dinov);
            gov=1;
            text.setPosition(vx+20,20);
        }
    }

    return 0;
}
