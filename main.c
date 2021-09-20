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
		string += sprintf(string, "%02X", hash[i]);
	}
}

static void copyHash(uint8_t destHash[32], const uint8_t sourceHash[32])
{	
	size_t i;
	for (i = 0; i < 32; i++) {
		destHash[i] = sourceHash[i];
		printf("%02X", destHash[i]);
	}
	printf("\n");
}

static void printHash(const uint8_t sourceHash[32]) {
	size_t i;
	for (i = 0; i < 32; i++) {
		printf("%02X", sourceHash[i]);
	}
	printf("\n");
}

static unsigned int compareHashes(uint8_t firstHash[32], const uint8_t secondHash[32]) {
		printf("Comparing hashes..\n");
		size_t i;
	for (i = 0; i < 32; i++) {
		if(firstHash[i] != secondHash[i]) {
			return 0; //not equal.
		}
	}
	return 1; //equal.
}
//------------------------------HASH FINISH-----------------------------//

int userNameValidifier(const char* userName) {
	return 1;
}

int inputValidifier(const char*input) {
	return 1;
}

int eMailValidifier(const char *email) {
	return 1;
}

int passwordValidifier(const char*password) {
	return 1;
}

unsigned int getNumberOfUsers(unsigned int *numberOfUsers) {
	//unsigned int numberOfUsers = 0;
	char *fileName = "usersDbStats.bin";
    FILE *file = NULL;
    file = fopen(fileName, "rb+");
    if (file == NULL)
    {
        printf("Cant open file: %s", fileName);
		return 0;
    }
	fseek(file, 0, SEEK_SET);
	fread(numberOfUsers, sizeof(*numberOfUsers), 1, file);
	printf("Number or users in file: %d\n",*numberOfUsers);
	
	fclose(file);
	return 1;

}

getHashOfUserByUserName(const char *scanBuffer,const uint8_t loginUserHash[32]) {
	
}

unsigned int saveNumberOfUsersToFile(const unsigned int numberOfUsers) {
	char *fileName = "usersDbStats.bin";
    FILE *file = NULL;
    file = fopen(fileName, "rb+");
    if (file == NULL)
    {
        printf("Cant open file: %s", fileName);
		return 0;
    }
	fseek(file, 0, SEEK_SET);
	fwrite(&numberOfUsers, sizeof(numberOfUsers), 1, file);
	printf("Saved number of users to file: %d",numberOfUsers);
	fclose(file);
	return 1;
}

void cleanDatabase(void) {
	fclose(fopen("usersDb.bin", "w"));
	fclose(fopen("usersDbStats.bin", "w"));
}


//Note: Add register time if possible. 
typedef struct
{
	unsigned int index;
	char userName[15]; 
	uint8_t hashedPassword[32];
	char fullName[100];
	char eMail[254]; //max e-mail
}User;

void loginUser() {

	unsigned int numberOfUsers = 0;
	char scanBuffer[245];
	int isValid = 0;
	int isUserName = 0;

	do {
	printf("Enter userName or e-mail: ");
	scanf("%s",scanBuffer);
	//if the string consist @ search by e-mail otherwise search by username.
	if(strchr(scanBuffer, '@') != NULL) {
	 isValid = eMailValidifier(scanBuffer);
	 if(isValid == 0) {
		printf("e-mail is not valid. Code = 0\n");
	}
	isUserName = 0;
	}
	else 
	{
	isValid = userNameValidifier(scanBuffer);
	 if(isValid == 0) {
		printf("userName is not valid. Code = 0\n");
	}
	isUserName = 1;
	}
	} while(!isValid); 
	
	char password[65];
	printf("Enter your password: ");
	scanf("%s",password);
	printf("Password is not valid. Code = 0\n");

	//Hash password. 
	uint8_t loginUserHash[32];
	calc_sha_256(loginUserHash,password, strlen(password));
	printHash(loginUserHash);
	
	uint8_t findedUserHash[32];

	if(isUserName == 1) {
		//searchUserByUserName(scanBuffer);
	 	if(getHashOfUserByUserName(scanBuffer,loginUserHash)) {
			 printf("Username is found.\n");
			 if(compareHashes(findedUserHash,loginUserHash)) {
				 printf("Acess is granted. Go to another place..\n");
			 }
			 else {
				 printf("Wrong password.\n");
			 }
		 }
		else{
			printf("Cant find the user.\n");
		}
		 
	}
	else 
	{
		//searchUserByEmail(scanBuffer);
	}

	

}


