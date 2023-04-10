#include <blocklist.pf/fetch.h>

dyn_array*
fetch_blocklist(blocklist *bl, int maxcols) {
  struct url *u;
  FILE *f;
  dyn_array *ary;
  u = fetchParseURL(bl->url);
  f = fetchGetHTTP(u, "");
  if (f == NULL) {
    return NULL;
  }
  ary = array_from_file(f, maxcols);
  fclose(f);
  return ary;
}
