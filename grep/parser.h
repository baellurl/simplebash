#ifndef PARSER_H
#define PARSER_H

#define _POSIX_C_SOURCE 200809L// Для getline()
#include <stdio.h>
#include <getopt.h>
#include <regex.h>
#include <stdlib.h>
#include <string.h>



typedef struct flags
{
    int e, i, v, c, l, n, h, s, f, o;
    char *pattern; // хранение регулярное выражение
    int len_pattern; // количество символов в массиве
    int mem_pattern;

} option;


option parser_flags(int argc, char **argv);
void add_pattern(option *flags, char *pattern);
void add_reg_from_file(option *flags, char *path);
void processFile(option flags,char *path,regex_t *compiled);
void outputFile(option flags, int argc, char **argv);
void read_pattern_file(option *flags, char *file_path);
void print_match(regex_t *regex, char *line);
#endif
