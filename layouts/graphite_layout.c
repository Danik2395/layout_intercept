#include "../layout.h"

const __u16 qwerty2layout[KEY_CNT] = {
    // Numbers row
    [KEY_GRAVE]      = KEY_GRAVE,       // <TLDE> ` ~
    [KEY_1]          = KEY_1,           // <AE01> 1 !
    [KEY_2]          = KEY_2,           // <AE02> 2 @
    [KEY_3]          = KEY_3,           // <AE03> 3 #
    [KEY_4]          = KEY_4,           // <AE04> 4 $
    [KEY_5]          = KEY_5,           // <AE05> 5 %
    [KEY_6]          = KEY_6,           // <AE06> 6 ^
    [KEY_7]          = KEY_7,           // <AE07> 7 &
    [KEY_8]          = KEY_8,           // <AE08> 8 *
    [KEY_9]          = KEY_9,           // <AE09> 9 (
    [KEY_0]          = KEY_0,           // <AE10> 0 )
    [KEY_MINUS]      = KEY_LEFTBRACE,   // <AE11> [ {
    [KEY_EQUAL]      = KEY_RIGHTBRACE,  // <AE12> ] }

    // Top Letter Row
    [KEY_Q]          = KEY_B,           // <AD01> b B
    [KEY_W]          = KEY_L,           // <AD02> l L
    [KEY_E]          = KEY_D,           // <AD03> d D
    [KEY_R]          = KEY_W,           // <AD04> w W
    [KEY_T]          = KEY_Z,           // <AD05> z Z
    [KEY_Y]          = KEY_APOSTROPHE,  // <AD06> ' _  (Non standart shift)
    [KEY_U]          = KEY_F,           // <AD07> f F
    [KEY_I]          = KEY_O,           // <AD08> o O
    [KEY_O]          = KEY_U,           // <AD09> u U
    [KEY_P]          = KEY_J,           // <AD10> j J
    [KEY_LEFTBRACE]  = KEY_SEMICOLON,   // <AD11> ; :
    [KEY_RIGHTBRACE] = KEY_EQUAL,       // <AD12> = +
    [KEY_BACKSLASH]  = KEY_BACKSLASH,   // <BKSL> \ |

    // Home Letter Row
    [KEY_A]          = KEY_N,           // <AC01> n N
    [KEY_S]          = KEY_R,           // <AC02> r R
    [KEY_D]          = KEY_T,           // <AC03> t T
    [KEY_F]          = KEY_S,           // <AC04> s S
    [KEY_G]          = KEY_G,           // <AC05> g G
    [KEY_H]          = KEY_Y,           // <AC06> y Y
    [KEY_J]          = KEY_H,           // <AC07> h H
    [KEY_K]          = KEY_A,           // <AC08> a A
    [KEY_L]          = KEY_E,           // <AC09> e E
    [KEY_SEMICOLON]  = KEY_I,           // <AC10> i I
    [KEY_APOSTROPHE] = KEY_COMMA,       // <AC11> , ?  (Non standart shift)

    // Bottom Letter Row
    [KEY_Z]          = KEY_Q,           // <AB01> q Q
    [KEY_X]          = KEY_X,           // <AB02> x X
    [KEY_C]          = KEY_M,           // <AB03> m M
    [KEY_V]          = KEY_C,           // <AB04> c C
    [KEY_B]          = KEY_V,           // <AB05> v V
    [KEY_N]          = KEY_K,           // <AB06> k K
    [KEY_M]          = KEY_P,           // <AB07> p P
    [KEY_COMMA]      = KEY_DOT,         // <AB08> . >
    [KEY_DOT]        = KEY_MINUS,       // <AB09> - "  (Non standart shift)
    [KEY_SLASH]      = KEY_SLASH,       // <AB10> / <  (Non standart shift)
};

const __u16 qwerty2layout_shifted[KEY_CNT] = {
    // Underscore = Shift + KEY_MINUS
    [KEY_Y]          = KEY_MINUS,

    // Question = Shift + KEY_SLASH
    [KEY_APOSTROPHE] = KEY_SLASH,

    // Quotedbl = Shift + KEY_APOSTROPHE
    [KEY_DOT]        = KEY_APOSTROPHE,

    // Less = Shift + KEY_COMMA
    [KEY_SLASH]      = KEY_COMMA,

    // Greater = Shift + KEY_DOT
    [KEY_COMMA]      = KEY_DOT
};

__u16 remap_key_layout(__u16 keycode, bool is_shift)
{
    if (keycode >= KEY_MAX) return keycode;

    __u16 mapped = 0;
    if (is_shift)
    {
        mapped = qwerty2layout_shifted[keycode];
        if (mapped != 0) return mapped;
    }

    mapped = qwerty2layout[keycode];
    return mapped ? mapped : keycode;
}
