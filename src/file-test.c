#include <stdio.h>	//General C
#include <stdint.h> //Used for uint8_t etc.
#include <string.h> //strcpy,strlen etc.

int main() {
    int numberOfUsers = 0;
    char fileName[] = "../db/usersDbStats.bin";
	FILE *file = NULL;
	file = fopen(fileName, "rb+");
	if (file == NULL)
	{
		printf("Cant open file: %s", fileName);
		return 0;
	}
    printf("Opened file: %s", fileName);
	fseek(file, 0, SEEK_SET);
	fwrite(&numberOfUsers, sizeof(numberOfUsers), 1, file);
	printf("Saved number of users to file: %d", numberOfUsers);
	fclose(file);
	return 1;
}