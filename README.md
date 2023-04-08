## About

blocklist.pf is a command line utility that can fetch common IP
blocklists, and from those blocklists create PF tables that can
be used when crafting firewall rules in `/etc/pf.conf`.
The available blocklists can be found in the
[`blocklists.c`](/src/blocklists.c)
file. The project is written in C, still young, one of my few C
projects, and for now only works on platforms where libfetch is
available (eg FreeBSD).

## Tables

The following tables are made available to use. It is up to you how
many of them are put into action:

* attacks <br>
  A table of IP addresses reported to be associated with attacks (eg brute force attacks).
* malware <br>
  A table of IP addresses reported to be associated with malware.
* reputation <br>
  A table of IP addresses reported to be associated with suspicous or malicious activity.
* anonymizers <br>
  A table of IP addresses reported to be associated with anonymity (eg Tor).
* adware <br>
  A table of IP addreses reported to be associated with adware.

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
