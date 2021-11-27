#include "menu.hpp"

Menu::Menu() :
    window_(sf::VideoMode(400, 600),
            "Chess Menu",
            sf::Style::Close),
    // Manage Buttons
    human_({50, 200}, {200, 50}, "one player"),
    ai_({50, 275}, {180, 50}, "stockfish"),
    settings_({50, 350}, {155, 50}, "settings"),
    exit_({50, 450}, {80, 50}, "exit") {
  // Mange window settings
  window_.setFramerateLimit(60);

  // Mange background picture
  if (!bg_texture_.loadFromFile("../assets/menu-textures/bg.jpg")) {
    throw std::runtime_error("Failed to load background texture");
  }
  bg_texture_.setSmooth(true);
  bg_sprite_.setTexture(bg_texture_);
  bg_sprite_.setScale(sf::Vector2f(400.f / 1127.f, 0.5));

  // Manage text settings
  if (!font_.loadFromFile("C:/Windows/Fonts/OLDENGL.TTF")) {
    throw std::runtime_error("Failed to load font for main menu");
  }
  title_.setFont(font_);
  title_.setString("Chess");
  title_.setCharacterSize(96);
  title_.setFillColor(sf::Color::White);
  title_.setPosition(75, 0);
}

bool Menu::IsOpen() const {
  return window_.isOpen();
}

void Menu::Events() {
  sf::Event event{};
  while (window_.pollEvent(event)) {
    switch (event.type) {
      case sf::Event::MouseButtonPressed: {
        if (human_.InArea(event.mouseButton.x, event.mouseButton.y)) {
          human_.SetStatus(Button::Status::clicked);

        } else if (ai_.InArea(event.mouseButton.x, event.mouseButton.y)) {
          ai_.SetStatus(Button::Status::clicked);

        } else if (settings_.InArea(event.mouseButton.x, event.mouseButton.y)) {
          settings_.SetStatus(Button::Status::clicked);

        } else if (exit_.InArea(event.mouseButton.x, event.mouseButton.y)) {
          exit_.SetStatus(Button::Status::clicked);
        }
        break;
      }

      case sf::Event::MouseButtonReleased: {
        if (human_.InArea(event.mouseButton.x, event.mouseButton.y)) {
          human_.SetStatus(Button::Status::hovered);

          // Close current window and open game window
          window_.setVisible(false);
          Game game(Game::Mode::human);
          while (game.IsOpen()) {
            game.Events();
            game.Display();
          }
          window_.setVisible(true);

        } else if (ai_.InArea(event.mouseButton.x, event.mouseButton.y)) {
          ai_.SetStatus(Button::Status::hovered);

        } else if (settings_.InArea(event.mouseButton.x, event.mouseButton.y)) {
          settings_.SetStatus(Button::Status::hovered);

        } else if (exit_.InArea(event.mouseButton.x, event.mouseButton.y)) {
          exit_.SetStatus(Button::Status::hovered);
          window_.close();
        }
        break;
      }

      case sf::Event::MouseMoved: {
        if (human_.InArea(event.mouseMove.x, event.mouseMove.y)) {
          if (human_.GetStatus() != Button::Status::clicked) {
            human_.SetStatus(Button::Status::hovered);
          }
        } else {
          human_.SetStatus(Button::Status::none);
        }

        if (ai_.InArea(event.mouseMove.x, event.mouseMove.y)) {
          if (ai_.GetStatus() != Button::Status::clicked) {
            ai_.SetStatus(Button::Status::hovered);
          }
        } else {
          ai_.SetStatus(Button::Status::none);
        }

        if (settings_.InArea(event.mouseMove.x, event.mouseMove.y)) {
          if (settings_.GetStatus() != Button::Status::clicked) {
            settings_.SetStatus(Button::Status::hovered);
          }
        } else {
          settings_.SetStatus(Button::Status::none);
        }

        if (exit_.InArea(event.mouseMove.x, event.mouseMove.y)) {
          if (exit_.GetStatus() != Button::Status::clicked) {
            exit_.SetStatus(Button::Status::hovered);
          }
        } else {
          exit_.SetStatus(Button::Status::none);
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

void Menu::Display() {
  window_.draw(bg_sprite_);
  window_.draw(title_);

  // Buttons
  window_.draw(human_);
  window_.draw(ai_);
  window_.draw(settings_);
  window_.draw(exit_);

  window_.display();
}
