#include <blocks/alloc.h>
#include <blocks/block.h>
#include <blocks/blocks.h>
#include <string.h>
#include <sys/param.h>
#include <curl/curl.h>

static block ALL_BLOCKS[] = {
    /**
     * table = attacks
     **/
    [0] = {.id       = 1,
           .name     = "FireHOL (level 1)",
           .desc     = "A set of IP addresses all internet facing servers, "
                       "routers and firewalls shouldn't communicate with",
           .table    = "attacks",
           .filename = "attacks_firehol1.txt",
           .url     = "https://iplists.firehol.org/files/firehol_level1.netset",
           .www     = "https://iplists.firehol.org/?ipset=firehol_level1",
           .format  = "netset",
           .enabled = true,
           .path    = block_path,
           .write   = block_write},
    [1]
    = {.id   = 2,
       .name = "FireHOL (web server)",
       .desc = "A set of IP addresses reported to pose a threat to web servers",
       .table    = "attacks",
       .filename = "attacks_fireholwebserver.txt",
       .url      = "https://iplists.firehol.org/files/firehol_webserver.netset",
       .www      = "https://iplists.firehol.org/?ipset=firehol_webserver",
       .format   = "netset",
       .enabled  = true,
       .path     = block_path,
       .write    = block_write},

    /**
     * table = malware
     **/
    [2] = {.id   = 3,
           .name = "FireHOL (web browser)",
           .desc
           = "A set of IP addresses reported to pose a threat to web browsers",
           .filename = "malware_fireholwebclient.txt",
           .table    = "malware",
           .url = "https://iplists.firehol.org/files/firehol_webclient.netset",
           .www = "https://iplists.firehol.org/?ipset=firehol_webclient",
           .format  = "netset",
           .enabled = true,
           .path    = block_path,
           .write   = block_write},

    /**
     * table = anonymizers
     **/
    [3] = {.id       = 4,
           .name     = "TOR exit nodes",
           .desc     = "A set of IP addresses that act as Tor exit nodes",
           .filename = "anonymizers_torexit.txt",
           .table    = "anonymizers",
           .url      = "https://iplists.firehol.org/files/tor_exits.ipset",
           .www      = "https://iplists.firehol.org/?ipset=tor_exits",
           .format   = "ipset",
           .enabled  = true,
           .path     = block_path,
           .write    = block_write},

    /**
     * table = adware
     **/
    [4] = {.id       = 5,
           .name     = "Ad Servers",
           .desc     = "A set of IP addresses associated with adware",
           .filename = "adware_yoyoadservers.txt",
           .table    = "adware",
           .url      = "https://iplists.firehol.org/files/yoyo_adservers.ipset",
           .www      = "https://iplists.firehol.org/?ipset=yoyo_adservers",
           .format   = "ipset",
           .enabled  = true,
           .path     = block_path,
           .write    = block_write},

    /**
     * Terminates the array. DO NOT REMOVE.
     **/
    [5] = NULL_BLOCKLIST};

block *
blocks_all(const char *state)
{
  if (strcmp(state, "enabled") == 0)
  {
    return (blocks_enabled(ALL_BLOCKS));
  }
  else if (strcmp(state, "disabled") == 0)
  {
    return (blocks_disabled(ALL_BLOCKS));
  }
  else
  {
    return (NULL);
  }
}

block *
blocks_enabled(block blocks[])
{
  block *enabled;
  block *dest;
  size_t size;
  size    = blocks_size(blocks);
  enabled = alloc(sizeof(block) * (size + 1));
  dest    = enabled;
  while (blocks->name != NULL)
  {
    if (blocks->enabled)
    {
      *dest = *blocks;
      dest++;
    }
    blocks++;
  }
  *dest = NULL_BLOCKLIST;
  return (enabled);
}

block *
blocks_disabled(block blocks[])
{
  block *disabled;
  block *dest;
  size_t size;
  size     = blocks_size(blocks);
  disabled = alloc(sizeof(block) * (size + 1));
  dest     = disabled;
  while (blocks->name != NULL)
  {
    if (!blocks->enabled)
    {
      *dest = *blocks;
      dest++;
    }
    blocks++;
  }
  *dest = NULL_BLOCKLIST;
  return (disabled);
}

block *
blocks_group(block blocks[], const char *table)
{
  block *group;
  block *dest;
  size_t size;
  size  = blocks_size(blocks);
  group = alloc(sizeof(block) * (size + 1));
  dest  = group;
  while (blocks->name != NULL)
  {
    if (strcmp(blocks->table, table) == 0)
    {
      *dest = *blocks;
      dest++;
    }
    blocks++;
  }
  *dest = NULL_BLOCKLIST;
  return (group);
}

size_t
blocks_size(block blocks[])
{
  size_t size = 0;
  while (blocks->name != NULL)
  {
    size++;
    blocks++;
  }
  return (size);
}
