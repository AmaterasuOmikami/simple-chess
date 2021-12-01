#include "game.hpp"

using namespace sf;

Game::Game(Game::Mode mode)
    : window_(VideoMode(800, 900),
              "Chess one player",
              Style::Close),
      mode_(mode),
      turn_(chsmv::WHITE) {
  // Mange window settings
  window_.setFramerateLimit(30);

  // Manage background picture
  if (!bg_texture_.loadFromFile("../assets/menu-textures/game_bg.jpg",
                                IntRect(560, 0, 800, 900))) {
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
      board_texture_size = 612;
      square_indent_ = 58;
      square_size_ = 62;
      break;
    }

    case 2: {
      if (!board_texture_.loadFromFile("../assets/boards/2.jpg")) {
        throw std::runtime_error("Failed to load board/2.jpg");
      }
      board_texture_size = 498;
      square_indent_ = 45;
      square_size_ = 51;
      break;
    }

    case 3: {
      if (!board_texture_.loadFromFile("../assets/boards/3.jpg")) {
        throw std::runtime_error("Failed to load board/3.jpg");
      }
      board_texture_size = 612;
      square_indent_ = 46;
      square_size_ = 65;
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
      // Just integer copy of piece_size_
      sz = 200;
      piece_size_ = static_cast<float>(sz);

      if (!white_king_.loadFromFile(path, IntRect(0, 0, sz, sz))
          || !white_queen_.loadFromFile(path, IntRect(sz, 0, sz, sz))
          || !white_bishop_.loadFromFile(path, IntRect(2 * sz, 0, sz, sz))
          || !white_knight_.loadFromFile(path, IntRect(3 * sz, 0, sz, sz))
          || !white_rook_.loadFromFile(path, IntRect(4 * sz, 0, sz, sz))
          || !white_pawn_.loadFromFile(path, IntRect(5 * sz, 0, sz, sz))

          || !black_king_.loadFromFile(path, IntRect(0, sz, sz, sz))
          || !black_queen_.loadFromFile(path, IntRect(sz, sz, sz, sz))
          || !black_bishop_.loadFromFile(path, IntRect(2 * sz, sz, sz, sz))
          || !black_knight_.loadFromFile(path, IntRect(3 * sz, sz, sz, sz))
          || !black_rook_.loadFromFile(path, IntRect(4 * sz, sz, sz, sz))
          || !black_pawn_.loadFromFile(path, IntRect(5 * sz, sz, sz, sz))) {
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
      path = "../assets/pieces/3.png";
      // Just integer copy of piece_size_
      sz = 300;
      piece_size_ = static_cast<float>(sz);

      if (!white_king_.loadFromFile(path, IntRect(3 * sz, 125 + sz, sz, sz))
          || !white_queen_.loadFromFile(path, IntRect(2 * sz, 125 + sz, sz, sz))
          || !white_bishop_.loadFromFile(path, IntRect(sz, 125 + sz, sz, sz))
          || !white_knight_.loadFromFile(path,
                                         IntRect(4 * sz, 125 + sz, sz, sz))
          || !white_rook_.loadFromFile(path, IntRect(0, 125 + sz, sz, sz))
          || !white_pawn_.loadFromFile(path, IntRect(5 * sz, 125 + sz, sz, sz))

          || !black_king_.loadFromFile(path, IntRect(3 * sz, 50, sz, sz))
          || !black_queen_.loadFromFile(path, IntRect(2 * sz, 50, sz, sz))
          || !black_bishop_.loadFromFile(path, IntRect(sz, 50, sz, sz))
          || !black_knight_.loadFromFile(path, IntRect(4 * sz, 50, sz, sz))
          || !black_rook_.loadFromFile(path, IntRect(0 * sz, 50, sz, sz))
          || !black_pawn_.loadFromFile(path, IntRect(5 * sz, 50, sz, sz))) {
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
  chsmv::NewPosition position;

  while (window_.pollEvent(event)) {
    switch (event.type) {
      case Event::MouseButtonPressed: {
        //------- Pieces -------//

        // Gather move
        if (first_square_.empty()) {
          first_square_ = ClickToSquare(event.mouseButton);

        } else if (second_square_.empty()) {

          second_square_ = ClickToSquare(event.mouseButton);
          if (chsmv::IsCurrentColor(fen_, second_square_)) {
            first_square_ = second_square_;
            second_square_.clear();
          }

          if (!second_square_.empty()) {
            position = chsmv::MoveProcess(fen_, first_square_ + second_square_);
            afterNewPosition:
            switch (position.status) {
              case chsmv::NewPosition::VALID: {
                fen_ = position.fen;
                ChangeTurn();
                break;
              }

              case chsmv::NewPosition::CHECK: {
                fen_ = position.fen;
                std::cout << "Check\n";
                if (chsmv::IsCheckmate(fen_)) {
                  std::cout << "Checkmate\n";
                  window_.close();
                }
                // TODO: add message about check
                ChangeTurn();
                break;
              }

              case chsmv::NewPosition::PAWN_PROMOTION: {
                char pawn_promotion;
                Promotion promotion(pawn_promotion);
                while (promotion.IsOpen()) {
                  promotion.Events();
                  promotion.Display();
                }

                position = chsmv::MoveProcess(fen_,
                                              first_square_ + second_square_
                                                  + pawn_promotion);

                goto afterNewPosition;
              }

              case chsmv::NewPosition::INVALID: {
                break;
              }
            }
            first_square_.clear();
            second_square_.clear();
          }
        }

        break;
      }

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

  // Rotate board
  if (mode_ == Mode::human && turn_ == chsmv::BLACK) {
    board_sprite_.setRotation(180.f);
    board_sprite_.setOrigin(board_texture_size, board_texture_size);
  } else if (mode_ == Mode::human && turn_ == chsmv::WHITE) {
    board_sprite_.setRotation(0.f);
    board_sprite_.setOrigin(0, 0);
  }
  window_.draw(board_sprite_);

  float row = square_indent_;
  float col = square_indent_;

  if (!first_square_.empty()) {

    RectangleShape square(Vector2f(square_size_, square_size_));
    square.setFillColor(Color(0, 128, 0, 128));

    auto valid_moves = chsmv::HighlightMoves(fen_, first_square_);

    // Reverse highlighting if black turn
    if (turn_ == chsmv::BLACK) {
      std::reverse(valid_moves.begin(), valid_moves.end());
    }

    for (int i = 0; i < valid_moves.size(); ++i) {
      square.setPosition(col, row);

      if (valid_moves[i] == '1') {
        window_.draw(square);
      }

      if ((i + 1) % 8 == 0) {
        row += square_size_;
        col = square_indent_;
        square.setPosition(col, row);
        continue;
      }

      col += square_size_;
    }
  }

  // Iterate thought FEN board and draw pieces
  Sprite piece;
  piece.setScale(square_size_ / piece_size_,
                 square_size_ / piece_size_);

  // Rotate pieces
  if (mode_ == Mode::human && turn_ == chsmv::BLACK) {
    auto it = std::find(fen_.begin(), fen_.end(), ' ');
    std::reverse(fen_.begin(), it);
  }

  row = square_indent_;
  col = square_indent_;

  for (int i = 0; fen_[i] != ' '; ++i) {
    piece.setPosition(col, row);

    if (fen_[i] == '/') {
      row += square_size_;
      col = square_indent_;
      piece.setPosition(col, row);
      continue;
    } else if (isdigit(fen_[i])) {
      // Skip empty squares
      for (int skip = fen_[i] - '0'; skip > 0; --skip) {
        col += square_size_;
      }
    } else {
      switch (fen_[i]) {
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

  // Rotate pieces again
  if (mode_ == Mode::human && turn_ == chsmv::BLACK) {
    auto it = std::find(fen_.begin(), fen_.end(), ' ');
    std::reverse(fen_.begin(), it);
  }

  window_.display();
}

std::string Game::ClickToSquare(const Event::MouseButtonEvent &click) const {
  // Check click on board
  if (square_indent_ < static_cast<float>(click.x)
      && square_indent_ + 8 * square_size_ > static_cast<float>(click.x)

      && square_indent_ < static_cast<float>(click.y)
      && square_indent_ + 8 * square_size_ > static_cast<float>(click.y)) {

    std::string square;
    char letter;
    char digit;

    if (turn_ == chsmv::WHITE) {
      letter = static_cast<char>('a' +
          (click.x - (int) square_indent_) / (int) square_size_);
      square += letter;

      digit = static_cast<char>('8' -
          (click.y - (int) square_indent_) / (int) square_size_);
      square += digit;
    } else {
      letter = static_cast<char>('h' -
          (click.x - (int) square_indent_) / (int) square_size_);
      square += letter;

      digit = static_cast<char>('1' +
          (click.y - (int) square_indent_) / (int) square_size_);
      square += digit;
    }
    return square;
  }

  // Invalid click
  return "";
}

void Game::ChangeTurn() {
  turn_ = (turn_ == chsmv::WHITE ? chsmv::BLACK : chsmv::WHITE);
}

