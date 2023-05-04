#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

using namespace sf;

void level1(RenderWindow& window);

int main() {
    RenderWindow window(VideoMode(1720, 1300), "Fireboy and Watergirl");
    
    Image icon;
    icon.loadFromFile("icon.png");
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
   
    level1(window);
    return 0;
}

//gravity
//slow computer: gravity =0.13 , moving speed = 3.5 , jumping =-5.5
//fast computer: gravity = 0.035 moving speed = 0.5 , jumping =-0.9
float gravity = 0.0035, fireboy_Vy = 0, watergirl_Vy = 0, box_Vy = 0;

// for animation
int x = 0, y = 0, a = 0,f = 0, g = 0;

bool doesIntersectElevator(Sprite& player, Sprite& elevator1, Sprite& elevator2);
void Fmove(Sprite& fireboy, RectangleShape& rWall, RectangleShape& rWall2, RectangleShape& rWall3,
    RectangleShape& lWall, RectangleShape& lWall2, RectangleShape ground[],RectangleShape& box, Sprite& elevator1, Sprite& elevator2,Event event);
void Wmove(Sprite& watergirl, RectangleShape& rWall, RectangleShape& rWall2, RectangleShape& rWall3,
    RectangleShape& lWall, RectangleShape& lWall2, RectangleShape ground[], RectangleShape& box, Sprite& elevator1, Sprite& elevator2, Event event);
void scaleFireboy(Sprite& sprite, const Vector2u& windowSize);
void scaleWatergirl(Sprite& sprite, const Vector2u& windowSize);
void scaleRectangles(sf::Vector2u windowSize, sf::RectangleShape ground[], int size);
void scaleRectangles(sf::Vector2u windowSize, sf::RectangleShape& ground);
void scaleBackground(Sprite& backgroundPic, const Vector2u& windowSize);
void scalePosition(float& xPos, float& yPos, const sf::RenderWindow& window);


