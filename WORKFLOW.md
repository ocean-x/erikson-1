A way to organize your projects would be:

* projectA - Parent Directory
  * projectA - Source code directory containing Arduino code
    * projectA.ino
    * header.h
    * implementation.cpp
  * docs - Your main documentation directory
  * schematics - these may be maintained separately on a separate Git repo or part of the same repo
  * libs - This will contain your third party libraries.
    * libA - These may be maintained as third party repositories
    * libC - ...
  * license
  * README
  * Makefile - Necessary to handle dependencies across directories
