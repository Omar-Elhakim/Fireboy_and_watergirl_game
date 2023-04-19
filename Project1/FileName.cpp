#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <iostream>

using namespace std;
using namespace sf;

// for animation
float gravity = 0.0035, fireboy_Vy = 0, watergirl_Vy = 0;
int x = 0, y = 0, a = 0;

void scaleFireboy(Sprite& sprite, const Vector2u& windowSize) {
    float xScale = (float)windowSize.x / 1720;
    float yScale = (float)windowSize.y / 1300;
    float xPos = 77 * xScale;
    float yPos = 1110 * yScale;
    sprite.setScale(1.f * xScale, 1.f * yScale);
    //sprite.setPosition(xPos, yPos);
}

void scaleWatergirl(Sprite& sprite, const Vector2u& windowSize) {
    float xScale = (float)windowSize.x / 1720;
    float yScale = (float)windowSize.y / 1300;
    float xPos = 78 * xScale;
    float yPos = 963 * yScale;
    sprite.setScale(1.f * xScale, 1.f * yScale);
    sprite.setPosition(xPos, yPos);
}
void scaleRectangles(sf::Vector2u windowSize, sf::RectangleShape ground[], int size) {
    // Calculate the scaling factors for x and y axis
    float scaleX = (float)windowSize.x / 1210.f;
    float scaleY = (float)windowSize.y / 850.f;

    // Iterate over the ground array and scale each rectangle
    for (int i = 0; i < size; i++) {
        sf::Vector2f position = ground[i].getPosition();
        sf::Vector2f size = ground[i].getSize();
        position.x *= scaleX;
        position.y *= scaleY;
        size.x *= scaleX;
        size.y *= scaleY;
        ground[i].setPosition(position);
        ground[i].setSize(size);
    }
}

void scaleRectangles(sf::Vector2u windowSize, sf::RectangleShape& ground) {
    // Calculate the scaling factors for x and y axis
    float scaleX = (float)windowSize.x / 1720.f;
    float scaleY = (float)windowSize.y / 1300.f;

    
        sf::Vector2f position = ground.getPosition();
        sf::Vector2f size = ground.getSize();
        position.x *= scaleX;
        position.y *= scaleY;
        size.x *= scaleX;
        size.y *= scaleY;
        ground.setPosition(position);
        ground.setSize(size);
    
}
void scaleBackground(Sprite& backgroundPic, const Vector2u& windowSize) {
    float scaleX = (float)windowSize.x / 1720.f;
    float scaleY = (float)windowSize.y / 1300.f;
    backgroundPic.setScale(scaleX, scaleY * 0.978f);
    backgroundPic.setPosition(-14.f * scaleX, 10.f * scaleY);
}


void scalePosition(float& xPos, float& yPos, const sf::RenderWindow& window) {
    float xScale = window.getSize().x / 1720.f;  // calculate x scaling factor
    float yScale = window.getSize().y / 1300.f;  // calculate y scaling factor

    // scale the diamond position
    xPos *= xScale;
    yPos *= yScale;
}

void level1(RenderWindow& window);

int main() {
    // Main window
    RenderWindow window(VideoMode(1720, 1300), "Fireboy and Watergirl");

    Image icon;
    icon.loadFromFile("icon.png");
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
    level1(window);
    return 0;
}

void Fmove(Sprite& fireboy, RectangleShape& rWall, RectangleShape& lWall,
    RectangleShape ground[], RectangleShape& roof);
void Wmove(Sprite& watergirl, RectangleShape& rWall, RectangleShape& lWall,
    RectangleShape ground[], RectangleShape& roof);

