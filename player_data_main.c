#include "hw6.h"

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

int g_player_count = 0;
player_t g_player_array[MAX_PLAYERS] = {0};

/*
 * Prints the information of a player.
 */

static void print_player(player_t player) {
  printf("\tusername: %s\n", player.username);
  printf("\tsecret: %s\n", player.secret);
  printf("\tfriend\ttrust:\n");
  for (int i = 0; i < MAX_FRIENDS; i++) {
    if (*player.friends[i] != 0) {
      printf("\t%s\t%d\n", player.friends[i], player.trust[i]);
    }
  }
} /* print_player() */

/*
 * This function is used to run the different functions implemented in file
 * hw6.c. User input is used to determine which function to run and what input
 * is passed to it. Upon completion, the function returns zero.
 */

int main() {
  int choice = 0;
  bool good_file = false;
  while (true) {
    printf(
      "Select a function to test:\n"
      "    1) read_players()\n"
      "    2) find_imposters()\n"
      "    3) print players\n"
      "    4) Exit\n"
      "Enter your choice: "
    );

    scanf("%d", &choice);
    getchar();

    char in_file[MAX_FILE_LEN] = {0};

    switch (choice) {
      case 1:
        good_file = false;

        /* read filename and open file */

        printf("\nEnter the input file name: ");
        scanf("%s", in_file);

        /* run read_players() and print result */

        int num_players = read_players(in_file);
        printf("\nread_players(%s) returned %d\n\n", in_file, num_players);

        if (num_players > 1) {
          good_file = true;
        }
        break;

      case 2:
        if (!good_file) {
          printf(
            "\ng_player_array is not loaded. Use read_courses() first!\n\n"
          );
          break;
        }

        /* run find_imposters() and print result */

        int num_imposters = find_imposters();
        printf("\nfind_imposters() returned %d\n\n", num_imposters);
        break;

      case 3:
        if (!good_file) {
          printf(
            "\ng_player_array is not loaded. Use read_courses() first!\n\n"
          );
          break;
        }

        printf("The following data were loaded:\n");
        for (int i = 0; i < g_player_count; i++) {
          printf("Player %d:\n", i + 1);
          print_player(g_player_array[i]);
        }
        printf("\n");
        break;

      case 4:
        printf("\nGoodbye!\n\n");
        return 0;

      default:
        printf("\nSelect one of the given options...!\n\n");
        break;
    }
  }

  return 0;
} /* main() */