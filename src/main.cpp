#include "config.h"

bool exitMaze = false;
bool startScreen = true;  // start screen flag
bool showScores = false;
int mapCount = 0;

int worldMap[mapWidth][mapHeight];

// variables for tile colors, easy to find and edit here
sf::Color playerColor(230, 57, 70);
sf::Color playerOutlineColor(0, 0, 0);

// player name
std::string playerName;

// outfile
std::string fileName = "playerData.bin";

// obstacle colors
sf::Color wallColor(69, 123, 157);
sf::Color exitColor(168, 218, 220);

// background color
sf::Color bgColor(241, 250, 238);

// grid lines
sf::Color gridLines(29, 53, 87, 30);  // alpha channel is transparency 30

// load textures from a file
sf::Texture loadTexture(const std::string& filePath) {
  sf::Texture texture;
  if (!texture.loadFromFile(filePath)) {
    std::cerr << "Failed to load texture: " << filePath << std::endl;
  }
  return texture;
}

int main() {
  int width = 528, height = 528;
  int playerPosX = 0;
  int playerPosY = 0;

  int posX = 2, posY = 1;

  // load exit wall texture
  sf::Texture exitTexture = loadTexture("assets/Exit.jpg");

  // load font
  sf::Font font;
  if (!font.loadFromFile("assets/Kanit-Light.ttf")) {
    std::cerr << "Failed to load default font " << std::endl;
  }

  sf::RenderWindow window(sf::VideoMode(width, height), "Maze Race");
  window.setFramerateLimit(60);

  sf::Clock clock;
  sf::Clock moveClock;       // clock to control player movement speed
  sf::Clock countdownClock;  // clock for the countdown timer

  // set countdown duration to 1 minute
  sf::Time countdownDuration = sf::seconds(60);

  mapRandomizer(worldMap);

  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) window.close();
      if (event.type == sf::Event::KeyPressed &&
          event.key.code == sf::Keyboard::Escape)
        window.close();
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) showScores = true;
      if (event.type == sf::Event::KeyPressed &&
          event.key.code == sf::Keyboard::Enter && !exitMaze) {
        // movement logic
        if (!exitMaze) {
          startScreen = true;  // start screen flag
        }
      }
    }

    if (startScreen) {
      RenderStartScreen(window, startScreen, bgColor, playerName);
    } else {
      if (moveClock.getElapsedTime().asMilliseconds() >
          60) {  // move player every 60ms
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
          if (playerPosY > 0 && worldMap[playerPosY - 1][playerPosX] != 1) {
            playerPosY--;
          }
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
          if (playerPosY < mapHeight - 1 &&
              worldMap[playerPosY + 1][playerPosX] != 1) {
            playerPosY++;
          }
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
          if (playerPosX > 0 && worldMap[playerPosY][playerPosX - 1] != 1) {
            playerPosX--;
          }
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
          if (playerPosX < mapWidth - 1 &&
              worldMap[playerPosY][playerPosX + 1] != 1) {
            playerPosX++;
          }
        }

        moveClock.restart();  // restart move clock
      }

      // clear window with bgcolor
      window.clear(bgColor);

      mazeMap(window, playerPosX, playerPosY, width, height, exitTexture);

      if (worldMap[playerPosY][playerPosX] == 2) {
        mapRandomizer(worldMap);
        mapCount++;
      }

      // mapCounts display
      sf::Text mapCountText;
      mapCountText.setFont(font);
      mapCountText.setCharacterSize(18);
      mapCountText.setFillColor(playerColor);
      mapCountText.setStyle(sf::Text::Bold);

      // update text string
      mapCountText.setString("Map Count: " + std::to_string(mapCount));

      // position in right corner
      sf::FloatRect textRect = mapCountText.getLocalBounds();
      mapCountText.setOrigin(textRect.width, 0);  // origin to top-right
      mapCountText.setPosition(window.getSize().x - 5,
                               5);  // top-right corner

      // semi-transparent background box
      sf::RectangleShape backgroundBox;
      backgroundBox.setSize(
          sf::Vector2f(textRect.width + 10, textRect.height + 10));  // padding
      backgroundBox.setFillColor(
          sf::Color(255, 255, 255, 128));  // color with 50% transparency
      backgroundBox.setPosition(
          mapCountText.getPosition().x - textRect.width - 5,
          mapCountText.getPosition().y - 5);  // position based on padding

      // countdown timer display
      sf::Time elapsedTime = countdownClock.getElapsedTime();
      sf::Time remainingTime = countdownDuration - elapsedTime;
      if (remainingTime.asSeconds() <= 0) {
        showScores = true;  // trigger end screen if time runs out
      }

      sf::Text countdownText;
      countdownText.setFont(font);
      countdownText.setCharacterSize(18);
      countdownText.setFillColor(playerColor);
      countdownText.setStyle(sf::Text::Bold);

      int seconds = static_cast<int>(remainingTime.asSeconds());
      countdownText.setString("Time: " + std::to_string(seconds) + "s");

      sf::FloatRect countdownRect = countdownText.getLocalBounds();
      countdownText.setOrigin(countdownRect.width, 0);  // origin to top-right
      countdownText.setPosition(window.getSize().x - 5,
                                25);  // below map count display

      // draw background box and text
      window.draw(backgroundBox);
      window.draw(mapCountText);
      window.draw(countdownText);
      window.display();

      if (showScores) {
        // save player score
        savePlayerScore(playerName, mapCount, fileName);
        // show high scores
        highScores(window, showScores, bgColor, fileName);
      }

      if (exitMaze) {
        window.close();
      }
    }
  }

  return EXIT_SUCCESS;
}
