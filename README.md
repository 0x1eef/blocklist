## About

blocklist.pf is a command line utility that can fetch common IP
blocklists, and from those blocklists create PF tables that can
be used when crafting firewall rules in `/etc/pf.conf`.
The available blocklists can be found in the
[`blocklists.c`](/src/blocklists.c)
file. The project is written in C, still young, one of my few C
projects, and for now only works on platforms where libfetch is
available (eg FreeBSD).

## Examples

The command line interface:

    # Fetch the blocklists.
    $ blocklist.pf fetch

    # Cat all PF tables to "/usr/local/share/pf/blocklist.pf"
    $ blocklist.pf cat > /usr/local/share/pf/blocklist.pf

An example of how the tables might be used from `/etc/pf.conf`:

    blocklists = "{ <attacks>, <malware>, <reputation>, <anonymizers>, <adware> }"
    include "/usr/local/share/pf/blocklist.pf"

    block all
    block in quick on ue0 from $blocklists to any
    block out quick on ue0 from any to $blocklists
    pass out on ue0
    pass in on ue0

## Tables

The following tables are made available:

* __attacks__ <br>
  A table of IP addresses reported to be associated with attacks (eg brute force attacks).
* __malware__ <br>
  A table of IP addresses reported to be associated with malware.
* __reputation__ <br>
  A table of IP addresses reported to be associated with suspicous or malicious activity.
* __anonymizers__ <br>
  A table of IP addresses reported to be associated with anonymity (eg Tor).
* __adware__ <br>
  A table of IP addreses reported to be associated with adware.

## Configuration

In order of preference, the blocklists that are fetched can be saved to:

* `$BLOCKLISTPF_DIR`
* Otherwise: `$XDG_DATA_HOME/blocklist.pf/`
* Otherwise: `$HOME/.local/share/blocklist.pf`
* Otherwise: `usr/local/share/blocklist.pf`

## Install

    git clone https://github.com/0x1eef/blocklist.pf
    cd blocklist.pf
    make build
    ./bin/blocklist.pf

## Sources

* [Source code (GitHub)](https://github.com/0x1eef/blocklist.pf#readme)
* [Source code (GitLab)](https://gitlab.com/0x1eef/blocklist.pf#about)
* [Source code (HardenedBSD)](https://git.hardenedbsd.org/0x1eef/blocklist.pf#about)

## License

[BSD Zero Clause](https://choosealicense.com/licenses/0bsd/).
<br>
See [LICENSE](./LICENSE).
