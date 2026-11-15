#include <X11/X.h>
static const unsigned int borderpx = 1; // border in pixels
static const unsigned int gappx = 15;   // gap in pixels
static const unsigned int snap = 32;    // snap in pixels

static const unsigned int systraypinning = 0; // 0 ->  follows selected monitor;
                                              // >0 -> pin systray to monitor X
static const unsigned int systrayspacing = 2;
static const int systraypinningfailfirst =
    1; // 1 -> if pinning fails, display systray on the first monitor;
       // False -> display systray on the last monitor
static const int showsystray = 1; // 0 ->  no systray; != 0 -> systray

static const int showbar = 1; // 0 -> no bar; != 0 -> bar
static const int topbar = 1;  // 0 -> means bottom bar; != 0 -> topbar

static const Bool viewontag = True;

static const char *fonts[] = {
    "Noto Sans Mono:size=12",
    // "JoyPixels:size=16:antialias=true:autohint=true",
};
static const char dmenufont[] = "Noto Sans Mono:size=12";
static const char col_gray1[] = "#282828"; // bar bg
static const char col_gray2[] = "#282828"; // unselected border
static const char col_gray3[] = "#ebdbb2"; // unselected workspaces && slstatus
static const char col_gray4[] = "#1d2021"; // selected workspace && title text
static const char col_gray5[] = "#a9b665"; // border
static const char col_cyan[] = "#BB7548";  // highlighted workspace, boarder

static const unsigned int baralpha = OPAQUE;
static const unsigned int borderalpha = OPAQUE;
static const char *colors[][3] = {
    //                fg         bg         border
    [SchemeNorm] = {col_gray3, col_gray1, col_gray2},
    [SchemeSel] = {col_gray4, col_cyan, col_cyan},
};
static const unsigned int alphas[][3] = {
    //               fg      bg        border
    [SchemeNorm] = {OPAQUE, baralpha, borderalpha},
    [SchemeSel] = {OPAQUE, baralpha, borderalpha},
};

// static const char *tags[] = { "I", "II", "III", "IV", "V", "VI", "VII",
// "VIII", "IX" };
static const char *tags[] = {"一", "二", "三", "四", "五",
                             "六", "七", "八", "九"};

static const Rule rules[] = {
    // xprop(1):
    //	WM_CLASS(STRING) = instance, class
    //	WM_NAME(STRING) = title
    //  use tags mask to point an application to a specific workspace
    //
    // class  instance title tags mask isfloating monitor
    {"Gimp", NULL, NULL, 0, 0, -1},
    {"Xfce4-terminal", NULL, NULL, 0, 1, -1},
    {"librewolf", NULL, NULL, 0, 0, -1},
    {"guvcview", NULL, NULL, 0, 1, -1}};

/* layout(s) */
static const float mfact = 0.50; // factor of master area size [0.05..0.95]
static const int nmaster = 1;    // number of clients in master area
static const int resizehints =
    1; // 1 means respect size hints in tiled resizals

#include "layouts.c"

static const Layout layouts[] = {
    // symbol     arrange function
    {"[]=", tile},
    {"[M]", monocle},
    {"><>", NULL}, // NULL layout function -> floating behavior
    {NULL, NULL},
    // { "HHH",      grid },
};

// key definitions
#define MODKEY Mod4Mask
#define TAGKEYS(KEY, TAG)                                                      \
  {MODKEY, KEY, view, {.ui = 1 << TAG}},                                       \
      {MODKEY | ControlMask, KEY, toggleview, {.ui = 1 << TAG}},               \
      {MODKEY | ShiftMask, KEY, tag, {.ui = 1 << TAG}},                        \
      {MODKEY | ControlMask | ShiftMask, KEY, toggletag, {.ui = 1 << TAG}},

// helper for spawning shell commands in the pre dwm-5.0 fashion
#define SHCMD(cmd)                                                             \
  {                                                                            \
    .v = (const char *[]) { "/bin/sh", "-c", cmd, NULL }                       \
  }

// commands
static const char *scrotcmd[] = {
    "scrot",
    "-d3",
    "/home/sazabi/Pictures/screenshots/%Y-%m-%d-%s_$wx$h.jpg",
    NULL,
};
static const char *scrotfocusedcmd[] = {
    "scrot",
    "--focused",
    "/home/sazabi/Pictures/screenshots/%Y-%m-%d-%s_$wx$h.jpg",
    NULL,
};

