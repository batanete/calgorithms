# Algorithms

This repository contains a few algorithms and data structures implemented in C in my free time as a hobbyist programmer. You are completely free to use these for anything you like, but keep in mind I did not do any thorough performance or functional testing beyond the basic tests posted here.

## HashTables
Hash table implementation. Keys are defined as strings, and values as void pointers(which means they can be anything). The hashing function can be changed on the hashtables.c file(function hash_function), but after some testing I came to the conclusion that the djb2 function used is already pretty efficient at preventing collisions.

This was implemented a long time ago, when I was still a student, so the code does not look that pretty :) Also, it does not support resizes when the size is exceeded(I might add this later on if I'm bored).
