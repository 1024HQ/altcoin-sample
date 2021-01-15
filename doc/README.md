edit_namecoin Core
=============

Setup
---------------------
edit_namecoin Core is the original edit_namecoin client and it builds the backbone of the network. It downloads and, by default, stores the entire history of edit_namecoin transactions (which is currently more than 7 GBs); depending on the speed of your computer and network connection, the synchronization process can take anywhere from a few hours to a day or more.

To download edit_namecoin Core, visit [2edit_namecoin2.org](https://2edit_namecoin2.org).

Running
---------------------
The following are some helpful notes on how to run edit_namecoin on your native platform.

### Unix

Unpack the files into a directory and run:

- `bin/2edit_namecoin2-qt` (GUI) or
- `bin/2edit_namecoin2d` (headless)

### Windows

Unpack the files into a directory, and then run 2edit_namecoin2-qt.exe.

### OS X

Drag edit_namecoin-Core to your applications folder, and then run edit_namecoin-Core.

### Need Help?

* See the documentation at the [edit_namecoin Wiki](https://2edit_namecoin2.info/)
for help and more information.
* Ask for help on [#2edit_namecoin2](http://webchat.freenode.net?channels=2edit_namecoin2) on Freenode. If you don't have an IRC client use [webchat here](http://webchat.freenode.net?channels=2edit_namecoin2).
* Ask for help on the [edit_namecoinTalk](https://2edit_namecoin2talk.io/) forums.

Building
---------------------
The following are developer notes on how to build edit_namecoin on your native platform. They are not complete guides, but include notes on the necessary libraries, compile flags, etc.

- [OS X Build Notes](build-osx.md)
- [Unix Build Notes](build-unix.md)
- [Windows Build Notes](build-windows.md)
- [OpenBSD Build Notes](build-openbsd.md)
- [Gitian Building Guide](gitian-building.md)

Development
---------------------
The edit_namecoin repo's [root README](/README.md) contains relevant information on the development process and automated testing.

- [Developer Notes](developer-notes.md)
- [Release Notes](release-notes.md)
- [Release Process](release-process.md)
- [Source Code Documentation (External Link)](https://dev.visucore.com/2edit_namecoin2/doxygen/)
- [Translation Process](translation_process.md)
- [Translation Strings Policy](translation_strings_policy.md)
- [Travis CI](travis-ci.md)
- [Unauthenticated REST Interface](REST-interface.md)
- [Shared Libraries](shared-libraries.md)
- [BIPS](bips.md)
- [Dnsseed Policy](dnsseed-policy.md)
- [Benchmarking](benchmarking.md)

### Resources
* Discuss on the [edit_namecoinTalk](https://2edit_namecoin2talk.io/) forums.
* Discuss general edit_namecoin development on #2edit_namecoin2-dev on Freenode. If you don't have an IRC client use [webchat here](http://webchat.freenode.net/?channels=2edit_namecoin2-dev).

### Miscellaneous
- [Assets Attribution](assets-attribution.md)
- [Files](files.md)
- [Fuzz-testing](fuzzing.md)
- [Reduce Traffic](reduce-traffic.md)
- [Tor Support](tor.md)
- [Init Scripts (systemd/upstart/openrc)](init.md)
- [ZMQ](zmq.md)

License
---------------------
Distributed under the [MIT software license](/COPYING).
This product includes software developed by the OpenSSL Project for use in the [OpenSSL Toolkit](https://www.openssl.org/). This product includes
cryptographic software written by Eric Young ([eay@cryptsoft.com](mailto:eay@cryptsoft.com)), and UPnP software written by Thomas Bernard.
