#include <blocklist/cmd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include <getopt.h>

static void
help(void)
{
  printf("Usage: blocklist fetch|cat [OPTIONS]\n");
}


int
main(int argc, char *argv[])
{
  if (argc < 2) {
    help();
    exit(0);
  }
  if (strcmp(argv[1], "fetch") == 0) {
    fetch_cmd();
  } else if (strcmp(argv[1], "cat") == 0) {
    cat_cmd();
  } else {
    help();
  }
}
