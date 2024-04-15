//
// Created by Jacob Ross on 4/14/24.
//

#ifndef BLOOM_ENGINE_KEYCODES_H
#define BLOOM_ENGINE_KEYCODES_H

#include "../../vendor/sdl2/2.30.1/include/SDL2/SDL.h"

enum class KeyCode {
    // Alphabetic keys
    A = SDLK_a,
    B = SDLK_b,
    C = SDLK_c,
    D = SDLK_d,
    E = SDLK_e,
    F = SDLK_f,
    G = SDLK_g,
    H = SDLK_h,
    I = SDLK_i,
    J = SDLK_j,
    K = SDLK_k,
    L = SDLK_l,
    M = SDLK_m,
    N = SDLK_n,
    O = SDLK_o,
    P = SDLK_p,
    Q = SDLK_q,
    R = SDLK_r,
    S = SDLK_s,
    T = SDLK_t,
    U = SDLK_u,
    V = SDLK_v,
    W = SDLK_w,
    X = SDLK_x,
    Y = SDLK_y,
    Z = SDLK_z,

    // Numeric keys
    NUM_1 = SDLK_1,
    NUM_2 = SDLK_2,
    NUM_3 = SDLK_3,
    NUM_4 = SDLK_4,
    NUM_5 = SDLK_5,
    NUM_6 = SDLK_6,
    NUM_7 = SDLK_7,
    NUM_8 = SDLK_8,
    NUM_9 = SDLK_9,
    NUM_0 = SDLK_0,


    // Special keys
    ESC = SDLK_ESCAPE,
    TILDE = SDLK_BACKQUOTE,
    TAB = SDLK_TAB,
    CAPS = SDLK_CAPSLOCK,
    LSHIFT = SDLK_LSHIFT,
    LCTRL = SDLK_LCTRL,
    WINDOWS = SDLK_LGUI,
    LALT = SDLK_LALT,
    SPACE = SDLK_SPACE,
    RALT = SDLK_RALT,
    MENU = SDLK_MENU,
    RCTRL = SDLK_RCTRL,
    RSHIFT = SDLK_RSHIFT,
    ENTER = SDLK_RETURN,
    BACKSLASH = SDLK_BACKSLASH,
    BACKSPACE = SDLK_BACKSPACE,

    // Function keys
    F1 = SDLK_F1,
    F2 = SDLK_F2,
    F3 = SDLK_F3,
    F4 = SDLK_F4,
    F5 = SDLK_F5,
    F6 = SDLK_F6,
    F7 = SDLK_F7,
    F8 = SDLK_F8,
    F9 = SDLK_F9,
    F10 = SDLK_F10,
    F11 = SDLK_F11,
    F12 = SDLK_F12,

    // Other keys
    PRT_SC = SDLK_PRINTSCREEN,
    INS = SDLK_INSERT,
    DEL = SDLK_DELETE,
    SCRL_LK = SDLK_SCROLLLOCK,
    HOME = SDLK_HOME,
    END = SDLK_END,
    PAUSE = SDLK_PAUSE,
    PG_UP = SDLK_PAGEUP,
    PG_DN = SDLK_PAGEDOWN,

    // Arrow keys
    ARROW_LEFT = SDLK_LEFT,
    ARROW_UP = SDLK_UP,
    ARROW_DOWN = SDLK_DOWN,
    ARROW_RIGHT = SDLK_RIGHT,

};

#endif //BLOOM_ENGINE_KEYCODES_H
