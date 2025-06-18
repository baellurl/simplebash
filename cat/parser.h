#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct flags{
  int b, n, v, t, e, s;

} option;

int v_output(int ch);
void output(option flags, int argc, char **argv);
option parser_flags(int argc, char **argv);