#pragma once

#include <SFML/Graphics.hpp>

#include "button.hpp"

class Menu {
 public:
  Menu();

  bool isOpen() const;

  void events();

  void display();

 private:
  sf::RenderWindow window_;

  sf::Texture bg_texture_;
  sf::Sprite bg_sprite_;

  sf::Font font_;
  sf::Text title_;

  Button one_player;
  Button ai;
  Button settings;
  Button exit;
};


