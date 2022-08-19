#include "utils.h"
#include "printf.h"
#include "cli.h"

void case_enter(struct cli* c) {
	// _putchar((char) 10); // ENTER is not the same as '\n'
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

void cli_start(struct cli* c) {
	memset(c, 0, sizeof(c));
	c->data_start = (char*) CMD_POS;

	_putchar('$'); _putchar(' ');

	// register char* cur_in;
	char t;
	for (;;) {
		_getchar(&t);
		if (t == 13 /* ENTER */)	{ case_enter(c); }
		else if (t == (char) 127)	{ case_delete(c); }
		else 											{ case_newchar(c, t); }
	}
}
