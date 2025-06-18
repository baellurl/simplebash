#include "parser.h"

int main(int argc, char **argv) {
  
  option flags = parser_flags(argc, argv);

  output(flags, argc, argv);

  return 0;
}