void level1(RenderWindow& window) {


    // Calculate the percentage of the window dimensions to use for scaling the grounds
    float scaleX = (float)window.getSize().x / 1210.f;
    float scaleY = (float)window.getSize().y / 850.f;

    // stopwatch
    Clock gameClock;
    Font font;
    font.loadFromFile("font.ttf");
    Text timeText;
    timeText.setFont(font);
    timeText.setCharacterSize(55);
    timeText.setFillColor(sf::Color(255, 215, 0));
    timeText.setPosition(780, 0);
    // background music
    Music backgroundMusic;
    backgroundMusic.openFromFile("background-music.wav");
    backgroundMusic.setLoop(true);
    // backgroundMusic.play();
    // death sound
    SoundBuffer death_buffer;
    death_buffer.loadFromFile("Death.wav");
    Sound death_sound;
    death_sound.setBuffer(death_buffer);
    // diamond sound
    SoundBuffer diamond_buffer;
    diamond_buffer.loadFromFile("Diamond.wav");
    Sound diamond_sound;
    diamond_sound.setBuffer(diamond_buffer);

    // background picture
    Texture backgroundTexture;
    backgroundTexture.loadFromFile("background.png");
    Sprite backgroundPic(backgroundTexture);
    backgroundPic.setScale(1.0f, 0.978f);
    scaleBackground(backgroundPic, window.getSize());
    //crating fireboy  diamonds
    Texture red1;
    red1.loadFromFile("redDiamond.png");
    //diamond1
    Sprite redDiamond1(red1);
    float x1 = 845.f, y1 = 1120.f;
    scalePosition(x1, y1, window);
    redDiamond1.setPosition(x1, y1);

    //diamond 2
    Sprite redDiamond2(red1);
    float x2 = 270.f, y2 = 550.f;
    scalePosition(x2, y2, window);
    redDiamond2.setPosition(x2, y2);

    //diamond 3
    Sprite redDiamond3(red1);
    float x3 = 400.f, y3 = 80.f;
    scalePosition(x3, y3, window);
    redDiamond3.setPosition(x3, y3);

    //diamond 4
    Sprite redDiamond4(red1);
    // scale diamond 4 position
    float x4 = 760.f, y4 = 160.f;
    scalePosition(x4, y4, window);
    redDiamond4.setPosition(x4, y4);

    //crating watergirl  diamonds
    Texture blue1;
    blue1.loadFromFile("blueDiamond.png");
    //diamond1
    Sprite blueDiamond1(blue1);
    float x5 = 1200.f, y5 = 1120.f;
    scalePosition(x5, y5, window);
    blueDiamond1.setPosition(x5, y5);

    //diamond2
    Sprite blueDiamond2(blue1);
    float x6 = 980.f, y6 = 600.f;
    scalePosition(x6, y6, window);
    blueDiamond2.setPosition(x6, y6);

    //diamond3
    Sprite blueDiamond3(blue1);
    float x7 = 55.f, y7 = 210.f;
    scalePosition(x7, y7, window);
    blueDiamond3.setPosition(x7, y7);


    //diamond4
    Sprite blueDiamond4(blue1);
    float x8 = 940.f, y8 = 170.f;
    scalePosition(x8, y8, window);
    blueDiamond4.setPosition(x8, y8);

    // creating lava
    RectangleShape lava(Vector2f(130.f, 10.f));
    lava.setPosition(830.f, 1238.f);
    lava.setFillColor(Color(255, 0, 0));
    scaleRectangles(window.getSize(), lava);
    // creating lake
    RectangleShape lake(Vector2f(145.f, 10.f));
    lake.setPosition(1165.f, 1238.f);
    lake.setFillColor(Color(0, 0, 255));
    scaleRectangles(window.getSize(), lake);

    // creating green goo
    RectangleShape green_goo(Vector2f(190.f, 10.f));
    green_goo.setPosition(1060.f, 968.f);
    green_goo.setFillColor(Color(0, 255, 0));
    scaleRectangles(window.getSize(), green_goo);

    //creating two walls
    //left wall
    RectangleShape left_wall(Vector2f(10.f, 1800.f));
    left_wall.setPosition(20.f, 0);
    left_wall.setFillColor(Color(255, 255, 255));

    //right wall
    RectangleShape right_wall(Vector2f(10.f, 1800.f));
    right_wall.setPosition(window.getSize().x - 50, 0);
    right_wall.setFillColor(Color(255, 255, 255));


    // Creating grounds for each floor
    RectangleShape ground[] = {
        // ground floor
        RectangleShape(Vector2f(1950.f, 10.f)),
        //groundright
        RectangleShape(Vector2f(10.f, 80.f)),
        RectangleShape(Vector2f(10.f, 35.f)),
        RectangleShape(Vector2f(40.f, 10.f)),
        //top
        RectangleShape(Vector2f(1950.f, 10.f)),
        // floor1
        RectangleShape(Vector2f(405.f, 30.f)),
        // floor2 straight right
        RectangleShape(Vector2f(450.f, 10.f)),
        // floor2 inclined
        RectangleShape(Vector2f(10.f, 70.f)),
        // floor2 straight left
        RectangleShape(Vector2f(540.f, 10.f)),
        //floor3 straight right
        RectangleShape(Vector2f(550.f, 10.f)),
        //floor3 inclined
        RectangleShape(Vector2f(10.f, 55.f)),
        //floor3 straight left
        RectangleShape(Vector2f(460.f, 10.f)),
        //floor4 straight left
        RectangleShape(Vector2f(400.f, 10.f)),
        //floor4 straight right
        RectangleShape(Vector2f(190.f, 10.f)),
        //floor4 middle obstacle straight up
        RectangleShape(Vector2f(225.f, 10.f)),
        //floor4 top of square left
        RectangleShape(Vector2f(155.f, 10.f)),
        //floor4 width of square left
        RectangleShape(Vector2f(10.f, 120.f)),
        //floor4 middle obstacle left
        RectangleShape(Vector2f(10.f, 50.f)),
        //floor4 middle obstacle incline
        RectangleShape(Vector2f(10.f, 75.f)),
        //floor5 middle straight
        RectangleShape(Vector2f(330.f, 10.f)),
        //floor5 straight right
        RectangleShape(Vector2f(220.f, 10.f)),
        //floor5 middle right incline
        RectangleShape(Vector2f(10.f, 55.f)),
        //floor5 middle left incline
        RectangleShape(Vector2f(10.f, 55.f)),
        //floor5 middle up straight
        RectangleShape(Vector2f(80.f,10.f)),
        //floor5 left obstacle
        RectangleShape(Vector2f(10.f, 50.f)),
        RectangleShape(Vector2f(10.f, 50.f)),
        RectangleShape(Vector2f(20.f, 10.f)),
        RectangleShape(Vector2f(70.f, 10.f)),
        RectangleShape(Vector2f(10.f, 35.f)),
    };

    //ground editing
    {
        // ground floor
        ground[0].setPosition(0.f, 815.f);
        //groundright
        ground[1].setPosition(1090.f, 750.f); //small right wall
        ground[2].setPosition(1115.f, 730.f);
        ground[2].setRotation(45);
        ground[3].setPosition(1125.f, 730.f);
        //top
        ground[4].setPosition(0.f, 35.f);
        // floor1
        ground[5].setPosition(0.f, 700.f);
        // floor2 straight right
        ground[6].setPosition(590.f, 645.f);
        // floor2 inclined
        ground[7].setPosition(530.f, 600.f);
        ground[7].setRotation(-45);
        // floor2 straight left
        ground[8].setPosition(0.f, 585.f);
        //floor3 straight right
        ground[9].setPosition(655.f, 470.f);
        //floor3 inclined
        ground[10].setPosition(610.f, 450.f);
        ground[10].setRotation(-45);
        //floor3 straight left
        ground[11].setPosition(160.f, 440.f);
        //floor4 straight left
        ground[12].setPosition(190.f, 330.f);
        //floor4 straight right
        ground[13].setPosition(870.f, 330.f);
        //floor4 middle obstacle straight up
        ground[14].setPosition(590.f, 270.f);
        //floor4 top of square left
        ground[15].setPosition(30.f, 215.f);
        //floor4 width of square left
        ground[16].setPosition(170.f, 215.f); //small  left wall
        //floor4 middle obstacle left
        ground[17].setPosition(595.f, 270.f);
        //floor4 middle obstacle incline
        ground[18].setPosition(810.f, 285.f);
        ground[18].setRotation(-45);
        //floor5 middle straight
        ground[19].setPosition(480.f, 185.f);
        //floor5 straight right
        ground[20].setPosition(960.f, 185.f);
        //floor5 middle right incline
        ground[21].setPosition(920.f, 160.f);
        ground[21].setRotation(-45);
        //floor5 middle left incline
        ground[22].setPosition(845.f, 150.f);
        ground[22].setRotation(45);
        //floor5 middle up straight
        ground[23].setPosition(850.f, 155.f);
        //floor5 left obstacle
        ground[24].setPosition(430.f, 165.f);
        ground[24].setRotation(-45);
        ground[25].setPosition(375.f, 130.f);
        ground[25].setRotation(-45);
        ground[26].setPosition(420.f, 155.f);
        ground[27].setPosition(310.f, 125.f);
        ground[28].setPosition(315.f, 120.f);
        ground[28].setRotation(45);
    }
    scaleRectangles(window.getSize(), ground, 29);

    //roof
    RectangleShape roof(Vector2f(969.f, 10));
    roof.setPosition(697.f, 310.f);


    /////////////////////////////////////
    // zatoona part    
    //button1
        //X: 460
        //Y:662
    RectangleShape butt1(Vector2f(18, 18));
    butt1.setPosition(Vector2f(543, 1205));
    butt1.setFillColor(Color(255, 0, 0));
    /////////////////////////////////////////
        //button2 //lever
    RectangleShape butt2(Vector2f(18, 18));
    butt2.setPosition(Vector2f(655, 1205));
    butt2.setFillColor(Color(0, 255, 0));



    //LEVER
        //lvr.jpg need fixingggg
        //
    Texture lever;
    lever.loadFromFile("lvr.png");
    RectangleShape lvr(Vector2f(20, 65));
    lvr.setTexture(&lever);
    lvr.setPosition(Vector2f(373, 1223));
    lvr.setOrigin(Vector2f(lvr.getLocalBounds().width, lvr.getLocalBounds().height) / 1.05f);
    lvr.setRotation(45);
    //    lvr.rotate(-90);
        ////start pos////
    RectangleShape stlvr(Vector2f(5, 40));
    stlvr.setFillColor(Color(0, 0, 0));
    stlvr.setPosition(Vector2f(392, 1204));
    ////end pos////
    RectangleShape endlvr(Vector2f(5, 40));
    endlvr.setFillColor(Color(0, 0, 0));
    endlvr.setPosition(Vector2f(330, 1204));



    /////////////////////////////////////////////////////////    
        //Elevator1 START fo2
    RectangleShape STRTelv1(Vector2f(160, 5));
    STRTelv1.setPosition(1500, 533);
    STRTelv1.setFillColor(Color(255, 0, 0));



    //Elevator11
    Texture elvv;
    elvv.loadFromFile("elev2.png");
    Sprite elevator1;
    elevator1.setTexture(elvv);
    elevator1.setPosition(Vector2f(1500, 553));



    //Elevator1   END t7t
    RectangleShape ENDelv1(Vector2f(160, 5));
    ENDelv1.setPosition(1500, 704);
    ENDelv1.setFillColor(Color(255, 0, 0));
    //////////////////////////////////////////////////////
    //
    // 
    // 
    // 
    // 
    // 
       //Elevator 2 START FO2
    RectangleShape STRTelv2(Vector2f(160, 5));
    STRTelv2.setPosition(37, 673);
    STRTelv2.setFillColor(Color(255, 0, 0));

    //37
    //673




    //ELEVATOR2
    Texture elv;
    elv.loadFromFile("elev1.png");
    Sprite elevator2;
    elevator2.setTexture(elv);
    elevator2.setPosition(Vector2f(37, 673));

    //x:37
    //y:673





    //ELEVATOR2 END t7t
    RectangleShape ENDelv2(Vector2f(160, 5));
    ENDelv2.setPosition(37, 820);
    ENDelv2.setFillColor(Color(255, 0, 0));

    //37 
    //820




    // making and editing fireboy
    Texture text;
    text.loadFromFile("fireboysheet.png");
    Sprite fireboy(text);
    //fireboy.setPosition(Vector2f(77, 1110));
    //fireboy.setScale(1.f, 1.f);
    fireboy.setTextureRect(sf::IntRect(0 * 113, 4 * 95, 105, 105));
    scaleFireboy(fireboy, window.getSize());

    // making and editing watergirl
    Texture texting;
    texting.loadFromFile("watergirlsheet.png");
    Sprite watergirl(texting);
    //watergirl.setPosition(Vector2f(78, 963));
    //watergirl.setScale(1.f, 1.f);
    watergirl.setTextureRect(sf::IntRect(0 * 175, 4 * 133, 100, 90));
    scaleWatergirl(watergirl, window.getSize());

    // gravity
    float gravity = 0.003, fireboy_velocity_y = 0, watergirl_Vy = 0;

    // main event
    Event ev;

    // Main Game loop
    while (window.isOpen()) {

        while (window.pollEvent(ev)) {
            if (ev.type == Event::Closed)
                window.close();
        }

        // timer
        Time gameTime = gameClock.getElapsedTime();
        int minutes = gameTime.asSeconds() / 60;
        int temp = gameTime.asSeconds();
        int seconds = temp % 60;
        timeText.setString(std::to_string(minutes) + ":" +
            (seconds < 10 ? "0" : "") + std::to_string(seconds));

        // move fireboy
        Fmove(fireboy, right_wall, left_wall, ground, roof);

        // fireboy diamonds
        {
            if (fireboy.getGlobalBounds().intersects(redDiamond1.getGlobalBounds())) {
                redDiamond1.move(9999.f, 0.f);
                diamond_sound.play();
            }
            if (fireboy.getGlobalBounds().intersects(redDiamond2.getGlobalBounds())) {
                redDiamond2.move(9999.f, 0.f);
                diamond_sound.play();
            }
            if (fireboy.getGlobalBounds().intersects(redDiamond2.getGlobalBounds())) {
                redDiamond2.move(9999.f, 0.f);
                diamond_sound.play();
            }
            if (fireboy.getGlobalBounds().intersects(redDiamond3.getGlobalBounds())) {
                redDiamond3.move(9999.f, 0.f);
                diamond_sound.play();
            }
            if (fireboy.getGlobalBounds().intersects(redDiamond4.getGlobalBounds())) {
                redDiamond4.move(9999.f, 0.f);
                diamond_sound.play();
            }
        }

        // fireboy dying
       /*if ((fireboy.getGlobalBounds().intersects(lake.getGlobalBounds())) ||
            (fireboy.getGlobalBounds().intersects(green_goo.getGlobalBounds()))) {
            fireboy.setPosition(Vector2f(-2000, 33330));
            backgroundMusic.pause();
            death_sound.play();
        }
        */
        // watergirl movments
        Wmove(watergirl, right_wall, left_wall, ground, roof);

        // watergirl diamonds
        {
            if (watergirl.getGlobalBounds().intersects(
                blueDiamond1.getGlobalBounds())) {
                blueDiamond1.move(9999.f, 0.f);
                diamond_sound.play();
            }
            if (watergirl.getGlobalBounds().intersects(
                blueDiamond2.getGlobalBounds())) {
                blueDiamond2.move(9999.f, 0.f);
                diamond_sound.play();
            }
            if (watergirl.getGlobalBounds().intersects(
                blueDiamond3.getGlobalBounds())) {
                blueDiamond3.move(9999.f, 0.f);
                diamond_sound.play();
            }
            if (watergirl.getGlobalBounds().intersects(
                blueDiamond4.getGlobalBounds())) {
                blueDiamond4.move(9999.f, 0.f);
                diamond_sound.play();
            }
        }

        // watergirl death
        if ((watergirl.getGlobalBounds().intersects(lava.getGlobalBounds())) ||
            (watergirl.getGlobalBounds().intersects(green_goo.getGlobalBounds()))) {
            watergirl.setPosition(Vector2f(-2000, 33330));
            backgroundMusic.pause();
            death_sound.play();
        }

        // retry
        if (Keyboard::isKeyPressed(Keyboard::Key::R)) {
            fireboy.setPosition(Vector2f(0, 0));
            watergirl.setPosition(Vector2f(77, 1110));
        }

        // exit when esc is pressed
        if (Keyboard::isKeyPressed(Keyboard::Key::Escape)) {
            window.close();
        }
        ground[4].setPosition(Vector2f(-2, -200));


        //lever adjustments
        if ((fireboy.getGlobalBounds().intersects(lvr.getGlobalBounds())) || (watergirl.getGlobalBounds().intersects(lvr.getGlobalBounds())))
        {
            if (((fireboy.getGlobalBounds().intersects(stlvr.getGlobalBounds())) && (!lvr.getGlobalBounds().intersects(endlvr.getGlobalBounds()))) ||
                ((watergirl.getGlobalBounds().intersects(stlvr.getGlobalBounds())) && (!lvr.getGlobalBounds().intersects(endlvr.getGlobalBounds()))))

            {
                lvr.rotate(-90);
            }


        }
        if ((fireboy.getGlobalBounds().intersects(lvr.getGlobalBounds())) || (watergirl.getGlobalBounds().intersects(lvr.getGlobalBounds())))
        {
            if (((fireboy.getGlobalBounds().intersects(endlvr.getGlobalBounds())) && (!lvr.getGlobalBounds().intersects(stlvr.getGlobalBounds()))) ||
                ((watergirl.getGlobalBounds().intersects(endlvr.getGlobalBounds())) && (!lvr.getGlobalBounds().intersects(stlvr.getGlobalBounds()))))

            {
                lvr.rotate(90);
            }


        }





        //elev2 implements
        if (((lvr.getGlobalBounds().intersects(endlvr.getGlobalBounds()))) && ((!elevator2.getGlobalBounds().intersects(ENDelv2.getGlobalBounds()))))


        {
            elevator2.move(0, 2);

        }

        if (((lvr.getGlobalBounds().intersects(stlvr.getGlobalBounds()))) && ((!elevator2.getGlobalBounds().intersects(STRTelv2.getGlobalBounds()))))
        {
            elevator2.move(0, -2);
        }
        if (((lvr.getGlobalBounds().intersects(stlvr.getGlobalBounds()))) && ((fireboy.getGlobalBounds().intersects(elevator2.getGlobalBounds()))))
        {
            fireboy.move(0, -2);
        }
        if (((lvr.getGlobalBounds().intersects(stlvr.getGlobalBounds()))) && ((watergirl.getGlobalBounds().intersects(elevator2.getGlobalBounds()))))
        {
            watergirl.move(0, -2);
        }

        //////buttons implements//////         
        if (((fireboy.getGlobalBounds().intersects(butt1.getGlobalBounds())) || (fireboy.getGlobalBounds().intersects(butt2.getGlobalBounds()))) || ((watergirl.getGlobalBounds().intersects(butt1.getGlobalBounds())) || (watergirl.getGlobalBounds().intersects(butt2.getGlobalBounds())))) {
            if (!elevator1.getGlobalBounds().intersects(ENDelv1.getGlobalBounds())) {

                elevator1.move(0, 2);
            }
        }
        if (((!fireboy.getGlobalBounds().intersects(butt1.getGlobalBounds())) && (!fireboy.getGlobalBounds().intersects(butt2.getGlobalBounds()))) && ((!watergirl.getGlobalBounds().intersects(butt1.getGlobalBounds())) && (!watergirl.getGlobalBounds().intersects(butt2.getGlobalBounds())))) {
            if (!elevator1.getGlobalBounds().intersects(STRTelv1.getGlobalBounds())) {

                elevator1.move(0, -2);
            }
        }

        //fireboy move up with elev 1 //
        if (fireboy.getGlobalBounds().intersects(elevator1.getGlobalBounds())) {
            fireboy.move(0, -2);
        }
        //fireboy move down with elev 1 //
        if (fireboy.getGlobalBounds().intersects(elevator1.getGlobalBounds())) {
            fireboy.move(0, 2);
        }
        //fireboy move up with elev 2 //
        if (fireboy.getGlobalBounds().intersects(elevator2.getGlobalBounds())) {
            fireboy.move(0, -2);
        }
        //fireboy move down with elev 2 //
        if (fireboy.getGlobalBounds().intersects(elevator2.getGlobalBounds())) {
            fireboy.move(0, 2);
        }


        //watergirl move up with elev 1 //
        if (fireboy.getGlobalBounds().intersects(elevator2.getGlobalBounds())) {
            fireboy.move(0, -2);
        }
        //watergirl move down with elev 1 //
        if (fireboy.getGlobalBounds().intersects(elevator2.getGlobalBounds())) {
            fireboy.move(0, 2);
        }
        //watergirl move up with elev 2 //
        if (fireboy.getGlobalBounds().intersects(elevator2.getGlobalBounds())) {
            fireboy.move(0, -2);
        }
        //watergirl move down with elev 2 //
        if (fireboy.getGlobalBounds().intersects(elevator2.getGlobalBounds())) {
            fireboy.move(0, 2);
        }






        //lever never touch
        if ((fireboy.getGlobalBounds().intersects(lvr.getGlobalBounds())) || (watergirl.getGlobalBounds().intersects(lvr.getGlobalBounds()))) {
            if ((fireboy.getGlobalBounds().intersects(lvr.getGlobalBounds())) && ((fireboy.getGlobalBounds().intersects(endlvr.getGlobalBounds())))) {
                fireboy.move(-2, 0);
            }

        }
        if ((fireboy.getGlobalBounds().intersects(lvr.getGlobalBounds())) || (watergirl.getGlobalBounds().intersects(lvr.getGlobalBounds()))) {
            if ((fireboy.getGlobalBounds().intersects(lvr.getGlobalBounds())) && ((fireboy.getGlobalBounds().intersects(stlvr.getGlobalBounds())))) {
                fireboy.move(2, 0);
            }

        }
        if ((fireboy.getGlobalBounds().intersects(lvr.getGlobalBounds())) || (watergirl.getGlobalBounds().intersects(lvr.getGlobalBounds()))) {
            if ((watergirl.getGlobalBounds().intersects(lvr.getGlobalBounds())) && ((watergirl.getGlobalBounds().intersects(endlvr.getGlobalBounds())))) {
                watergirl.move(-2, 0);
            }

        }
        if ((fireboy.getGlobalBounds().intersects(lvr.getGlobalBounds())) || (watergirl.getGlobalBounds().intersects(lvr.getGlobalBounds()))) {
            if ((watergirl.getGlobalBounds().intersects(lvr.getGlobalBounds())) && ((watergirl.getGlobalBounds().intersects(stlvr.getGlobalBounds())))) {
                watergirl.move(2, 0);
            }

        }




        // drawing
        {
            window.clear();
            window.draw(backgroundPic);
            window.draw(lvr);
            window.draw(butt1);

            //window.draw(right_wall);
          //  window.draw(left_wall);
          //  for (int i = 0; i < 29; i++) {
                //ground[i].setFillColor(Color(255, 255, 255));

           //     window.draw(ground[i]);
           // }
            window.draw(lava);
            window.draw(lake);

            window.draw(stlvr);
            window.draw(endlvr);

            window.draw(elevator1);
            window.draw(STRTelv1);
            window.draw(ENDelv1);
            window.draw(butt2);
            window.draw(elevator2);
            window.draw(STRTelv2);
            window.draw(ENDelv2);

            window.draw(green_goo);
            window.draw(redDiamond1);
            window.draw(redDiamond2);
            window.draw(redDiamond3);
            window.draw(redDiamond4);
            window.draw(blueDiamond1);
            window.draw(blueDiamond2);
            window.draw(blueDiamond3);
            window.draw(blueDiamond4);
            window.draw(fireboy);
            window.draw(watergirl);
            window.draw(timeText);
           // window.draw(roof);
            window.display();
        }
    }
}bool doesIntersect(Sprite& player, RectangleShape ground[]) {
    for (int i = 0; i < 29; i++) {
        if (player.getGlobalBounds().intersects(ground[i].getGlobalBounds())) {
            // Check if the bottom side of the player sprite intersects with the top side of the ground rectangle
            if (player.getPosition().y + player.getGlobalBounds().height >= ground[i].getPosition().y &&
                player.getPosition().y + player.getGlobalBounds().height <= ground[i].getPosition().y + ground[i].getGlobalBounds().height &&
                player.getPosition().x + player.getGlobalBounds().width > ground[i].getPosition().x &&
                player.getPosition().x < ground[i].getPosition().x + ground[i].getGlobalBounds().width) {
                return true;
            }/*
            // Check if the top side of the player sprite intersects with the bottom side of the ground rectangle
            if (player.getPosition().y <= ground[i].getPosition().y + ground[i].getGlobalBounds().height &&
                player.getPosition().y + player.getGlobalBounds().height >= ground[i].getPosition().y + ground[i].getGlobalBounds().height &&
                player.getPosition().x + player.getGlobalBounds().width > ground[i].getPosition().x &&
                player.getPosition().x < ground[i].getPosition().x + ground[i].getGlobalBounds().width-10) {
                fireboy_Vy=0;
                //player.setPosition(player.getPosition().x, player.getPosition().y + 3);

            }*/
        }
    }
    return false;
}




