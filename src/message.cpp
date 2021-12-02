#include "message.hpp"

using namespace sf;

Message::Message(const std::string &message, const sf::VideoMode &video_mode) :
    window_(video_mode, "Promotion", Style::Close) {
  // Mange window settings
  window_.setFramerateLimit(30);

  // Mange background picture
  if (!bg_texture_.loadFromFile("../assets/menu-textures/game_bg.jpg")) {
    throw std::runtime_error("Failed to load background texture");
  }
  bg_texture_.setSmooth(true);
  bg_sprite_.setTexture(bg_texture_);

  // Manage text settings
  if (!font_.loadFromFile("C:/Windows/Fonts/COOPBL.TTF")) {
    throw std::runtime_error("Failed to load font for message");
  }
  message_.setFont(font_);
  message_.setString(message);
  message_.setCharacterSize(64);
  message_.setFillColor(sf::Color::White);
}

bool Message::IsOpen() const {
  return window_.isOpen();
}

void Message::Events() {
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

void Message::Display() {
  window_.draw(bg_sprite_);
  window_.draw(message_);

  window_.display();
}
