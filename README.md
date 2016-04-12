# Rabbit-Cipher

Rabbit cipher is a 128 bit stream cipher designed by Martin Boesgaard, Mette Vesterager, Thomas Pedersen, Jesper Christiansen and Ove Scavenius.

It uses a 128 bit key and a 64 bit initialization vector.

It is implemented in C++.

More about this cipher can be read at [its eSTREAM page](http://www.ecrypt.eu.org/stream/e2-rabbit.html "Title").

## Usage

First set the 128 bit key.
Then call the encrypt() function with the message to be encrypted in a vector of container of size 32 bit.

### Example

key1 = [0000 0000 0000 0000 0000 0000 0000 0000]

plain_text = [0000 0000 0000 0000 ]

iv = [0000 0000]

cipher_text = [ED B7 05 67 37 5D CD 7C D8 95 54 F8 5E 27 A7 C6]
