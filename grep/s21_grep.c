#include "parser.h"

int main(int argc, char **argv) {

  option flags = parser_flags(argc, argv); //?

  outputFile(flags, argc, argv);
  
  if (flags.pattern != NULL) {

    free(flags.pattern);
  
  }

  return 0;
}

