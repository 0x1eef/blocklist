#include <blocklist/alloc.h>
#include <blocklist/blocks.h>
#include <string.h>
#include <stdio.h>
#include <sys/param.h>
#include <curl/curl.h>

static block ALL_BLOCKS[] = {
    /**
     * table = attacks
     **/
    [0] = {.name  = "firehol (level 1)",
           .desc  = "An IP blocklist that's suitable for basic protection on "
                    "all internet facing servers, routers and firewalls.",
           .table = "attacks",
           .filename = "attacks_firehol1.txt",
           .url     = "https://iplists.firehol.org/files/firehol_level1.netset",
           .www     = "https://iplists.firehol.org/?ipset=firehol_level1",
           .format  = "netset",
           .enabled = true,
           .local_path = blocklist_localpath,
           .write      = blocklist_write},
    [1] = {.name     = "firehol (web server)",
           .desc     = "An IP blocklist made from blocks that track IPs "
                       "a web server should never talk to.",
           .table    = "attacks",
           .filename = "attacks_fireholwebserver.txt",
           .url = "https://iplists.firehol.org/files/firehol_webserver.netset",
           .www = "https://iplists.firehol.org/?ipset=firehol_webserver",
           .format     = "netset",
           .enabled    = true,
           .local_path = blocklist_localpath,
           .write      = blocklist_write},

    /**
     * table = malware
     **/
    [2] = {.name     = "firehol (web browser)",
           .desc     = "An IP blocklist made from blocks that track IPs "
                       "a web browser should never talk to.",
           .filename = "malware_fireholwebclient.txt",
           .table    = "malware",
           .url = "https://iplists.firehol.org/files/firehol_webclient.netset",
           .www = "https://iplists.firehol.org/?ipset=firehol_webclient",
           .format     = "netset",
           .enabled    = true,
           .local_path = blocklist_localpath,
           .write      = blocklist_write},

    /**
     * table = anonymizers
     **/
    [3] = {.name       = "TOR exit nodes",
           .desc       = "An IP blocklist of TOR exit nodes.",
           .filename   = "anonymizers_torexit.txt",
           .table      = "anonymizers",
           .url        = "https://iplists.firehol.org/files/tor_exits.ipset",
           .www        = "https://iplists.firehol.org/?ipset=tor_exits",
           .format     = "ipset",
           .enabled    = true,
           .local_path = blocklist_localpath,
           .write      = blocklist_write},

    /**
     * table = adware
     **/
    [4] = {.name     = "adservers",
           .desc     = "An IP blocklist of ad servers.",
           .filename = "adware_yoyoadservers.txt",
           .table    = "adware",
           .url      = "https://iplists.firehol.org/files/yoyo_adservers.ipset",
           .www      = "https://iplists.firehol.org/?ipset=yoyo_adservers",
           .format   = "ipset",
           .enabled  = true,
           .local_path = blocklist_localpath,
           .write      = blocklist_write},

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
