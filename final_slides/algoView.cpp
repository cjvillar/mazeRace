/*

visualization for DFS algo.

g++ -std=c++17 -Wall -I./dependencies/include -L/usr/local/lib
 -lsfml-graphics -lsfml-window -lsfml-system -o algoView algoView.cpp

 */
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <stack>
#include <utility>
#include <vector>

#include "../dependencies/include/SFML/Graphics.hpp"

int windowWidth = 528, windowHeight = 528;

const int mapWidth = 24;
const int mapHeight = 24;
// const int tileSize = 15;

float scaleTilesize = 1;  // tile size scale
int tileSizeX = (windowWidth / mapWidth) * scaleTilesize;
int tileSizeY = (windowHeight / mapHeight) * scaleTilesize;

int offsetX = (windowWidth - tileSizeX * mapWidth) / 2;
int offsetY = (windowHeight - tileSizeY * mapHeight) / 2;

float tileScale = 1.0f;

// obstacle colors
sf::Color wallColor(69, 123, 157);
// background color
sf::Color bgColor(241, 250, 238);
// grid line color
sf::Color gridLines(29, 53, 87, 30);

void drawMap(sf::RenderWindow& window, int worldMap[][mapHeight]) {
  window.clear(bgColor);

  for (int y = 0; y < mapHeight; ++y) {
    for (int x = 0; x < mapWidth; ++x) {
      // sf::RectangleShape tile(sf::Vector2f(tileSize, tileSize));
      sf::RectangleShape tile(
          sf::Vector2f(tileSizeX * tileScale, tileSizeY * tileScale));
      tile.setPosition(offsetX + x * tileSizeX, offsetY + y * tileSizeY);
      // tile.setPosition(x * tileSize, y * tileSize);

      if (worldMap[x][y] == 1) {
        tile.setFillColor(wallColor);  // Wall
      } else if (worldMap[x][y] == 0) {
        tile.setFillColor(bgColor);  // Path
      } else if (worldMap[x][y] == 2) {
        tile.setFillColor(sf::Color::Red);  // Exit
      }

      window.draw(tile);
    }
  }

  // draw grid lines
  for (int y = 0; y <= mapHeight; y++) {
    sf::RectangleShape line(
        sf::Vector2f(windowWidth, 1));  // 1 is grid line thickness
    line.setFillColor(gridLines);       // gridline Y
    line.setPosition(0, offsetY + y * tileSizeY);
    window.draw(line);
  }
  for (int x = 0; x <= mapWidth; x++) {
    sf::RectangleShape line(
        sf::Vector2f(1, windowHeight));  // 1 is grid line thickness
    line.setFillColor(gridLines);        // gridline X
    line.setPosition(offsetX + x * tileSizeX, 0);
    window.draw(line);
  }

  window.display();
}

void mapRandomizer(int worldMap[][mapHeight], sf::RenderWindow& window) {
  // init map with walls (1)
  for (int y = 0; y < mapHeight; ++y) {
    for (int x = 0; x < mapWidth; ++x) {
      worldMap[x][y] = 1;
    }
  }

  int visitedTiles = 0;
  std::stack<std::pair<int, int>> vtStack;

  // init algorithm with the first tile (0, 0) aka player start origin
  vtStack.push(std::make_pair(0, 0));
  worldMap[0][0] = 0;

  srand(static_cast<unsigned int>(time(0)));  // rand num seed
  std::pair<int, int> lastVisitedTile(0, 0);

  while (!vtStack.empty()) {
    std::vector<int> neighbors;

    int x = vtStack.top().first;
    int y = vtStack.top().second;

    // check north neighbor
    if (y > 1 && worldMap[x][y - 2] == 1) neighbors.push_back(0);
    // check east neighbor
    if (x < mapWidth - 2 && worldMap[x + 2][y] == 1) neighbors.push_back(1);
    // check south neighbor
    if (y < mapHeight - 2 && worldMap[x][y + 2] == 1) neighbors.push_back(2);
    // check west neighbor
    if (x > 1 && worldMap[x - 2][y] == 1) neighbors.push_back(3);

    // check for available neighbors
    if (!neighbors.empty()) {
      // randomly choose a neighbor
      int nextTileDirection = neighbors[rand() % neighbors.size()];

      switch (nextTileDirection) {
        case 0:  // North
          worldMap[x][y - 1] = 0;
          worldMap[x][y - 2] = 0;
          vtStack.push(std::make_pair(x, y - 2));
          lastVisitedTile = std::make_pair(x, y - 2);
          break;
        case 1:  // East
          worldMap[x + 1][y] = 0;
          worldMap[x + 2][y] = 0;
          vtStack.push(std::make_pair(x + 2, y));
          lastVisitedTile = std::make_pair(x + 2, y);
          break;
        case 2:  // South
          worldMap[x][y + 1] = 0;
          worldMap[x][y + 2] = 0;
          vtStack.push(std::make_pair(x, y + 2));
          lastVisitedTile = std::make_pair(x, y + 2);
          break;
        case 3:  // West
          worldMap[x - 1][y] = 0;
          worldMap[x - 2][y] = 0;
          vtStack.push(std::make_pair(x - 2, y));
          lastVisitedTile = std::make_pair(x - 2, y);
          break;
      }
      ++visitedTiles;

      // draw the map after each step
      drawMap(window, worldMap);
      sf::sleep(
          sf::milliseconds(40));  // slow down the drawing for visualization
    } else {
      // no neighbors backtrack
      vtStack.pop();
    }
  }

  // exit tile
  worldMap[lastVisitedTile.first][lastVisitedTile.second] = 2;
  drawMap(window, worldMap);
}

int main() {
  sf::RenderWindow window(
      // sf::VideoMode(mapWidth * tileSize, mapHeight * tileSize),
      sf::VideoMode(windowWidth, windowHeight), "Map Randomizer (DFS)");
  int worldMap[mapWidth][mapHeight];

  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
      }
    }

    mapRandomizer(worldMap, window);
    sf::sleep(sf::milliseconds(1000));  // pause for 1 sec
  }

  return 0;
}
