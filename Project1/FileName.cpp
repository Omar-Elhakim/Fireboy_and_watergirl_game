#include<iostream>

#include<SFML/Graphics.hpp>
#include<SFML/Network.hpp>
#include<SFML/System.hpp>
#include<SFML/Window.hpp>
#include<SFML/Audio.hpp>

using namespace std;
using namespace sf;
int main()
{
    //Main window
    RenderWindow window(VideoMode(1720, 1300), "Fireboy and Watergirl");

    // background music
    Music  backgroundMusic;
    backgroundMusic.openFromFile("background-music.wav");
    backgroundMusic.setLoop(true);
    //backgroundMusic.play();


    //background picture
    Texture backgroundTexture;
    backgroundTexture.loadFromFile("image.PNG");
    Sprite backgroundPic(backgroundTexture);
    cout<<backgroundPic.getGlobalBounds();


    //creating lava
    RectangleShape lava(Vector2f(190.f, 10.f));
    lava.setPosition(800.f, 1234.f);
    lava.setFillColor(Color(255, 0, 0));

    //creating lake
    RectangleShape lake(Vector2f(190.f, 10.f));
    lake.setPosition(1153.f, 1234.f);
    lake.setFillColor(Color(0, 0, 255));


    //creating green goo
    RectangleShape green_goo(Vector2f(190.f, 10.f));
    green_goo.setPosition(1060.f, 968.f);
    green_goo.setFillColor(Color(0, 255, 0));


    // creating two walls
    //left wall
    RectangleShape left_wall(Vector2f(10.f, 1800.f));
    left_wall.setPosition(37.f, 0);
    left_wall.setFillColor(Color(0, 0, 0));

    //right wall
    RectangleShape right_wall(Vector2f(10.f, 1800.f));
    right_wall.setPosition(1657.f, 0);
    right_wall.setFillColor(Color(0, 0, 0));


    // Creating grounds for each floor
    //ground floor
    RectangleShape ground1(Vector2f(1800.f, 10.f));
    ground1.setPosition(0.f, 1234.f);
    ground1.setFillColor(Color(0, 0, 0));

    //floor 1.5
    RectangleShape ground1_5(Vector2f(550.f, 10.f));
    ground1_5.setPosition(0.f, 1060.f);
    ground1_5.setFillColor(Color(0, 0, 0));


    //floor 1.7
    RectangleShape ground1_7(Vector2f(610.f, 10.f));
    ground1_7.setPosition(840.f, 968.f);
    ground1_7.setFillColor(Color(0, 0, 0));

    
    
    //floor 2
    RectangleShape ground2(Vector2f(758.f, 10.f));
    ground2.setPosition(0.f, 885.f);
    ground2.setFillColor(Color(0, 0, 0));
    
    //floor 2.8
    RectangleShape ground2_8(Vector2f(760.f, 10.f));
    ground2_8.setPosition(920.f, 710.f);
    ground2_8.setFillColor(Color(0, 0, 0));

    //floor 3
    RectangleShape ground3(Vector2f(660.f, 10.f));
    ground3.setPosition(223.f, 665.f);
    ground3.setFillColor(Color(0, 0, 0));
   
    
    
    
    //making and editing fireboy
    Texture text;
    text.loadFromFile("fireboy.png");
    Sprite fireboy(text);
    fireboy.setPosition(Vector2f(77, 1110));
    fireboy.setScale(0.41f, 0.41f);
    bool fireboyOnground = fireboy.getGlobalBounds().intersects(ground1.getGlobalBounds());


    //making and editing watergirl
    Texture texting;
    texting.loadFromFile("watergirl.png");
    Sprite watergirl(texting);
    watergirl.setPosition(Vector2f(78, 963));
    watergirl.setScale(0.24f, 0.24f);
    bool watergirlOnground = true;


    //main event
    Event ev;


    //Main Game loop
    while (window.isOpen())
    {
        while (window.pollEvent(ev))
        {
            switch (ev.type)
            {
            case Event::Closed:
                window.close();
                break;
            }
        }

        //fireboy movments
        //fireboy jumping
        if ((!fireboy.getGlobalBounds().intersects(ground1.getGlobalBounds())))
        {
            
            //fireboyOnground = false;
            fireboy.move(0, 0.2f);
        }
        
        
        //&& (fireboy.getGlobalBounds().intersects(ground1.getGlobalBounds()))
        if ((Keyboard::isKeyPressed(Keyboard::Key::Up)) )
        {
            fireboy.move(0.0f, -0.9f);
        }
        //to the right
        if ((Keyboard::isKeyPressed(Keyboard::Key::Right)) && (!fireboy.getGlobalBounds().intersects(right_wall.getGlobalBounds())))
        {
            fireboy.move(0.5f, 0.0f);
        }
        //to the left
        if (Keyboard::isKeyPressed(Keyboard::Key::Left) && (!fireboy.getGlobalBounds().intersects(left_wall.getGlobalBounds())))
        {
            fireboy.move(-0.7f, 0.0f);
        }

     
       /* if (Keyboard::isKeyPressed(Keyboard::Key::Down))
        {
            fireboy.move(0.0f, 0.2f);
        }
        */

        //watergirl movments
        //to the right
        if ((Keyboard::isKeyPressed(Keyboard::Key::D)) && (!watergirl.getGlobalBounds().intersects(right_wall.getGlobalBounds())))
        {
            watergirl.move(0.7f, 0.0f);
        }
        //to the left
        if ((Keyboard::isKeyPressed(Keyboard::Key::A)) && (!watergirl.getGlobalBounds().intersects(left_wall.getGlobalBounds())))
        {
            watergirl.move(-0.7f, 0.0f);
        }

        //watergirl jumping
        if (Keyboard::isKeyPressed(Keyboard::Key::W))
        {
            watergirl.move(0.0f, -0.2f);
        }




        //exit when esc is pressed
        if (Keyboard::isKeyPressed(Keyboard::Key::Escape))
        {
            window.close();
        }




        window.clear();
        window.draw(backgroundPic);
        window.draw(right_wall);
        window.draw(left_wall);
        window.draw(ground1);
        window.draw(ground1_5);
        window.draw(ground1_7);
        window.draw(ground2);
        window.draw(ground2_8);
        window.draw(ground3);
        window.draw(lava);
        window.draw(lake);
        window.draw(green_goo);
        window.draw(fireboy);
        window.draw(watergirl);
        window.display();
    }
    return 0;
}
