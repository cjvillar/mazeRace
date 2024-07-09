#include "mazeMap.h"

extern int worldMap[mapWidth][mapHeight];
extern sf::Color wallColor;
extern sf::Color exitColor;
extern sf::Color bgColor;
extern sf::Color gridLines;

void mazeMap(sf::RenderWindow &window, int playerPosX, int playerPosY,
            int windowWidth, int windowHeight,
             sf::Texture exitTexture) {
  float scaleTilesize = 1;  // tile size scale
  int tileSizeX = (windowWidth / mapWidth) * scaleTilesize;
  int tileSizeY = (windowHeight / mapHeight) * scaleTilesize;

  float tileScale = 1.0f;
  float playerScale = 1.0f;

  int offsetX = (windowWidth - tileSizeX * mapWidth) / 2;
  int offsetY = (windowHeight - tileSizeY * mapHeight) / 2;

  // draw map tiles
  for (int y = 0; y < mapHeight; y++) {
    for (int x = 0; x < mapWidth; x++) {
      sf::RectangleShape mapTile(
          sf::Vector2f(tileSizeX * tileScale, tileSizeY * tileScale));
      mapTile.setPosition(offsetX + x * tileSizeX, offsetY + y * tileSizeY);

      if (worldMap[y][x] == 1) { 
        mapTile.setFillColor(wallColor);
      } else if (worldMap[y][x] == 2) {
        mapTile.setTexture(&exitTexture);
      } else {
        mapTile.setFillColor(bgColor);
      }

      window.draw(mapTile);
    }
  }

  // draw player
  drawPlayer(window, playerPosX, playerPosY, tileSizeX, tileSizeY, offsetX,
            offsetY);

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
}
