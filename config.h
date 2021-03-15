/* See LICENSE file for copyright and license details. */

/* appearance */

static unsigned int borderpx		= 2;			/* border pixel of windows */
static unsigned int snap			= 32;		/* snap pixel */
static const int gappx			= 20;		/* gaps between windows */
static const int swallowfloating	= 0;			/* 1 means swallow floating windows by default */

static int showbar				= 1;			/* 0 means no bar */
static int topbar				= 1;			/* 0 means bottom bar */
static const int usealtbar		= 1;			/* 1 means use non-dwm status bar */
static const char *altbarclass	= "Polybar";	/* Alternate bar class name */
static const char *altbarcmd		= "polyLaunch";/* Alternate bar launch command */

static const char *fonts[]		= { "JetBrains Mono:size=12" };
static const char dmenufont[]		= "JetBrains Mono:size=10";

//#include "/home/gabriel/.cache/wal/dwm.h"
static char normfgcolor[]	= "#a2bfc0";
static char normbgcolor[]	= "#0F161E";
static char normbordercolor[] = "#0F161E";
static char selfgcolor[]		= "#e94f63";
static char selbgcolor[]		= "#0F161E";
static char selbordercolor[]	= "#e94f63";
static char *colors[][3]		= {
       /*               fg           bg           border   */
       [SchemeNorm] = { normfgcolor, normbgcolor, normbordercolor },
       [SchemeSel]  = { selfgcolor,  selbgcolor,  selbordercolor  },
};

static const unsigned int baralpha		= 0xd0;
static const unsigned int borderalpha	= OPAQUE;
static const unsigned int alphas[][3]	= {
	/*               fg      bg        border     */
	[SchemeNorm] = { OPAQUE, baralpha, borderalpha },
	[SchemeSel]  = { OPAQUE, baralpha, borderalpha },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9", "10" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class     instance  title           tags mask  isfloating  isterminal  noswallow  monitor */
	{ NULL,		NULL,     "Event Tester", 0,         0,          0,           1,        -1 }, //xev 
	{ "scratchpad",NULL,     NULL,           0,         1,          1,          -1,        -1 },
	{ "Alacritty",	NULL,     NULL,           0,         0,          1,          -1,        -1 },
	{ "St",		NULL,	NULL,	      0,         0,          1,          -1,        -1 }, 
};

/* layout(s) */
static float mfact     = 0.50; /* factor of master area size [0.05..0.95] */
static int nmaster     = 1;    /* number of clients in master area */
static int resizehints = 0;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "",	tile		},    /* first entry is default */
	//{ "",	NULL		},    /* no layout function means floating behavior */
	{ "><>",	NULL		},    /* no layout function means floating behavior */
	{ "[0]",	monocle	},
 	{ "[@]",	spiral	},
 	{ "[\\]",	dwindle	},
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, NULL };
static const char *termcmd[]  = { "st", NULL };
static const char *jgmenucmd[]  = { "jgmenu_run", NULL };

static Key keys[] = {
	/* modifier				key			function        argument */
	{ MODKEY|ShiftMask,			XK_b,		togglebar,      {0} },
	{ MODKEY,					XK_j,		focusstack,     {.i = +1 } },
	{ MODKEY,					XK_k,		focusstack,     {.i = -1 } },
	{ MODKEY|ControlMask,		XK_j,		movestack,      {.i = +1 } },
	{ MODKEY|ControlMask,		XK_k,		movestack,      {.i = -1 } },
	{ MODKEY|ShiftMask,			XK_j,		viewtoleft,     {.i = +1 } },
	{ MODKEY|ShiftMask,			XK_k,		viewtoright,	 {.i = -1 } },
	{ MODKEY|ShiftMask,			XK_h,		tagtoleft,      {.i = +1 } },
	{ MODKEY|ShiftMask,			XK_l,		tagtoright,	 {.i = -1 } },
	{ MODKEY,					XK_i,		incnmaster,     {.i = +1 } },
	{ MODKEY|ShiftMask,			XK_i,		incnmaster,     {.i = -1 } },
	{ MODKEY,					XK_h,		setmfact,       {.f = -0.05} },
	{ MODKEY,					XK_l,		setmfact,       {.f = +0.05} },
	{ MODKEY,					XK_space,		zoom,           {0} },
	{ MODKEY,					XK_Tab,		view,           {0} },
	{ MODKEY,					XK_u,		focusurgent,    {0} },
	{ MODKEY,					XK_q,		killclient,     {0} },
	{ MODKEY,					XK_t,		setlayout,      {.v = &layouts[0]} },
	{ MODKEY,					XK_n,		setlayout,      {.v = &layouts[1]} },
	{ MODKEY,					XK_m,		setlayout,      {.v = &layouts[2]} },

	{ MODKEY|ShiftMask,			XK_s,		setlayout,      {.v = &layouts[3]} },
	{ MODKEY|ControlMask,		XK_s,		setlayout,      {.v = &layouts[4]} },
	{ MODKEY|ShiftMask,			XK_space,		setlayout,      {0} },
	{ MODKEY|ShiftMask,			XK_f,		togglefloating, {0} },
	{ MODKEY,					XK_f,		togglefullscr,  {0} },
	{ MODKEY,					XK_comma,		focusmon,       {.i = -1 } },
	{ MODKEY,					XK_period,	focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,			XK_comma,		tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,			XK_period,	tagmon,         {.i = +1 } },
	{ MODKEY,					XK_minus,		setgaps,        {.i = -5 } },
	{ MODKEY,					XK_equal,		setgaps,        {.i = +5 } },
	{ MODKEY|ShiftMask,			XK_equal,		setgaps,        {.i = 0  } },
	{ MODKEY|ShiftMask,			XK_r,		quit,           {0} },
	{ MODKEY,					XK_0,		view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,			XK_0,		tag,            {.ui = ~0 } },
	TAGKEYS(					XK_1,					  0)
	TAGKEYS(					XK_2,					  1)
	TAGKEYS(					XK_3,					  2)
	TAGKEYS(					XK_4,					  3)
	TAGKEYS(					XK_5,					  4)
	TAGKEYS(					XK_6,					  5)
	TAGKEYS(					XK_7,					  6)
	TAGKEYS(					XK_8,					  7)
	TAGKEYS(					XK_9,					  8)
	//TAGKEYS(				XK_dead_grave,				  9)
	//TAGKEYS(				XK_apostrophe,				  9)
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
	{ ClkRootWin,		    0,			Button3,		 spawn,		  {.v = jgmenucmd } },
};
/*
 * Xresources preferences to load at startup
 */
