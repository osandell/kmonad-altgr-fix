#include "framework.h"
#include "coding-keyboard-remapper.h"
#include "headers/stdafx.h"
#include "headers/interception.h"
#include "headers/utils.h"
#include <thread>
#include <string>
#include <iostream>
#include <vector>


using namespace std;

namespace scancode {
    enum {
        esc = 0x01,
        one = 0x02,
        two = 0x03,
        three = 0x04,
        four = 0x05,
        five = 0x06,
        six = 0x07,
        seven = 0x08,
        eight = 0x09,
        nine = 0x0A,
        zero = 0x0B,
        dash = 0x0C,
        equals = 0x0D,
        backSpace = 0x0E,
        tab = 0x0F,
        q = 0x10,
        w = 0x11,
        e = 0x12,
        r = 0x13,
        t = 0x14,
        y = 0x15,
        u = 0x16,
        i = 0x17,
        o = 0x18,
        p = 0x19,
        leftBrace = 0x1A,
        rightBrace = 0x1B,
        enter = 0x1C,
        ctrl = 0x1D,
        ctrl_win = 0x11,
        leftWin = 0x5b,
        leftWin_win = 0x5b,
        rightWin = 0x5c,
        a = 0x1E,
        s = 0x1F,
        s_win = 0x53,
        d = 0x20,
        f = 0x21,
        g = 0x22,
        h = 0x23,
        j = 0x24,
        k = 0x25,
        l = 0x26,
        semicolon = 0x27,
        apostrophe = 0x28,
        backQuote = 0x29,
        leftShift = 0x2A,
        backSlash = 0x2B,
        lessThan = 0x56,
        z = 0x2C,
        x = 0x2D,
        c = 0x2E,
        v = 0x2F,
        b = 0x30,
        n = 0x31,
        m = 0x32,
        comma = 0x33,
        period = 0x34,
        slash = 0x35,
        rightShift = 0x36,
        keypadAsterisk = 0x37,
        alt = 0x38,
        space = 0x39,
        capsLock = 0x3A,
        f1 = 0x3B,
        f2 = 0x3C,
        f3 = 0x3D,
        f4 = 0x3E,
        f5 = 0x3F,
        f6 = 0x40,
        f7 = 0x41,
        f8 = 0x42,
        f9 = 0x43,
        f10 = 0x44,
        numLock = 0x45,
        scrollLock = 0x46,
        key7 = 0x47,
        key8 = 0x48,
        key9 = 0x49,
        keyMinus = 0x4A,
        key4 = 0x4B,
        key5 = 0x4C,
        key6 = 0x4D,
        keyPlus = 0x4E,
        key1 = 0x4F,
        key2 = 0x50,
        key3 = 0x51,
        key0 = 0x52,
        keyDot = 0x53,
        f11 = 0x57,
        f12 = 0x58,
        keyEnter = 0x9C,
        keyDivide = 0xB5,
        home = 0xC7,
        up = 0xC8,
        pgUp = 0xC9,
        left = 0xCB,
        right = 0xCD,
        end = 0xCF,
        down = 0xD0,
        pgDown = 0xD1,
        insert = 0xD2,
        del = 0xD3

    };
}

