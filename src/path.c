#include <blockem/path.h>

static char * join_sep(char *str, char *chr);

char *
blocklistpf_dir(void)
{
  if (getenv("BLOCKEM_DIR")) {
    return (strdup(getenv("BLOCKEM_DIR")));
  } else if (getenv("XDG_DATA_HOME")) {
    return (join_path(getenv("XDG_DATA_HOME"), "blockem", NULL));
  } else if (getenv("HOME")) {
    return (join_path(getenv("HOME"), ".local", "share", "blockem", NULL));
  } else {
    return (strdup("/usr/local/share/blockem"));
  }
}


char *
join_path(char *str, ...)
{
  char *path;
  int c;
  va_list args;
  path = strdup("\0");
  c = 0;
  va_start(args, str);
  while (str != NULL)
  {
    char *j;
    j = join_sep(str, "/");
    c += strlen(j);
    path = realloc(path, sizeof(char[c + 2]));
    strncat(path, j, strlen(j));
    str = va_arg(args, char *);
  }
  va_end(args);
  return (path);
}


int
mkdir_p(char *path)
{
  char *token, *copy;
  struct stat st;
  path = strdup(path);
  copy = NULL;
  while ((token = strsep(&path, "/")) != NULL)
  {
    if (strlen(token) == 0) {
      continue;
    }
    copy = (copy ? join_path(copy, token, NULL) : join_path(token, NULL));
    errno = 0;
    if (stat(copy, &st) == -1) {
      if (errno == ENOENT) {
        errno = 0;
        return (mkdir(copy, S_IRWXU | S_IFDIR));
      } else {
        return (-1);
      }
    }
  }
  return (0);
}


static char *
join_sep(char *str, char *sep)
{
  int len, i, j;
  char *cpy, *cpyptr;
  len = strlen(str);
  cpyptr = cpy = malloc(sizeof(char[len + 2]));
  cpyptr = cpy;
  memcpy(cpyptr++, sep, 1);
  i = str[0] == *sep ? 1 : 0;
  j = str[len-1] == *sep ? len-1 : len;
  while (i < j)
  {
    memcpy(cpyptr++, &str[i], 1);
    i++;
  }
  memcpy(cpyptr, "\0", 1);
  return (cpy);
}
