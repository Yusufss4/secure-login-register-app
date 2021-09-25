#ifndef HASH_OPS_H
#define HASH_OPS_H

void hash_to_string(char string[65], const uint8_t hash[32]);

void copyHash(uint8_t destHash[32], const uint8_t sourceHash[32]);

void printHash(const uint8_t sourceHash[32]);

unsigned int compareHashes(const uint8_t firstHash[32], const uint8_t secondHash[32]);

#endif