// #define _DEFAULT_SOURCE
// #define _BSD_SOURCE
// #define _GNU_SOURCE

#include <ctype.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <termios.h>
#include <time.h>
#include <unistd.h>

void editorSetStatusMessage(const char *fmt, ...);
void editorRefreshScreen();
char *editorPrompt(char *prompt);

#include "./src/const.c"
#include "./src/terminal.c"
#include "./src/buffer.c"
#include "./src/file.c"
#include "./src/output.c"
#include "./src/input.c"

void initEditor() {
  // initialize struct for editor

  // set initial cursor position
  E.cx = 0;
  E.cy = 0;
  E.rx = 0;

  // row and column offsets
  E.rowoff = 0;
  E.coloff = 0;

  // rows are initially empty
  E.numrows = 0;
  E.row = NULL;
  E.dirty = 0;

  E.filename = NULL;
  E.status[0] = '\0';
  E.status_time = 0;

  if (getWindowSize(&E.screenrows, &E.screencols) == -1) die("getWindowSize");
  E.screenrows -= 2;
}

int main(int argc, char *argv[]) {
  enableRawMode();
  initEditor();

  // open a file from the command line if one was supplied
  if (argc >= 2) editorOpen(argv[1]);

  editorSetStatusMessage("Ctrl-Q = quit");

  while (1) {
    editorRefreshScreen();
    editorProcessKeypress();
  }

  return 0;
}