InterceptionKeyStroke
esc_down = { scancode::esc     , INTERCEPTION_KEY_DOWN, 0 },
leftAlt_down = { scancode::alt    , INTERCEPTION_KEY_DOWN, 0 },
rightAlt_down = { scancode::alt    , INTERCEPTION_KEY_DOWN | INTERCEPTION_KEY_E0, 0 },
leftCtrl_down = { scancode::ctrl    , INTERCEPTION_KEY_DOWN, 0 },
rightCtrl_down = { scancode::ctrl    , INTERCEPTION_KEY_DOWN | INTERCEPTION_KEY_E0, 0 },
leftShift_down = { scancode::leftShift    , INTERCEPTION_KEY_DOWN, 0 },
leftShift_down2 = { scancode::leftShift      , INTERCEPTION_KEY_DOWN | INTERCEPTION_KEY_E0, 0 },
rightShift_down = { scancode::rightShift    , INTERCEPTION_KEY_DOWN, 0 },
leftWin_down = { scancode::leftWin    , INTERCEPTION_KEY_DOWN | INTERCEPTION_KEY_E0, 0 },
rightWin_down = { scancode::rightWin    , INTERCEPTION_KEY_DOWN | INTERCEPTION_KEY_E0, 0 },
capsLock_down = { scancode::capsLock, INTERCEPTION_KEY_DOWN, 0 },
backQuote_down = { scancode::backQuote, INTERCEPTION_KEY_DOWN, 0 },
lessThan_down = { scancode::lessThan, INTERCEPTION_KEY_DOWN, 0 },
d_down = { scancode::d, INTERCEPTION_KEY_DOWN, 0 },
h_down = { scancode::h, INTERCEPTION_KEY_DOWN, 0 },
j_down = { scancode::j, INTERCEPTION_KEY_DOWN, 0 },
k_down = { scancode::k, INTERCEPTION_KEY_DOWN, 0 },
l_down = { scancode::l, INTERCEPTION_KEY_DOWN, 0 },
left_down = { scancode::left, INTERCEPTION_KEY_DOWN | INTERCEPTION_KEY_E0, 0 },
down_down = { scancode::down, INTERCEPTION_KEY_DOWN | INTERCEPTION_KEY_E0, 0 },
down_down_laptop = { scancode::key2, INTERCEPTION_KEY_DOWN | INTERCEPTION_KEY_E0, 0 },
up_down = { scancode::up, INTERCEPTION_KEY_DOWN | INTERCEPTION_KEY_E0, 0 },
up_down_laptop = { scancode::key8, INTERCEPTION_KEY_DOWN | INTERCEPTION_KEY_E0, 0 },
kp8_down = { scancode::key8, INTERCEPTION_KEY_DOWN, 0 },
right_down = { scancode::right, INTERCEPTION_KEY_DOWN | INTERCEPTION_KEY_E0, 0 },
tab_down = { scancode::tab, INTERCEPTION_KEY_DOWN, 0 },
del_down = { scancode::del, INTERCEPTION_KEY_DOWN | INTERCEPTION_KEY_E0, 0 },
esc_up = { scancode::esc     , INTERCEPTION_KEY_UP  , 0 },
leftAlt_up = { scancode::alt    , INTERCEPTION_KEY_UP, 0 },
rightAlt_up = { scancode::alt    , INTERCEPTION_KEY_UP | INTERCEPTION_KEY_E0, 0 },
leftCtrl_up = { scancode::ctrl    , INTERCEPTION_KEY_UP  , 0 },
rightCtrl_up = { scancode::ctrl    , INTERCEPTION_KEY_UP | INTERCEPTION_KEY_E0, 0 },
leftShift_up = { scancode::leftShift    , INTERCEPTION_KEY_UP, 0 },
leftShift_up2 = { scancode::leftShift    , INTERCEPTION_KEY_UP | INTERCEPTION_KEY_E0, 0 },
rightShift_up = { scancode::rightShift    , INTERCEPTION_KEY_UP, 0 },
leftWin_up = { scancode::leftWin    , INTERCEPTION_KEY_UP | INTERCEPTION_KEY_E0, 0 },
rightWin_up = { scancode::rightWin    , INTERCEPTION_KEY_UP | INTERCEPTION_KEY_E0, 0 },
capsLock_up = { scancode::capsLock, INTERCEPTION_KEY_UP  , 0 },
backQuote_up = { scancode::backQuote, INTERCEPTION_KEY_UP, 0 },
lessThan_up = { scancode::lessThan, INTERCEPTION_KEY_UP, 0 },
d_up = { scancode::d, INTERCEPTION_KEY_UP, 0 },
h_up = { scancode::h, INTERCEPTION_KEY_UP, 0 },
j_up = { scancode::j, INTERCEPTION_KEY_UP, 0 },
k_up = { scancode::k, INTERCEPTION_KEY_UP, 0 },
l_up = { scancode::l, INTERCEPTION_KEY_UP, 0 },
left_up = { scancode::left, INTERCEPTION_KEY_UP | INTERCEPTION_KEY_E0, 0 },
down_up = { scancode::down, INTERCEPTION_KEY_UP | INTERCEPTION_KEY_E0, 0 },
down_up_laptop = { scancode::key2, INTERCEPTION_KEY_UP | INTERCEPTION_KEY_E0, 0 },
up_up = { scancode::up, INTERCEPTION_KEY_UP | INTERCEPTION_KEY_E0, 0 },
up_up_laptop = { scancode::key8, INTERCEPTION_KEY_UP | INTERCEPTION_KEY_E0, 0 },
kp8_up = { scancode::key8, INTERCEPTION_KEY_UP, 0 },
right_up = { scancode::right, INTERCEPTION_KEY_UP | INTERCEPTION_KEY_E0, 0 },
tab_up = { scancode::tab, INTERCEPTION_KEY_UP, 0 },
del_up = { scancode::del, INTERCEPTION_KEY_UP | INTERCEPTION_KEY_E0, 0 };


bool operator==(const InterceptionKeyStroke& first,
    const InterceptionKeyStroke& second) {
    return first.code == second.code && first.state == second.state;
}



int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)


       
    //int main()
{
   
    

    InterceptionContext context;
    InterceptionDevice device;
    InterceptionKeyStroke kstroke;

    raise_process_priority();

    context = interception_create_context();

    interception_set_filter(context, interception_is_keyboard,
        INTERCEPTION_FILTER_KEY_ALL);

    while (interception_receive(context, device = interception_wait(context),
        (InterceptionStroke*)&kstroke, 1) > 0) {

        vector<InterceptionKeyStroke> kstrokes;

                  
    if (kstroke == rightAlt_down) {
         kstrokes.push_back(kp8_down);
    }
    else if (kstroke == rightAlt_up) {
        kstrokes.push_back(kp8_up);
    }
    else
        kstrokes.push_back(kstroke);
   
        if (kstrokes.size() > 0) {
            interception_send(context, device,
                (InterceptionStroke*)&kstrokes[0],
                kstrokes.size());
        }
    }

    interception_destroy_context(context);

    return false;
}

