#pragma once

#include <SFML/Graphics.hpp>

class Message {
 public:
  Message(const std::string& message, const sf::VideoMode& video_mode);

  bool IsOpen() const;

  void Events();

  void Display();

 private:
  sf::RenderWindow window_;

  sf::Texture bg_texture_;
  sf::Sprite bg_sprite_;

  sf::Font font_;
  sf::Text message_;
};


