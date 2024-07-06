#include "config.h"

extern sf::Color playerColor;
extern sf::Color playerOutlineColor;

void drawPlayer(sf::RenderWindow &window, int posX, int posY, int tileSizeX,
                int tileSizeY, int offsetX, int offsetY) {
  sf::RectangleShape player(sf::Vector2f(tileSizeX, tileSizeY));
  player.setFillColor(playerColor);
  player.setOutlineColor(playerOutlineColor);
  player.setOrigin(player.getSize().x / 2, player.getSize().y / 2);
  player.setPosition(offsetX + posX * tileSizeX + tileSizeX / 2,
                     offsetY + posY * tileSizeY + tileSizeY / 2);

  window.draw(player);
}
