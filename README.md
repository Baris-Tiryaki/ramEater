# ramEater
Memory and pagefile testing program

It was compiled for 64-bit windows with gcc version 11.2.0 (MSYS2)

It asks how much ram do you want to allocate.
Then allocates it.
Then fills it with random data.
Then reads it forever.

If requested memory is greater than available RAM, pagefile will be used.
It can be slow, and freeze/crash your system, so use carefully.
Save all your files beforehand.

