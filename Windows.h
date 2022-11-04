#pragma once
#include<iostream>
#include<Windows.h>

// this class to create a window for displaying the whole game

class Windows
{
public:
    Windows();
    static void DisableResizeWindow(); 
    static void gotoXY( int, int);
    static void TextColor(int, int);
    static void Nocursortype();
};
