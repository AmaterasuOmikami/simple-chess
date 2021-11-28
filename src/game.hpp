#pragma once

#include <array>
#include <fstream>

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

  std::string
      fen_board{"rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1"};
};


