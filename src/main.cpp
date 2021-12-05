#include "menu.hpp"

int main() {
  Menu menu;
  while (menu.IsOpen()) {
    menu.Events();
    menu.Display();
  }

  return 0;
}