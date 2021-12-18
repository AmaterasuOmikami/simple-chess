#include "menu.hpp"

int main() {
  Menu menu;
  while (menu.IsOpen()) {
    menu.Display();
    menu.Events();
  }
}