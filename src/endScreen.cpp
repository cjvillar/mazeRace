#include "config.h"

void RenderEndScreen(sf::RenderWindow &window, bool &endScreen, sf::Color &bgColor, const std::string &fileName) {
    // load font
    sf::Font font;
    if (!font.loadFromFile("assets/Kanit-Light.ttf")) {
        std::cerr << "Failed to load default font" << std::endl;
        return;
    }

    // read player data
    std::vector<PlayerData> players;
    readPlayerScore(players, fileName);

    // sort players by mapCount in desc order
    std::sort(players.begin(), players.end());

    // create text elements for top three scores
    std::vector<sf::Text> texts;
    for (size_t i = 0; i < 3 && i < players.size(); ++i) {
        sf::Text text;
        text.setFont(font);
        text.setString(players[i].playerName + ": " + std::to_string(players[i].mapCount));
        text.setCharacterSize(24);
        text.setFillColor(sf::Color(230, 57, 70));

        sf::FloatRect textBounds = text.getLocalBounds();
        float xPos = (window.getSize().x - textBounds.width) / 2;
        float yPos = (window.getSize().y - textBounds.height) / 2 + i * 30;
        text.setPosition(xPos, yPos);

        texts.push_back(text);
    }

    // main loop 
    while (window.isOpen() && endScreen) {
        sf::Event event;

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) window.close();
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) window.close();
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) endScreen = false;
        }

        // show window
        window.clear(sf::Color(bgColor));
        for (const auto& text : texts) {
            window.draw(text);
        }
        window.display();
    }
}
