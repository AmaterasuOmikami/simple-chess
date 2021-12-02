#pragma once

#include <iostream>

#include <array>
#include <fstream>
#include <iostream>

#include <SFML/Graphics.hpp>
#include <chsmv.h>

#include "promotion.hpp"

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

  std::string ClickToSquare(const sf::Event::MouseButtonEvent &click) const;

  void ChangeTurn();

 private:
  sf::RenderWindow window_;

  sf::Texture bg_texture_;
  sf::Sprite bg_sprite_;

  sf::Texture board_texture_;
  sf::Sprite board_sprite_;
  float board_texture_size;
  float square_indent_;
  float square_size_;

  sf::Texture white_king_;
  sf::Texture white_queen_;
  sf::Texture white_bishop_;
  sf::Texture white_knight_;
  sf::Texture white_rook_;
  sf::Texture white_pawn_;

  sf::Texture black_king_;
  sf::Texture black_queen_;
  sf::Texture black_bishop_;
  sf::Texture black_knight_;
  sf::Texture black_rook_;
  sf::Texture black_pawn_;

  float piece_size_;

  Mode mode_;

  chsmv::Color turn_;

  std::string fen_{"rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1"};
  std::string first_square_;
  std::string second_square_;
};


