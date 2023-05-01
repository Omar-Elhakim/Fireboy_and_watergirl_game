// notes :-RenderWindow &window,RectangleShape &menu
// for increasing performance change Keyboard evnets handling in the menu
// functions to be like play function
// cause it's a nested loop unlike the level1 func.
// i changed the way the while loop work from while(window.isOpen()) to
// while (Menu.isActive) so i can close the loop without closing the window.
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window.hpp>
#include <ctime>
#include <iostream>

using namespace sf;

// defining important variables
//
// setting width and height
float width = 1210, height = 850;
// for animation
float gravity = 0.003, fireboy_Vy = 0, watergirl_Vy = 0;
int x = 0, y = 0, a = 0;
// getting the right coordinates to center Menu text
float getCenter(Text text) {
  return (width - text.getGlobalBounds().width) / 2;
}

struct Menu {
  bool isActive = false;
  // dynamic text array size but i won't make a dynamic array,
  // for using in moving functions.
  int size;
  Font font;
  Text mainmenu[4];
  int selected = 0;
  void draw(RenderWindow &window) {
    for (int i = 0; i < size; i++) {
      window.draw(mainmenu[i]);
    }
  }
  void MoveDown() {
    if (selected < size - 1) // not in exit (last option in the menu)
    {
      mainmenu[selected].setFillColor(Color::White);
      selected++;
      mainmenu[selected].setFillColor(Color{255, 204, 0});
    } else {
      mainmenu[selected].setFillColor(Color::White);
      selected = 0;
      mainmenu[selected].setFillColor(Color{255, 204, 0});
    }
  }
  void MoveUp() {
    if (selected > 0) // not in play (first option in the menu)
    {
      mainmenu[selected].setFillColor(Color::White);
      selected--;
      mainmenu[selected].setFillColor(Color{255, 204, 0});
    } else {
      mainmenu[selected].setFillColor(Color::White);
      selected = size - 1;
      mainmenu[selected].setFillColor(Color{255, 204, 0});
    }
  }
  void setSelected(int n) { selected = n; }
  int pressed() { return selected; }
  void setcharsize(int n) {
    for (int i = 0; i < size; i++) {
      mainmenu[i].setCharacterSize(n);
    }
  }

  void setTextPosition(int n) {
    for (int i = 0; i < size; i++) {
      mainmenu[i].setPosition(
          Vector2f(getCenter(mainmenu[i]), height / (4) + n * i));
    }
  }
  // big menu background
  Texture background;
  Sprite bg;
  void setbackgroud(Texture &background, Sprite &bg) {
    background.loadFromFile("TempleHallForest.png");
    bg.setTexture(background);
    bg.setScale(width / background.getSize().x,
                height / background.getSize().y);
  }

  // small menus background
  Texture sbackground;
  Texture GameNameForest;
  Sprite logo;
  Sprite smenu;
  void setsbackgroud() {
    sbackground.loadFromFile("smallmenuback.png");
    GameNameForest.loadFromFile("GameNameForest.png");
    smenu.setTexture(sbackground);
    logo.setTexture(GameNameForest);
    smenu.setScale(Vector2f(0.8, 0.8));
    logo.setPosition((width - GameNameForest.getSize().x) / 2, 50);
    smenu.setPosition((width - (sbackground.getSize().x * 0.8)) / 2,50 + GameNameForest.getSize().y);
  }
} menu, optionsMenu, pausemenu, losingmenu, winingmenu, creditesmenu;

// define some functions
void drawMenu(RenderWindow &window);
void drawOptoinsMenu(RenderWindow &window);
void drawPauseMenu(RenderWindow &window);
void drawLosingMenu(RenderWindow &window);
void drawWinningMenu(RenderWindow &window);
void drawCreditesMenu(RenderWindow &window);
void level1(RenderWindow &window);
void Fmove(Sprite &fireboy, RectangleShape &rWall, RectangleShape &lWall,
           RectangleShape ground[]);
void Wmove(Sprite &watergirl, RectangleShape &rWall, RectangleShape &lWall,
           RectangleShape ground[]);