static char dmenumon[2] = "0"; // use spawn to manipulate dmenumon cmd
static const char *dmenucmd[] = {
    "dmenu_run", "-m",      dmenumon, "-fn",    dmenufont, "-nb",     col_gray1,
    "-nf",       col_gray3, "-sb",    col_cyan, "-sf",     col_gray4, NULL,
};

static const char *filecmd[] = {
    "thunar",
    NULL,
};

static const char *calendar[] = {
    "gsimplecal",
    NULL,
};

static const char *taskmanager[] = {
    "xfce4-taskmanager",
    NULL,
};

static const char *termcmd[] = {
    "alacritty",
    NULL,
};

static const char *browser[] = {
    "firefox-bin",
    NULL,
};

static const char *browser2[] = {
    "qutebrowser",
    NULL,
};

static const char *browser3[] = {
    NULL,
    NULL,
};

static const char *spotifyterm[] = {"alacritty", "-e", "spotify_player", NULL};

// static const char *music[] = {
//     "spotty-tray",
//     "-i",
//     "/home/sazabi/Pictures/icons/ocarina.png",
//     NULL
// };

static const char *music[] = {
    "kitty",
    "kew",
    NULL
};

// spotty-tray definitions
static const char *spotifymenu[] = {"spotty-tray", "--menu", NULL};
static const char *spotifytoggle[] = {"spotty-tray", "--cmd", "toggle", NULL};


// static const char *spotifynext[] = {"spotty-tray", "--cmd", "next", NULL};
// static const char *spotifyprev[] = {"spotty-tray", "--cmd", "prev", NULL};
//

// Kew bindings 
static const char *playernext[] = {"playerctl", "-p", "kew", "next", NULL};
static const char *playerprev[] = {"playerctl", "-p", "kew", "previous", NULL};
static const char *playershuffle[] =  {"playerctl", "-p", "kew", "shuffle", "Toggle", NULL};

static const char *notes[] = {
    "obsidian",
    NULL,
};

static const char *webcam[] = {
    "guvcview",
    NULL,
};

static const char *logout[] = {
    "simplexit",
    NULL,
};

/* pulseaudio
 *
 * static const char *mutecmd[] = {
 *   "amixer", "-q", "set", "Master", "toggle", NULL,
 * };
 * static const char *volupcmd[] = {
 *   "amixer", "-q", "set", "Master", "5%+", "unmute", NULL,
 * };
 * static const char *voldowncmd[] = {
 *   "amixer", "-q", "set", "Master", "5%-", "unmute", NULL,
 * };
 * */

// pipewire
static const char *mutecmd[] = {
    "/home/sazabi/.scripts/voctl.sh",
    "mute",
    NULL,
};
static const char *unmutecmd[] = {
    "/home/sazabi/.scripts/voctl.sh",
    "mute",
    NULL,
};
static const char *volupcmd[] = {
    "/home/sazabi/.scripts/voctl.sh",
    "up",
    NULL,
};
static const char *voldowncmd[] = {
    "/home/sazabi/.scripts/voctl.sh",
    "down",
    NULL,
};

// change keyboard layout on the fly using dmenu
static const char *kbdlayout[] = {
    "/home/sazabi/.scripts/kbd.sh",
    NULL,
};

#include "selfrestart.c"
#include "shiftview.c"
#include "confine.c"

