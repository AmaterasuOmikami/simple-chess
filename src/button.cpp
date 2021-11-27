#include "button.hpp"

Button::Button(const sf::Vector2i &coordinates,
               const sf::Vector2i &size,
               const std::string &text)
    : coordinates_(coordinates), size_(size) {
  // Manage texture
  if (!texture_.loadFromFile("../assets/menu-textures/button_color.jpg")) {
    throw std::runtime_error("Failed to load button texture");
  }
  sprite_.setTexture(texture_);
  sprite_.setPosition(static_cast<sf::Vector2f>(coordinates_));
  sprite_.setScale(static_cast<sf::Vector2f>(size_) / 1024.f);

  // Manage text
  if (!font_.loadFromFile("C:/Windows/Fonts/COOPBL.TTF")) {
    throw std::runtime_error("Failed to load button font");
  }
  text_.setFont(font_);
  text_.setString(text);
  text_.setCharacterSize(36);
  text_.setFillColor(sf::Color::White);
  text_.setPosition(static_cast<sf::Vector2f>(coordinates_));
}
void Button::draw(sf::RenderTarget &target, sf::RenderStates states) const {
  target.draw(sprite_);
  target.draw(text_);
}
