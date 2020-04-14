/* See LICENSE file for copyright and license details. */

/* appearance */
static const char font[]        = "monospace:size=14";
static const char* normbgcolor  = "#222222";
static const char* normfgcolor  = "#cccccc";
static const char* selbgcolor   = "#555555";
static const char* selfgcolor   = "#ffffff";
static const char* urgbgcolor   = "#111111";
static const char* urgfgcolor   = "#cc0000";
static const char before[]      = "<";
static const char after[]       = ">";
static const char titletrim[]   = "...";
static const int  tabwidth      = 200;
static const Bool foreground    = True;
static       Bool urgentswitch  = True;

/*
 * Where to place a new tab when it is opened. When npisrelative is True,
 * then the current position is changed + newposition. If npisrelative
 * is False, then newposition is an absolute position.
 */
static int  newposition   = 1;
static Bool npisrelative  = True;

#define SETPROP(p) { \
        .v = (char *[]){ "/bin/sh", "-c", \
                "prop=\"`xwininfo -children -id $1 | grep '^     0x' |" \
                "sed -e's@^ *\\(0x[0-9a-f]*\\) \"\\([^\"]*\\)\".*@\\1 \\2@' |" \
                "tail -n +2 | dmenu -i -l 10 -p 'Switch to: '`\" &&" \
                "xprop -id $1 -f $0 8s -set $0 \"$prop\"", \
                p, winid, NULL \
        } \
}

#define OPENTERMSOFT(p) { \
	.v = (char *[]){ "/bin/sh", "-c", \
		"printf '%s\n' \"htop\" \"ncdu\" \"nvim\" \"fzf\" \"nnn\" \"ncmpcpp\" \"nmtui\" \"joplin\" |" \
		"dmenu -i -p 'Softwares to run: ' |" \
		"xargs -I {} urxvt -name \"{}\" -embed $1 -e \"{}\"", \
		p, winid, NULL \
	} \
}

#define OPENTERM(p) { \
	.v = (char *[]){ "/bin/sh", "-c", \
		"cd \"$(xwininfo -children -id $1 | grep '^     0x' |" \
                "sed -e's@^ *\\(0x[0-9a-f]*\\) \"\\([^\"]*\\)\".*@\\1 \\2@' |" \
		"dmenu -i -l 10 -p 'New term path based on: ' |" \
		"cut -f 1 | xargs -I {} xprop -id \"{}\" | grep _NET_WM_PID |" \
		"cut -d ' ' -f 3 | xargs -I {} pstree -p \"{}\" |" \
		"cut -d '(' -f 3 | cut -d ')' -f 1 |" \
		"xargs -I {} readlink -e /proc/\"{}\"/cwd/)\" &&" \
		"urxvt -embed $1", \
		p, winid, NULL \
	} \
}

#define ATTACHWIN(p) { \
	.v = (char *[]){ "/bin/sh", "-c", \
		"wmctrl -x -l |" \
		"grep -E \" $(xprop -root -notype _NET_CURRENT_DESKTOP | cut -d ' ' -f 3) \" |" \
		"grep -v tabbed | cut -d ' ' -f 1,4 | dmenu -i -l 5 -p \"Attach: \" |" \
		"cut -d ' ' -f 1 | xargs -I {} xdotool windowreparent \"{}\" $1", \
		p, winid, NULL \
	} \
}

#define DETACHWIN(p) { \
        .v = (char *[]){ "/bin/sh", "-c", \
		"rootid=\"`xwininfo -root | grep \"Window id\" | cut -d ' ' -f 4`\" &&" \
                "wid=\"`xwininfo -children -id $1 | grep '^     0x' |" \
                "sed -e's@^ *\\(0x[0-9a-f]*\\) \"\\([^\"]*\\)\".*@\\1 \\2@' |" \
                "dmenu -i -l 10 -p 'Detach: ' | cut -d ' ' -f 1`\" &&" \
		"xdotool windowreparent \"$wid\" \"$rootid\"", \
                p, winid, NULL \
        } \
}


#define MODKEY Mod4Mask
static Key keys[] = {
	/* modifier            key          function     argument */
	{ MODKEY|ShiftMask,    XK_Return,   focusonce,   { 0 } },
	{ MODKEY|ShiftMask,    XK_Return,   spawn,       { 0 } },

	{ MODKEY|ShiftMask,    XK_k,        rotate,      { .i = +1 } },
	{ MODKEY|ShiftMask,    XK_j,        rotate,      { .i = -1 } },
	{ MODKEY|ShiftMask,    XK_h,        movetab,     { .i = -1 } },
	{ MODKEY|ShiftMask,    XK_l,        movetab,     { .i = +1 } },
	{ ShiftMask,           XK_Tab,      rotate,      { .i = 0 } },

	{ MODKEY|ShiftMask,    XK_comma,    spawn,       SETPROP("_TABBED_SELECT_TAB") },
	{ MODKEY|ShiftMask,    XK_period,   spawn,       OPENTERMSOFT("_TABBED_SELECT_TERMAPP") },
	{ MODKEY|ShiftMask,    XK_slash,    spawn,       OPENTERM("_TABBED_TERM") },
	{ MODKEY|ShiftMask,    XK_a,	    spawn,       ATTACHWIN("_TABBED_ATTACH_WIN") },
	{ MODKEY|ShiftMask,    XK_d,	    spawn,       DETACHWIN("_TABBED_DETACH_WIN") },
	{ ControlMask,         XK_1,        move,        { .i = 0 } },
	{ ControlMask,         XK_2,        move,        { .i = 1 } },
	{ ControlMask,         XK_3,        move,        { .i = 2 } },
	{ ControlMask,         XK_4,        move,        { .i = 3 } },
	{ ControlMask,         XK_5,        move,        { .i = 4 } },
	{ ControlMask,         XK_6,        move,        { .i = 5 } },
	{ ControlMask,         XK_7,        move,        { .i = 6 } },
	{ ControlMask,         XK_8,        move,        { .i = 7 } },
	{ ControlMask,         XK_9,        move,        { .i = 8 } },
	{ ControlMask,         XK_0,        move,        { .i = 9 } },

	{ ControlMask,         XK_q,        killclient,  { 0 } },

	{ MODKEY,              XK_u,        focusurgent, { 0 } },
	{ MODKEY|ShiftMask,    XK_u,        toggle,      { .v = (void*) &urgentswitch } },

	{ 0,                   XK_F11,      fullscreen,  { 0 } },

	{ MODKEY,              XK_Shift_L,  showbar,     { .i = 1 } },
	{ ShiftMask,           XK_Super_L,  showbar,     { .i = 1 } },
};

static Key keyreleases[] = {
	/* modifier            key          function     argument */
	{ MODKEY|ShiftMask,    XK_Shift_L,  showbar,     { .i = 0 } },
	{ MODKEY|ShiftMask,    XK_Super_L,  showbar,     { .i = 0 } },
};
