#pragma once

#include <SDL2/SDL.h>
#ifdef _WIN32
#include <windows.h>
#endif
#include <stdint.h>

void gotoNextMulti(void);
void textMarkerMoveLeft(void);
void textMarkerMoveRight(void);
void textCharPrevious(void);
void textCharNext(void);
void readKeyModifiers(void);
void handleKeyRepeat(SDL_Scancode scancode);
void keyUpHandler(SDL_Scancode scancode);
void keyDownHandler(SDL_Scancode scancode, SDL_Keycode keycode);
void handleTextEditInputChar(char textChar);

#if defined _WIN32 && !defined _DEBUG
LRESULT CALLBACK lowLevelKeyboardProc(int32_t nCode, WPARAM wParam, LPARAM lParam);
#endif
