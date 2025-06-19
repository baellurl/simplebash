#include "parser.h"

option parser_flags(int argc, char **argv) {

  option flags = {0};

  int opt;

  while ((opt = getopt(argc, argv, "e:ivclnhsf:o")) != -1) {
    switch (opt) {
    case 'e':
      flags.e = 1;
      add_pattern(&flags, optarg);
      // ??

      break;

    case 'i':
      flags.i = REG_ICASE;
      break;

    case 'v':
      flags.v = 1;
      break;

    case 'c':
      flags.c = 1;
      break;

    case 'l':
      flags.l = 1;
      break;

    case 'n':
      flags.n = 1;
      break;

    case 'h':
      flags.h = 1;
      break;

    case 's':
      flags.s = 1;
      break;

    case 'f':
      flags.f = 1;
      read_pattern_file(&flags, optarg);

      break;

    case 'o':
      flags.o = 1;
      break;

    default:

      fprintf(stderr, "Usage: grep [OPTION]... PATTERNS [FILE]...\n");
      fprintf(stderr, "Try 'grep --help' for more information.\n");
      exit(1);
    }
  }
  if (flags.pattern == NULL) {
    add_pattern(&flags, argv[optind]);
    optind++;
  }

  if (argc - optind == 1) {
    flags.h = 1;
  }

  return flags;
}

// ВЫВОД СТРОКИ
void output_line(char *line, int n) {

  for (int i = 0; i < n; i++) {
    putchar(line[i]);
  }
  if (line[n - 1] != '\n') {
    putchar('\n');
  }
}

void print_match(regex_t *_regex, char *line) {

  regmatch_t match;
  int offset = 0;

  while (1) {

    int result = regexec(_regex, line + offset, 1, &match, 0);

    if (result != 0) {
      break;
    }
    for (int i = match.rm_so; i < match.rm_eo; i++) {

      putchar(line[offset + i]);
    }
    putchar('\n');

    offset += match.rm_eo;
  }
}

void add_pattern(option *flags, char *pattern) { // для двойного флага -е
  int n = strlen(pattern);
  if (flags->len_pattern == 0) {
    flags->pattern = malloc(1024 * sizeof(char));
    flags->mem_pattern = 1024;
  }

  if (flags->mem_pattern < flags->len_pattern + n) {
    flags->pattern = realloc(flags->pattern, flags->mem_pattern * 2);
  }

  if (flags->len_pattern != 0) {
    flags->len_pattern += sprintf(flags->pattern + flags->len_pattern, "|");
  }

  flags->len_pattern +=
      sprintf(flags->pattern + flags->len_pattern, "(%s)", pattern);
}

//ФЛАГ -f
void read_pattern_file(option *flags, char *file_path) {

  FILE *file_ptr = fopen(file_path, "r");

  if (file_ptr == NULL) {
    fprintf(stderr, "s21_grep: %s: No such file or directory\n", file_path);

    exit(1);
  }

  char *line = NULL;

  size_t buffer_size = 0;
  ssize_t read;

  read = getline(&line, &buffer_size, file_ptr);

  while (read != -1) {

    if (line[read - 1] == '\n')
      line[read - 1] = '\0';

    add_pattern(flags, line);

    read = getline(&line, &buffer_size, file_ptr);
  }

  free(line);

  fclose(file_ptr);
}

//  обработка файла   regex_t *reg
void processFile(option flags, char *path, regex_t *compiled) {

  FILE *_ptr_file = fopen(path, "r");
  if (_ptr_file == NULL) {
    // ???
    if (!flags.s)
      fprintf(stderr, "s21_grep: %s: No such file or directory\n", path);
    return;
  }

  char *_lineptr = NULL; // указатель на первый символ в памяти
  size_t _n = 0;    // размер_буффера_строки
  ssize_t read = 0; // количество символов
  int line_number = 1;
  int str_match = 0; // количество совпадающих строк

  read = getline(&_lineptr, &_n, _ptr_file);

  while (read != -1) {

    int result = regexec(compiled, _lineptr, 0, NULL, 0);

    if ((result == 0 && !flags.v) || (flags.v && result != 0)) {

      if (!flags.c && !flags.l) {
        if (!flags.h)
          printf("\033[0;35m%s:\033[0m", path);

        if (flags.n) {
          printf("%d:", line_number);
        }

        if (flags.o) {
          print_match(compiled, _lineptr);
        } else {
          output_line(_lineptr, read);
        }
      }
      str_match++;
    }

    read = getline(&_lineptr, &_n, _ptr_file);

    line_number++;
  }

  free(_lineptr);

  if (flags.l) {
    printf("\033[0;35m%s\033[0m\n", path);
  }
  if (flags.c) {
    printf("%d\n", str_match);
  }

  fclose(_ptr_file);
}

// компиляц рег выражение и вывод

void outputFile(option flags, int argc, char **argv) {
  regex_t _pregex;
  int error = regcomp(&_pregex, flags.pattern, REG_EXTENDED | flags.i);
  if (error)
    perror("Error");

  for (int i = optind; i < argc; i++) {

    processFile(flags, argv[i], &_pregex);
  }

  regfree(&_pregex);
}
