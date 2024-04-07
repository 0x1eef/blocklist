## About

blocklist is a command line utility that can download common IPv4
blocklists, and from those blocklists emit
[pf.conf(5)](https://man.freebsd.org/cgi/man.cgi?pf.conf(5))
tables that can be used when crafting firewall rules in `/etc/pf.conf`.
The available blocklists can be found in
[`src/blocklists.c`](/src/blocklists.c).

## Examples

* **CLI**

        # Setup directories
        $ mkdir -p ~/.local/share/blocklist/
        $ mkdir -p /usr/local/share/pf/

        # Download blocklists into ~/.local/share/blocklist/
        $ blocklist download

        # Emit pf.conf(5) tables
        $ blocklist emit > /usr/local/share/pf/blocklist

* **`/etc/pf.conf`**

        include "/usr/local/share/pf/blocklist"
        blocklist = "{ <attacks>, <malware>, <anonymizers>, <adware> }"

        set skip on lo0
        block all
        pass out on ue0
        block out on ue0 from any to $blocklist

## Tables

* __&lt;attacks&gt;__ <br>
  A table of IP addresses reported to be associated with attacks (eg brute force attacks).
* __&lt;malware&gt;__ <br>
  A table of IP addresses reported to be associated with malware.
* __&lt;anonymizers&gt;__ <br>
  A table of IP addresses reported to be associated with anonymity (eg Tor).
* __&lt;adware&gt;__ <br>
  A table of IP addreses reported to be associated with adware.

## Install

    # Clone repository
    $ git clone https://github.com/0x1eef/blocklist
    $ cd blocklist

    # Build and install
    $ make build
    # make install

## See also

* [libcurl](https://curl.se/libcurl/)
  is a required runtime dependency.
* [blocklist.cron](https://github.com/0x1eef/blocklist.cron#readme)
  configures blocklist to run at regular intervals via
  [cron(8)](https://man.freebsd.org/cgi/man.cgi?cron(8)).

## Sources

* [GitHub](https://github.com/0x1eef/blocklist#readme)
* [GitLab](https://gitlab.com/0x1eef/blocklist#about)
* [git.hardenedbsd.org](https://git.hardenedbsd.org/0x1eef/blocklist#about)

## License

[BSD Zero Clause](https://choosealicense.com/licenses/0bsd/).
<br>
See [LICENSE](./LICENSE).
