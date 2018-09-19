#include "interception.h"
#include "intercept_keys.h"
#include "KeyboardMap.h"
#include "stdio.h"
#include "list"
#include <fstream>
#include <string>
#include <iostream>
#include <map>
#include <unordered_map>

enum ScanCode
{
    SCANCODE_ESC = 0x01
};

typedef std::list<KeyboardMap*> ManyKeyboards;

wchar_t* getKeyboardHWID() {
    InterceptionContext context;
    InterceptionDevice device;
    InterceptionStroke stroke;

    wchar_t *hardware_id = new wchar_t[500];


    context = interception_create_context();

    interception_set_filter(context, interception_is_keyboard, INTERCEPTION_FILTER_KEY_DOWN);

    while(interception_receive(context, device = interception_wait(context), &stroke, 1) > 0)
    {
        if(interception_is_keyboard(device))
        {
            InterceptionKeyStroke keystroke = *(InterceptionKeyStroke *) &stroke;

            if(keystroke.code == SCANCODE_ESC) {
                printf("Exiting because esc\r\n");
                break;
            }

        }

        size_t length = interception_get_hardware_id(context, device, hardware_id, 1000);

        if(length > 0 && length < 1000) {
            interception_destroy_context(context);
            return hardware_id;
        }

        interception_send(context, device, &stroke, 1);
    }

    interception_destroy_context(context);

    throw "Broke out of while";
}

ManyKeyboards getMappedKeyboards() {
    ManyKeyboards keyboards;

    std::ifstream myfile ("kbconfig.txt");
    std::string line;
    unsigned short start = nextUsableCode(0);
    int kb_nmb = 1;

    while (std::getline(myfile, line)) {
        KeyboardMap* kb = new KeyboardMap;
        for (int i=0; i<line.length(); i++) {
            char c = line[i];
            kb->setKey(c, start);
            start = nextUsableCode(start);
        }
        std::cout << "Press any key on the " << kb_nmb++ << " keyboard" << std::endl;
        kb->setName(getKeyboardHWID());
        keyboards.push_front(kb);
    }

    myfile.close();

    return keyboards;
}

int main()
{
    ManyKeyboards keyboards = getMappedKeyboards();
    std::cout << "Keyboards ready" << std::endl;

    InterceptionContext context;
    InterceptionDevice device;
    InterceptionKeyStroke stroke;

    wchar_t hardware_id[500];

    context = interception_create_context();

    interception_set_filter(context, interception_is_keyboard, INTERCEPTION_FILTER_KEY_DOWN | INTERCEPTION_FILTER_KEY_UP);
    // interception_set_filter(context, interception_is_mouse, INTERCEPTION_FILTER_MOUSE_LEFT_BUTTON_DOWN);
    interception_set_filter(context, interception_is_invalid, INTERCEPTION_FILTER_KEY_DOWN);

    while(device = interception_wait(context) > 0)
    {
        if (interception_receive(context, device, (InterceptionStroke *)&stroke, 1) <= 0) {
            break;
        }
        if(interception_is_keyboard(device))
        {
            if(stroke.code == SCANCODE_ESC) break;

            size_t length = interception_get_hardware_id(context, device, hardware_id, sizeof(hardware_id));

            if(length > 0 && length < sizeof(hardware_id)) {
                for (auto kb: keyboards) {
                    if (kb->isNamed(hardware_id)) {
                        unsigned short n = kb->getKey(stroke.code, 2);
                        stroke.code = n;
                        break;
                    }
                }
            }
        } else {
            size_t length = interception_get_hardware_id(context, device, hardware_id, sizeof(hardware_id));
        }

        printf("hwid: %S\r\n", hardware_id);




        interception_send(context, device, (InterceptionStroke *)&stroke, 1);
    }

    interception_destroy_context(context);

    return 0;
}
