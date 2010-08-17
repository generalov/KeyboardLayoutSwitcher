/* Thanks to Evgeny V. Generalov (C) 2010, GNU GPL */

/* Compilation: gcc -L/usr/include/X11 -lX11 -o xkbswitchlang xkbswitchlang.c */

/* Usage:
 *      xkbswitchlang    # Show current group
 *      xkbswitchlang 0  # Switch to first group
 *      xkbswitchlang 1  # Switch to second group
 */

#include <X11/Xlib.h>
#include <X11/XKBlib.h>
#include <stdio.h>
#include <stdlib.h>

int main (int argc, char *argv[]) {
    Display *dpy;
    int group;

    if (argc > 2) {
	fprintf(stderr, "Usage: %s [group]\n", argv[0]);
	return -1;
    }

    dpy = XkbOpenDisplay(NULL, NULL, NULL, NULL, NULL, NULL);
    if (NULL == dpy) {
        fprintf (stderr, "%s: Can't open display\n", argv[0]);
	return -1;
    }

    if (1 == argc) {
	XkbStateRec xkbState;
	XkbGetState(dpy, XkbUseCoreKbd, &xkbState);
	group = xkbState.group;
	fprintf (stdout, "%d\n", group);
    } else { /* 2 == argc */
	group = atoi(argv[1]);
	if (False == XkbLockGroup(dpy, XkbUseCoreKbd, abs (group % 4))) {
	    fprintf(stderr, "%s: Can't lock group\n", argv[0]);
	    XCloseDisplay(dpy);
	    return -2;
	}
	XSync(dpy, False);
    }

    XCloseDisplay(dpy);
    return 0;
}
