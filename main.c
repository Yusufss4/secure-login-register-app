//TODO: Currenty all user related things are in the main we will seperate them.
//NEXT: There will be second binary file where we will hold the user statitcs like numberOfUsers. 

#include <stdint.h> //Used for uint8_t etc.
#include <stdio.h> //General C
#include <stdlib.h>  //Memory Allocation
#include <string.h> //strcpy,strlen etc.

//------------------------------HASH START-----------------------------//
#include "sha-256.h"
//We dont need hash to string. 
static void hash_to_string(char string[65], const uint8_t hash[32])
{
	size_t i;
	for (i = 0; i < 32; i++) {
		string += sprintf(string, "%02x", hash[i]);
	}
}

static void copyHash(uint8_t destHash[32], const uint8_t sourceHash[32])
{	
	printf("Concat Strings...\n");
	size_t i;
	for (i = 0; i < 32; i++) {
		destHash[i] = sourceHash[i];
		printf("%x", destHash[i]);
	}
}

static void printHash(const uint8_t sourceHash[32]) {
	printf("Printing hash...\n");
	size_t i;
	for (i = 0; i < 32; i++) {
		printf("%x", sourceHash[i]);
	}

}
//------------------------------HASH FINISH-----------------------------//



//Note: change structure make hash second, add time if possible. 
typedef struct
{
	unsigned int index; 
	char fullName[100];
	char eMail[100];
	char username[100];
	uint8_t hashedPassword[32];
}User;

unsigned int numberOfUsers; //Currently global make it private.

void registerUser() {
	//Take inputs. 
	//Hash password. 
	//Create User struct from the info.
	//Save user to usersDb.bin file.
	//Increase the number of users in statsDb.bin file.
}


void registerUserTest() {
	printf("\nRegistering the user...\n");
	//char enteredUsername[100] = "yusufss";
	//char enteredPassword[100] = "kedi";
	//char enteredMail[100] = "yusufsss4@gmail.com";
	uint8_t hash[32];
	char hash_string_1[65];
	calc_sha_256(hash,"abc", strlen("abc"));
	


	User newUser = {1,"Yusuf Savaş","yusufsss4@gmail.com","yusufss"};
	User secondUser = {2,"Yusuf Yusuf","abc@gmail.com","yusufss"};
	copyHash(newUser.hashedPassword,hash);
	copyHash(secondUser.hashedPassword,hash);
	//hash_to_string(hash_string_1, newUser.hashedPassword);
	//printf("HASH Testing in Register User: %s\n", hash_string_1);


	char *fileName = "usersDb.bin";
    FILE *file = NULL;
    //MODE:rb+ -> Open binary file for read and write. If not exist cant create.
    file = fopen(fileName, "rb+");
    if (file == NULL)
    {
        printf("Cant open file: %s", fileName);
    }

    //Write to the file.
	//2 user is wroted.
    fwrite(&newUser, sizeof(newUser), 1, file);
	fwrite(&secondUser, sizeof(secondUser), 1, file);
    fclose(file);

    User readUser;
    file = fopen(fileName, "rb+");
    if (file == NULL)
    {
        printf("Cant open file: %s", fileName);
    }
    //Read from the file.
	char hash_string_2[65];
    fread(&readUser, sizeof(readUser), 1, file);
	hash_to_string(hash_string_2, readUser.hashedPassword);
    printf("Information From the File\n");
    printf("-------------------------\n");
    printf("Index      : %d\n", readUser.index);
    printf("fullName       : %s\n", readUser.fullName);
	printf("eMail       : %s\n", readUser.eMail);
	printf("userName       : %s\n", readUser.username);
	printf("Hash           : %s\n", hash_string_2);

	char hash_string_3[65];
	fread(&readUser, sizeof(readUser), 1, file);
	hash_to_string(hash_string_3, readUser.hashedPassword);
    printf("Information From the File Second\n");
    printf("-------------------------\n");
    printf("Index      : %d\n", readUser.index);
    printf("fullName       : %s\n", readUser.fullName);
	printf("eMail       : %s\n", readUser.eMail);
	printf("userName       : %s\n", readUser.username);
	printf("Hash           : %s\n", hash_string_3);

	printf("======= SIZES =======\n");
	printf("Char: %lu\n", sizeof(char));
    printf("Int: %lu\n", sizeof(int));
    printf("Float: %lu\n", sizeof(float));
    printf("Double: %lu\n", sizeof(double));
	/*SEEK_SET - Beginning of file
	  SEEK_CUR - Current position.
	  SEEK_END - End of file*/
	  int sizeOfNewUser = 0;
	sizeOfNewUser = sizeof(newUser.eMail) + sizeof(newUser.fullName) + sizeof(newUser.index) + sizeof(newUser.username);
	printf("Size of new User except hash: %d\n",sizeOfNewUser);

	sizeOfNewUser = sizeof(secondUser.eMail) + sizeof(secondUser.fullName) + sizeof(secondUser.index) + sizeof(secondUser.username);
	printf("Size of second User except hash: %d\n",sizeOfNewUser);

	/*Return to start, go from start of file to start of the first hash and save it to new hash.
	Will be used in read function not a part of register */
	fseek(file, sizeOfNewUser, SEEK_SET);
	uint8_t readedHash[32];
	fread(&readedHash, sizeof(readedHash), 1, file);
	printHash(readedHash);
	fread(&readUser, sizeof(readUser), 1, file);
	//hash_to_string(hash_string_3, readUser.hashedPassword);
    printf("Information From the File Second\n");
    printf("-------------------------\n");
    printf("Index      : %d\n", readUser.index);
    printf("fullName       : %s\n", readUser.fullName);
	printf("eMail       : %s\n", readUser.eMail);
	printf("userName       : %s\n", readUser.username);
	printHash(readUser.hashedPassword);

	fclose(file);
}


void printMenu();



int main(void) {
	printf("=============================================\n");
    /*char *e_mail = "abc";
    uint8_t hash[32];
	char hash_string_main[65];
	calc_sha_256(hash, e_mail, strlen(e_mail));
	hash_to_string(hash_string_main, hash);
    printf("HASH Test One: %s\n", hash_string_main);

	char hash_string_main2[65];
	calc_sha_256(hash, "abc", strlen("abc"));
	hash_to_string(hash_string_main2, hash);
    printf("HASH Test Two: %s\n", hash_string_main2); */

    printf("-----------------------------\n");
    printf("-----User Login-Register Database App------\n");
    printf("-----------------------------\n");
    int option;
    while (1)
    {
        printMenu();
        scanf("%d", &option);
        switch (option)
        {
        case 0:
            printf("Saving the movies...\n");
            //registerMovies();
            printf("Exiting from the program...\n");
            exit(0);
            break;
        case 1:
            registerUserTest();
            break;
        case 2:
            //deleteMovie();
			registerUser();
            break;
        case 3:
			readAllUsers();
            //listingMoviesSubMenu();
            break;
        default:
            printf("Wrong value. Please enter again.\n");
            break;
        }
    }





}


void printMenu()
{
    printf("\nMain Menu: \n");
    printf("1. Register User\n");
	printf("2. List All Users\n");
    //printf("2. Delete Movie\n");
    //printf("3. List Movies\n");
    printf("0. Save and Exit From the Program.\n\n");
    printf("Enter your option: ");
}