ResourcePref resources[] = {
		{ "normbgcolor",		STRING,  &normbgcolor },
		{ "normbordercolor",	STRING,  &normbordercolor },
		{ "normfgcolor",		STRING,  &normfgcolor },
		{ "selbgcolor",		STRING,  &selbgcolor },
		{ "selbordercolor",		STRING,  &selbordercolor },
		{ "selfgcolor",		STRING,  &selfgcolor },
		{ "borderpx",			INTEGER, &borderpx },
		{ "snap",				INTEGER, &snap },
		{ "showbar",          	INTEGER, &showbar },
		{ "topbar",          	INTEGER, &topbar },
		{ "nmaster",          	INTEGER, &nmaster },
		{ "resizehints",       	INTEGER, &resizehints },
		{ "mfact",      	 	FLOAT,   &mfact },
};

static const char *ipcsockpath = "/tmp/dwm.sock";
static IPCCommand ipccommands[] = {
  IPCCOMMAND(  view,                1,      {ARG_TYPE_UINT}   ),
  IPCCOMMAND(  toggleview,          1,      {ARG_TYPE_UINT}   ),
  IPCCOMMAND(  tag,                 1,      {ARG_TYPE_UINT}   ),
  IPCCOMMAND(  toggletag,           1,      {ARG_TYPE_UINT}   ),
  IPCCOMMAND(  tagmon,              1,      {ARG_TYPE_UINT}   ),
  IPCCOMMAND(  focusmon,            1,      {ARG_TYPE_SINT}   ),
  IPCCOMMAND(  focusstack,          1,      {ARG_TYPE_SINT}   ),
  IPCCOMMAND(  incnmaster,          1,      {ARG_TYPE_SINT}   ),
  IPCCOMMAND(  killclient,          1,      {ARG_TYPE_SINT}   ),
  IPCCOMMAND(  setgaps,	           1,      {ARG_TYPE_SINT}   ),
  IPCCOMMAND(  togglebar,           1,      {ARG_TYPE_NONE}   ),
  IPCCOMMAND(  zoom,                1,      {ARG_TYPE_NONE}   ),
  IPCCOMMAND(  togglefloating,      1,      {ARG_TYPE_NONE}   ),
  IPCCOMMAND(  togglefullscr,       1,      {ARG_TYPE_NONE}   ),
  IPCCOMMAND(  viewtoleft,	      1,      {ARG_TYPE_NONE}   ),
  IPCCOMMAND(  viewtoright,         1,      {ARG_TYPE_NONE}   ),
  IPCCOMMAND(  tagtoright,          1,      {ARG_TYPE_NONE}   ),
  IPCCOMMAND(  tagtoleft,           1,      {ARG_TYPE_NONE}   ),
  IPCCOMMAND(  setmfact,            1,      {ARG_TYPE_FLOAT}  ),
  IPCCOMMAND(  setlayoutsafe,       1,      {ARG_TYPE_PTR}    ),
  IPCCOMMAND(  quit,                1,      {ARG_TYPE_NONE}   ),
  IPCCOMMAND(  reload_xresources,   1,      {ARG_TYPE_NONE}   )
};

