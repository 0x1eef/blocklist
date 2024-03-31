#include <blocklist/alloc.h>
#include <blocklist/blocklist.h>
#include <errno.h>
#include <string.h>
#include <curl/curl.h>

char *
blocklist_path(const char *filename)
{
  char *home;
  home = getenv("HOME");
  if (home)
  {
    char *relpath  = "/.local/share/blocklist/", *fullpath;
    size_t offset1 = strlen(home), offset2 = strlen(relpath),
           bufsize = offset1 + offset2 + strlen(filename) + 1;
    fullpath       = alloc(sizeof(char) * bufsize);
    memcpy(&fullpath[0], home, offset1);
    memcpy(&fullpath[offset1], relpath, offset2);
    memcpy(&fullpath[offset1 + offset2], filename, strlen(filename) + 1);
    return (fullpath);
  }
  else
  {
    char *fullpath = strdup("/usr/local/share/pf/blocklist");
    if (fullpath)
    {
      return (fullpath);
    }
    else
    {
      fprintf(stderr, "[fatal] %s", strerror(errno));
      abort();
    }
  }
}

int
blocklist_store(const char *urlstr, const char *path)
{
  FILE *file;
  file = fopen(path, "w");
  if (file == NULL)
  {
    return (-1);
  }
  else
  {
    CURL *curl;
    CURLcode res;
    curl = curl_easy_init();
    curl_easy_setopt(curl, CURLOPT_URL, urlstr);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, file);
    res = curl_easy_perform(curl);
    curl_easy_cleanup(curl);
    fclose(file);
    return (res);
  }
}
