#pragma once

#include <SFML/Graphics.hpp>

#include "game.hpp"
#include "settings.hpp"

class Menu {
 public:
  Menu();

  bool IsOpen() const;

  void Events();

  void Display();

 private:
  sf::RenderWindow window_;

  sf::Texture bg_texture_;
  sf::Sprite bg_sprite_;

  sf::Font font_;
  sf::Text title_;

  Button human_;
  Button ai_;
  Button settings_;
  Button exit_;
};