static Key keys[] = {
    // modifier   key   function  argument
    // ---------------- Latin --------------
    {
        0,
        XK_Home,
        spawn,
        {.v = scrotcmd},
    },
    {
        ShiftMask,
        XK_Home,
        spawn,
        {.v = scrotfocusedcmd},
    },
    {
        MODKEY,
        XK_p,
        spawn,
        {.v = dmenucmd},
    },
    {
        MODKEY | ShiftMask,
        XK_Return,
        spawn,
        {.v = filecmd},
    },
    {
        MODKEY,
        XK_x,
        spawn,
        {.v = logout},
    },
    {
        MODKEY,
        XK_b,
        togglebar,
        {0},
    },
    {
        MODKEY | ShiftMask,
        XK_o,
        spawn,
        {.v = browser2},
    },
    {
        MODKEY | ControlMask | ShiftMask,
        XK_o,
        spawn,
        {.v = browser3},
    },
    {
        MODKEY,
        XK_o,
        spawn,
        {.v = browser},
    },
    {
        MODKEY,
        XK_s,
        spawn,
        {.v = music},
    },
    {
        MODKEY,
        XK_l,
        spawn,
        {.v = spotifymenu},
    },
    /*{
        MODKEY,
        XK_n,
        spawn,
        {.v = notes},
    },*/
    {
        MODKEY,
        XK_g,
        spawn,
        {.v = webcam},
    },
    {
        MODKEY,
        XK_Return,
        spawn,
        {.v = termcmd},
    },
    {
        MODKEY,
        XK_j,
        focusstack,
        {.i = +1},
    },
    {
        MODKEY,
        XK_k,
        focusstack,
        {.i = -1},
    },
    {
        MODKEY,
        XK_Right,
        spawn,
        {.v = playernext },
    },
    {
        MODKEY,
        XK_Left,
        spawn,
        {.v = playerprev },
    },
    { MODKEY | ShiftMask, 
      XK_s,             
      spawn, 
      {.v = playershuffle } 
    },
    {
        MODKEY,
        XK_i,
        incnmaster,
        {.i = +1},
    },
    {
        MODKEY,
        XK_d,
        incnmaster,
        {.i = -1},
    },
    {
        MODKEY,
        XK_h,
        setmfact,
        {.f = -0.05},
    },
    {
        MODKEY,
        XK_l,
        setmfact,
        {.f = +0.05},
    },
    {
        MODKEY,
        XK_minus,
        setgaps,
        {.i = -1},
    },
    {
        MODKEY,
        XK_equal,
        setgaps,
        {.i = +1},
    },
    {
        MODKEY | ShiftMask,
        XK_equal,
        setgaps,
        {.i = 0},
    },
    {
        MODKEY,
        XK_q,
        killclient,
        {0},
    },
    {
        MODKEY | ControlMask,
        XK_comma,
        cyclelayout,
        {.i = -1},
    },
    {
        MODKEY | ControlMask,
        XK_period,
        cyclelayout,
        {.i = +1},
    },
    {
        MODKEY,
        XK_space,
        cyclelayout,
        {.i = +1},
    },
    {
        MODKEY | ShiftMask,
        XK_space,
        togglefloating,
        {0},
    },
    {
        MODKEY | ShiftMask,
        XK_b,
        togglefloating == NULL ? NULL : toggleconfine,
        {0},
    },
    {
        MODKEY,
        XK_comma,
        focusmon,
        {.i = -1},
    },
    {
        MODKEY,
        XK_period,
        focusmon,
        {.i = +1},
    },
    {
        MODKEY | ShiftMask,
        XK_comma,
        tagmon,
        {.i = -1},
    },
    {
        MODKEY | ShiftMask,
        XK_period,
        tagmon,
        {.i = +1},
    },
    {
        MODKEY | ShiftMask,
        XK_m,
        spawn,
        {.v = mutecmd},
    },
    {
        MODKEY | ShiftMask,
        XK_u,
        spawn,
        {.v = unmutecmd},
    },
    {
        MODKEY,
        XK_Down,
        spawn,
        {.v = voldowncmd},
    },
    {
        MODKEY,
        XK_Up,
        spawn,
        {.v = volupcmd},
    },
    {
        MODKEY | ShiftMask,
        XK_k,
        spawn,
        {.v = kbdlayout},
    },

    //-------------------------- Cyrilic ------------------------

    {
        MODKEY | ShiftMask,
        XK_Cyrillic_el,
        spawn,
        {.v = kbdlayout},
    },
    {
        MODKEY,
        XK_Cyrillic_ze,
        spawn,
        {.v = dmenucmd},
    },
    {
        MODKEY,
        XK_Cyrillic_che,
        spawn,
        {.v = logout},
    },
    {
        MODKEY,
        XK_Cyrillic_i,
        togglebar,
        {0},
    },
    {
        MODKEY | ShiftMask,
        XK_Cyrillic_shcha,
        spawn,
        {.v = browser2},
    },
    {
        MODKEY | ControlMask | ShiftMask,
        XK_Cyrillic_shcha,
        spawn,
        {.v = browser3},
    },
    {
        MODKEY,
        XK_Cyrillic_shcha,
        spawn,
        {.v = browser},
    },
    {
        MODKEY,
        XK_Cyrillic_yeru,
        spawn,
        {.v = music},
    },
    {
        MODKEY,
        XK_Cyrillic_te,
        spawn,
        {.v = notes},
    },
    {
        MODKEY,
        XK_Cyrillic_pe,
        spawn,
        {.v = webcam},
    },
    {
        MODKEY,
        XK_Cyrillic_o,
        focusstack,
        {.i = +1},
    },
    {
        MODKEY,
        XK_Cyrillic_el,
        focusstack,
        {.i = -1},
    },
    {
        MODKEY,
        XK_Cyrillic_sha,
        incnmaster,
        {.i = +1},
    },
    {
        MODKEY,
        XK_Cyrillic_ve,
        incnmaster,
        {.i = -1},
    },
    {
        MODKEY,
        XK_Cyrillic_er,
        setmfact,
        {.f = -0.05},
    },
    {
        MODKEY,
        XK_Cyrillic_de,
        setmfact,
        {.f = +0.05},
    },
    {
        MODKEY,
        XK_Cyrillic_shorti,
        killclient,
        {0},
    },
    {
        MODKEY | ControlMask,
        XK_Cyrillic_be,
        cyclelayout,
        {.i = -1},
    },
    {
        MODKEY | ControlMask,
        XK_Cyrillic_yu,
        cyclelayout,
        {.i = +1},
    },
    {
        MODKEY,
        XK_Cyrillic_be,
        focusmon,
        {.i = -1},
    },
    {
        MODKEY,
        XK_Cyrillic_yu,
        focusmon,
        {.i = +1},
    },
    {
        MODKEY | ShiftMask,
        XK_Cyrillic_be,
        tagmon,
        {.i = -1},
    },
    {
        MODKEY | ShiftMask,
        XK_Cyrillic_yu,
        tagmon,
        {.i = +1},
    },
    {
        MODKEY | ShiftMask,
        XK_Cyrillic_softsign,
        spawn,
        {.v = mutecmd},
    },
    {
        MODKEY | ShiftMask,
        XK_Cyrillic_ghe,
        spawn,
        {.v = unmutecmd},
    },

    TAGKEYS(XK_1, 0) TAGKEYS(XK_2, 1) TAGKEYS(XK_3, 2) TAGKEYS(XK_4, 3)
        TAGKEYS(XK_5, 4) TAGKEYS(XK_6, 5) TAGKEYS(XK_7, 6) TAGKEYS(XK_8, 7)
            TAGKEYS(XK_9, 8)};

