#include <stdio.h>	//General C
#include <stdint.h> //Used for uint8_t etc.
#include <string.h> //strcpy,strlen etc.

#include "validation.h" //Validation functions for e-mail,username and password.
#include "hash-ops.h"	//Contains functions like hash copy, hash compare etc.
#include "sha-256.h" //Contains calc_sha_256 function.
#include "login-register.h" //Main API for login and register functions. 

unsigned int getNumberOfUsers(unsigned int *numberOfUsers)
{
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
	printf("Number or users in file: %d\n", *numberOfUsers);

	fclose(file);
	return 1;
}

static unsigned int getHashOfUserByUserName(const char *scanBuffer, uint8_t loginUserHash[32])
{
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
	for (unsigned int i = 0; i < numberOfUsers; i++)
	{
		fread(&readUser, sizeof(readUser), 1, file);
		//hash_to_string(hash_string_3, readUser.hashedPassword);
		printf("\n------------USER SEARCH for Login------------\n");
		printf("Index      : %d\n", readUser.index);
		printf("Full Name  : %s\n", readUser.fullName);
		printf("eMail      : %s\n", readUser.eMail);
		printf("User Name  : %s\n", readUser.userName);
		printf("Hash: ");
		printHash(readUser.hashedPassword);
		if (strcmp(scanBuffer, readUser.userName) == 0)
		{
			printf("User is found. Returning hash.\n");
			copyHash(loginUserHash, readUser.hashedPassword);
			fclose(file);
			return 1;
		}
	}
	printf("User not found...\n");
	fclose(file);
	return 0;
}

/* In the performance mode you dont need to read all the details of users, 
by using the fseek we directly access username and password. Thus increasing overall performance*/
static unsigned int getHashOfUserByUserNamePerformanceMode(const char *scanBuffer, uint8_t findedUserHash[32])
{
	char *fileName = "usersDb.bin";
	FILE *file = NULL;
	file = fopen(fileName, "rb+");
	if (file == NULL)
	{
		printf("Cant open file: %s", fileName);
	}

	unsigned int numberOfUsers = 0;
	getNumberOfUsers(&numberOfUsers);

	User testUser;
	const int totalSizeOfUser = sizeof(testUser);
	const int totalBytesUntilUserName = sizeof(testUser.index);
	char userName[15];
	const int hashSize = sizeof(testUser.hashedPassword);
	const int bytesLeftAfterHash = totalSizeOfUser - (totalBytesUntilUserName + sizeof(userName) + hashSize);

	fseek(file, 0, SEEK_SET); //start from the beginning of file.
	for (unsigned int i = 0; i < numberOfUsers; i++)
	{

		//Read username, fseek is after the username.
		fseek(file, totalBytesUntilUserName, SEEK_CUR);
		fread(&userName, sizeof(userName), 1, file);
		printf("Current userName: ");
		printf("%s\n", userName);

		//Compare the username with the given username if equal read hash and return.
		if (strcmp(scanBuffer, userName) == 0)
		{
			printf("User is found. Returning hash.\n");
			fread(findedUserHash, sizeof(testUser.hashedPassword), 1, file);
			printHash(findedUserHash);
			fclose(file);
			return 1;
		}
		else
		{
			fseek(file, hashSize, SEEK_CUR);
			fseek(file, bytesLeftAfterHash, SEEK_CUR);
		}
	}
	printf("User not found...\n");
	fclose(file);
	return 0;
}

static unsigned int saveNumberOfUsersToFile(const unsigned int numberOfUsers)
{
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
	printf("Saved number of users to file: %d", numberOfUsers);
	fclose(file);
	return 1;
}

void cleanDatabase(void)
{
	fclose(fopen("usersDb.bin", "w"));
	fclose(fopen("usersDbStats.bin", "w"));
}

