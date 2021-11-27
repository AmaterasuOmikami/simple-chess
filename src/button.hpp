#pragma once

#include <SFML/Graphics.hpp>

class Button : public sf::Drawable {
 public:
  enum class Status {
    none,
    hovered,
    clicked
  };

  Button(const sf::Vector2i &coordinates,
         const sf::Vector2i &size,
         const std::string &text);

  bool InArea(int x, int y) const;

  Status GetStatus() const;

  void SetStatus(Status status);

  void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

 private:
  sf::Vector2i coordinates_;
  sf::Vector2i size_;

  sf::Texture texture_;
  sf::Sprite sprite_;

  Status status_;

  sf::Font font_;
  sf::Text text_;
};


