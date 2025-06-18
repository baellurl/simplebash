#include "parser.h"

option parser_flags(int argc, char **argv) { 
  
  option flags = {0}; // obnulyaem struct

  struct option long_options[] = {
      {"number-nonblank", no_argument, NULL, 'b'},
      {"number", no_argument, NULL, 'n'},
      {"squeeze-blank", no_argument, NULL, 's'},
      {NULL, 0, NULL, 0}  // Завершающая структура
  };

  int c;

  while ((c = getopt_long(argc, argv, "bnsEtTve", long_options, NULL)) != -1) {
    switch (c) {
      case 'b':
        flags.b = 1;
        break;

      case 'n':
        flags.n = 1;
        break;

      case 's':
        flags.s = 1;
        break;

      case 't':
        flags.t = 1;
        flags.v = 1;

        break;

      case 'v':
        flags.v = 1;
        break;

      case 'T':
        flags.t = 1;
        break;

      case 'E':
        flags.e = 1;
        break;

      case 'e':
        flags.e = 1;
        flags.v = 1;
        break;

      default:
        fprintf(stderr, "Try 'cat --help' for more information.\n");
        exit(1);
    }
  }
  return flags;
}

 int v_output(int ch) { 
  if (ch == 9 || ch == 10) return ch;

  if (ch <= 31) {
    putchar('^');
    ch += 64;
  } else if (ch == 127) {
    putchar('^');
    putchar('?');
  }

  else if (ch >= 128 && ch < 160) {
    putchar('M');
    putchar('-');
    putchar('^');
    ch -= 64;
  }

  else if (ch >= 160 && ch < 255) {
    putchar('M');
    putchar('-');
    ch -= 128;
  }

  return ch;
}

void output(option flags, int argc, char **argv) {
  FILE *fptr;
  int line_counter = 0;  // счетчик строк
  int temp_variebl = 1;
  int empty_row_counter = 1;  // счетчик пустых строк

  for (int i = optind; i < argc; i++) {
    fptr = fopen(argv[i], "r");

    if (fptr == NULL) {
      fprintf(stderr, "s21_cat: %s: No such file or directory\n", argv[i]);
      continue;
    }

    int ch;

    while ((ch = fgetc(fptr)) != EOF) {
      if (flags.b) {
        flags.n = 0;
      }

      if (flags.b) {
        if (temp_variebl && ch != '\n') {
          printf("%6d\t", ++line_counter);
          temp_variebl = 0;  // чтобы putchar не печатал нумерацию через каждый символ
        }
        if (ch == '\n') {
          temp_variebl = 1;
        }
      }

      if (flags.s) {
        if (ch == '\n') {
          if (empty_row_counter > 1) {
            continue;
          }
          empty_row_counter++;
        } else {
          empty_row_counter = 0;
        }
      }

      if (flags.n) {
        if (temp_variebl && flags.n) {
          printf("%6d\t", ++line_counter);
          temp_variebl = 0;
        }
        if (ch == '\n') {
          temp_variebl = 1;
        }
      }

      if (flags.e) {
        if (ch == '\n') {
          printf("$");
        }
      }

      if (flags.v) {
        ch = v_output(ch);
      }

      if (flags.t) {
        if (ch == 9) {
          printf("^");
          ch = 'I';
        }
      }

      putchar(ch);
    }

    fclose(fptr);
  }
}