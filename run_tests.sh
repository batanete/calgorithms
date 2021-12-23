# yes, I'm too lazy to make a makefile for this
cc queues/queues.c hashtables/hashtables.c tries/tries.c test/tests.c test/hashtable_tests.c test/queue_tests.c test/trie_tests.c -Wall -g -o tests
./tests
rm ./tests