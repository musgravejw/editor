#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

struct termios orig_termios;

void die(const char *s) {
  perror(s); // print a descriptive error message
  exit(1);
}

void disableRawMode() {
  if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios) == -1)
  die("tcsetattr");
}

void enableRawMode() {
  if (tcgetattr(STDIN_FILENO, &orig_termios) == -1) die("tcgetattr");
  // register function to be called on exit
  atexit(disableRawMode);

  struct termios raw = orig_termios;

  // remove bitflags for input, output, and control signals
  raw.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);
  raw.c_oflag &= ~(OPOST);
  raw.c_cflag |= (CS8);
  // remove local bitflags for canonical mode, control signals
  raw.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);

  raw.c_cc[VMIN] = 0; // minimum number of bytes before a read
  raw.c_cc[VTIME] = 1; // minimum amount of time before a read (0.1s)

  // get terminal attributes
  tcgetattr(STDIN_FILENO, &raw);
  // remove echo
  raw.c_lflag &= ~(ECHO);

  // set new attributes, wait until pending output is written to terminal
  if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw) == -1) die("tcsetattr");
}

int main() {
  enableRawMode();

  char c;
  while (1) {
    // get a character from STDIN, until q
    char c = '\0';
    if (read(STDIN_FILENO, &c, 1) == -1 && errno != EAGAIN) die("read");
    // test for control character
    if (iscntrl(c)) {
      printf("%d\r\n", c);
    } else {
      // display characters typed
      printf("%d ('%c')\r\n", c, c);
    }
    if (c == 'q') break;
  }

  return 0;
}
