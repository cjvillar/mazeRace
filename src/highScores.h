#ifndef HIGHSCORES_H
#define HIGHSCORES_H

#include "config.h"

void highScores(sf::RenderWindow &window, bool &showScores,
                     sf::Color &bgColor, const std::string &fileName);

#endif  // HIGHSCORES_H