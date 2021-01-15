### Qos ###

This is a Linux bash script that will set up tc to limit the outgoing bandwidth for connections to the edit_namecoin network. It limits outbound TCP traffic with a source or destination port of 9333, but not if the destination IP is within a LAN (defined as 192.168.x.x).

This means one can have an always-on 2edit_namecoin2d instance running, and another local 2edit_namecoin2d/2edit_namecoin2-qt instance which connects to this node and receives blocks from it.
