#include <string.h>

char*
chomp(char *str) {
  for(int i = strlen(str); i > 0; i--) {
    if(str[i] == '\n') {
      str[i] = '\0';
      return str;
    }
  }
  return str;
}
