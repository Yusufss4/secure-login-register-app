#ifndef LOGIN_REGISTER_H
#define LOGIN_REGISTER_H

#include <stdint.h> //Used for uint8_t etc.

#define userDbFileLocation "../db/usersDb.bin"
#define userDbStatsFileLocation "../db/usersDbStats.bin"

//------------------------------USER STRUCT-----------------------------//
//Note: Add register time if possible.
typedef struct
{
    unsigned int index;
    char userName[15];
    uint8_t hashedPassword[32];
    char fullName[100];
    char eMail[254]; //max e-mail
} User;
//------------------------------USER STRUCT END-----------------------------//

//extern char const userDbFileLocation[] = "../db/usersDb.bin";
//extern char const userDbStatsFileLocation[] = "../db/usersDbStats.bin";

unsigned int getNumberOfUsers(unsigned int *numberOfUsers);

void cleanDatabase(void);

void loginUser(void);

void registerUser(void);

void readAllUsers(void);

#endif