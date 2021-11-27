#include "menu.hpp"

Menu::Menu() :
    window_(sf::VideoMode(400, 600),
            "Chess Menu",
            sf::Style::Close),
    // Manage Buttons
    one_player({50, 200}, {200, 50}, "one player"),
    ai({50, 275}, {180, 50}, "stockfish"),
    settings({50, 350}, {155, 50}, "settings"),
    exit({50, 450}, {80, 50}, "exit") {
  // Mange window settings
  window_.setVerticalSyncEnabled(true);

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

bool Menu::isOpen() const {
  return window_.isOpen();
}

void Menu::events() {
  sf::Event event{};
  while (window_.pollEvent(event)) {
    switch (event.type) {
      case sf::Event::Closed:window_.close();
        break;

      default:break;
    }
  }
}

void Menu::display() {
  window_.draw(bg_sprite_);
  window_.draw(title_);

  // Buttons
  window_.draw(one_player);
  window_.draw(ai);
  window_.draw(settings);
  window_.draw(exit);

  window_.display();
}