void registerUser() {
	unsigned int numberOfUsers = 0;
	char registerUserName[15];
	int isValid = 0;

	do {
	printf("Enter userName: ");
	scanf("%s",registerUserName);
	isValid = userNameValidifier(registerUserName);
	if(isValid == 0) {
		printf("User name is not valid. Code = 0\n");
	}
	} while(!isValid); 

	isValid = 0;
	char registerFullName[100];
	do {
	printf("Enter your full name: ");
	scanf("%s",registerFullName);
	isValid = inputValidifier(registerFullName);
	if(isValid == 0) {
		printf("User name is not valid. Code = 0\n");
	}
	} while(!isValid);

	isValid = 0;
	char eMail[254];
	do {
	printf("Enter your e-mail: ");
	scanf("%s",eMail);
	isValid = eMailValidifier(eMail);
	if(isValid == 0) {
		printf("E-mail is not valid. Code = 0\n");
	}
	} while(!isValid);


	isValid = 0;
	char password[65];
	do {
	printf("Enter your password: ");
	scanf("%s",password);
	isValid = passwordValidifier(password);
	if(isValid == 0) {
		printf("Password is not valid. Code = 0\n");
	}
	} while(!isValid);

	//Hash password. 
	uint8_t hash[32];
	calc_sha_256(hash,password, strlen(password));
	printHash(hash);

	getNumberOfUsers(&numberOfUsers);
	
	//Create new user.
	User newUser;
	numberOfUsers++;
	newUser.index = numberOfUsers;
	strcpy(newUser.userName,registerUserName);
	strcpy(newUser.eMail,eMail);
	strcpy(newUser.fullName,registerFullName);
	copyHash(newUser.hashedPassword,hash);
	

	//Open file.
	char *fileName = "usersDb.bin";
    FILE *file = NULL;
    file = fopen(fileName, "rb+");
    if (file == NULL)
    {
        printf("Cant open file: %s", fileName);
    }

	//Write user information to the file.
	fseek(file, ((numberOfUsers-1)*sizeof(newUser)), SEEK_SET);
    fwrite(&newUser, sizeof(newUser), 1, file);
	fclose(file);

	//Write number of user information to file.
	saveNumberOfUsersToFile(numberOfUsers);
	


	//Take inputs. 
	//Hash password. 
	//Create User struct from the info.
	//Save user to usersDb.bin file.
	//Increase the number of users in statsDb.bin file.
}

void readAllUsers() {
	char *fileName = "usersDb.bin";
    FILE *file = NULL;
	file = fopen(fileName, "rb+");
    if (file == NULL)
    {
        printf("Cant open file: %s", fileName);
    }

	unsigned int numberOfUsers = 0;
	getNumberOfUsers(&numberOfUsers);

	User readUser;
	for(unsigned int i = 0; i<numberOfUsers; i++) {
	fread(&readUser, sizeof(readUser), 1, file);
	//hash_to_string(hash_string_3, readUser.hashedPassword);
    printf("\n-------------------------\n");
    printf("Index      : %d\n", readUser.index);
    printf("Full Name  : %s\n", readUser.fullName);
	printf("eMail      : %s\n", readUser.eMail);
	printf("User Name  : %s\n", readUser.userName);
	printf("Hash: ");
	printHash(readUser.hashedPassword); }
	fclose(file);
}


void registerUserTest() {
	printf("\nRegistering the user...\n");
	//char enteredUserName[100] = "yusufss";
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
	printf("userName       : %s\n", readUser.userName);
	printf("Hash           : %s\n", hash_string_2);

	char hash_string_3[65];
	fread(&readUser, sizeof(readUser), 1, file);
	hash_to_string(hash_string_3, readUser.hashedPassword);
    printf("Information From the File Second\n");
    printf("-------------------------\n");
    printf("Index      : %d\n", readUser.index);
    printf("fullName       : %s\n", readUser.fullName);
	printf("eMail       : %s\n", readUser.eMail);
	printf("userName       : %s\n", readUser.userName);
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
	sizeOfNewUser = sizeof(newUser.eMail) + sizeof(newUser.fullName) + sizeof(newUser.index) + sizeof(newUser.userName);
	printf("Size of new User except hash: %d\n",sizeOfNewUser);

	sizeOfNewUser = sizeof(secondUser.eMail) + sizeof(secondUser.fullName) + sizeof(secondUser.index) + sizeof(secondUser.userName);
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
	printf("userName       : %s\n", readUser.userName);
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
		case 4:
			cleanDatabase();
            break;
        default:
            printf("Wrong value. Please enter again.\n");
            break;
        }
    }





}


void printMenu()
{
    printf("\n\nMain Menu: \n");
    printf("1. Register User Test\n");
	printf("2. Register User\n");
	printf("3. List All Users\n");
	printf("4. Clean Database\n");
    printf("0. Save and Exit From the Program.\n\n");
    printf("Enter your option: ");
}