void loginUser(void)
{

	unsigned int numberOfUsers = 0;
	char scanBuffer[245];
	int isValid = 0;
	int isUserName = 0;

	do
	{
		printf("Enter userName or e-mail: ");
		scanf("%s", scanBuffer);
		//if the string consist @ search by e-mail otherwise search by username.
		if (strchr(scanBuffer, '@') != NULL)
		{
			isValid = eMailValidifier(scanBuffer);
			if (isValid == 0)
			{
				printf("e-mail is not valid. Code = 0\n");
			}
			isUserName = 0;
		}
		else
		{
			isValid = userNameValidifier(scanBuffer);
			if (isValid == 0)
			{
				printf("userName is not valid. Code = 0\n");
			}
			isUserName = 1;
		}
	} while (!isValid);

	char password[65];
	printf("Enter your password: ");
	scanf("%s", password);

	//Hash password.
	uint8_t loginUserHash[32];
	calc_sha_256(loginUserHash, password, strlen(password));
	printHash(loginUserHash);

	uint8_t findedUserHash[32];

	if (isUserName == 1)
	{
		//searchUserByUserName(scanBuffer);
		if (getHashOfUserByUserNamePerformanceMode(scanBuffer, findedUserHash))
		{
			printf("Username is found.\n");
			if (compareHashes(findedUserHash, loginUserHash))
			{
				printf("Acess is granted. Go to another place..\n");
			}
			else
			{
				printf("Wrong password.\n");
			}
		}
		else
		{
			printf("Cant find the user.\n");
		}
	}
	else
	{
		//searchUserByEmail(scanBuffer);
	}
}

void registerUser(void)
{
	unsigned int numberOfUsers = 0;
	char registerUserName[15];
	int isValid = 0;

	do
	{
		printf("Enter userName: ");
		scanf("%s", registerUserName);
		isValid = userNameValidifier(registerUserName);
		if (isValid == 0)
		{
			printf("User name is not valid. Code = 0\n");
		}
	} while (!isValid);

	isValid = 0;
	char registerFullName[100];
	do
	{
		printf("Enter your full name: ");
		scanf(" %[^\n]%*c", registerFullName);
		isValid = inputValidifier(registerFullName);
		if (isValid == 0)
		{
			printf("User name is not valid. Code = 0\n");
		}
	} while (!isValid);

	isValid = 0;
	char eMail[254];
	do
	{
		printf("Enter your e-mail: ");
		scanf(" %s", eMail);
		isValid = eMailValidifier(eMail);
		if (isValid == 0)
		{
			printf("E-mail is not valid. Code = 0\n");
		}
	} while (!isValid);

	isValid = 0;
	char password[65];
	do
	{
		printf("Enter your password: ");
		scanf(" %s", password);
		isValid = passwordValidifier(password);
		if (isValid == 0)
		{
			printf("Password is not valid. Code = 0\n");
		}
	} while (!isValid);

	//Hash password.
	uint8_t hash[32];
	calc_sha_256(hash, password, strlen(password));
	printHash(hash);

	getNumberOfUsers(&numberOfUsers);

	//Create new user.
	User newUser;
	numberOfUsers++;
	newUser.index = numberOfUsers;
	strcpy(newUser.userName, registerUserName);
	strcpy(newUser.eMail, eMail);
	strcpy(newUser.fullName, registerFullName);
	copyHash(newUser.hashedPassword, hash);

	//Open file.
	char *fileName = "usersDb.bin";
	FILE *file = NULL;
	file = fopen(fileName, "rb+");
	if (file == NULL)
	{
		printf("Cant open file: %s", fileName);
	}

	//Write user information to the file.
	fseek(file, ((numberOfUsers - 1) * sizeof(newUser)), SEEK_SET);
	fwrite(&newUser, sizeof(newUser), 1, file);
	fclose(file);

	//Write number of user information to file.
	saveNumberOfUsersToFile(numberOfUsers);
}

void readAllUsers(void)
{
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
	for (unsigned int i = 0; i < numberOfUsers; i++)
	{
		fread(&readUser, sizeof(readUser), 1, file);
		printf("\n-------------------------\n");
		printf("Index      : %d\n", readUser.index);
		printf("Full Name  : %s\n", readUser.fullName);
		printf("eMail      : %s\n", readUser.eMail);
		printf("User Name  : %s\n", readUser.userName);
		printf("Hash: ");
		printHash(readUser.hashedPassword);
	}
	fclose(file);
}