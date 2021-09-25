#ifndef LOGIN_REGISTER_H
#define LOGIN_REGISTER_H

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
//------------------------------USER STRUC END-----------------------------//

unsigned int getNumberOfUsers(unsigned int *numberOfUsers);

void cleanDatabase(void);

void loginUser(void);

void registerUser(void);

void readAllUsers(void);

#endif