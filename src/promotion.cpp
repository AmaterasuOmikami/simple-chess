#include "promotion.hpp"

using namespace sf;

Promotion::Promotion(char &pawn_promotion) :
    window_(VideoMode(200, 400),
            "Promotion",
            Style::None),
    // Manage buttons
    queen_({30, 45}, {120, 50}, "Queen"),
    rook_({30, 125}, {100, 50}, "Rook"),
    bishop_({30, 205}, {135, 50}, "Bishop"),
    knight_({30, 285}, {140, 50}, "Knight"),

    pawn_promotion_(pawn_promotion) {
  // Mange window settings
  window_.setFramerateLimit(30);

  // Mange background picture
  if (!bg_texture_.loadFromFile("../assets/menu-textures/game_bg.jpg",
                                IntRect(860, 0, 200, 400))) {
    throw std::runtime_error("Failed to load background texture");
  }
  bg_texture_.setSmooth(true);
  bg_sprite_.setTexture(bg_texture_);
}

bool Promotion::IsOpen() const {
  return window_.isOpen();
}

void Promotion::Events() {
  sf::Event event{};
  while (window_.pollEvent(event)) {
    switch (event.type) {
      case sf::Event::MouseButtonPressed: {
        if (queen_.InArea(event.mouseButton.x, event.mouseButton.y)) {
          queen_.SetStatus(Button::Status::CLICKED);

        } else if (rook_.InArea(event.mouseButton.x, event.mouseButton.y)) {
          rook_.SetStatus(Button::Status::CLICKED);

        } else if (bishop_.InArea(event.mouseButton.x, event.mouseButton.y)) {
          bishop_.SetStatus(Button::Status::CLICKED);

        } else if (knight_.InArea(event.mouseButton.x, event.mouseButton.y)) {
          knight_.SetStatus(Button::Status::CLICKED);
        }
        break;
      }

      case sf::Event::MouseButtonReleased: {
        if (queen_.InArea(event.mouseButton.x, event.mouseButton.y)) {
          queen_.SetStatus(Button::Status::HOVERED);
          pawn_promotion_ = 'q';
          window_.close();

        } else if (rook_.InArea(event.mouseButton.x, event.mouseButton.y)) {
          rook_.SetStatus(Button::Status::HOVERED);
          pawn_promotion_ = 'r';
          window_.close();

        } else if (bishop_.InArea(event.mouseButton.x, event.mouseButton.y)) {
          bishop_.SetStatus(Button::Status::HOVERED);
          pawn_promotion_ = 'b';
          window_.close();

        } else if (knight_.InArea(event.mouseButton.x, event.mouseButton.y)) {
          knight_.SetStatus(Button::Status::HOVERED);
          pawn_promotion_ = 'n';
          window_.close();
        }
        break;
      }

      case sf::Event::MouseMoved: {
        if (queen_.InArea(event.mouseMove.x, event.mouseMove.y)) {
          if (queen_.GetStatus() != Button::Status::CLICKED) {
            queen_.SetStatus(Button::Status::HOVERED);
          }
        } else {
          queen_.SetStatus(Button::Status::NONE);
        }

        if (rook_.InArea(event.mouseMove.x, event.mouseMove.y)) {
          if (rook_.GetStatus() != Button::Status::CLICKED) {
            rook_.SetStatus(Button::Status::HOVERED);
          }
        } else {
          rook_.SetStatus(Button::Status::NONE);
        }

        if (bishop_.InArea(event.mouseMove.x, event.mouseMove.y)) {
          if (bishop_.GetStatus() != Button::Status::CLICKED) {
            bishop_.SetStatus(Button::Status::HOVERED);
          }
        } else {
          bishop_.SetStatus(Button::Status::NONE);
        }

        if (knight_.InArea(event.mouseMove.x, event.mouseMove.y)) {
          if (knight_.GetStatus() != Button::Status::CLICKED) {
            knight_.SetStatus(Button::Status::HOVERED);
          }
        } else {
          knight_.SetStatus(Button::Status::NONE);
        }
        break;
      }

      case sf::Event::Closed: {
        window_.close();
        break;
      }

      default: {
        break;
      }
    }
  }
}

void Promotion::Display() {
  window_.clear();

  window_.draw(bg_sprite_);

  // Buttons
  window_.draw(queen_);
  window_.draw(rook_);
  window_.draw(bishop_);
  window_.draw(knight_);

  window_.display();
}
