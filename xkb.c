// copied from https://gist.github.com/fikovnik/ef428e82a26774280c4fdf8f96ce8eeb
// compile with `gcc -I/usr/include getxkblayout.c -lX11 -lxkbfile`

#include "xkb.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <X11/XKBlib.h>
#include <X11/extensions/XKBrules.h>

char* get_layout() {
  Display *dpy = XOpenDisplay(NULL);

  if (dpy == NULL) {
    fprintf(stderr, "Cannot open display\n");
    exit(1);
  }

  XkbStateRec state;
  XkbGetState(dpy, XkbUseCoreKbd, &state);

  XkbDescPtr desc = XkbGetKeyboard(dpy, XkbAllComponentsMask, XkbUseCoreKbd);
  char *group = XGetAtomName(dpy, desc->names->groups[state.group]);
  printf("Full name: %s\n", group);

  XkbRF_VarDefsRec vd; 
  XkbRF_GetNamesProp(dpy, NULL, &vd);

  char *tok = strtok(vd.layout, ",");

  for (int i = 0; i < state.group; i++) {
    tok = strtok(NULL, ",");
    if (tok == NULL) {
      return "";
    }   
  }

  return tok;
}
