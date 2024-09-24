#include "player_data.h"
#include <assert.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int g_player_count;
player_t g_player_array[MAX_PLAYERS];

int normal_characters(const char *str);
int unique_username(const char *str);
int get_lines(FILE *file);

bool has_duplicates() {
  for (int i = 0; i < g_player_count; ++i) {
    int count = 1;
    for (int j = 0; j < g_player_count; ++j) {
      if ((i != j) &&
        (strcmp(g_player_array[i].username, g_player_array[j].username) == 0)) {
        count++;
        if (count >= 2) {
          return true;
        }
      }
    }
  }
  return false;
}

int normal_characters(const char *str) {
  for (int i = 0; str[i]; i++) {
    if (!isalpha(str[i])) {
      return 0;
    }
  }
  return 1;
}

char* strtoke(char *str, const char *delim) {
  static char *g_check = NULL;
  char *token = NULL;
  if (str) g_check = str;
  if (!g_check) return NULL;
  token = g_check;
  g_check = strpbrk(g_check, delim);
  if (g_check) *g_check++ = '\0';
  return token;
}

int unique_username(const char *str) {
  for (int i = 0; i < g_player_count; i++) {
    if (strcmp(g_player_array[i].username, str) == 0) {
      return 0;
    }
  }
  return 1;
}

int get_lines(FILE *file) {
  int ch = 0;
  int lines = 0;
  while (!feof(file)) {
    ch = fgetc(file);
    if (ch == '\n') {
      lines++;
    }
  }
  rewind(file);
  return lines;
}

int read_players(char *in_file) {
  g_player_count = 0;
  assert(in_file != NULL);
  FILE *file = fopen(in_file, "r");
  if (file == NULL) {
    return NON_READABLE_FILE;
  }
  int lines = get_lines(file);
  if (lines > MAX_PLAYERS) {
    fclose(file);
    return TOO
