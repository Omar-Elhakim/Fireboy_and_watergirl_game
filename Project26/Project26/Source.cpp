#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;
int main()
{
    sf::RenderWindow window(sf::VideoMode(512, 512), "KIKI", sf:: Style:: Titlebar| sf::Style::Close| sf::Style::Resize| sf::Style::Default);
    sf::RectangleShape player(sf::Vector2f(30.0f, 60.0f));
    sf::RectangleShape player2(sf::Vector2f(30.0f, 60.0f));
    sf::RectangleShape back(sf::Vector2f(500.0f, 500.0f));
 
        
  //  player.setFillColor(sf::Color::Blue);
    
    player.setPosition(22.0f, 366.0f);
    player2.setPosition(22.0f, 430.0f);

    back.setPosition(0.0f, 0.0f);
    sf::Texture background;
    background.loadFromFile("FBWGL1.png");
    back.setTexture(&background);
    sf::Texture playertxt;
    playertxt.loadFromFile("bhfxh0rq.png");
    player.setTexture(&playertxt);
    sf::Texture playertxt2;
    playertxt2.loadFromFile("hizcc7zw.png");
    player2.setTexture(&playertxt2);
    while (window.isOpen())
    {
        sf::Event toto;
        while (window.pollEvent(toto))
        {
            switch (toto.type)
            {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::Resized:
                cout << "New width is   " << toto.size.width << endl << "New Height is   " << toto.size.height << endl;
                break;
                //case sf:: Event:: TextEntered:
                   // if (toto.text.unicode < 1000)
                     //   cout  << toto.text.unicode;

            }
            // if (toto.type == toto.Closed)
               //  window.close()
        }

            
          if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
            {
             player.move(-0.1f, 0.0f);
            }
           if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
            {
             player.move(0.0f, -0.1f);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
            {
                player.move(0.0f,0.1f);
            }
           if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
            {
            player.move(0.1f, 0.0f);
            }
           if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
           {
               player2.move(-0.1f, 0.0f);
           }
           if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
           {
               player2.move(0.0f, -0.1f);
           }
           if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
           {
               player2.move(0.0f, 0.1f);
           }
           if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
           {
               player2.move(0.1f, 0.0f);
           }
           if (player.getGlobalBounds().intersects(player2.getGlobalBounds()))
           {
               player.move(0.0f, -0.1f);
               
           }
            window.clear();
           
            window.draw(back);
           window.draw(player);
           window.draw(player2);
           
            window.display();

    }
    return 0;
}