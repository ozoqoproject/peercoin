Pozoqo 0.11.8 BETA

Setup
---------------------
Pozoqo is the original Pozoqo client and it builds the backbone of the network. It downloads and, by default, stores the entire history of Pozoqo transactions (which is currently less than one gigabyte); depending on the speed of your computer and network connection, the synchronization process can take anywhere from a few hours to a day or more.

To download Pozoqo, visit [pozoqo.tech](https://pozoqo.tech/download).

Running
---------------------
The following are some helpful notes on how to run Pozoqo on your native platform.

### Unix

Unpack the files into a directory and run:

- `bin/pozoqo-qt` (GUI) or
- `bin/pozoqod` (headless)

### Windows

Unpack the files into a directory, and then run pozoqo-qt.exe.

### macOS

Drag Pozoqo to your applications folder, and then run Pozoqo.

### Need Help?

* See the documentation at the [Pozoqo Wiki](https://docs.pozoqo.tech/)
for help and more information.
* Pozoqo is very similar to bitcoin, so you can use their wiki [Bitcoin Wiki](https://en.bitcoin.it/wiki/Main_Page).
* Ask for help on [#general](https://pozoqo.chat/) on pozoqo.chat.

Building
---------------------
The following are developer notes on how to build Pozoqo on your native platform. They are not complete guides, but include notes on the necessary libraries, compile flags, etc.

- [Dependencies](dependencies.md)
- [macOS Build Notes](build-osx.md)
- [Unix Build Notes](build-unix.md)
- [Windows Build Notes](build-windows.md)
- [FreeBSD Build Notes](build-freebsd.md)
- [OpenBSD Build Notes](build-openbsd.md)
- [NetBSD Build Notes](build-netbsd.md)
- [Gitian Building Guide (External Link)](https://github.com/bitcoin-core/docs/blob/master/gitian-building.md)

Development
---------------------
The Pozoqo repo's [root README](/README.md) contains relevant information on the development process and automated testing.

- [Developer Notes](developer-notes.md)
- [Productivity Notes](productivity.md)
- [Release Notes](release-notes.md)
- [Release Process](release-process.md)
- [Source Code Documentation (External Link)](none-yet)
- [Translation Process](translation_process.md)
- [Translation Strings Policy](translation_strings_policy.md)
- [JSON-RPC Interface](JSON-RPC-interface.md)
- [Unauthenticated REST Interface](REST-interface.md)
- [Shared Libraries](shared-libraries.md)
- [BIPS](bips.md)
- [Dnsseed Policy](dnsseed-policy.md)
- [Benchmarking](benchmarking.md)

### Resources
* Discuss on the [Pozoqo](https://talk.pozoqo.tech/) forums.

### Miscellaneous
- [Assets Attribution](assets-attribution.md)
- [bitcoin.conf Configuration File](bitcoin-conf.md)
- [Files](files.md)
- [Fuzz-testing](fuzzing.md)
- [Reduce Memory](reduce-memory.md)
- [Reduce Traffic](reduce-traffic.md)
- [Tor Support](tor.md)
- [Init Scripts (systemd/upstart/openrc)](init.md)
- [ZMQ](zmq.md)
- [PSBT support](psbt.md)

License
---------------------
Distributed under the [MIT software license](/COPYING).
