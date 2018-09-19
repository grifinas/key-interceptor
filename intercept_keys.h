#pragma once

enum {
    CODE_KB_START = 16,
    CODE_KB_END = 81,

    CODE_Q = 16,
    CODE_W = 17,
    CODE_E = 18,
    CODE_R = 19,
    CODE_T = 20,
    CODE_Y = 21,
    CODE_U = 22,
    CODE_I = 23,
    CODE_O = 24,
    CODE_P = 25,

    CODE_A = 30,
    CODE_S = 31,
    CODE_D = 32,
    CODE_F = 33,
    CODE_G = 34,
    CODE_H = 35,
    CODE_J = 36,
    CODE_K = 37,
    CODE_L = 38,

    CODE_Z = 44,
    CODE_X = 45,
    CODE_C = 46,
    CODE_V = 47,
    CODE_B = 48,
    CODE_N = 49,
    CODE_M = 50
} ;

char codeToChar(unsigned short key);

unsigned short charToCode(const char key);

unsigned short nextUsableCode(unsigned short);
