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
        /*
        if (selectedIndex-1>=0) { selectedIndex--; }
        else if (viewBase-1>=0) { viewBase--; }
         */
        break;
      case VKEY_DOWN:
        /*
        if (viewBase+selectedIndex+1 >= excludeList.size()) {;}
        else if (selectedIndex+1<=15) { selectedIndex++; }
        else if (viewBase+selectedIndex < excludeList.size()) { viewBase++; }
         */
        break;
    }
  }

  gui.GotoXY(0, 59);
}