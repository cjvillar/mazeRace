#include "config.h"

void RenderStartScreen(sf::RenderWindow &window, bool &startScreen,
                       sf::Color &bgColor, std::string &playerName) {
  // load font
  sf::Font font;
  if (!font.loadFromFile("assets/Kanit-Light.ttf")) {
    std::cerr << "Failed to load default font " << std::endl;
    return;
  }

  // text attrib
  sf::Text titleText;
  titleText.setFont(font);
  titleText.setString("The Maze Race: Press Enter To Start.");
  titleText.setCharacterSize(24);
  titleText.setStyle(sf::Text::Bold);
  titleText.setFillColor(sf::Color(230, 57, 70));

  sf::Text inputPromptText;
  inputPromptText.setFont(font);
  inputPromptText.setString("Enter your name: ");
  inputPromptText.setCharacterSize(24);
  inputPromptText.setFillColor(sf::Color(230, 57, 70));

  sf::Text inputText;
  inputText.setFont(font);
  inputText.setCharacterSize(24);
  inputText.setFillColor(sf::Color(230, 57, 70));

  // center title text
  sf::FloatRect titleBounds = titleText.getLocalBounds();
  float titleXPos = (window.getSize().x - titleBounds.width) / 2;
  float titleYPos =
      (window.getSize().y - titleBounds.height) / 2 - 70;  // set for prompt
  titleText.setPosition(titleXPos, titleYPos);

  // position input prompt text
  sf::FloatRect inputPromptBounds = inputPromptText.getLocalBounds();
  float inputPromptXPos = (window.getSize().x - inputPromptBounds.width) / 8;
  float inputPromptYPos =
      titleYPos + titleBounds.height + 20;  // set below title
  inputPromptText.setPosition(inputPromptXPos, inputPromptYPos);

  // position input text
  float inputTextXPos = inputPromptXPos + inputPromptBounds.width;
  float inputTextYPos = inputPromptYPos;
  inputText.setPosition(inputTextXPos - 150,
                        inputTextYPos + 45);  // set text same pos as box

  // main loop
  std::string input;
  while (window.isOpen() && startScreen) {
    sf::Event event;

    // //  input box
    // sf::RectangleShape inputBox(sf::Vector2f(200, 50)); // size of box
    // inputBox.setFillColor(sf::Color(241, 250, 238));
    // inputBox.setOutlineColor(sf::Color::Black);
    // inputBox.setOutlineThickness(1);
    // inputBox.setPosition(inputTextXPos - 150, inputTextYPos + 55); //adjust
    // text box pos here

    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) window.close();

      if ((event.type == sf::Event::KeyPressed) &&
          (event.key.code == sf::Keyboard::Escape))
        window.close();

      if (event.type == sf::Event::KeyPressed &&
          event.key.code == sf::Keyboard::Enter) {
        startScreen = false;
        playerName = input;  // save player's name
        std::cout << "Player: " << playerName << std::endl;
      }

      // text input
      if (event.type == sf::Event::TextEntered) {
        if (event.text.unicode < 128) {      // ASCII char
          if (event.text.unicode == '\b') {  // to handle backspace
            if (!input.empty()) {
              input.pop_back();
            }
          } else {
            input += static_cast<char>(event.text.unicode);
          }
          inputText.setString(input);
        }
      }
    }

    // show window
    window.clear(sf::Color(bgColor));
    window.draw(titleText);
    window.draw(inputPromptText);
    // draw input box and text
    // window.draw(inputBox);
    window.draw(inputText);
    window.display();
  }
}