void Fmove(Sprite& fireboy, RectangleShape& rWall, RectangleShape& lWall,
    RectangleShape ground[],RectangleShape& roof)
{

    // Check if the top side of the player sprite intersects with the bottom side of the roof rectangle
   
    if (fireboy.getGlobalBounds().intersects(roof.getGlobalBounds()))
    {
        fireboy.setPosition(fireboy.getPosition().x, roof.getPosition().y + 10);
    }

    // to the right
    if ((Keyboard::isKeyPressed(Keyboard::Key::Right)) &&
        (!fireboy.getGlobalBounds().intersects(rWall.getGlobalBounds()))) {
        fireboy.move(0.5f, 0.0f);
        a++;
        if (a % 50 == 0) {
            x++;
        }
        y = 0;
        x = x % 5;
        fireboy.setTextureRect(sf::IntRect(x * 113, y * 95, 95, 95));
    }
    // to the left
    if (Keyboard::isKeyPressed(Keyboard::Key::Left) &&
        (!fireboy.getGlobalBounds().intersects(lWall.getGlobalBounds()))) {
        fireboy.move(-0.7f, 0.0f);
        a++;
        if (a % 50 == 0) {
            x++;
        }
        y = 1;
        x = x % 5;
        fireboy.setTextureRect(sf::IntRect(x * 113, y * 95, 100, 95));
    }
    // fireboy jumping
    if ((!doesIntersect(fireboy, ground))) {
        fireboy_Vy += gravity;
    }
    else {
        fireboy_Vy = 0;
    }
    if ((Keyboard::isKeyPressed(Keyboard::Key::Up)) &&
        (doesIntersect(fireboy, ground))) {
        fireboy_Vy = -0.9;
        a++;
        if (a % 50 == 0)
            x++;
        y = 2;
        x = x % 4;
        fireboy.setTextureRect(sf::IntRect(x * 113, y * 95, 100, 95));
    }
    // to the up
    fireboy.move(0, fireboy_Vy);
}

