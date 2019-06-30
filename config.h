/* See LICENSE file for copyright and license details. */

/*
* Keys:
* $ locate keysymdef.h
* xev:
*
*/
/* XF86 Media Keys */
#include <X11/XF86keysym.h>

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayspacing = 2;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray        = 1;     /* 0 means no systray */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "terminus:size=12" };
static const char dmenufont[]       = "terminus:size=12";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#005577";
static const char *colors[][3]      = {
    /*               fg         bg         border   */
    [SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
    [SchemeSel]  = { col_gray4, col_cyan,  col_cyan  },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
    /* xprop(1):
     *  WM_CLASS(STRING) = instance, class
     *  WM_NAME(STRING) = title
     */
    /* class      instance    title       tags mask     isfloating   monitor */
    { "Gimp",     NULL,       NULL,       0,            1,           -1 },
    //{ "Firefox",  NULL,       NULL,       1 << 8,       0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = False;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
    /* symbol     arrange function */
    { "[]=",      tile },    /* first entry is default */
    { "><>",      NULL },    /* no layout function means floating behavior */
    { "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod1Mask
#define WINKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
    { MODKEY|ShiftMask,             KEY,      view,           {.ui = 1 << TAG} }, \
    { MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
    { ControlMask|ShiftMask,        KEY,      tag,            {.ui = 1 << TAG} }, \
    { MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, "-l", "10", NULL };
static const char *termcmd[] = { "mate-terminal", NULL };
static const char *eddcmd[] = { "mate-terminal", "-e", "/bin/bash -ic edd", NULL };
// workaround - mate-terminal doesn't load ~/.bashrc when -e is used
static const char *filemanagercmd[] = { "mate-terminal", "-e", "ranger", NULL };
static const char *cmdkilldwm[] = { "killall", "dwm", NULL };
/* Sound & media keys */
static const char *cmdsoundup[] = { "amixer", "-q", "sset", "Master", "2%+", NULL };
static const char *cmdsounddown[] = { "amixer", "-q", "sset", "Master", "2%-", NULL };
static const char *cmdsoundtoggle[] = { "amixer", "-q", "sset", "Master", "toggle", NULL };
/* Media control */
static const char *pctlplaycmd[]  = { "playerctl", "play-pause", NULL };
static const char *pctlnextcmd[]  = { "playerctl", "next", NULL };
static const char *pctlpreviouscmd[] = { "playerctl", "previous", NULL };
/* Brightness */
static const char *cmdbrightnessup[] = { "xbacklight", "-inc", "10", NULL };
static const char *cmdbrightnessdown[] = { "xbacklight", "-dec", "10", NULL };
/* Scripts */
static const char *cmddwmmenu[] = { "dwm-menu", NULL };
static const char *cmdscreenshot[] = { "screenshot", "-i", NULL };
/* DPMS - wake lock (dwm-panel needed) */
static const char *cmdtogglewakelock[] = { "dwm-panel", "toggle", "wakelock", NULL };
static const char *cmdlockworkspace[] = { "slock", NULL };
static const char *cmdkblayout[] = { "dwm-switch-keyboard", NULL };
/* doer */
static const char *cmddoer[] = { "doer", NULL };
static const char *cmddoerask[] = { "doer", "--ask", NULL };

static Key keys[] = {
    /* modifier                     key        function              argument */
    { MODKEY,                       XK_F2,     spawn,                {.v = dmenucmd } },
    { MODKEY|ShiftMask,             XK_Return, spawn,                {.v = termcmd } },
    { MODKEY|ShiftMask,             XK_f,      spawn,                {.v = filemanagercmd} },
    { MODKEY|ShiftMask,             XK_m,      spawn,                {.v = cmddwmmenu } },
    { MODKEY|ShiftMask,             XK_w,      spawn,                {.v = cmdtogglewakelock } },
    { MODKEY|ShiftMask,             XK_s,      spawn,                {.v = cmdscreenshot } },
    /* Sound & media keys */
    { MODKEY|ShiftMask,             XK_Up,     spawn,                {.v = cmdsoundup } },
    { MODKEY|ShiftMask,             XK_Down,   spawn,                {.v = cmdsounddown } },
    { 0,                            XF86XK_AudioRaiseVolume, spawn,  {.v = cmdsoundup } },
    { 0,                            XF86XK_AudioLowerVolume, spawn,  {.v = cmdsounddown } },
    { 0,                            XF86XK_AudioMute, spawn,         {.v = cmdsoundtoggle } },
    { 0,                            XF86XK_AudioPlay, spawn,         {.v = pctlplaycmd} },
    { 0,                            XF86XK_AudioNext, spawn,         {.v = pctlnextcmd} },
    { 0,                            XF86XK_AudioPrev, spawn,         {.v = pctlpreviouscmd} },
    { 0,                            XF86XK_Launch6, spawn,           {.v = pctlnextcmd} },
    { 0,                            XF86XK_Launch5, spawn,           {.v = pctlpreviouscmd} },
    /* Killing dwm */
    //{ MODKEY|ShiftMask,             XK_q,      spawn,                {.v = cmdkilldwm} },
    /* Brightness */
    { 0,                            XF86XK_MonBrightnessUp, spawn,   {.v = cmdbrightnessup } },
    { 0,                            XF86XK_MonBrightnessDown, spawn, {.v = cmdbrightnessdown } },
    { MODKEY|ControlMask,           XK_b,      togglebar,            {0} },
    { MODKEY|ControlMask,           XK_j,      focusstack,           {.i = +1 } },
    { MODKEY|ControlMask,           XK_k,      focusstack,           {.i = -1 } },
    { MODKEY|ControlMask,           XK_i,      incnmaster,           {.i = +1 } },
    { MODKEY|ControlMask,           XK_d,      incnmaster,           {.i = -1 } },
    { MODKEY|ControlMask,           XK_h,      setmfact,             {.f = -0.05} },
    { MODKEY|ControlMask,           XK_l,      setmfact,             {.f = +0.05} },
    { MODKEY,                       XK_Return, zoom,                 {0} },
    { MODKEY,                       XK_Tab,    view,                 {0} },
    { MODKEY|ShiftMask,             XK_c,      killclient,           {0} },
    { MODKEY|ControlMask,           XK_t,      setlayout,            {.v = &layouts[0]} },
    { MODKEY|ControlMask,           XK_f,      setlayout,            {.v = &layouts[1]} },
    { MODKEY|ControlMask,           XK_m,      setlayout,            {.v = &layouts[2]} },
    { MODKEY|ControlMask,           XK_space,  setlayout,            {0} },
    { MODKEY|ShiftMask,             XK_space,  togglefloating,       {0} },
    { MODKEY|ControlMask,           XK_0,      view,                 {.ui = ~0 } },
    { MODKEY|ShiftMask,             XK_0,      tag,                  {.ui = ~0 } },
    { MODKEY,                       XK_comma,  focusmon,             {.i = -1 } },
    { MODKEY,                       XK_period, focusmon,             {.i = +1 } },
    { MODKEY|ShiftMask,             XK_comma,  tagmon,               {.i = -1 } },
    { MODKEY|ShiftMask,             XK_period, tagmon,               {.i = +1 } },
    TAGKEYS(                        XK_1,                            0)
    TAGKEYS(                        XK_2,                            1)
    TAGKEYS(                        XK_3,                            2)
    TAGKEYS(                        XK_4,                            3)
    TAGKEYS(                        XK_5,                            4)
    TAGKEYS(                        XK_6,                            5)
    TAGKEYS(                        XK_7,                            6)
    TAGKEYS(                        XK_8,                            7)
    TAGKEYS(                        XK_9,                            8)
    // Restart thanks to dwm-personalized
    { MODKEY|ShiftMask,             XK_r,      quit,                 {0} },
    // Let's get some use for winkey, which is totally useless on *nix anyway
    { WINKEY,                       XK_l,      spawn,                {.v = cmdlockworkspace} },
    /* cfacts */
    { WINKEY,                       XK_i,      setcfact,             {.f = +0.25} },
    { WINKEY,                       XK_k,      setcfact,             {.f = -0.25} },
    { WINKEY,                       XK_o,      setcfact,             {.f =  0.00} },
    // edd - https://github.com/psss/edd
    { WINKEY,                       XK_e,      spawn,                {.v = eddcmd } },
    // doer
    { WINKEY,                       XK_d,      spawn,                {.v = cmddoer } },
    { ControlMask|WINKEY,           XK_d,      spawn,                {.v = cmddoer } },
    // Change keyboard layout
    { WINKEY|ShiftMask,             XK_k,      spawn,                {.v = cmdkblayout } },
};

/* button definitions */
/* click can be ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
    /* click                event mask      button          function        argument */
    { ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
    { ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
    { ClkWinTitle,          0,              Button2,        zoom,           {0} },
    // kill window
    { ClkWinTitle,          0,              Button3,        killclient,     {0} },
    // dmenu
    { ClkWinTitle,          0,              Button1,        spawn,          {.v = dmenucmd} },
    { ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
    { ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
    { ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
    { ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
    { ClkTagBar,            0,              Button1,        view,           {0} },
    { ClkTagBar,            0,              Button3,        toggleview,     {0} },
    { ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
    { ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

