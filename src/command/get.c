#include <blocks/blocks.h>
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
    char *path      = block->path(block);
    if (path)
    {
      int err = block->write(path, url);
      if (err)
      {
        if (err == -1)
        {
          fprintf(stderr, "error: write error\n");
          return (EX_IOERR);
        }
        else
        {
          fprintf(stderr, "error: network error\n");
          return (EX_UNAVAILABLE);
        }
      }
      else
      {
        fprintf(stdout, "ok: %s\n", block->filename);
      }
      block++;
      free(path);
    }
    else
    {
      fprintf(stdout, "error: unable to determine path\n");
      return (EX_IOERR);
    }
  }
  free(enabled);
  return (EX_OK);
}
