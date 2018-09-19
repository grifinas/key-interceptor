#pragma once
#include <map>

class KeyboardMap{
    public:
        bool hasKey(unsigned short key);
        void setKey(unsigned short key, unsigned short value);
        void setKey(const char key, unsigned short value);
        void setName(wchar_t *name);
        bool isNamed(const wchar_t *name);
        unsigned short getKey(unsigned short, unsigned short);
        unsigned short getKey(unsigned short key);
    private:
        std::map<unsigned short, unsigned short> keys;
        wchar_t *name;
};
