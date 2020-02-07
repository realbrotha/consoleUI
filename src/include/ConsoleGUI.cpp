//
// Created by realbro on 2/6/20.
//

#include "ConsoleGUI.h"

struct termios ConsoleGUI::saved_ = {0,};

void ConsoleGUI::Initialize() {
  //do something
  DrawBackground();
}

void ConsoleGUI::DrawBackground() {

  SetNoEcho();
  PrintColored("WELCOME TEST STRING ABCDEGGSADF SAFD 간드아아아 !@#%$!@#!@#!@#",
               ANSI_COLOR_WHITE,
               true);
  RestoreDefaultColor();
  NewLine();

  for (int j = 0; j < 19; j++) {
    for (int i = 0; i < 35; i++) {
      DirectSgr(color_infos_[background_array_[j][i]]);
      Print("  ");
    }
    RestoreDefaultColor();
    NewLine();
  }

  CursorUp(20);
  SetAsBasePos();

  DrawPanel();
}

void ConsoleGUI::DrawPanel() {
  GotoXY(0, 1);

  for (int j = 0; j < 17; j++) {
    for (int i = 0; i < 35; i++) {
      DirectSgr(color_infos_[background_array_[j][i]]);
      Print("  ");
    }
    RestoreDefaultColor();
    NewLine();
  }

  GotoXY(0, 1);
  PrintColored("     MENU-TOP1-Title", ANSI_COLOR_WHITE, true, ANSI_COLOR_BLACK, true);

  GotoXY(18, 1);
  PrintColored("               MENU-SUB2-TITLE     ", ANSI_COLOR_WHITE, true, ANSI_COLOR_BLACK, false);

  GotoXY(0, selectedIndex + 2);
  PrintColored("              ",ANSI_COLOR_WHITE,true,ANSI_COLOR_YELLOW,false);

  DrawChildAttr();
  GotoXY(0, 18);
  PrintColored(" Key Input Message",ANSI_COLOR_WHITE,true, ANSI_COLOR_BLACK,false);
  GotoXY(26, 18);
  PrintColored("TEST 33333333", ANSI_COLOR_WHITE, true, ANSI_COLOR_WHITE, false);
  GotoXY(0, 19);
  PrintColored(" TEST 44444",ANSI_COLOR_WHITE,true,ANSI_COLOR_BLACK,false);
  GotoXY(70, selectedIndex + 2);

  Flush();
}


void ConsoleGUI::DrawChildAttr() {
  constexpr int kMAX_MENU_SIZE = 5;

  for(int i=0; i<5; i++)
  {
    if (viewBase + i < kMAX_MENU_SIZE)
    {
      if (selectedIndex == i)
      {
        GotoXY(0, 2+i);
        PrintColored(" On Cursor         ", ANSI_COLOR_BLACK, false, ANSI_COLOR_YELLOW, false);
        GotoXY(19, 2+i);
        PrintColored(" On Cursor               ", ANSI_COLOR_BLACK, false, ANSI_COLOR_YELLOW, false);
      }
      else
      {
        GotoXY(0, 2+i);
        PrintColored(" TEST String 11", ANSI_COLOR_WHITE, true, ANSI_COLOR_BLACK, true);
        GotoXY(19, 2+i);
        PrintColored(" TEST String 22", ANSI_COLOR_WHITE, true, ANSI_COLOR_BLACK, false);
      }
    }
  }
}

void ConsoleGUI::SetEcho() {
  tcsetattr(STDIN_FILENO, TCSANOW, &saved_);
}

void ConsoleGUI::SetNoEcho() {
  tcgetattr(STDIN_FILENO, &saved_);
  atexit(SetEcho);

  struct termios attr = {0,};
  tcgetattr(STDIN_FILENO, &attr);
  attr.c_lflag &= ~(ICANON | ECHO);
  attr.c_cc[VMIN] = 1;
  attr.c_cc[VTIME] = 0;
  tcsetattr(STDIN_FILENO, TCSAFLUSH, &attr);
}


