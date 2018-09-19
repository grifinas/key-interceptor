#include "intercept_keys.h"


char codeToChar(unsigned short key) {
    char keyboard[] = "qwertyuiop____asdfghjkl_____zxcvbnm____________________789-456+123";
    char retkey = '_';

    unsigned short start = CODE_KB_START;
    unsigned short end = CODE_KB_END - 16 + 1;

    if (key >= start && key < end) {
        retkey = keyboard[key];
    }

    if (retkey == '_') {
        throw "Unsuported key";
    }

    return retkey;
}

unsigned short charToCode(const char key) {
    if (key == '_') {
        throw "Unsuported key";
    }
    char keyboard[] = "qwertyuiop____asdfghjkl_____zxcvbnm____________________789-456+123";
    unsigned short i=0;
    for (; i<CODE_KB_END - CODE_KB_START + 1; i++) {
        if (key == keyboard[i]) {
            break;
        }
    }

    return i+CODE_KB_START;
}

unsigned short nextUsableCode(unsigned short now) {
    now++;
    if (now <= CODE_KB_START) {
        return CODE_KB_START;
    }
    if (now <= CODE_P) {
        return now;
    }
    if (now <= CODE_A) {
        return CODE_A;
    }
    if (now <= CODE_L) {
        return now;
    }
    if (now <= CODE_Z) {
        return CODE_Z;
    }
    if (now <= CODE_M) {
        return now;
    }
    if (now <= 71) {
        return 71;
    }
    if (now <= 81) {
        return now;
    }
    throw "ran out";
}
