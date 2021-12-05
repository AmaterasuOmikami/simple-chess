#pragma once

#include <fstream>

#include "button.hpp"

class Settings {
 public:
  Settings();

  bool IsOpen() const;

  void Events();

  void Display();

  void NextBoardOption();

  void NextPieceOption();

  void NextAiColorOption();

 private:
  sf::RenderWindow window_;

  sf::Texture bg_texture_;
  sf::Sprite bg_sprite_;

  sf::Font font_;
  sf::Text settings_text_[3];

  Button board_button_;
  Button pieces_button_;
  Button ai_color_button_;
};


