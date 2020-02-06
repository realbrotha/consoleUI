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

  DrawPanel(console);
}

void ConsoleGUI::DrawPanel(ConsoleImpl &console) {
  console.GotoXY(0, 1);

  for (int j = 0; j < 17; j++) {
    for (int i = 0; i < 35; i++) {
      console.DirectSgr(color_infos_[background_array_[j][i]]);
      console.Print("  ");
    }
    console.RestoreDefaultColor();
    console.NewLine();
  }

  console.GotoXY(0, 1);
  console.PrintColored("     TEST1     ", ANSI_COLOR_WHITE, true, ANSI_COLOR_BLUE, true);

  console.GotoXY(18, 1);
  console.PrintColored("               Test2     ", ANSI_COLOR_WHITE, true, ANSI_COLOR_BLUE, false);

  console.GotoXY(0, selectedIndex + 2);
  console.PrintColored("                                                                      ",
                       ANSI_COLOR_WHITE,
                       true,
                       ANSI_COLOR_YELLOW,
                       false);

  console.GotoXY(0, 18);
  console.PrintColored(" Menu???????                                              ",
                       ANSI_COLOR_WHITE,
                       true,
                       ANSI_COLOR_BLUE,
                       false);
  console.GotoXY(26, 18);
  console.PrintColored("TEST 33333333", ANSI_COLOR_WHITE, true, ANSI_COLOR_BLUE, false);
  console.GotoXY(0, 19);
  console.PrintColored("                                                                      ",
                       ANSI_COLOR_WHITE,
                       true,
                       ANSI_COLOR_BLUE,
                       false);

  console.GotoXY(70, selectedIndex + 2);
  console.Flush();
}


