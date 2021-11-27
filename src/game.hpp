#pragma once

#include <array>

#include <SFML/Graphics.hpp>

class Game {
 public:
  enum class Mode {
    human,
    ai
  };

  explicit Game(Mode mode);

  bool IsOpen() const;

  void Events();

  void Display();

 private:
  sf::RenderWindow window_;

  sf::Texture bg_texture_;
  sf::Sprite bg_sprite_;

  sf::Texture board_texture_;
  sf::Sprite board_sprite_;

  Mode mode_;
};