void level1(RenderWindow& window)
{
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
    //backgroundMusic.play();
    
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

    //box
    RectangleShape box(Vector2f(60.0f, 60.0f));
    Texture boxtxt;
    box.setPosition(871.0F, 350.0F);
    boxtxt.loadFromFile("box.png");
    box.setTexture(&boxtxt);

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
    RectangleShape lava(Vector2f(118.f, 10.f));
    lava.setPosition(838.f, 1238.f);
    scaleRectangles(window.getSize(), lava);
   
    // creating lake
    RectangleShape lake(Vector2f(129.f, 10.f));
    lake.setPosition(1173.f, 1238.f);
     scaleRectangles(window.getSize(), lake);

    // creating green goo
    RectangleShape green_goo(Vector2f(105.f, 10.f));
    green_goo.setPosition(1105.f, 968.f);
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
        RectangleShape(Vector2f(10.f, 90.f)),
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
        ground[12].setPosition(190.f, 320.f);
        //floor4 straight right
        ground[13].setPosition(870.f, 330.f);
        //floor4 middle obstacle straight up
        ground[14].setPosition(590.f, 270.f);
        //floor4 top of square left
        ground[15].setPosition(0.f, 215.f);
        //floor4 width of square left
        ground[16].setPosition(160.f, 225.f); //small  left wall
        //floor4 middle obstacle left
        ground[17].setPosition(595.f, 290.f); //small right wall up
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

    //zatoona
    
    //button1
    RectangleShape butt1(Vector2f(18, 18));
    butt1.setPosition(Vector2f(463, 646));
    
    //button2 
    RectangleShape butt2(Vector2f(18, 18));
    butt2.setPosition(Vector2f(1311, 477));
   
    //LEVER 373, 1223
    Texture lever;
    lever.loadFromFile("lvr.png");
    RectangleShape lvr(Vector2f(20, 65));
    lvr.setTexture(&lever);
    lvr.setPosition(Vector2f(460, 886));
    lvr.setOrigin(Vector2f(lvr.getLocalBounds().width, lvr.getLocalBounds().height) / 1.05f);
    lvr.setRotation(45);
   
    ////starting position of the lever////
    RectangleShape stlvr(Vector2f(5, 40));
    stlvr.setPosition(Vector2f(479, 867));
    
    ////end position of the lever////
    RectangleShape endlvr(Vector2f(5, 40));
    endlvr.setPosition(Vector2f(417, 867));
    
    //Elevator1 // the right one with the buttons
    Texture elvv;
    elvv.loadFromFile("elev2.png");
    Sprite elevator1;
    elevator1.setTexture(elvv);
    elevator1.setPosition(Vector2f(1500, 553));
   
    //Elevator1 START fo2 
    RectangleShape STRTelv1(Vector2f(160, 5));
    STRTelv1.setPosition(1500, 533);
  
    //Elevator1   END t7t
    RectangleShape ENDelv1(Vector2f(160, 5));
    ENDelv1.setPosition(1500, 704);
   
    //ELEVATOR2 the left one with the lever
    Texture elv;
    elv.loadFromFile("elev1.png");
    Sprite elevator2;
    elevator2.setTexture(elv);
    elevator2.setPosition(Vector2f(37, 673));
   
    //Elevator 2 START FO2
    RectangleShape STRTelv2(Vector2f(160, 5));
    STRTelv2.setPosition(37, 673);
  
    //ELEVATOR2 END t7t
    RectangleShape ENDelv2(Vector2f(160, 5));
    ENDelv2.setPosition(37, 840);
    
    // making and editing fireboy
    Texture text;
    text.loadFromFile("fireboysheet.png");
    Sprite fireboy(text);
    fireboy.setTextureRect(sf::IntRect(5, 4 * 100, 85, 112));
    scaleFireboy(fireboy, window.getSize());
    
    // making and editing watergirl
    Texture texting;
    texting.loadFromFile("watergirlsheet.png");
    Sprite watergirl(texting);
    watergirl.setTextureRect(sf::IntRect(5, 4 * 130, 120, 120));
    scaleWatergirl(watergirl, window.getSize());
  
    //doors
    //fireboy door
	Texture bdtexture;
    bdtexture.loadFromFile("bdoor.png");
	Sprite bdoor(bdtexture);
	bdoor.setPosition(sf::Vector2f(1368.0f, 153.0f));
	bdoor.setTextureRect(sf::IntRect(0, 0, 110, 130));
    
    //watergirl door
	Texture gdtexture;
	gdtexture.loadFromFile("gdoor.png");
	Sprite gdoor(gdtexture);
	gdoor.setPosition(sf::Vector2f(1500.0f, 153.0f));
	gdoor.setTextureRect(sf::IntRect(0, 0, 110, 130));

	Clock clock;

    // main event
    Event ev;
    
    // Main Game loop
    while (window.isOpen()) {

        while (window.pollEvent(ev)) {
            if (ev.type == Event::Closed)
                window.close();
        }
       
        // stopwatch
        Time gameTime = gameClock.getElapsedTime();
        int minutes = gameTime.asSeconds() / 60;
        int temp = gameTime.asSeconds();
        int seconds = temp % 60;
        timeText.setString(std::to_string(minutes) + ":" +
            (seconds < 10 ? "0" : "") + std::to_string(seconds));
        
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

        // fireboy and watergirl death
        {
            if ((fireboy.getGlobalBounds().intersects(lake.getGlobalBounds())) ||
                (fireboy.getGlobalBounds().intersects(green_goo.getGlobalBounds()))) {
                fireboy.setPosition(Vector2f(-2000, 33330));
                backgroundMusic.pause();
                death_sound.play();
            }
            if ((watergirl.getGlobalBounds().intersects(lava.getGlobalBounds())) ||
                (watergirl.getGlobalBounds().intersects(green_goo.getGlobalBounds()))) {
                watergirl.setPosition(Vector2f(-2000, 33330));
                backgroundMusic.pause();
                death_sound.play();
            }
        }

        // retry
        {
            if (Keyboard::isKeyPressed(Keyboard::Key::R)) {
                fireboy.setPosition(Vector2f(77, 1140));
                watergirl.setPosition(Vector2f(78, 953));
                backgroundMusic.play();
               
            }
        }

        // exit when esc is pressed
        {
            if (Keyboard::isKeyPressed(Keyboard::Key::Escape)) {
                window.close();
            }
        }
        //zatoona
        
         //lever moving right and left
        {
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
        }

         //elevator2 moves with the lever
         {
             if (((lvr.getGlobalBounds().intersects(endlvr.getGlobalBounds()))) &&
                ((!elevator2.getGlobalBounds().intersects(ENDelv2.getGlobalBounds()))))
             {
                 elevator2.move(0, 0.5);
             }
             if (((lvr.getGlobalBounds().intersects(stlvr.getGlobalBounds()))) &&
                 ((!elevator2.getGlobalBounds().intersects(STRTelv2.getGlobalBounds()))))
             {
                 elevator2.move(0, -1);
                 if (doesIntersectElevator(fireboy, elevator1, elevator2))
                 {
                     fireboy.move(0, -1);
                 }
                 if (doesIntersectElevator(watergirl, elevator1, elevator2))
                 {
                     watergirl.move(0, -1);
                 }
             }
         }

         //elevator1 moves with the buttons
         {
             if ((((fireboy.getGlobalBounds().intersects(butt1.getGlobalBounds())) ||
                 (fireboy.getGlobalBounds().intersects(butt2.getGlobalBounds()))) ||
                 ((watergirl.getGlobalBounds().intersects(butt1.getGlobalBounds())) ||
                     (watergirl.getGlobalBounds().intersects(butt2.getGlobalBounds())))) &&
                 (!elevator1.getGlobalBounds().intersects(ENDelv1.getGlobalBounds())))
             {
                 elevator1.move(0, 0.5);
             }
             if (((!fireboy.getGlobalBounds().intersects(butt1.getGlobalBounds())) &&
                 (!fireboy.getGlobalBounds().intersects(butt2.getGlobalBounds()))) &&
                 ((!watergirl.getGlobalBounds().intersects(butt1.getGlobalBounds())) &&
                     (!watergirl.getGlobalBounds().intersects(butt2.getGlobalBounds()))) &&
                 (!elevator1.getGlobalBounds().intersects(STRTelv1.getGlobalBounds())))
             {
                 elevator1.move(0, -1);
                 if (doesIntersectElevator(fireboy, elevator1, elevator2))
                 {
                     fireboy.move(0, -1.5);
                 }
                 if (doesIntersectElevator(watergirl, elevator1, elevator2))
                 {
                     watergirl.move(0, -1.5);
                 }
             }
         }

         //sprites not walking through the lever
         {
             if ((fireboy.getGlobalBounds().intersects(lvr.getGlobalBounds())))
             {
                 if ((fireboy.getGlobalBounds().intersects(lvr.getGlobalBounds())) &&
                     ((fireboy.getGlobalBounds().intersects(endlvr.getGlobalBounds()))))
                 {
                     fireboy.move(-5, 0);
                 }
                 else if ((fireboy.getGlobalBounds().intersects(lvr.getGlobalBounds())) &&
                     ((fireboy.getGlobalBounds().intersects(stlvr.getGlobalBounds()))))
                 {
                     fireboy.move(5, 0);
                 }
             }
             if ((watergirl.getGlobalBounds().intersects(lvr.getGlobalBounds())))
             {
                 if ((watergirl.getGlobalBounds().intersects(lvr.getGlobalBounds())) &&
                     ((watergirl.getGlobalBounds().intersects(endlvr.getGlobalBounds()))))
                 {
                     watergirl.move(-5, 0);
                 }
                 else if ((watergirl.getGlobalBounds().intersects(lvr.getGlobalBounds())) &&
                     ((watergirl.getGlobalBounds().intersects(stlvr.getGlobalBounds()))))
                 {
                     watergirl.move(5, 0);
                 }

             }
         }

         // box
         {
             //box gravity
             if ((!box.getGlobalBounds().intersects(ground[14].getGlobalBounds())) &&
                 (!box.getGlobalBounds().intersects(ground[12].getGlobalBounds())))
             {
                 box_Vy += gravity;
             }
             else
             {
                 box_Vy = 0;
             }
             box.move(0, box_Vy);

             //box movements with fireboy
             if (Keyboard::isKeyPressed(Keyboard::Key::Right) &&
                 fireboy.getGlobalBounds().intersects(box.getGlobalBounds()) &&
                 !box.getGlobalBounds().intersects(ground[17].getGlobalBounds()) &&
                 (fireboy.getPosition().x < box.getPosition().x))
             {
                 box.move(0.5, 0);
             }
             else if (fireboy.getGlobalBounds().intersects(box.getGlobalBounds()) &&
                 !box.getGlobalBounds().intersects(ground[16].getGlobalBounds()) &&
                 Keyboard::isKeyPressed(Keyboard::Key::Left) &&
                 (fireboy.getPosition().x > box.getPosition().x))
             {
                 box.move(-0.5, 0);
             }

             //box movements with watergirl
             if (Keyboard::isKeyPressed(Keyboard::Key::D) &&
                 watergirl.getGlobalBounds().intersects(box.getGlobalBounds()) &&
                 !box.getGlobalBounds().intersects(ground[17].getGlobalBounds()) &&
                 (watergirl.getPosition().x < box.getPosition().x))
             {
                 box.move(0.5, 0);
             }
             else if (watergirl.getGlobalBounds().intersects(box.getGlobalBounds()) &&
                 !box.getGlobalBounds().intersects(ground[16].getGlobalBounds()) &&
                 Keyboard::isKeyPressed(Keyboard::Key::A) &&
                 (watergirl.getPosition().x > box.getPosition().x))
             {
                 box.move(-0.5, 0);
             }

         }

         // fireboy moving function
         Fmove(fireboy, right_wall, ground[1], ground[17], left_wall ,ground[16], ground, box, elevator1, elevator2,ev);
         
         // watergirl moving function
         Wmove(watergirl, right_wall, ground[1], ground[17], left_wall, ground[16], ground,box, elevator1, elevator2,ev);

         //doors mechanism
         {
             if (fireboy.getGlobalBounds().intersects(bdoor.getGlobalBounds())) {

                 if (f < 8) {
                     if (clock.getElapsedTime().asSeconds() >= 0.15) {
                         f++;
                         clock.restart();
                     }

                     bdoor.setTextureRect(sf::IntRect(0, f * 173, 110, 130));
                 }

             }
             if (watergirl.getGlobalBounds().intersects(gdoor.getGlobalBounds())) {

                 if (g < 8) {
                     if (clock.getElapsedTime().asSeconds() >= 0.15) {
                         g++;
                         clock.restart();
                     }
                     gdoor.setTextureRect(sf::IntRect(0, g * 158, 110, 130));
                 }

             }
         }

         //winnig 
         {
             if (fireboy.getGlobalBounds().intersects(bdoor.getGlobalBounds()) &&
                 watergirl.getGlobalBounds().intersects(gdoor.getGlobalBounds()) &&
                 f == 8 && g == 8)
             {
                 fireboy.setPosition(-100, 0);
                 watergirl.setPosition(-100, 0);
                 window.close();
             }
         }

         // drawing
         { 
                window.clear();
                window.draw(backgroundPic);
                window.draw(lvr); 
                window.draw(elevator1); 
                window.draw(elevator2); 
                window.draw(box);
                window.draw(redDiamond1);
                window.draw(redDiamond2);
                window.draw(redDiamond3);
                window.draw(redDiamond4);
                window.draw(blueDiamond1);
                window.draw(blueDiamond2);
                window.draw(blueDiamond3);
                window.draw(blueDiamond4);
				window.draw(bdoor);
				window.draw(gdoor);
                window.draw(fireboy);
                window.draw(watergirl);
                window.draw(timeText);
                window.display();
            }
    }
}

