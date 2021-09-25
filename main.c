//TODO: Currenty all user related things are in the main we will seperate them.
//NEXT: There will be second binary file where we will hold the user statitcs like numberOfUsers.

#include <stdio.h>	//General C
#include <stdlib.h> //Memory Allocation

#include "login-register.h" //Main API for login and register functions.

void printMenu();

int main(void)
{
	printf("=============================================\n");
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
			printf("Exiting from the program...\n");
			exit(0);
			break;
		case 1:
			break;
		case 2:
			registerUser();
			break;
		case 3:
			loginUser();
			break;
		case 4:
			readAllUsers();
			break;
		case 5:
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
	printf("1. Test - Not implemented.\n");
	printf("2. Register User\n");
	printf("3. Login User\n");
	printf("4. List All Users\n");
	printf("5. Clean Database\n");
	printf("0. Save and Exit From the Program.\n\n");
	printf("Enter your option: ");
}