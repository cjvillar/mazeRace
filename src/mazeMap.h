#ifndef MAZEMAP_H
#define MAZEMAP_H

#include "config.h"
#include "drawPlayer.h"

void mazeMap(sf::RenderWindow &window, int playerPosX, int playerPosY,
             int windowWidth, int windowHeight,
             sf::Texture exitTexture);

#endif  // MAZEMAP_H