bool doesIntersectElevator(Sprite& player, Sprite& elevator1, Sprite& elevator2) {

    // checking for collision with the right elevator
    if (player.getPosition().y + player.getGlobalBounds().height >= elevator1.getPosition().y &&
        player.getPosition().y + player.getGlobalBounds().height <= elevator1.getPosition().y + elevator1.getGlobalBounds().height &&
        player.getPosition().x + player.getGlobalBounds().width > elevator1.getPosition().x &&
        player.getPosition().x < elevator1.getPosition().x + elevator1.getGlobalBounds().width)
    {
        return true;
    }
    // checking for collision with the left elevator
    else if (player.getPosition().y + player.getGlobalBounds().height >= elevator2.getPosition().y &&
             player.getPosition().y + player.getGlobalBounds().height <= elevator2.getPosition().y + elevator2.getGlobalBounds().height &&
             player.getPosition().x + player.getGlobalBounds().width > elevator2.getPosition().x &&
             player.getPosition().x < elevator2.getPosition().x + elevator2.getGlobalBounds().width)
    {
        return true;
    }  
    return false;
}

bool doesIntersect(Sprite& player, RectangleShape ground[],RectangleShape& box) {
   // checking for collision with the box
    if (player.getPosition().y + player.getGlobalBounds().height >= box.getPosition().y &&
        player.getPosition().y + player.getGlobalBounds().height <= box.getPosition().y + box.getGlobalBounds().height &&
        player.getPosition().x + player.getGlobalBounds().width > box.getPosition().x &&
        player.getPosition().x < box.getPosition().x + box.getGlobalBounds().width)
    {
        return true;
    }
    for (int i = 0; i < 29; i++) {
        if (player.getGlobalBounds().intersects(ground[i].getGlobalBounds())&& i!=1 && i != 16 && i != 17) {
            // Check if the bottom side of the player sprite intersects with the top side of the ground rectangle
            if (player.getPosition().y + player.getGlobalBounds().height >= ground[i].getPosition().y &&
                player.getPosition().y + player.getGlobalBounds().height <= ground[i].getPosition().y + ground[i].getGlobalBounds().height &&
                player.getPosition().x + player.getGlobalBounds().width > ground[i].getPosition().x &&
                player.getPosition().x < ground[i].getPosition().x + ground[i].getGlobalBounds().width) {
                return true;
            }
        }
    }
    return false;
}

