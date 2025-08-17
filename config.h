/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx = 3; /* border pixel of windows */
static const unsigned int snap = 32; /* snap pixel */


/* vanitygaps: currently turned-off */
static const unsigned int gappih = 0; /* horiz inner gap between windows */
static const unsigned int gappiv = 0; /* vert inner gap between windows */
static const unsigned int gappoh = 0; /* horiz outer gap between windows and screen edge */
static const unsigned int gappov = 0; /* vert outer gap between windows and screen edge */
static const int smartgaps = 0; /* 1 means no outer gap when there is only one window */

/* systray */
static const unsigned int systraypinning = 0;
/* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayonleft = 0; /* 0: systray in the right corner, >0: systray on left of status text */
static const unsigned int systrayspacing = 2; /* systray spacing */
static const int systraypinningfailfirst = 1;
/* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray = 1; /* 0 means no systray */
static const int showbar = 1; /* 0 means no bar */
static const int topbar = 1; /* 0 means bottom bar */

static const char *fonts[] = {
    "Noto Sans Mono:size=12:antialias=true:autohint=true",
    "JoyPixels:pixelsize=12:antialias=true:autohint=true",
};

static const char dmenufont[] = "Noto Sans Mono:size=12:antialias=true:autohint=true";

static const char col_gray1[] = "#222222";
static const char col_gray2[] = "#444444";
static const char col_gray3[] = "#bbbbbb";
static const char col_gray4[] = "#eeeeee";
static const char col_cyan[] = "#005577";
static const char *colors[][3] = {
    /*               fg         bg         border   */
    [SchemeNorm] = {col_gray3, col_gray1, col_gray2},
    [SchemeSel] = {col_gray4, col_cyan, col_cyan},
};

/* tagging */
static const char *tags[] = {"1", "10", "11", "100", "101", "110", "111", "1000", "1001"};

/* rules */
static const Rule rules[] = {
    /* class             instance    title       tags mask  isfloating  monitor */
    {"Gimp", NULL, NULL, 0, 0, -1},
    {"Xfce4-terminal", NULL, NULL, 0, 1, -1},
    {"textsnatcher", NULL, NULL, 0, 1, -1},
    {"librewolf", NULL, NULL, 0, 0, -1},
    {"guvcview", NULL, NULL, 0, 1, -1},
};

/* layout(s) */
static const float mfact = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster = 1; /* number of clients in master area */
static const int resizehints = 1; /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
    /* symbol     arrange function */
    {"瓦", tile}, /* first entry is default */
    {"漂う", NULL}, /* no layout function means floating behavior */
    {"一", monocle},
    {NULL, NULL},
};

/* key definitions */
#define MODKEY Mod1Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = {
    "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf",
    col_gray4, NULL
};

static const char *scrotcmd[] = {
    "scrot", "-d3", "/home/pedro/Pictures/screenshots/%Y-%m-%d-%s_$wx$h.jpg",NULL,
};
static const char *scrotfocusedcmd[] = {
    "scrot", "--focused", "/home/pedro/Pictures/screenshots/%Y-%m-%d-%s_$wx$h.jpg",NULL,
};

static const char *filecmd[] = {"thunar", NULL};
static const char *calendar[] = {"gsimplecal", NULL};
static const char *taskmanager[] = {"xfce4-taskmanager", NULL};
static const char *termcmd[] = {"alacritty", NULL};
static const char *browser[] = {"librewolf", NULL};
static const char *browser2[] = {"chromium", NULL};
static const char *browser3[] = {"qutebrowser", NULL};
static const char *music[] = {"spotify-tray", NULL};
static const char *notes[] = {"obsidian", NULL};
static const char *webcam[] = {"guvcview", NULL};
static const char *logout[] = {"archlinux-logout", NULL};

