#ifndef ALYAC_CONSOLEUI_CONSOLEUI_HPP
#define ALYAC_CONSOLEUI_CONSOLEUI_HPP

#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <fcntl.h>
#include <string>
#include "common/StringDefine.h"

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
#define WINDOWS
#else
#undef WINDOWS
#endif

enum AnsiColor
{
    ANSI_COLOR_BLACK = 0,
    ANSI_COLOR_RED,
    ANSI_COLOR_GREEN,
    ANSI_COLOR_YELLOW,
    ANSI_COLOR_BLUE,
    ANSI_COLOR_MAGENTA,
    ANSI_COLOR_CYAN,
    ANSI_COLOR_WHITE,
    ANSI_COLOR_NONE,
};

enum VIRTUAL_KEYS
{
    VKEY_UP = 257,
    VKEY_DOWN,
    VKEY_LEFT,
    VKEY_RIGHT,
};

class ConsoleUI
{
public:
    ConsoleUI() : baseX(0), baseY(0) {;}
    void CursorUp(int n);
    void SetAsBasePos();
    void GotoXY(int x, int y);
    void RestoreDefaultColor();
    void DirectSgr(int sgrCode);
    void SetForeground(int color, bool bright);
    void SetBackground(int color, bool bright);
    void SetColor(int fColor, bool fgBright, int bColor, bool bgBright);
    void Print(const char* str);
    void PrintColored(const char* str, int color, bool bright, int bgColor = ANSI_COLOR_NONE, bool bgBright = false);
    void EnableLineWrap();
    void DisableLineWrap();
    void Flush();
    void NewLine();
    int GetKey();
    bool IsRedirected();
private:
    int baseX;
    int baseY;
};

inline void ConsoleUI::SetAsBasePos()
{
    int ttyFd = 0;
    char ch;
    bool readFail = false;
    ayn::String rowString;

    printf("\x1b[6n");
    fflush(stdout);

    ttyFd = open("/dev/tty", O_RDONLY);
    ch = 0;
    rowString = "";

    read(ttyFd, &ch, 1);
    read(ttyFd, &ch, 1);
    read(ttyFd, &ch, 1);

    while (ch != ';')
        {
        rowString = rowString + ch;
        if (read(ttyFd, &ch, 1) == 0) { readFail = true; break; }
        }

    if (!readFail)
        {
        baseY = atoi(rowString.c_str())-1;
        }
    baseX = 0;

    while (ch != 'R')
        {
        if (read(ttyFd, &ch, 1) == 0) { readFail = true; break; }
        }

    close(ttyFd);
}

inline void ConsoleUI::NewLine()
{
    printf("\n");
}

inline void ConsoleUI::CursorUp(int n)
{
    printf("\x1b[%dA", n);
}

inline void ConsoleUI::GotoXY(int x, int y)
{
    printf("\x1b[%d;%dH", y+baseY+1, x+baseX+1);
}

inline void ConsoleUI::RestoreDefaultColor()
{
    printf("\x1b[0m");
}

inline void ConsoleUI::DirectSgr(int sgrCode)
{
    printf("\x1b[%dm", sgrCode);
}

inline void ConsoleUI::SetForeground(int color, bool bright)
{
    int colorBase = bright ? 90 : 30;

    printf("\x1b[%dm", color + colorBase);
}

inline void ConsoleUI::SetBackground(int color, bool bright)
{
    int colorBase = bright ? 100 : 40;

    printf("\x1b[%dm", color + colorBase);
}

inline void ConsoleUI::SetColor(int fColor, bool fgBright, int bColor, bool bgBright)
{
    SetForeground(fColor, fgBright);
    SetBackground(bColor, bgBright);
}

inline void ConsoleUI::Print(const char* str)
{
    printf("%s", str);
}

inline void ConsoleUI::Flush()
{
    fflush(stdout);
}

inline bool ConsoleUI::IsRedirected()
{
    return isatty(STDOUT_FILENO);
}

inline void ConsoleUI::PrintColored(const char* str, int color, bool bright, int bgColor, bool bgBright)
{
    SetForeground(color, bright);
    if (bgColor != ANSI_COLOR_NONE) { SetBackground(bgColor, bgBright); }
    Print(str);
    RestoreDefaultColor();
}

inline int ConsoleUI::GetKey()
{
    char ch = getchar();

    if (ch >= 'a' && ch <= 'z') { return ch; }
    if (ch >= 'A' && ch <= 'Z') { return ch; }
    if (ch >= '0' && ch <= '9') { return ch; }

    if (ch == 0x1b)
        {
        ch = getchar();
        if (ch == 0x5b)
        {
        ch = getchar();
        }
        }

    if (ch == 0x41) { return VKEY_UP; }
    if (ch == 0x42) { return VKEY_DOWN; }
    if (ch == 0x43) { return VKEY_RIGHT; }
    if (ch == 0x44) { return VKEY_LEFT; }

    return ch;
}

inline void ConsoleUI::EnableLineWrap()
{
    printf("\x1b[7h");
    Flush();
}

inline void ConsoleUI::DisableLineWrap()
{
    printf("\x1b[7l");
    Flush();
}
#endif // ALYAC_CONSOLEUI_CONSOLEUI_HPP
