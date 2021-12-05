#include "settings.hpp"

Settings::Settings() :
    window_(sf::VideoMode(400, 300),
            "Settings",
            sf::Style::Close),
    // Manage Buttons
    board_button_({50, 50}, {210, 50}, "board type"),
    pieces_button_({50, 125}, {215, 50}, "pieces type"),
    ai_color_button_({50, 200}, {160, 50}, "AI color") {
  // Mange window settings
  window_.setFramerateLimit(30);

  // Mange background picture
  if (!bg_texture_.loadFromFile("../assets/menu-textures/game_bg.jpg",
                                sf::IntRect(760, 0, 400, 300))) {
    throw std::runtime_error("Failed to load setting background texture");
  }
  bg_texture_.setSmooth(true);
  bg_sprite_.setTexture(bg_texture_);

  // Manage text
  if (!font_.loadFromFile("C:/Windows/Fonts/COOPBL.TTF")) {
    throw std::runtime_error("Failed to load settings font");
  }
  for (auto &setting: settings_text_) {
    setting.setFont(font_);
    setting.setCharacterSize(36);
    setting.setFillColor(sf::Color::White);
  }

  // Load data form .settings
  std::ifstream settings_file("../.settings");
  if (!settings_file.is_open()) {
    throw std::runtime_error("Failed to open .settings");
  }

  std::string record;

  std::getline(settings_file, record);
  settings_text_[0].setString(record.substr(0, 1));
  settings_text_[0].setPosition(270, 50);

  std::getline(settings_file, record);
  settings_text_[1].setString(record.substr(0, 1));
  settings_text_[1].setPosition(275, 125);

  std::getline(settings_file, record);
  settings_text_[2].setString(
      stoi(record.substr(0, 1)) == 0 ? "white" : "black");
  settings_text_[2].setPosition(220, 200);

  settings_file.close();
}

bool Settings::IsOpen() const {
  return window_.isOpen();
}

void Settings::Events() {
  sf::Event event{};
  while (window_.pollEvent(event)) {
    switch (event.type) {
      case sf::Event::MouseButtonPressed: {
        if (board_button_.InArea(event.mouseButton.x, event.mouseButton.y)) {
          board_button_.SetStatus(Button::Status::CLICKED);

        } else if (pieces_button_.InArea(event.mouseButton.x,
                                         event.mouseButton.y)) {
          pieces_button_.SetStatus(Button::Status::CLICKED);

        } else if (ai_color_button_.InArea(event.mouseButton.x,
                                           event.mouseButton.y)) {
          ai_color_button_.SetStatus(Button::Status::CLICKED);

        }
        break;
      }

      case sf::Event::MouseButtonReleased: {
        if (board_button_.InArea(event.mouseButton.x, event.mouseButton.y)) {
          board_button_.SetStatus(Button::Status::HOVERED);

          NextBoardOption();

        } else if (pieces_button_.InArea(event.mouseButton.x,
                                         event.mouseButton.y)) {
          pieces_button_.SetStatus(Button::Status::HOVERED);

          NextPieceOption();

        } else if (ai_color_button_.InArea(event.mouseButton.x,
                                           event.mouseButton.y)) {
          ai_color_button_.SetStatus(Button::Status::HOVERED);

          NextAiColorOption();
        }
        break;
      }

      case sf::Event::MouseMoved: {
        if (board_button_.InArea(event.mouseMove.x, event.mouseMove.y)) {
          if (board_button_.GetStatus() != Button::Status::CLICKED) {
            board_button_.SetStatus(Button::Status::HOVERED);
          }
        } else {
          board_button_.SetStatus(Button::Status::NONE);
        }

        if (pieces_button_.InArea(event.mouseMove.x, event.mouseMove.y)) {
          if (pieces_button_.GetStatus() != Button::Status::CLICKED) {
            pieces_button_.SetStatus(Button::Status::HOVERED);
          }
        } else {
          pieces_button_.SetStatus(Button::Status::NONE);
        }

        if (ai_color_button_.InArea(event.mouseMove.x, event.mouseMove.y)) {
          if (ai_color_button_.GetStatus() != Button::Status::CLICKED) {
            ai_color_button_.SetStatus(Button::Status::HOVERED);
          }
        } else {
          ai_color_button_.SetStatus(Button::Status::NONE);
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

void Settings::Display() {
  window_.draw(bg_sprite_);

  for (auto &setting: settings_text_) {
    window_.draw(setting);
  }

  // Buttons
  window_.draw(board_button_);
  window_.draw(pieces_button_);
  window_.draw(ai_color_button_);

  window_.display();
}

void Settings::NextBoardOption() {
  std::string value;
  // Set fist value when current is last value
  if (settings_text_[0].getString() == "3") {
    value = "1";
  } else {
    value = settings_text_[0].getString();
    value = std::to_string(stoi(value) + 1);
  }
  settings_text_[0].setString(value);

  // Update .settings

  // I HATE THIS LANGUAGE, JUST WHY I MUST OPEN OFSTREAM IN INPUT MODE??????
  std::ofstream settings_file("../.settings", std::ios::in | std::ios::ate);
  if (!settings_file.is_open()) {
    throw std::runtime_error("Failed to open .settings");
  }
  settings_file.seekp(0, std::ios::beg);

  settings_file << value;
  settings_file.close();
}

void Settings::NextPieceOption() {
  std::string value;
  // Set fist value when current is last value
  if (settings_text_[1].getString() == "3") {
    value = "1";
  } else {
    value = settings_text_[1].getString();
    value = std::to_string(stoi(value) + 1);
  }
  settings_text_[1].setString(value);

  // Update .settings

  std::fstream settings_file("../.settings", std::ios::out | std::ios::in);
  if (!settings_file.is_open()) {
    throw std::runtime_error("Failed to open .settings");
  }

  settings_file.ignore(200, '\n');
  settings_file.seekp(settings_file.tellg());
  settings_file.seekp(-2, std::ios::cur);

  settings_file << value;
  settings_file.close();
}

void Settings::NextAiColorOption() {
  std::string value;
  // Set fist value when current is last value
  value = settings_text_[2].getString() == "black" ? "0" : "1";
  settings_text_[2].setString(value == "0" ? "white" : "black");

  // Update .settings

  std::fstream settings_file("../.settings", std::ios::out | std::ios::in);
  if (!settings_file.is_open()) {
    throw std::runtime_error("Failed to open .settings");
  }

  settings_file.ignore(200, '\n');
  settings_file.ignore(200, '\n');
  settings_file.seekp(settings_file.tellg());
  settings_file.seekp(-1, std::ios::cur);

  settings_file << value;
  settings_file.close();
}