int main() {
  // Main window
  RenderWindow window(VideoMode(width, height), "Fireboy and Watergirl");
  Image icon;
  icon.loadFromFile("icon.png");
  window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
  menu.isActive = true;
  drawMenu(window);
  return 0;
}

void drawMenu(RenderWindow &window) {
  // making menu options
  menu.font.loadFromFile("varsity_regular.ttf");
  menu.size = 4;

  menu.mainmenu[0].setFont(menu.font);
  menu.mainmenu[0].setFillColor(Color{204, 153, 0});
  menu.mainmenu[0].setString("Play");

  menu.mainmenu[1].setFont(menu.font);
  menu.mainmenu[1].setFillColor(Color::White);
  menu.mainmenu[1].setString("Options");

  menu.mainmenu[2].setFont(menu.font);
  menu.mainmenu[2].setFillColor(Color::White);
  menu.mainmenu[2].setString("Credits");

  menu.mainmenu[3].setFont(menu.font);
  menu.mainmenu[3].setFillColor(Color::White);
  menu.mainmenu[3].setString("Exit");

  menu.setcharsize(90);
  menu.setTextPosition(100);
  menu.setbackgroud(menu.background, menu.bg);

  while (menu.isActive && window.isOpen()) {
    Event event;
    while (window.pollEvent(event)) {
      if (event.type == Event::Closed) {
        window.close();
        break;
      } else if (event.type == Event::KeyPressed) {
        if (event.key.code == Keyboard::Up) {
          menu.MoveUp();
        }
        if (event.key.code == Keyboard::Down) {
          menu.MoveDown();
        }
      } else if (event.type == Event::KeyReleased) {
        if (event.key.code == Keyboard::Enter) {
          switch (menu.selected) {
          case 0:
            window.clear();
            menu.isActive = false;
            level1(window);
            break;
          case 1:
            window.clear();
            menu.setSelected(0);
            optionsMenu.isActive = true;
            menu.isActive = false;
            drawOptoinsMenu(window);
            break;
          case 2:
            break;
          case 3:
            window.close();
            break;
          }
        } else if (event.key.code == Keyboard::Escape) {
          window.close();
        }
      }
    }
    window.clear();
    window.draw(menu.bg);
    menu.draw(window);
    window.display();
  }
}

