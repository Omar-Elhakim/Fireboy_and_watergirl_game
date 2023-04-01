#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <iostream>

using namespace std;
using namespace sf;

int main() {

  // Main window
  RenderWindow window(VideoMode(1720, 1300), "Fireboy and Watergirl");
  Image icon;
  icon.loadFromFile("icon.png");
  window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

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
  backgroundPic.setPosition(Vector2f(-14, 10));

  // crating fireboy  diamonds
  Texture red1;
  red1.loadFromFile("redDiamond.png");
  // diamond1
  Sprite redDiamond1(red1);
  redDiamond1.setPosition(845.f, 1120.f);

  // diamond 2
  Sprite redDiamond2(red1);
  redDiamond2.setPosition(270.f, 550.f);

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
  blueDiamond1.setPosition(1200.f, 1120.f);

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
  left_wall.setPosition(37.f, 0);
  left_wall.setFillColor(Color(0, 0, 0));

  // right wall
  RectangleShape right_wall(Vector2f(10.f, 1800.f));
  right_wall.setPosition(1657.f, 0);
  right_wall.setFillColor(Color(0, 0, 0));

  // Creating grounds for each floor
  // ground floor
  RectangleShape ground1(Vector2f(1800.f, 10.f));
  ground1.setPosition(0.f, 1244.f);
  ground1.setFillColor(Color(0, 0, 0));

  // floor 1.5
  RectangleShape ground1_5(Vector2f(550.f, 10.f));
  ground1_5.setPosition(0.f, 1060.f);
  ground1_5.setFillColor(Color(0, 0, 0));

  // floor 1.7
  RectangleShape ground1_7(Vector2f(610.f, 10.f));
  ground1_7.setPosition(840.f, 968.f);
  ground1_7.setFillColor(Color(0, 0, 0));

  // floor 2
  RectangleShape ground2(Vector2f(758.f, 10.f));
  ground2.setPosition(0.f, 885.f);
  ground2.setFillColor(Color(0, 0, 0));

  // floor 2.8
  RectangleShape ground2_8(Vector2f(760.f, 10.f));
  ground2_8.setPosition(920.f, 710.f);
  ground2_8.setFillColor(Color(0, 0, 0));

  // floor 3
  RectangleShape ground3(Vector2f(660.f, 10.f));
  ground3.setPosition(223.f, 665.f);
  ground3.setFillColor(Color(0, 0, 0));

  // making and editing fireboy
  Texture text;
  text.loadFromFile("fireboysheet.png");
  Sprite fireboy(text);
  fireboy.setPosition(Vector2f(77, 1110));
  // fireboy.setScale(1.f, 1.f);
  fireboy.setTextureRect(sf::IntRect(0 * 113, 4 * 97, 100, 110));

  // making and editing watergirl
  Texture texting;
  texting.loadFromFile("watergirlsheet.png");
  Sprite watergirl(texting);
  watergirl.setPosition(Vector2f(78, 963));
  watergirl.setScale(1.f, 1.f);
  watergirl.setTextureRect(sf::IntRect(0 * 175, 4 * 133, 100, 90));

  // gravity
  float gravity = 0.003, fireboy_velocity_y = 0, watergirl_velocity_y = 0;

  // main event
  Event ev;

  // for animation
  int x = 0, y = 0, a = 0;
  // Main Game loop
  while (window.isOpen()) {
    while (window.pollEvent(ev)) {
      switch (ev.type) {
      case Event::Closed:
        window.close();
        break;
      }
    }
    // timer
    Time gameTime = gameClock.getElapsedTime();
    int minutes = gameTime.asSeconds() / 60;
    int temp = gameTime.asSeconds();
    int seconds = temp % 60;
    timeText.setString(std::to_string(minutes) + ":" +
                       (seconds < 10 ? "0" : "") + std::to_string(seconds));

    // fireboy movments
    // fireboy jumping
    if ((!fireboy.getGlobalBounds().intersects(ground1.getGlobalBounds()))) {
      fireboy_velocity_y += gravity;
    } else {
      fireboy_velocity_y = 0;
    }
    // to the up
    if ((Keyboard::isKeyPressed(Keyboard::Key::Up)) &&
        (fireboy.getGlobalBounds().intersects(ground1.getGlobalBounds()))) {
      fireboy_velocity_y = -0.9;
      a++;
      if (a % 50 == 0)
        x++;
      y = 2;
      x = x % 4;
      fireboy.setTextureRect(sf::IntRect(x * 113, y * 95, 100, 95));
    }
    fireboy.move(0, fireboy_velocity_y);

    // to the right
    if ((Keyboard::isKeyPressed(Keyboard::Key::Right)) &&
        (!fireboy.getGlobalBounds().intersects(right_wall.getGlobalBounds()))) {
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
        (!fireboy.getGlobalBounds().intersects(left_wall.getGlobalBounds()))) {
      fireboy.move(-0.7f, 0.0f);
      a++;
      if (a % 50 == 0)
        x++;
      y = 1;
      x = x % 5;
      fireboy.setTextureRect(sf::IntRect(x * 113, y * 95, 100, 95));
    }

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

    if ((fireboy.getGlobalBounds().intersects(lake.getGlobalBounds())) ||
        (fireboy.getGlobalBounds().intersects(green_goo.getGlobalBounds()))) {
      fireboy.setPosition(Vector2f(-2000, 33330));
      backgroundMusic.pause();
      death_sound.play();
    }
    // retry
    if (Keyboard::isKeyPressed(Keyboard::Key::R)) {
      fireboy.setPosition(Vector2f(77, 1110));
      watergirl.setPosition(Vector2f(77, 1110));
    }

    // watergirl movments
    // to the right
    if ((Keyboard::isKeyPressed(Keyboard::Key::D)) &&
        (!watergirl.getGlobalBounds().intersects(
            right_wall.getGlobalBounds()))) {
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
        (!watergirl.getGlobalBounds().intersects(
            left_wall.getGlobalBounds()))) {
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
    if ((!watergirl.getGlobalBounds().intersects(ground1.getGlobalBounds())) &&
        (!watergirl.getGlobalBounds().intersects(
            ground1_5.getGlobalBounds()))) {
      watergirl_velocity_y += gravity;
    } else {
      watergirl_velocity_y = 0;
    }

    if (Keyboard::isKeyPressed(Keyboard::Key::W) &&
        ((watergirl.getGlobalBounds().intersects(ground1.getGlobalBounds())) ||
         (watergirl.getGlobalBounds().intersects(
             ground1_5.getGlobalBounds())))) {
      watergirl_velocity_y = -0.9;
      a++;
      if (a % 50 == 0) {
        x++;
      }
      y = 2;
      x = x % 4;
      watergirl.setTextureRect(sf::IntRect(x * 175, y * 133, 120, 120));
    }

    watergirl.move(0, watergirl_velocity_y);
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

    // exit when esc is pressed
    if (Keyboard::isKeyPressed(Keyboard::Key::Escape)) {
      window.close();
    }

    // drawing
    {
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
      window.display();
    }
  }

  return 0;
}