void Wmove(Sprite& watergirl, RectangleShape& rWall, RectangleShape& lWall,
    RectangleShape ground[], RectangleShape& roof) {

    if (watergirl.getGlobalBounds().intersects(roof.getGlobalBounds()))
    {
        watergirl.setPosition(watergirl.getPosition().x, roof.getPosition().y + 10);
    }
    // to the right
    if ((Keyboard::isKeyPressed(Keyboard::Key::D)) &&
        (!watergirl.getGlobalBounds().intersects(rWall.getGlobalBounds()))) {
        watergirl.move(0.5f, 0.0f);
        a++;
        if (a % 50 == 0) {
            x++;
        }
        y = 1;
        x = x % 5;
        watergirl.setTextureRect(sf::IntRect(x * 175, y * 133, 120, 120));
    }
    // to the left
    if ((Keyboard::isKeyPressed(Keyboard::Key::A)) &&
        (!watergirl.getGlobalBounds().intersects(lWall.getGlobalBounds()))) {
        watergirl.move(-0.5f, 0.0f);
        a++;
        if (a % 50 == 0) {
            x++;
        }
        y = 0;
        x = x % 5;
        watergirl.setTextureRect(sf::IntRect(x * 175, y * 133, 120, 120));
    }
    // watergirl jumping
    if ((!doesIntersect(watergirl, ground))) {
        watergirl_Vy += gravity;
    }
    else {
        watergirl_Vy = 0;
    }
    if ((Keyboard::isKeyPressed(Keyboard::Key::W)) &&
        (doesIntersect(watergirl, ground))) {
        watergirl_Vy = -0.9;
        a++;
        if (a % 50 == 0)
            x++;
        y = 2;
        x = x % 4;
        watergirl.setTextureRect(sf::IntRect(x * 175, y * 133, 120, 120));
    }
    // to the up
    watergirl.move(0, watergirl_Vy);
}