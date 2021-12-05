#include "game.hpp"

using namespace sf;

Game::Game(Game::Mode mode)
    : window_(VideoMode(800, 900),
              "Game",
              Style::Close),
      back_button_({680, 820}, {100, 50}, "Back"),
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

  std::ifstream settings("../.settings");
  if (!settings) {
    throw std::runtime_error("Failed to open .settings");
  }
  // Manage board settings
  int board_type;
  settings >> board_type;
  // Skip parameter comment
  settings.ignore(50, '\n');
  switch (board_type) {
    case 1: {
      if (!board_texture_.loadFromFile("../assets/boards/1.jpg")) {
        throw std::runtime_error("Failed to load board/1.jpg");
      }
      board_texture_size_ = 612;
      square_indent_ = 58;
      square_size_ = 62;
      break;
    }

    case 2: {
      if (!board_texture_.loadFromFile("../assets/boards/2.jpg")) {
        throw std::runtime_error("Failed to load board/2.jpg");
      }
      board_texture_size_ = 498;
      square_indent_ = 45;
      square_size_ = 51;
      break;
    }

    case 3: {
      if (!board_texture_.loadFromFile("../assets/boards/3.jpg")) {
        throw std::runtime_error("Failed to load board/3.jpg");
      }
      board_texture_size_ = 612;
      square_indent_ = 46;
      square_size_ = 65;
      break;
    }

    default: {
      throw std::runtime_error("Unknown board type in .settings");
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
  settings >> pieces_type;
  // Skip parameter comment
  settings.ignore(50, '\n');

  // Single piece size in texture
  std::string path;
  int size;

  switch (pieces_type) {
    case 1: {
      path = "../assets/pieces/1.png";
      // Just integer copy of piece_size_
      size = 200;
      piece_size_ = static_cast<float>(size);

      if (!white_king_.loadFromFile(path, IntRect(0, 0, size, size))
          || !white_queen_.loadFromFile(path, IntRect(size, 0, size, size))
          || !white_bishop_.loadFromFile(path, IntRect(2 * size, 0, size, size))
          || !white_knight_.loadFromFile(path, IntRect(3 * size, 0, size, size))
          || !white_rook_.loadFromFile(path, IntRect(4 * size, 0, size, size))
          || !white_pawn_.loadFromFile(path, IntRect(5 * size, 0, size, size))

          || !black_king_.loadFromFile(path, IntRect(0, size, size, size))
          || !black_queen_.loadFromFile(path, IntRect(size, size, size, size))
          || !black_bishop_.loadFromFile(path, IntRect(2 * size, size, size, size))
          || !black_knight_.loadFromFile(path, IntRect(3 * size, size, size, size))
          || !black_rook_.loadFromFile(path, IntRect(4 * size, size, size, size))
          || !black_pawn_.loadFromFile(path, IntRect(5 * size, size, size, size))) {
        throw std::runtime_error("Failed to load pieces/1.png");
      }
      break;
    }

    case 2: {
      path = "../assets/pieces/2.png";
      // Just integer copy of piece_size_
      size = 64;
      piece_size_ = static_cast<float>(size);

      if (!white_king_.loadFromFile(path, IntRect(0, size, size, size))
          || !white_queen_.loadFromFile(path, IntRect(size, size, size, size))
          || !white_bishop_.loadFromFile(path, IntRect(4 * size, size, size, size))
          || !white_knight_.loadFromFile(path, IntRect(3 * size, size, size, size))
          || !white_rook_.loadFromFile(path, IntRect(2 * size, size, size, size))
          || !white_pawn_.loadFromFile(path, IntRect(5 * size, size, size, size))

          || !black_king_.loadFromFile(path, IntRect(0, 0, size, size))
          || !black_queen_.loadFromFile(path, IntRect(size, 0, size, size))
          || !black_bishop_.loadFromFile(path, IntRect(4 * size, 0, size, size))
          || !black_knight_.loadFromFile(path, IntRect(3 * size, 0, size, size))
          || !black_rook_.loadFromFile(path, IntRect(2 * size, 0, size, size))
          || !black_pawn_.loadFromFile(path, IntRect(5 * size, 0, size, size))) {
        throw std::runtime_error("Failed to load pieces/2.png");
      }
      break;
    }

    case 3: {
      path = "../assets/pieces/3.png";
      // Just integer copy of piece_size_
      size = 300;
      piece_size_ = static_cast<float>(size);

      if (!white_king_.loadFromFile(path, IntRect(3 * size, 125 + size, size, size))
          || !white_queen_.loadFromFile(path, IntRect(2 * size, 125 + size, size, size))
          || !white_bishop_.loadFromFile(path, IntRect(size, 125 + size, size, size))
          || !white_knight_.loadFromFile(path, IntRect(4 * size, 125 + size, size, size))
          || !white_rook_.loadFromFile(path, IntRect(0, 125 + size, size, size))
          || !white_pawn_.loadFromFile(path, IntRect(5 * size, 125 + size, size, size))

          || !black_king_.loadFromFile(path, IntRect(3 * size, 50, size, size))
          || !black_queen_.loadFromFile(path, IntRect(2 * size, 50, size, size))
          || !black_bishop_.loadFromFile(path, IntRect(size, 50, size, size))
          || !black_knight_.loadFromFile(path, IntRect(4 * size, 50, size, size))
          || !black_rook_.loadFromFile(path, IntRect(0 * size, 50, size, size))
          || !black_pawn_.loadFromFile(path, IntRect(5 * size, 50, size, size))) {
        throw std::runtime_error("Failed to load pieces/3.png");
      }
      break;
    }

    default: {
      throw std::runtime_error("Unknown pieces type in .settings");
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

  // Manage text
  if (!fen_font_.loadFromFile("C:/Windows/Fonts/BRITANIC.TTF")) {
    throw std::runtime_error("Failed to load fen string font");
  }
  fen_text_.setFont(fen_font_);
  fen_text_.setString(fen_);
  fen_text_.setCharacterSize(18);
  fen_text_.setFillColor(Color::White);
  fen_text_.setPosition(20, 820);

  // Manage sound settings
  if (!move_sound_buffer_.loadFromFile("../assets/sounds/move.wav")) {
    throw std::runtime_error("Filed to load move sound");
  }
  move_sound_.setBuffer(move_sound_buffer_);

  // Add start position to list
  fens_list_.push_back(fen_);

  //----- AI --------//

  if (mode_ == Mode::AI) {
    // Read AI color
    int ai_color;
    settings >> ai_color;
    // Skip parameter comment
    settings.ignore(50, '\n');
    ai_color_ = ai_color == 0 ? chsmv::WHITE : chsmv::BLACK;

    // Run engine
    char engine_path[] = "C:/programming/chess/stockfish/stockfish.exe";
    Engine::ConnectToEngine(engine_path);
  }

  settings.close();
}

void Game::Close() {
  Engine::CloseConnection();
  window_.close();
}

bool Game::IsOpen() const {
  return window_.isOpen();
}

void Game::Events() {
  Event event{};
  chsmv::NewPosition position;

  // If stockfish mode and his turn
  if (mode_ == Mode::AI && turn_ == ai_color_) {
    std::string move = Engine::GetNextMove(fen_);
    position = chsmv::MakeMove(fen_, move);
    goto position_status_validation;
  }

  while (window_.pollEvent(event)) {
    switch (event.type) {
      case Event::MouseButtonPressed: {
        // Buttons

        if (back_button_.InArea(event.mouseButton.x, event.mouseButton.y)) {
          back_button_.SetStatus(Button::Status::CLICKED);
        }

        //------- Pieces -------//

        // Gather move
        if (spot_1_.empty()) {
          spot_1_ = ClickToSquare(event.mouseButton);

        } else if (spot_2_.empty()) {

          spot_2_ = ClickToSquare(event.mouseButton);
          if (chsmv::IsCurrentColor(fen_, spot_2_)) {
            spot_1_ = spot_2_;
            spot_2_.clear();
          }

          if (!spot_2_.empty()) {
            position = chsmv::MakeMove(fen_, spot_1_ + spot_2_);
            position_status_validation:
            switch (position.status) {
              case chsmv::NewPosition::VALID: {
                ConfirmMove(position);
                ChangeTurn();
                break;
              }

              case chsmv::NewPosition::CHECK: {
                ConfirmMove(position);
                Display();

                Message message("Check", sf::VideoMode(210, 70));
                while (message.IsOpen()) {
                  message.Events();
                  message.Display();
                }
                ChangeTurn();
                break;
              }

              case chsmv::NewPosition::DRAW: {
                ConfirmMove(position);
                Display();

                Message message("Draw", sf::VideoMode(185, 70));
                while (message.IsOpen()) {
                  message.Events();
                  message.Display();
                }
                Close();
                break;
              }

              case chsmv::NewPosition::CHECKMATE: {
                ConfirmMove(position);
                Display();

                Message message("Checkmate", sf::VideoMode(370, 70));
                while (message.IsOpen()) {
                  message.Events();
                  message.Display();
                }
                Close();
                break;
              }

              case chsmv::NewPosition::PAWN_PROMOTION: {
                char promotion;
                Promotion promotion_window(promotion);
                while (promotion_window.IsOpen()) {
                  promotion_window.Events();
                  promotion_window.Display();
                }

                position = chsmv::MakeMove(fen_, spot_1_ + spot_2_ + promotion);
                goto position_status_validation;
              }

              case chsmv::NewPosition::INVALID: {
                break;
              }
            }
            spot_1_.clear();
            spot_2_.clear();
          }
        }

        break;
      }

      case Event::MouseButtonReleased: {
        if (back_button_.InArea(event.mouseButton.x, event.mouseButton.y)) {
          back_button_.SetStatus(Button::Status::HOVERED);

          RewindPosition();
        }
        break;
      }

      case sf::Event::MouseMoved: {
        if (back_button_.InArea(event.mouseMove.x, event.mouseMove.y)) {
          if (back_button_.GetStatus() != Button::Status::CLICKED) {
            back_button_.SetStatus(Button::Status::HOVERED);
          }
        } else {
          back_button_.SetStatus(Button::Status::NONE);
        }
        break;
      }

      case Event::Closed: {
        Close();
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
  if ((mode_ == Mode::HUMAN && turn_ == chsmv::BLACK)
      || (mode_ == Mode::AI && ai_color_ == chsmv::WHITE)) {
    board_sprite_.setRotation(180.f);
    board_sprite_.setOrigin(board_texture_size_, board_texture_size_);
  } else if ((mode_ == Mode::HUMAN && turn_ == chsmv::WHITE)
      || (mode_ == Mode::AI && ai_color_ == chsmv::BLACK)) {
    board_sprite_.setRotation(0.f);
    board_sprite_.setOrigin(0, 0);
  }
  window_.draw(board_sprite_);

  // Draw fen string
  window_.draw(fen_text_);

  // Draw back button
  window_.draw(back_button_);

  float row = square_indent_;
  float col = square_indent_;

  if ((mode_ == Mode::HUMAN && !spot_1_.empty())
      || (mode_ == Mode::AI && turn_ != ai_color_)) {

    RectangleShape square(Vector2f(square_size_, square_size_));
    square.setFillColor(Color(0, 128, 0, 128));

    auto valid_moves = chsmv::HighlightMoves(fen_, spot_1_);

    // Reverse highlighting if black turn
    if ((mode_ == Mode::HUMAN && turn_ == chsmv::BLACK)
        || (mode_ == Mode::AI && ai_color_ == chsmv::WHITE)) {
      std::reverse(valid_moves.begin(), valid_moves.end());
    }

    for (size_t i = 0; i < valid_moves.size(); ++i) {
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
  if ((mode_ == Mode::HUMAN && turn_ == chsmv::BLACK)
      || (mode_ == Mode::AI && ai_color_ == chsmv::WHITE)) {
    auto iter = std::find(fen_.begin(), fen_.end(), ' ');
    std::reverse(fen_.begin(), iter);
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
  if ((mode_ == Mode::HUMAN && turn_ == chsmv::BLACK)
      || (mode_ == Mode::AI && ai_color_ == chsmv::WHITE)) {
    auto iter = std::find(fen_.begin(), fen_.end(), ' ');
    std::reverse(fen_.begin(), iter);
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

void Game::ConfirmMove(const chsmv::NewPosition &position) {
  // Play move sound
  move_sound_.play();
  // Change board position
  fen_ = position.fen;
  // Set new fen position in fen string
  fen_text_.setString(fen_);
  // Add current fen position to list
  fens_list_.push_back(fen_);
}

void Game::RewindPosition() {
  // Do nothing if list have only one node
  if (fens_list_.size() < 3) {
    return;
  }

  fens_list_.pop_back();
  fens_list_.pop_back();
  fen_ = fens_list_.back();
}

void Game::ChangeTurn() {
  turn_ = (turn_ == chsmv::WHITE ? chsmv::BLACK : chsmv::WHITE);
}
