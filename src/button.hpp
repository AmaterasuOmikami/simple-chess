#pragma once

#include <SFML/Graphics.hpp>

class Button : public sf::Drawable {
 public:
  Button(const sf::Vector2i &coordinates,
         const sf::Vector2i &size,
         const std::string &text);



  void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

 private:
  sf::Vector2i coordinates_;
  sf::Vector2i size_;

  sf::Texture texture_;
  sf::Sprite sprite_;

  sf::Font font_;
  sf::Text text_;
};


