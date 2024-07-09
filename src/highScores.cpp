#include "config.h"

void highScores(sf::RenderWindow &window, bool &showScores, sf::Color &bgColor,
                const std::string &fileName) {
  sf::Font font;
  if (!font.loadFromFile("assets/Kanit-Light.ttf")) { // load font
    std::cerr << "Failed to load default font" << std::endl;
    return;
  }
  std::vector<PlayerData> players; // read player data
  readPlayerScore(players, fileName);
  std::sort(players.begin(), players.end()); // sort players by mapCount in desc order
  std::vector<sf::Text> texts; // create text elements for top three scores
  for (size_t i = 0; i < 3 && i < players.size(); ++i) {
    sf::Text text;
    text.setFont(font);
    text.setString(players[i].playerName + ": " +
                   std::to_string(players[i].mapCount));
    text.setCharacterSize(24);
    text.setFillColor(sf::Color(230, 57, 70));

    sf::FloatRect textBounds = text.getLocalBounds();
    float xPos = (window.getSize().x - textBounds.width) / 2;
    float yPos = (window.getSize().y - textBounds.height) / 2 + i * 30;
    text.setPosition(xPos, yPos);
    texts.push_back(text);
  }
  // main loop
  while (window.isOpen() && showScores) {
    sf::Event event;

    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) window.close();
      if (event.type == sf::Event::KeyPressed &&
          event.key.code == sf::Keyboard::Escape)
        window.close();
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) showScores = false;
    }
    // show window
    window.clear(sf::Color(bgColor));
    for (const auto &text : texts) {
      window.draw(text);
    }
    window.display();
  }
}