void level1(RenderWindow &window) {
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
  backgroundPic.setScale(0.7f, 0.65f);

  // crating fireboy  diamonds
  Texture red1;
  red1.loadFromFile("redDiamond.png");
  // diamond1
  Sprite redDiamond1(red1);
  redDiamond1.setPosition(700.f, 60.f);
  // diamond 2
  Sprite redDiamond2(red1);
  redDiamond2.setPosition(600.f, 550.f);
  // diamond 3
  Sprite redDiamond3(red1);
  redDiamond3.setPosition(400.f, 80.f);
  // diamond 4
  Sprite redDiamond4(red1);
  redDiamond4.setPosition(760.f, 160.f);

  // crating watergirl  diamonds
  Texture blue1;
  blue1.loadFromFile("blueDiamond.png");
  // diamond1
  Sprite blueDiamond1(blue1);
  blueDiamond1.setPosition(200.f, 300.f);
  // diamond2
  Sprite blueDiamond2(blue1);
  blueDiamond2.setPosition(980.f, 600.f);
  // diamond3
  Sprite blueDiamond3(blue1);
  blueDiamond3.setPosition(55.f, 210.f);
  // diamond4
  Sprite blueDiamond4(blue1);
  blueDiamond4.setPosition(940.f, 170.f);

  // creating lava
  RectangleShape lava(Vector2f(130.f, 10.f));
  lava.setPosition(830.f, 1238.f);
  lava.setFillColor(Color(255, 0, 0, 0));
  // creating lake
  RectangleShape lake(Vector2f(145.f, 10.f));
  lake.setPosition(1165.f, 1238.f);
  lake.setFillColor(Color(0, 0, 255, 0));
  // creating green goo
  RectangleShape green_goo(Vector2f(190.f, 10.f));
  green_goo.setPosition(1060.f, 968.f);
  green_goo.setFillColor(Color(0, 255, 0));
  // creating two walls
  // left wall
  RectangleShape left_wall(Vector2f(10.f, 1800.f));
  left_wall.setPosition(20.f, 0);
  left_wall.setFillColor(Color(255, 255, 255));
  // right wall
  RectangleShape right_wall(Vector2f(10.f, 1800.f));
  right_wall.setPosition(1180.f, 0);
  right_wall.setFillColor(Color(255, 255, 255));

  // Creating grounds for each floor
  RectangleShape ground[] = {
      // ground floor
      RectangleShape(Vector2f(1950.f, 10.f)),
      // groundright
      RectangleShape(Vector2f(10.f, 80.f)),
      RectangleShape(Vector2f(10.f, 35.f)),
      RectangleShape(Vector2f(40.f, 10.f)),
      // top
      RectangleShape(Vector2f(1950.f, 10.f)),
      // floor1
      RectangleShape(Vector2f(405.f, 30.f)),
      // floor2 straight right
      RectangleShape(Vector2f(450.f, 10.f)),
      // floor2 inclined
      RectangleShape(Vector2f(10.f, 70.f)),
      // floor2 straight left
      RectangleShape(Vector2f(540.f, 10.f)),
      // floor3 straight right
      RectangleShape(Vector2f(550.f, 10.f)),
      // floor3 inclined
      RectangleShape(Vector2f(10.f, 55.f)),
      // floor3 straight left
      RectangleShape(Vector2f(460.f, 10.f)),
      // floor4 straight left
      RectangleShape(Vector2f(400.f, 10.f)),
      // floor4 straight right
      RectangleShape(Vector2f(190.f, 10.f)),
      // floor4 middle obstacle straight up
      RectangleShape(Vector2f(225.f, 10.f)),
      // floor4 top of square left
      RectangleShape(Vector2f(155.f, 10.f)),
      // floor4 width of square left
      RectangleShape(Vector2f(10.f, 120.f)),
      // floor4 middle obstacle left
      RectangleShape(Vector2f(10.f, 50.f)),
      // floor4 middle obstacle incline
      RectangleShape(Vector2f(10.f, 75.f)),
      // floor5 middle straight
      RectangleShape(Vector2f(330.f, 10.f)),
      // floor5 straight right
      RectangleShape(Vector2f(220.f, 10.f)),
      // floor5 middle right incline
      RectangleShape(Vector2f(10.f, 55.f)),
      // floor5 middle left incline
      RectangleShape(Vector2f(10.f, 55.f)),
      // floor5 middle up straight
      RectangleShape(Vector2f(80.f, 10.f)),
      // floor5 left obstacle
      RectangleShape(Vector2f(10.f, 50.f)),
      RectangleShape(Vector2f(10.f, 50.f)),
      RectangleShape(Vector2f(20.f, 10.f)),
      RectangleShape(Vector2f(70.f, 10.f)),
      RectangleShape(Vector2f(10.f, 35.f)),
  };

  // ground floor
  ground[0].setPosition(0.f, 815.f);
  // groundright
  ground[1].setPosition(1090.f, 750.f);
  ground[2].setPosition(1115.f, 730.f);
  ground[2].setRotation(45);
  ground[3].setPosition(1125.f, 730.f);
  // top
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
  // floor3 straight right
  ground[9].setPosition(655.f, 470.f);
  // floor3 inclined
  ground[10].setPosition(610.f, 450.f);
  ground[10].setRotation(-45);
  // floor3 straight left
  ground[11].setPosition(160.f, 440.f);
  // floor4 straight left
  ground[12].setPosition(190.f, 330.f);
  // floor4 straight right
  ground[13].setPosition(870.f, 330.f);
  // floor4 middle obstacle straight up
  ground[14].setPosition(590.f, 270.f);
  // floor4 top of square left
  ground[15].setPosition(30.f, 215.f);
  // floor4 width of square left
  ground[16].setPosition(170.f, 215.f);
  // floor4 middle obstacle left
  ground[17].setPosition(595.f, 270.f);
  // floor4 middle obstacle incline
  ground[18].setPosition(810.f, 285.f);
  ground[18].setRotation(-45);
  // floor5 middle straight
  ground[19].setPosition(480.f, 185.f);
  // floor5 straight right
  ground[20].setPosition(960.f, 185.f);
  // floor5 middle right incline
  ground[21].setPosition(920.f, 160.f);
  ground[21].setRotation(-45);
  // floor5 middle left incline
  ground[22].setPosition(845.f, 150.f);
  ground[22].setRotation(45);
  // floor5 middle up straight
  ground[23].setPosition(850.f, 155.f);
  // floor5 left obstacle
  ground[24].setPosition(430.f, 165.f);
  ground[24].setRotation(-45);
  ground[25].setPosition(375.f, 130.f);
  ground[25].setRotation(-45);
  ground[26].setPosition(420.f, 155.f);
  ground[27].setPosition(310.f, 125.f);
  ground[28].setPosition(315.f, 120.f);
  ground[28].setRotation(45);
  for (int i = 0; i < 29; i++)
    ground[i].setFillColor(Color(255, 255, 255));
  // making and editing fireboy
  Texture text;
  text.loadFromFile("fireboysheet.png");
  Sprite fireboy(text);
  fireboy.setPosition(Vector2f(0, 0));
  fireboy.setScale(0.8f, 0.8f);
  fireboy.setTextureRect(sf::IntRect(0 * 113, 4 * 95, 105, 105));

  // making and editing watergirl
  Texture texting;
  texting.loadFromFile("watergirlsheet.png");
  Sprite watergirl(texting);
  watergirl.setPosition(Vector2f(100, 0));
  watergirl.setScale(0.5f, 0.5f);
  watergirl.setTextureRect(sf::IntRect(0 * 175, 4 * 133, 100, 90));

  // gravity
  float gravity = 0.003, fireboy_velocity_y = 0, watergirl_Vy = 0;

  // main event
  Event ev;

  int initialscnds = 0;
  int initialmnts = 0;
  // Main Game loop
  while (window.isOpen()) {
    while (window.pollEvent(ev)) {
      if (ev.type == Event::Closed) {
        window.close();
      }
    }

    if (!pausemenu.isActive) {
      // timer
      Time gameTime = gameClock.getElapsedTime();
      int minutes = gameTime.asSeconds() / 60;
      int temp = gameTime.asSeconds();
      int seconds = temp % 60;
      timeText.setString(std::to_string(minutes) + ":" +
                         (seconds < 10 ? "0" : "") + std::to_string(seconds));
      initialmnts = 0;
      initialscnds = 0;

      // move fireboy
      Fmove(fireboy, right_wall, left_wall, ground);

      // fireboy diamonds
      {
        if (fireboy.getGlobalBounds().intersects(
                redDiamond1.getGlobalBounds())) {
          redDiamond1.move(9999.f, 0.f);
          diamond_sound.play();
        }
        if (fireboy.getGlobalBounds().intersects(
                redDiamond2.getGlobalBounds())) {
          redDiamond2.move(9999.f, 0.f);
          diamond_sound.play();
        }
        if (fireboy.getGlobalBounds().intersects(
                redDiamond2.getGlobalBounds())) {
          redDiamond2.move(9999.f, 0.f);
          diamond_sound.play();
        }
        if (fireboy.getGlobalBounds().intersects(
                redDiamond3.getGlobalBounds())) {
          redDiamond3.move(9999.f, 0.f);
          diamond_sound.play();
        }
        if (fireboy.getGlobalBounds().intersects(
                redDiamond4.getGlobalBounds())) {
          redDiamond4.move(9999.f, 0.f);
          diamond_sound.play();
        }
      }

      // fireboy dying
      if ((fireboy.getGlobalBounds().intersects(lake.getGlobalBounds())) ||
          (fireboy.getGlobalBounds().intersects(green_goo.getGlobalBounds()))) {
        fireboy.setPosition(Vector2f(-2000, 33330));
        backgroundMusic.pause();
        death_sound.play();
      }

      // watergirl movments
      Wmove(watergirl, right_wall, left_wall, ground);

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
          (watergirl.getGlobalBounds().intersects(
              green_goo.getGlobalBounds()))) {
        watergirl.setPosition(Vector2f(-2000, 33330));
        backgroundMusic.pause();
        death_sound.play();
      }

      // retry
      if (Keyboard::isKeyPressed(Keyboard::Key::R)) {
        fireboy.setPosition(Vector2f(77, 1110));
        watergirl.setPosition(Vector2f(77, 1110));
        gameClock.restart();
      }

      // pause
      if (Keyboard::isKeyPressed(Keyboard::Key::P)) {
        initialscnds += seconds;
        initialmnts += minutes;
        pausemenu.isActive = true;
        gameClock.restart();
      }

      // exit when esc is pressed
      if (Keyboard::isKeyPressed(Keyboard::Key::Q)) {
        window.clear();
        menu.isActive = true;
        drawMenu(window);
      }
    } else {
      // if paused
      drawPauseMenu(window);
    }
    // drawing
    {
      window.clear();
      window.draw(backgroundPic);
      window.draw(right_wall);
      window.draw(left_wall);
      for (int i = 0; i < 29; i++) {
        window.draw(ground[i]);
      }
      window.draw(lava);
      window.draw(lake);
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
      // if (pausemenu.isActive) {
      //   window.draw(pausemenu.smenu);
      // }
      window.display();
    }
  }
}

