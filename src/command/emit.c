#include <blocks/alloc.h>
#include <blocks/blocks.h>
#include <errno.h>
#include <sysexits.h>
#include <isinetaddr.h>
#include <string.h>

static const int LINELEN = 128;
static const char *tablenames[]
    = {"attacks", "malware", "anonymizers", "adware", NULL};
static int write_table_head(FILE *, const char *);
static int write_table_body(FILE *, FILE *);
static int write_table_tail(FILE *);
static int write_table_comment(FILE *, block *);

int
emit_command(void)
{
  const char **name = tablenames;
  block *enabled    = blocks_all("enabled");
  while (*name != NULL)
  {
    block *blocks = blocks_group(enabled, *name);
    block *block  = blocks;
    write_table_head(stdout, *name);
    while (block->name != NULL)
    {
      char *path = block->path(block);
      if (path)
      {
        FILE *in = fopen(path, "r");
        write_table_comment(stdout, block);
        if (in == NULL || write_table_body(stdout, in))
        {
          fprintf(stderr, "[x] %s: IO error\n", path);
          return (EX_IOERR);
        }
        free(path);
        block++;
      }
      else
      {
        fprintf(stderr, "[x] '%s' unable to determine path\n", block->name);
        return (EX_IOERR);
      }
    }
    write_table_tail(stdout);
    name++;
    free(blocks);
  }
  free(enabled);
  return (EX_OK);
}

static int
write_table_head(FILE *out, const char *name)
{
  fprintf(out, "table <%s> {\n", name);
  return 0;
}

static int
write_table_body(FILE *out, FILE *in)
{
  char buf[LINELEN];
  int err = 0;
  errno   = 0;
  while (fgets(buf, LINELEN, in))
  {
    buf[strcspn(buf, "\n")] = '\0';
    if (iscidraddr4(buf))
    {
      fprintf(out, "  %s\n", buf);
    }
    if (errno)
    {
      err = -1;
      break;
    }
  }
  return err;
}

static int
write_table_tail(FILE *out)
{
  fprintf(out, "}\n");
  return 0;
}

static int
write_table_comment(FILE *out, block *block)
{
  fprintf(out,
          "  ##\n"
          "  # %s\n"
          "  # %s\n"
          "  # www: %s\n"
          "  # raw: %s\n",
          block->name,
          block->desc,
          block->www,
          block->url);
  return 0;
}
