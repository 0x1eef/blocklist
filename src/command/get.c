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
    if (path)
    {
      int err = block->write(path, url);
      if (err)
      {
        if (err == -1)
        {
          fprintf(stderr, "[x] %s (%s)\n", strerror(errno), path);
          return (EX_IOERR);
        }
        else
        {
          fprintf(stderr, "[x] network error (%s)\n", url);
          return (EX_UNAVAILABLE);
        }
      }
      else
      {
        fprintf(stdout, "[-] GET\t%s\n", path);
      }
      block++;
      free(path);
    }
    else
    {
      fprintf(stdout, "[x] '%s' unable to determine path\n", block->name);
      return (EX_IOERR);
    }
  }
  free(enabled);
  return (EX_OK);
}
