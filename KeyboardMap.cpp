#include "KeyboardMap.h"
#include "intercept_keys.h"



bool KeyboardMap::hasKey(unsigned short key) {
    return this->keys.find(key) != this->keys.end();
}

void KeyboardMap::setKey(unsigned short key, unsigned short value) {
    this->keys[key] = value;
}

void KeyboardMap::setKey(const char key, unsigned short value) {
    this->keys[charToCode(key)] = value;
}

unsigned short KeyboardMap::getKey(unsigned short key, unsigned short def) {
    if (!this->hasKey(key)) {
        return def;
    }

    return this->keys[key];
}

unsigned short KeyboardMap::getKey(unsigned short key) {
    if (!this->hasKey(key)) {
        return 0;
    }

    return this->keys[key];
}

void KeyboardMap::setName(wchar_t *name) {
    this->name = name;
}

bool KeyboardMap::isNamed(const wchar_t *name) {
    int i = 0;
    while (true) {
        char first = this->name[i];
        char second = name[i];
        if (first != second) {
            return false;
        }

        if (first == '\0') {
            break;
        }

        i++;
    }

    return true;
}
