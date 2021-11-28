#include "game.hpp"

using namespace sf;

Game::Game(Game::Mode mode)
    : window_(VideoMode(800, 900),
              "Chess one player",
              Style::Close),
      mode_(mode) {
  // Manage background picture
  if (!bg_texture_.loadFromFile("../assets/menu-textures/game_bg.jpg",
                                IntRect(0, 0, 800, 900))) {
    throw std::runtime_error("Failed to load game background texture");
  }
  bg_texture_.setSmooth(true);
  bg_sprite_.setTexture(bg_texture_);

  std::ifstream config("../.cfg");
  if (!config) {
    throw std::runtime_error("Failed to open .cfg (settings file)");
  }
  // Manage board settings
  int board_type;
  config >> board_type;
  // Skip parameter comment
  config.ignore(50, '\n');
  switch (board_type) {
    case 1: {
      if (!board_texture_.loadFromFile("../assets/boards/1.jpg")) {
        throw std::runtime_error("Failed to load board/1.jpg");
      }
      break;
    }

    case 2: {
      if (!board_texture_.loadFromFile("../assets/boards/2.jpg")) {
        throw std::runtime_error("Failed to load board/2.jpg");
      }
      square_indent_ = 45;
      square_size_ = 51;
      break;
    }

    case 3: {
      if (!board_texture_.loadFromFile("../assets/boards/3.jpg")) {
        throw std::runtime_error("Failed to load board/3.jpg");
      }
      break;
    }

    default: {
      throw std::runtime_error("Unknown board type in .cfg (settings file)");
    }
  }
  board_texture_.setSmooth(true);
  board_sprite_.setTexture(board_texture_);
  board_sprite_.setScale(
      800.f / static_cast<float>(board_texture_.getSize().x),
      800.f / static_cast<float>(board_texture_.getSize().y)
  );
  // Change values according to new scale
  square_indent_ *= board_sprite_.getScale().x;
  square_size_ *= board_sprite_.getScale().x;

  // Manage pieces settings

  int pieces_type;
  config >> pieces_type;
  // Skip parameter comment
  config.ignore(50, '\n');

  // Single piece size in texture
  std::string path;
  int sz;

  switch (pieces_type) {
    case 1: {
      path = "../assets/pieces/1.png";
      if (false) {
        throw std::runtime_error("Failed to load pieces/1.png");
      }
      break;
    }

    case 2: {
      path = "../assets/pieces/2.png";
      // Just integer copy of piece_size_
      sz = 64;
      piece_size_ = static_cast<float>(sz);

      if (!white_king_.loadFromFile(path, IntRect(0, sz, sz, sz))
          || !white_queen_.loadFromFile(path, IntRect(sz, sz, sz, sz))
          || !white_bishop_.loadFromFile(path, IntRect(4 * sz, sz, sz, sz))
          || !white_knight_.loadFromFile(path, IntRect(3 * sz, sz, sz, sz))
          || !white_rook_.loadFromFile(path, IntRect(2 * sz, sz, sz, sz))
          || !white_pawn_.loadFromFile(path, IntRect(5 * sz, sz, sz, sz))

          || !black_king_.loadFromFile(path, IntRect(0, 0, sz, sz))
          || !black_queen_.loadFromFile(path, IntRect(sz, 0, sz, sz))
          || !black_bishop_.loadFromFile(path, IntRect(4 * sz, 0, sz, sz))
          || !black_knight_.loadFromFile(path, IntRect(3 * sz, 0, sz, sz))
          || !black_rook_.loadFromFile(path, IntRect(2 * sz, 0, sz, sz))
          || !black_pawn_.loadFromFile(path, IntRect(5 * sz, 0, sz, sz))) {
        throw std::runtime_error("Failed to load pieces/2.png");
      }
      break;
    }

    case 3: {
      if (false) {
        throw std::runtime_error("Failed to load pieces/3.png");
      }
      break;
    }

    default: {
      throw std::runtime_error("Unknown pieces type in .cfg (settings file)");
    }
  }
  white_king_.setSmooth(true);
  white_queen_.setSmooth(true);
  white_bishop_.setSmooth(true);
  white_knight_.setSmooth(true);
  white_rook_.setSmooth(true);
  white_pawn_.setSmooth(true);
  black_king_.setSmooth(true);
  black_queen_.setSmooth(true);
  black_bishop_.setSmooth(true);
  black_knight_.setSmooth(true);
  black_rook_.setSmooth(true);
  black_pawn_.setSmooth(true);

  config.close();
}

bool Game::IsOpen() const {
  return window_.isOpen();
}

void Game::Events() {
  Event event{};
  while (window_.pollEvent(event)) {
    switch (event.type) {
      case Event::Closed: {
        window_.close();
        break;
      }

      default: {
        break;
      }
    }
  }
}

void Game::Display() {
  window_.draw(bg_sprite_);
  window_.draw(board_sprite_);

  // Iterate thought FEN board and draw pieces
  Sprite piece;
  piece.setScale(square_size_ / piece_size_,
                 square_size_ / piece_size_);
  float row = square_indent_;
  float col = square_indent_;
  for (int i = 0; fen_board[i] != ' '; ++i) {
    piece.setPosition(col, row);
    if (fen_board[i] == '/') {
      row += square_size_;
      col = square_indent_;
      piece.setPosition(col, row);
      continue;
    } else if (isdigit(fen_board[i])) {
      // Skip empty squares
      for (int skip = fen_board[i] - '0'; skip > 0; --skip) {
        col += square_size_;
      }
    } else {
      switch (fen_board[i]) {
        case 'K':piece.setTexture(white_king_);
          break;

        case 'Q':piece.setTexture(white_queen_);
          break;

        case 'B':piece.setTexture(white_bishop_);
          break;

        case 'N':piece.setTexture(white_knight_);
          break;

        case 'R':piece.setTexture(white_rook_);
          break;

        case 'P':piece.setTexture(white_pawn_);
          break;

        case 'k':piece.setTexture(black_king_);
          break;

        case 'q':piece.setTexture(black_queen_);
          break;

        case 'b':piece.setTexture(black_bishop_);
          break;

        case 'n':piece.setTexture(black_knight_);
          break;

        case 'r':piece.setTexture(black_rook_);
          break;

        case 'p':piece.setTexture(black_pawn_);
          break;

        default:throw std::runtime_error("Invalid FEN character");
      }
      window_.draw(piece);
      col += square_size_;
    }
  }

  window_.display();
}
