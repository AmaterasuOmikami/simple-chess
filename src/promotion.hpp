#pragma once

#include "button.hpp"

class Promotion {
 public:
  explicit Promotion(char &pawn_promotion);

  bool IsOpen() const;

  void Events();

  void Display();

 private:
  sf::RenderWindow window_;

  sf::Texture bg_texture_;
  sf::Sprite bg_sprite_;

  Button queen_;
  Button rook_;
  Button bishop_;
  Button knight_;

  // Store selected promotion option
  char &pawn_promotion_;
};


