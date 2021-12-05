#pragma once

#include <array>
#include <fstream>
#include <iostream>
#include <memory>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <chsmv.h>

#include "promotion.hpp"
#include "message.hpp"
#include "engine.hpp"

class Game {
 public:
  enum class Mode {
    HUMAN,
    AI
  };

  explicit Game(Mode mode);

  void Close();

  bool IsOpen() const;

  void Events();

  void Display();

  std::string ClickToSquare(const sf::Event::MouseButtonEvent &click) const;

  void ConfirmMove(const chsmv::NewPosition &position);

  void ChangeTurn();

 private:
  sf::RenderWindow window_;

  sf::Texture bg_texture_;
  sf::Sprite bg_sprite_;

  sf::Texture board_texture_;
  sf::Sprite board_sprite_;
  float board_texture_size_;
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

  sf::Font fen_font_;
  sf::Text fen_text_;

  sf::SoundBuffer move_sound_buffer_;
  sf::Sound move_sound_;

  Mode mode_;

  chsmv::Color ai_color_;

  chsmv::Color turn_;

  std::string fen_{"rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1"};
  std::string spot_1_;
  std::string spot_2_;
};