void Fmove(Sprite& fireboy, RectangleShape& rWall, RectangleShape& rWall2, RectangleShape& rWall3,
    RectangleShape& lWall, RectangleShape& lWall2, RectangleShape ground[],RectangleShape& box, Sprite& elevator1, Sprite& elevator2,Event event)
{
    if (event.type == sf::Event::KeyReleased)
    {
        if ((event.key.code == sf::Keyboard::Right) ||
            (event.key.code == sf::Keyboard::Left) ||
            fireboy_Vy==0)
        {
            fireboy.setTextureRect(sf::IntRect(5, 4 * 100, 85, 112));
        }
    }
    // Check if the top side of the player sprite intersects with the bottom side of the grounds
    for (int i = 0; i < 29; i++)
    {
        if (fireboy.getGlobalBounds().intersects(ground[i].getGlobalBounds()) && !doesIntersect(fireboy,ground,box) &&
            fireboy.getPosition().y>ground[i].getPosition().y
            && i != 1 && i != 2 && i != 3 && i != 16 && i != 17)
        {
            fireboy.setPosition(fireboy.getPosition().x, ground[i].getPosition().y + ground[i].getGlobalBounds().height);
            fireboy_Vy += gravity;
        }
    }
    // to the right
    if ((Keyboard::isKeyPressed(Keyboard::Key::Right)) &&
        (!fireboy.getGlobalBounds().intersects(rWall.getGlobalBounds())) &&
        (!fireboy.getGlobalBounds().intersects(rWall2.getGlobalBounds())) &&
        (!fireboy.getGlobalBounds().intersects(rWall3.getGlobalBounds())) &&
        !(fireboy.getGlobalBounds().intersects(box.getGlobalBounds()) && box.getGlobalBounds().intersects(rWall3.getGlobalBounds())))
    {
        fireboy.move(0.5f, 0.0f);
        a++;
        if (a % 30 == 0)
        {
            x++;
        }
        y = 0;
        x = x % 5;
        fireboy.setTextureRect(sf::IntRect(x * 113, y * 95, 95, 95));
    }
    // to the left
    if (Keyboard::isKeyPressed(Keyboard::Key::Left) &&
        (!fireboy.getGlobalBounds().intersects(lWall.getGlobalBounds())) &&
        (!fireboy.getGlobalBounds().intersects(lWall2.getGlobalBounds())) &&
        !(fireboy.getGlobalBounds().intersects(box.getGlobalBounds()) && box.getGlobalBounds().intersects(lWall2.getGlobalBounds())))
    {
        fireboy.move(-0.5f, 0.0f);
        a++;
        if (a % 30 == 0)
        {
            x++;
        }
        y = 1;
        x = x % 5;
        fireboy.setTextureRect(sf::IntRect(x * 113, y * 95, 100, 95));
    }
    // fireboy jumping
    if ((!doesIntersect(fireboy, ground,box)) && !doesIntersectElevator(fireboy,elevator1,elevator2)) {
        fireboy_Vy += gravity;
    }
    else {
        fireboy_Vy = 0;
    }
    if ((Keyboard::isKeyPressed(Keyboard::Key::Up)) &&
       ((doesIntersect(fireboy, ground,box)) ||
       doesIntersectElevator(fireboy, elevator1, elevator2)))
    {
        fireboy_Vy = -0.9f;
        a++;
        if (a % 40 == 0)
            x++;
        y = 2;
        x = x % 4;
        fireboy.setTextureRect(sf::IntRect(x * 113, y * 95, 100, 95));
    }
    a == 0;
    //upwards
    fireboy.move(0, fireboy_Vy);
    /*
    if ((fireboy_Vy>0)&& !doesIntersect(fireboy,ground,box)) {
        x++;
        y = 3;
        x = x % 4;
        fireboy.setTextureRect(sf::IntRect(x * 113, y * 95, 100, 95));
    }
    */
}

