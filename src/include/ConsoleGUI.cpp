//
// Created by realbro on 2/6/20.
//

#include "ConsoleGUI.h"

ConsoleGUI::ConsoleGUI() {
}

ConsoleGUI::~ConsoleGUI() {
}

void ConsoleGUI::Initialize() {
  //do something
  DrawBackground(console_);
}

void ConsoleGUI::DrawBackground(ConsoleImpl &console) {
  console.PrintColored("WELCOME TEST STRING ABCDEGGSADF SAFD 간드아아아 !@#%$!@#!@#!@#",
                       ANSI_COLOR_WHITE,
                       true);
  console.RestoreDefaultColor();
  console.NewLine();

  for (int j = 0; j < 19; j++) {
    for (int i = 0; i < 35; i++) {
      console.DirectSgr(color_infos_[background_array_[j][i]]);
      console.Print("  ");
    }
    console.RestoreDefaultColor();
    console.NewLine();
  }

  console.CursorUp(20);
  console.SetAsBasePos();
}
