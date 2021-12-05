#include "menu.hpp"

int main() {
  // TODO: Back button
  Menu menu;
  while (menu.IsOpen()) {
    menu.Events();
    menu.Display();
  }

  return 0;
}