void Wmove(Sprite& watergirl, RectangleShape& rWall, RectangleShape& rWall2, RectangleShape& rWall3,
    RectangleShape& lWall, RectangleShape& lWall2, RectangleShape ground[], RectangleShape& box, Sprite& elevator1, Sprite& elevator2,Event event)
{
    
    if (event.type == sf::Event::KeyReleased)
    {
        if ((event.key.code == sf::Keyboard::D) ||
            (event.key.code == sf::Keyboard::A) ||
            watergirl_Vy==0)
        {
            watergirl.setTextureRect(sf::IntRect(5, 4 * 130, 120, 120));
        }
    }
    
    // Check if the top side of the player sprite intersects with the bottom side of the grounds
    for (int i = 0; i < 29; i++)
    {
        if (watergirl.getGlobalBounds().intersects(ground[i].getGlobalBounds()) && !doesIntersect(watergirl, ground, box) &&
            watergirl.getPosition().y > ground[i].getPosition().y
            && i != 1 && i != 2 && i != 3 && i != 16 && i != 17)
        {
            watergirl.setPosition(watergirl.getPosition().x, ground[i].getPosition().y + ground[i].getGlobalBounds().height);
            watergirl_Vy += gravity;
        }
    }

    // to the right
    if ((Keyboard::isKeyPressed(Keyboard::Key::D)) &&
        (!watergirl.getGlobalBounds().intersects(rWall.getGlobalBounds())) &&
        (!watergirl.getGlobalBounds().intersects(rWall2.getGlobalBounds())) &&
        (!watergirl.getGlobalBounds().intersects(rWall3.getGlobalBounds())) &&
        !(watergirl.getGlobalBounds().intersects(box.getGlobalBounds()) && box.getGlobalBounds().intersects(rWall3.getGlobalBounds()))) {
        watergirl.move(0.5f, 0.0f);
        a++;
        if (a % 30 == 0) {
            x++;
        }
        y = 1;
        x = x % 5;
        watergirl.setTextureRect(sf::IntRect(x * 175, y * 133, 120, 120));
    }
    // to the left
    if ((Keyboard::isKeyPressed(Keyboard::Key::A)) &&
        (!watergirl.getGlobalBounds().intersects(lWall.getGlobalBounds())) &&
        (!watergirl.getGlobalBounds().intersects(lWall2.getGlobalBounds()))&&
        !(watergirl.getGlobalBounds().intersects(box.getGlobalBounds()) && box.getGlobalBounds().intersects(lWall2.getGlobalBounds()))) {
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
    if ((!doesIntersect(watergirl, ground,box)) && 
       !doesIntersectElevator(watergirl, elevator1, elevator2)) {
        watergirl_Vy += gravity;
    }
    else {
        watergirl_Vy = 0;
    }
    if ((Keyboard::isKeyPressed(Keyboard::Key::W)) &&
       (doesIntersect(watergirl, ground,box) ||
       doesIntersectElevator(watergirl, elevator1, elevator2))) {
        watergirl_Vy = -0.9;
        a++;
        if (a % 30 == 0)
            x++;
        y = 2;
        x = x % 4;
        watergirl.setTextureRect(sf::IntRect(x * 175, y * 133, 120, 120));
    }
    // to the up
    watergirl.move(0, watergirl_Vy);


    /*
    if (watergirl_Vy > 0 && !doesIntersect(watergirl, ground, box)) {
        x++;
        y = 3;
        x = x % 2;
        watergirl.setTextureRect(sf::IntRect(x * 175, y * 130, 120, 120));
    }
	*/
}

void scaleFireboy(Sprite& sprite, const Vector2u& windowSize) {
    float xScale = (float)windowSize.x / 1720;
    float yScale = (float)windowSize.y / 1300;
    float xPos = 77 * xScale;
    float yPos = 1140 * yScale;
    sprite.setScale(0.85f * xScale, 0.85f * yScale);
    sprite.setPosition(xPos, yPos);
}
void scaleWatergirl(Sprite& sprite, const Vector2u& windowSize) {
    float xScale = (float)windowSize.x / 1720;
    float yScale = (float)windowSize.y / 1300;
    float xPos = 78 * xScale;
    float yPos = 953 * yScale;
    sprite.setScale(0.85f * xScale, 0.85f * yScale);
    sprite.setPosition(xPos, yPos);
}
void scaleRectangles(sf::Vector2u windowSize, sf::RectangleShape ground[], int size) {
    // Calculate the scaling factors for x and y axis
    float scaleX = (float)windowSize.x / 1210.f;
    float scaleY = (float)windowSize.y / 850.f;
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
    Vector2f position = ground.getPosition();
    Vector2f size = ground.getSize();
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
