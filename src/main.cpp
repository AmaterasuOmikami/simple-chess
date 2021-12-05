#include "menu.hpp"

int main() {
  // TODO: Back button
  // TODO: Show fen
  Menu menu;
  while (menu.IsOpen()) {
    menu.Events();
    menu.Display();
  }

  return 0;
}