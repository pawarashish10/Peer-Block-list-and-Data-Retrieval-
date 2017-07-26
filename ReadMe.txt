To build a peer-to-peer application Using Socket Programming

PEER1/SERVER

- Server will accept following command and will respond back based on command

0x00 Peer List Request 
0x01 Peer List Response
0x02 Block List Request
0x03 Block List Response
0x04 Block Request
0x05 Block Response Success
0x06 Block Response Failure
0x07 File Size Request
0x08 File Size Response 
0x7F Error


Peer List Request Messages - 
Peer List Request messages are sent to peers to query what other peers they know about. The message is only one byte in 
size, consisting of the Type ?eld with a value 0x00.

Peer List Response Messages - 
Peer List Response messages contain the list of peers shared by the queried peer. These messages contain the following 
?elds, in the order described below.

Block List Request Messages
Block List Request messages are sent to peers to query what blocks are available. The message is only one byte in size, 
consisting of the Type ?eld with a value 0x02.

Block List Response Messages
Block List Response messages contain the list of block ranges available at the queried peer. These messages contain the 
following ?elds, in the order described below.
1. Type: the one byte type ?eld with the value 0x03. 
2. Block Range Count: a two byte ?eld which contains the number of block ranges to follow. At most 32767 block ranges 
may be in a Block List Response message. 
3. Block Range: a number of block ranges, as speci?ed by the Block Range Count. Each block range is a two byte start 
value and a two byte end value.

Block Request Messages
Block Request messages are sent to peers to request data for a range of blocks. Each message contains three ?elds, 
the type, the starting block number, and the ending block number. Block numbers are unsigned short values and 16 bits 
in size. The starting and ending block numbers may be the same if you are requesting only one block. The peers will return 
all data for the block from starting to ending block numbers, inclusive.

Block Response Success Messages
Block Response Success messages contain the data requested by the previous Block Request message. Their size varies 
depending on how many blocks were requested. The message starts with the one byte type ?eld and continues with the block 
data. The data returned by the peer is for all the blocks requested in numerical order.

Block Response Failure Messages
Block Response Failure messages indicate that the peer could not retrieve the requested blocks. Each message contains 
the one byte type ?eld followed by a NULL terminated string indicating the error.

File Size Request Messages
File Size Request messages contain only the type byte and request that the peer return the size of the ?le to download 
measured in Bytes.

File Size Response Messages
File Size Response messages provide the size of the ?le to download. Each message contains the type byte followed by the 
number of Bytes in the ?le encoded in an integer (32-bits). These messages are thus 5 Bytes in size.

PEER2/CLIENT

1. Read the hostname or IP address from the command line 
2. Connect to the peer over TCP on port 8888 
3. Send a valid Peer List Request message 
4. Receive the Peer List Response message 
//5. Print the peers to the terminal
6.Connect to the peer 
7. Request the available blocks at that peer 
//8. Print the peer address and blocks to the terminal
9. Connect to a peer with the block or blocks you need 
10. Download the block or blocks you need 
11. Save the blocks to a ?le







