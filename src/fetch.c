#include <blocklist/fetch.h>

dyn_array *
fetch_blocklist(blocklist *bl)
{
  struct url *u;
  FILE *f;
  dyn_array *ary;
  u = fetchParseURL(bl->url);
  f = fetchGetHTTP(u, "");
  if (f == NULL) {
    return (NULL);
  }
  ary = array_from_file(f);
  fclose(f);
  return (ary);
}
