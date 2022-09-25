#include "utils.h"
#include "printf.h"
#include "cli.h"

/* ENTER (ascii 13) is not the same as '\n' (ascii 10).
 * Enter does something weird.
 */
void case_enter(struct cli* c) {
  c->data_start[c->cur.x] = 0;
  c->cur.x = 0;
  c->cmd_end.x = 0;
  printf("\ncmd: %s\n$ ", c->data_start);
}

void case_delete(struct cli* c) {
  if (c->cur.x == 0) return;
  _delchar();
  c->cur.x--;
}

void case_newchar(struct cli* c, char t) {
  _putchar(t);
  c->data_start[c->cur.x] = t;
  if (c->cur.x == c->cmd_end.x) c->cmd_end.x++;
  c->cur.x++;
}

void cli_start(register struct cli* c, char* kernel_boundary) {
  memset(c, 0, sizeof(*c));
  c->data_start = kernel_boundary;

  _putchar('$'); _putchar(' ');

  char t;
  for (;;) {
    _getchar(&t);
    if (t == 13 /* ENTER */)	{ case_enter(c); }
    else if (t == (char) 127)	{ case_delete(c); }
    else                      { case_newchar(c, t); }
  }
}
