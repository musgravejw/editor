#define VERSION "0.0.1"
#define TAB_STOP 8
#define QUIT_TIMES 2

// ctrl key mapping
#define CTRL_KEY(k) ((k) & 0x1f)

// start constants at 1000
enum editorKey {
  BACKSPACE = 127,
  ARROW_LEFT = 1000,
  ARROW_RIGHT,
  ARROW_UP,
  ARROW_DOWN,
  DEL_KEY,
  HOME_KEY,
  END_KEY,
  PAGE_UP,
  PAGE_DOWN
};

typedef struct erow {
  int size;
  int rsize;
  char *chars;
  char *render;
} erow;

struct editorConfig {
  int cx;
  int cy;
  int rx;
  int rowoff;
  int coloff;
  int screenrows;
  int screencols;
  int numrows;
  erow *row;
  int dirty;
  char *filename;
  char status[80];
  time_t status_time;
  struct termios orig_termios;
};

struct editorConfig E;

struct abuf {
  char *b;
  int len;
};

#define ABUF_INIT {NULL, 0}
