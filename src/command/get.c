#include <blocklist/blocks.h>
#include <curl/curl.h>
#include <errno.h>
#include <sysexits.h>
#include <stdlib.h>
#include <string.h>

int
get_command(void)
{
  block *enabled;
  block *block;
  enabled = blocks_all("enabled");
  block   = enabled;
  while (block->name != NULL)
  {
    const char *url = block->url;
    char *path      = block->local_path(block);
    int err         = block->write(path, url);
    if (err)
    {
      if (err == -1)
      {
        fprintf(stderr, "[fatal] %s: %s\n", path, strerror(errno));
        return (EX_IOERR);
      }
      else
      {
        fprintf(stderr, "[fatal] network error (%s)\n", url);
        return (EX_UNAVAILABLE);
      }
    }
    else
    {
      printf("[ok] %s\n", path);
    }
    block++;
    free(path);
  }
  free(enabled);
  return (EX_OK);
}