/* pipewire volume + brightness */
static const char *mutecmd[] = {"pamixer", "-m", NULL};
static const char *unmutecmd[] = {"pamixer", "-u", NULL};
static const char *volupcmd[] = {"pamixer", "-i", "5", NULL};
static const char *voldowncmd[] = {"pamixer", "-d", "5", NULL};
static const char *brightnessupcmd[] = {"brightnessctl", "set", "+10%", NULL};
static const char *brightnessdowncmd[] = {"brightnessctl", "set", "10%-", NULL};

/* scripts */
static const char *kbdlayout[] = {"/home/pedro/.scripts/kbd.sh", NULL};
static const char *restoremonitor[] = {"/home/pedro/.scripts/restore_monitor.sh", NULL};

static Key keys[] = {
    /* ---------- Latin ---------- */
    {0, XK_Home, spawn, {.v = scrotcmd}},
    {ShiftMask, XK_Home, spawn, {.v = scrotfocusedcmd}},
    {MODKEY, XK_p, spawn, {.v = dmenucmd}},
    {MODKEY | ShiftMask, XK_Return, spawn, {.v = filecmd}},
    {MODKEY, XK_x, spawn, {.v = logout}},
    {MODKEY, XK_b, togglebar, {0}},

    {MODKEY | ShiftMask, XK_o, spawn, {.v = browser2}},
    {MODKEY | ControlMask | ShiftMask, XK_o, spawn, {.v = browser3}},
    {MODKEY, XK_o, spawn, {.v = browser}},

    {MODKEY, XK_s, spawn, {.v = music}},
    {MODKEY, XK_n, spawn, {.v = notes}},
    {MODKEY, XK_g, spawn, {.v = webcam}},
    {MODKEY, XK_Return, spawn, {.v = termcmd}},

    {MODKEY, XK_j, focusstack, {.i = +1}},
    {MODKEY, XK_k, focusstack, {.i = -1}},

    {MODKEY, XK_Right, spawn, {.v = brightnessupcmd}},
    {MODKEY, XK_Left, spawn, {.v = brightnessdowncmd}},

    {MODKEY | ShiftMask, XK_i, incnmaster, {.i = +1}},
    {MODKEY | ShiftMask, XK_d, incnmaster, {.i = -1}},

    {MODKEY, XK_h, setmfact, {.f = -0.05}},
    {MODKEY, XK_l, setmfact, {.f = +0.05}},

    /* vanitygaps quick adjust + reset */
    {MODKEY, XK_minus, incrgaps, {.i = -1}},
    {MODKEY, XK_equal, incrgaps, {.i = +1}},
    {MODKEY | ShiftMask, XK_equal, defaultgaps, {0}},

    {MODKEY, XK_q, killclient, {0}},

    /* cyclelayouts (requires patch) */
    {MODKEY | ControlMask, XK_comma, cyclelayout, {.i = -1}},
    {MODKEY | ControlMask, XK_period, cyclelayout, {.i = +1}},
    {MODKEY, XK_space, cyclelayout, {.i = +1}},

    {MODKEY | ShiftMask, XK_space, togglefloating, {0}},

    {MODKEY, XK_comma, focusmon, {.i = -1}},
    {MODKEY, XK_period, focusmon, {.i = +1}},
    {MODKEY | ShiftMask, XK_comma, tagmon, {.i = -1}},
    {MODKEY | ShiftMask, XK_period, tagmon, {.i = +1}},

    /* audio */
    {MODKEY | ShiftMask, XK_m, spawn, {.v = mutecmd}},
    {MODKEY | ShiftMask, XK_u, spawn, {.v = unmutecmd}},
    {MODKEY, XK_Down, spawn, {.v = voldowncmd}},
    {MODKEY, XK_Up, spawn, {.v = volupcmd}},

    /* scripts */
    {MODKEY | ShiftMask, XK_k, spawn, {.v = kbdlayout}},
    {MODKEY | ControlMask | ShiftMask, XK_m, spawn, {.v = restoremonitor}},

    /* ---------- Cyrillic ---------- */
    {MODKEY | ShiftMask, XK_Cyrillic_el, spawn, {.v = kbdlayout}},
    {MODKEY, XK_Cyrillic_ze, spawn, {.v = dmenucmd}},
    {MODKEY, XK_Cyrillic_che, spawn, {.v = logout}},
    {MODKEY, XK_Cyrillic_i, togglebar, {0}},

    {MODKEY | ShiftMask, XK_Cyrillic_shcha, spawn, {.v = browser2}},
    {MODKEY | ControlMask | ShiftMask, XK_Cyrillic_shcha, spawn, {.v = browser3}},
    {MODKEY, XK_Cyrillic_shcha, spawn, {.v = browser}},

    {MODKEY, XK_Cyrillic_yeru, spawn, {.v = music}},
    {MODKEY, XK_Cyrillic_te, spawn, {.v = notes}},
    {MODKEY, XK_Cyrillic_pe, spawn, {.v = webcam}},

    {MODKEY, XK_Cyrillic_o, focusstack, {.i = +1}},
    {MODKEY, XK_Cyrillic_el, focusstack, {.i = -1}},

    {MODKEY, XK_Cyrillic_sha, incnmaster, {.i = +1}},
    {MODKEY, XK_Cyrillic_ve, incnmaster, {.i = -1}},
    {MODKEY, XK_Cyrillic_er, setmfact, {.f = -0.05}},
    {MODKEY, XK_Cyrillic_de, setmfact, {.f = +0.05}},

    {MODKEY, XK_Cyrillic_shorti, killclient, {0}},
    {MODKEY | ControlMask, XK_Cyrillic_be, cyclelayout, {.i = -1}},
    {MODKEY | ControlMask, XK_Cyrillic_yu, cyclelayout, {.i = +1}},
    {MODKEY, XK_Cyrillic_be, focusmon, {.i = -1}},
    {MODKEY, XK_Cyrillic_yu, focusmon, {.i = +1}},
    {MODKEY | ShiftMask, XK_Cyrillic_be, tagmon, {.i = -1}},
    {MODKEY | ShiftMask, XK_Cyrillic_yu, tagmon, {.i = +1}},
    {MODKEY | ShiftMask, XK_Cyrillic_softsign, spawn, {.v = mutecmd}},
    {MODKEY | ShiftMask, XK_Cyrillic_ghe, spawn, {.v = unmutecmd}},

    /* tags */
    TAGKEYS(XK_1, 0) TAGKEYS(XK_2, 1) TAGKEYS(XK_3, 2)
    TAGKEYS(XK_4, 3) TAGKEYS(XK_5, 4) TAGKEYS(XK_6, 5)
    TAGKEYS(XK_7, 6) TAGKEYS(XK_8, 7) TAGKEYS(XK_9, 8)
};

/* mouse buttons */
static const Button buttons[] = {
    /* click            event mask  button   function        argument */
    {ClkLtSymbol, 0, Button1, setlayout, {0}},
    {ClkLtSymbol, 0, Button3, setlayout, {.v = &layouts[2]}},
    {ClkWinTitle, 0, Button2, zoom, {0}},

    {ClkStatusText, 0, Button1, spawn, {.v = taskmanager}},
    {ClkStatusText, 0, Button2, spawn, {.v = filecmd}},
    {ClkStatusText, 0, Button3, spawn, {.v = calendar}},

    {ClkClientWin, MODKEY, Button1, movemouse, {0}},
    {ClkClientWin, MODKEY, Button2, togglefloating, {0}},
    {ClkClientWin, MODKEY, Button3, resizemouse, {0}},

    {ClkTagBar, 0, Button1, view, {0}},
    {ClkTagBar, 0, Button3, toggleview, {0}},
    {ClkTagBar, MODKEY, Button1, tag, {0}},
    {ClkTagBar, MODKEY, Button3, toggletag, {0}},
};
