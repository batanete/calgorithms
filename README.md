# Algorithms

This repository contains a few algorithms and data structures implemented in C. The rationale for implementing these, is mostly for practice and fun. Event if you don't often use C in your field(I personally use mostly JVM languages), implementing data structures from scratch using C can be a good way to understand how their implementations work in the background.

That being said, you are completely free to use these for anything you like, but keep in mind I did not do any thorough performance or functional testing beyond the basic tests posted here.


## Queues
Queue implementation. All operations(insert, remove and peek) are handled in O(1) time complexity(uses a ring buffer-like implementation to achieve this, as using a linked list would impact locality of reference). Resizes are supported(capacity is doubled when the elements limit is exceeded)

## HashTables
Hash table implementation. Keys are defined as strings, and values as void pointers(which can point towards anything). The hashing function can be changed on the hashtables.c file(function hash_function), but after some testing I came to the conclusion that the djb2 function used is already pretty efficient at preventing collisions. Resizes are supported.

All basic operations(inserts, searches and deletes) are done in O(1) time complexity(assuming collisions are rare), although I'm sure the implementation could still be optimized further.

## Trie
String(char array) trie implementation. Useful mainly for doing partial searches on a set of strings(for example, searching for a prefix for a given string). Worst-time complexity for all supported search operations is O(m) where m is the length of the string.