// button definitions
// click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle,
// ClkClientWin and ClkRootWin
static Button buttons[] = {
    // click    event mask      button    function argument
    {
        ClkLtSymbol,
        0,
        Button1,
        setlayout,
        {0},
    },
    {
        ClkLtSymbol,
        0,
        Button3,
        setlayout,
        {.v = &layouts[2]},
    },
    {
        ClkWinTitle,
        0,
        Button2,
        zoom,
        {0},
    },
    {
        ClkStatusText,
        0,
        Button1,
        spawn,
        {.v = taskmanager},
    },
    {
        ClkStatusText,
        0,
        Button2,
        spawn,
        {.v = filecmd},
    },
    {
        ClkStatusText,
        0,
        Button3,
        spawn,
        {.v = calendar},
    },
    {
        ClkClientWin,
        MODKEY,
        Button1,
        movemouse,
        {0},
    },
    {
        ClkClientWin,
        MODKEY,
        Button2,
        togglefloating,
        {0},
    },
    {
        ClkClientWin,
        MODKEY,
        Button3,
        resizemouse,
        {0},
    },
    {
        ClkTagBar,
        0,
        Button1,
        view,
        {0},
    },
    {
        ClkTagBar,
        0,
        Button3,
        toggleview,
        {0},
    },
    {
        ClkTagBar,
        MODKEY,
        Button1,
        tag,
        {0},
    },
    {
        ClkTagBar,
        MODKEY,
        Button3,
        toggletag,
        {0},
    },
};