bool doesIntersect(Sprite &player, RectangleShape ground[]) {
  bool state = false;
  for (int i = 0; i < 29; i++) {
    if ((player.getGlobalBounds().intersects(ground[i].getGlobalBounds())) &&
        (!player.getGlobalBounds().intersects(ground[4].getGlobalBounds()))) {
      state = true;
    }
  }
  return state;
}

void Fmove(Sprite &fireboy, RectangleShape &rWall, RectangleShape &lWall,
           RectangleShape ground[]) {
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
  } else {
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

void Wmove(Sprite &watergirl, RectangleShape &rWall, RectangleShape &lWall,
           RectangleShape ground[]) {
  // int x = 0, y = 0, a = 0;
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
  } else {
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

void drawOptoinsMenu(RenderWindow &window) {
  // making menu options
  optionsMenu.font.loadFromFile("varsity_regular.ttf");
  optionsMenu.size = 3;

  optionsMenu.mainmenu[0].setFont(menu.font);
  optionsMenu.mainmenu[0].setFillColor(Color{204, 153, 0});
  optionsMenu.mainmenu[0].setString("Music");

  optionsMenu.mainmenu[1].setFont(menu.font);
  optionsMenu.mainmenu[1].setFillColor(Color::White);
  optionsMenu.mainmenu[1].setString("EFX");

  optionsMenu.mainmenu[2].setFont(menu.font);
  optionsMenu.mainmenu[2].setFillColor(Color::White);
  optionsMenu.mainmenu[2].setString("Back");

  optionsMenu.setcharsize(90);
  optionsMenu.setTextPosition(200);
  optionsMenu.setbackgroud(optionsMenu.background, optionsMenu.bg);

  while (optionsMenu.isActive) {
    Event event;
    while (window.pollEvent(event)) {
      if (event.type == Event::Closed) {
        window.close();
        break;
      } else if (event.type == Event::KeyPressed) {
        if (event.key.code == Keyboard::Up) {
          optionsMenu.MoveUp();
        }
        if (event.key.code == Keyboard::Down) {
          optionsMenu.MoveDown();
        }
        if (event.key.code == Keyboard::Escape) {
          window.close();
        }
      } else if (event.type == Event::KeyReleased) {
        if (event.key.code == Keyboard::Enter) {
          switch (optionsMenu.selected) {
          case 0:
            // place holder for the music settings function
            break;
          case 1:
            // place holder for the EFX settings function
            break;
          case 2:
            window.clear();
            optionsMenu.setSelected(0);
            optionsMenu.isActive = false;
            menu.isActive = true;
            drawMenu(window);
            break;
          }
        }
      }
    }
    window.clear();
    window.draw(optionsMenu.bg);
    optionsMenu.draw(window);
    window.display();
  }
}

void drawPauseMenu(RenderWindow &window) {
  pausemenu.setsbackgroud();
  while (pausemenu.isActive) {
    if (Keyboard::isKeyPressed(Keyboard::Key::Escape)) {
      window.clear();
      pausemenu.isActive = false;
    }
    window.draw(pausemenu.smenu);
    window.draw(pausemenu.logo);
    window.display();
  }
}
