#include "button.hpp"

Button::Button(const sf::Vector2i &coordinates,
               const sf::Vector2i &size,
               const std::string &text)
    : coordinates_(coordinates), size_(size), status_(Status::NONE) {
  // Manage texture
  if (!texture_.loadFromFile("../assets/menu-textures/button_color.jpg")) {
    throw std::runtime_error("Failed to load button texture");
  }
  sprite_.setTexture(texture_);
  sprite_.setColor(sf::Color(0, 0, 0, 0));
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

bool Button::InArea(int x, int y) const {
  return coordinates_.x <= x && x <= coordinates_.x + size_.x
      && coordinates_.y <= y && y <= coordinates_.y + size_.y;
}

Button::Status Button::GetStatus() const {
  return status_;
}

void Button::SetStatus(Button::Status status) {
  switch (status_ = status) {
    case Status::NONE: {
      sprite_.setColor(sf::Color(0, 0, 0, 0));
      break;
    }

    case Status::HOVERED: {
      sprite_.setColor(sf::Color(255, 255, 255, 128));

      break;
    }

    case Status::CLICKED: {
      sprite_.setColor(sf::Color(255, 128, 128, 128));
      break;
    }
  }
}

void Button::draw(sf::RenderTarget &target, sf::RenderStates states) const {
  target.draw(sprite_, states);
  target.draw(text_, states);
}

