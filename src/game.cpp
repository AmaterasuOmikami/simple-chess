#include "game.hpp"

Game::Game(Game::Mode mode)
    : window_(sf::VideoMode(1000, 1000),
              "Chess one player",
              sf::Style::Close),
      mode_(mode) {
  // Load texture

}

bool Game::IsOpen() const {
  return window_.isOpen();
}

void Game::Events() {
  sf::Event event{};
  while (window_.pollEvent(event)) {
    switch (event.type) {
      case sf::Event::Closed: {
        window_.close();
        break;
      }

      default: {
        break;
      }
    }
  }
}

void Game::Display() {

}
