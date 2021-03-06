//
// Created by realbro on 1/23/20.
//
#include <stdio.h>

#include "ConsoleGUI.h"

int main(int argc, char **argv) {
  ConsoleGUI gui;
  gui.Initialize();

  bool exitLoop = false;
  while (!exitLoop) {
    int key = gui.GetKey();
    switch (key) {
      case 'q':
      case 'Q':exitLoop = true;
        break;
      case VKEY_UP:
        if (gui.selectedIndex - 1 >= 0) gui.selectedIndex--;
        else if (gui.viewBase - 1 >= 0) gui.viewBase--;
        break;
      case VKEY_DOWN:
        if (gui.selectedIndex + 1 <= 4) gui.selectedIndex++;
        else if (gui.viewBase + gui.selectedIndex < 5) gui.viewBase++;

        break;
    }

    if (key != 'q' && key != 'Q') {
      gui.DrawPanel();
    }
  }

  gui.GotoXY(0, 59);
}