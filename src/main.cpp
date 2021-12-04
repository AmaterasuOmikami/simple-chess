#include "menu.hpp"

int main() {
  // TODO: settings menu
  // TODO: Game menu name window
  // TODO: Sound (add function for lib to validate capture and casual move)
  // TODO: Back button
  // TODO: Show fen
  Menu menu;
  while (menu.IsOpen()) {
    menu.Events();
    menu.Display();
  }

  return 0;
}