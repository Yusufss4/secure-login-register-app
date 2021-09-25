#include <stdio.h>  //General C
#include <stdint.h> //Used for uint8_t etc.

#include "hash-ops.h"
#include "sha-256.h"

void hash_to_string(char string[65], const uint8_t hash[32])
{
    size_t i;
    for (i = 0; i < 32; i++)
    {
        string += sprintf(string, "%02X", hash[i]);
    }
}

void copyHash(uint8_t destHash[32], const uint8_t sourceHash[32])
{
    size_t i;
    for (i = 0; i < 32; i++)
    {
        destHash[i] = sourceHash[i];
        printf("%02X", destHash[i]);
    }
    printf("\n");
}

void printHash(const uint8_t sourceHash[32])
{
    size_t i;
    for (i = 0; i < 32; i++)
    {
        printf("%02X", sourceHash[i]);
    }
    printf("\n");
}

unsigned int compareHashes(const uint8_t firstHash[32], const uint8_t secondHash[32])
{
    printf("Comparing hashes...\n");
    printf("Hash returned from user search: ");
    printHash(firstHash);
    printf("Hash from the user: ");
    printHash(secondHash);
    size_t i;
    for (i = 0; i < 32; i++)
    {
        if (firstHash[i] != secondHash[i])
        {
            return 0; //not equal.
        }
    }
    return 1; //equal.
}
