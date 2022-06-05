#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define IDSize 10
#define ageLimit 4
#define descriptionSize 212
#define lowestAge 18
#define highestAge 100


enum hobbies {
	BASEBALL = 1, BASKETBALL, BICYCLE, BOOKS,
	DRAWING, GYM, MOVIES, POETRY
};

enum { false, true };

typedef struct profile {
	char ID[IDSize];
	char* firstName;
	char* lastName;
	char age[ageLimit];
	char gender;
	char* userName;
	char* password;
	char* description;
	unsigned short int hobbies;
	struct profile* next;
} profile;

//declarations
void copyProfileData(profile* userA, profile* userB);
void getHobbie(profile* user, int hobbie);
void Register(profile*** maleList, profile** femaleList, int* size);
int searchForID(char ID[], profile** maleList, profile* femaleList, int size);
void dataReciever(int* flagFile, FILE** fp, profile*** maleList, profile** femaleList, int* size);
int femaleIDSearch(char ID[], profile* femaleList);
int ConvStringToInt(char str[]);
void logIn(int flag, int* size, profile*** maleList, profile** femaleList);
profile* searchUserByName(char userName[], profile** maleList, profile* femaleList, int size);
profile* femaleSearch(char userName[], profile* femaleList);
profile** insertToDynamicArr(profile** head, int* size, profile* user);
void updateUser(profile** head, profile* user);
void copyUser(profile** head, profile* user);
void printArr(profile* user);
void detailCopy(char buffer[], FILE* fp, int* flagFile);
void missionChoise(profile*** maleList, profile** femaleList, int* size);
void femaleListOrg(profile** femaleList);
void mainMenu(profile* user, profile*** malelist, profile** femaleList, int* size);
profile* insertNodeToTree(profile* femaleList, profile* node);
profile* createNewNode(profile* femaleList, profile* user);
void printHobbies(int eNumber);
void resetUser(profile* user);
void freeProfile(profile** user);
profile* delFromList(profile* user, profile* femaleList);
void arrPlaceChanger(profile** maleArr, int index, int size);
profile** deleteFromArr(profile* user, profile** maleArr, int* size);
void deleteMe(profile* user, profile*** malelist, profile** femaleList, int* size);
void findAMan(profile* user, profile** maleList, int minAge, int maxAge, int size);
int hobbiesCheck(profile* user, profile* potentialMate);
void findAWoman(profile* user, profile* femaleList, int minAge, int maxAge);
void findAMatch(profile* user, profile** maleList, profile* femaleList, int size);
void deleteArr(profile** maleList, int* size);
void deleteList(profile* femaleList);
void exitProgram(profile*** maleList, profile** femaleList, int* size);
void writeFile(profile** maleList, profile* femaleList, int size);
void writeUser(profile* user, FILE* output);
void writeFemales(profile* femaleList, FILE* output);

/************************************************************************
* function name: main 							    					*
* The Input:														    *
* The output:													    	*
* The Function operation: The function opens opens file and sends to a  *
						  file reading function and than goes to open	*
						  menu											*
*************************************************************************/
int main()
{
	int size = 0;
	int flag = true;
	FILE* fp = fopen("input.txt", "r");	//opens file
	if (fp == NULL) {
		flag = false;
		// create file if not created
		fp = fopen("input.txt", "w+");
		if (fp == NULL) {
			exit(5);
		}
	}
	//creating and reseting male and female lists
	profile** maleList = NULL;
	profile* femaleList = NULL;
	while (flag == true) //recieving users from file
	{
		dataReciever(&flag, &fp, &maleList, &femaleList, &size);
	}
	fclose(fp);	//close file
	missionChoise(&maleList, &femaleList, &size); //1st menu
	return 0;
}

/************************************************************************
* function name: missionChoise 							    			*
* The Input: address of pointer arr male list, address of link list		*
			 femalelist and address of male array size					*
* The output:													       	*
* The Function operation: The function scans a number from user and		*
						  according to the num goes to a function:		*
						  1 - log in									*
						  2 - register									*
						  3 - exits program								*
*************************************************************************/
void missionChoise(profile*** maleList, profile** femaleList, int* size)
{
	int flag = true, mChoise;
	//reads 1st menu choise
	while (flag == true)
	{
		printf("Welcome! please choose an option\n");
		printf("1 - Log in\n2 - New member\n3 - Exit\n");
		scanf("%d", &mChoise);
		switch (mChoise)
		{
		case (1):	//log in
			logIn(true, size, maleList, femaleList);
			break;
		case (2):	//register
			Register(maleList, femaleList, size);
			break;
		case (3): //exit
			exitProgram(maleList, femaleList, size);
			return;
			flag = false;
			break;
		default:
			printf("Bad choice, please try again\n");
			scanf("%d", &mChoise);
			break;
		}
	}
	return;
}

/************************************************************************
* function name: getHobbie 							    				*
* The Input: a pointer profile user and hobbie number-1					*
* The output:													       	*
* The Function operation: the function shifts 1 according to the hobbie *
						  and asuume it into user's hobbie with 'or'	*
						  operator										*
*************************************************************************/
void getHobbie(profile* user, int index)
{
	unsigned int tmpHobbie = 1;
	tmpHobbie = tmpHobbie << index; //move 1 with hobbie-1 times left
	user->hobbies = (user)->hobbies ^ tmpHobbie; //xoring to add new hobbie in bit
	return;
}

/************************************************************************
* function name: printHobbies 							    			*
* The Input: int number													*
* The output:													       	*
* The Function operation: the function prints hobbie according to		*
						  number and enum hobbie						*
*************************************************************************/

void printHobbies(int eNumber)
{

	switch (eNumber)
	{
	case(BASEBALL):
	{
		printf("Baseball");
		break;
	}
	case(BASKETBALL):
	{
		printf("Basketball");
		break;
	}
	case(BICYCLE):
	{
		printf("Bicycle");
		break;
	}
	case(BOOKS):
	{
		printf("Books");
		break;
	}
	case(DRAWING):
	{
		printf("Drawing");
		break;
	}
	case(GYM):
	{
		printf("Gym");
		break;
	}
	case(MOVIES):
	{
		printf("Movies");
		break;
	}
	case(POETRY):
	{
		printf("Poetry");
		break;
	}
	default: {
		break;
	}
	}
}

//data base

/************************************************************************
* function name: dataReciever 							    			*
* The Input: int flag num, file pointer address, address of pointer		*
			 arr male list, address of link list femalelist				*
			  and address of male array size							*
* The output:													       	*
* The Function operation: the function reads a user from input.txt file	*
						  assigns memory accordingly and copies into	*
						  gender matched array/list						*
*************************************************************************/

void dataReciever(int* flagFile, FILE** fp, profile*** maleList, profile** femaleList, int* size)
{
	int index, hobbNum;
	char buffer[descriptionSize] = { 0 };
	profile* user = NULL;
	user = (profile*)malloc(sizeof(profile)); //creating tmp user
	if (user == NULL)
	{
		free(user);
		exit(1);
	}
	user->hobbies = 0; //reseting user hobbies
	detailCopy(buffer, *fp, flagFile); //ID copy from file into buffer array
	strcpy(user->ID, buffer); //copy into user the ID
	detailCopy(buffer, *fp, flagFile);	//FIRST NAME copy from file into buffer array
	user->firstName = (char*)malloc(sizeof(char) * (strlen(buffer) + 1));
	if (user->firstName == NULL)
	{
		freeProfile(&user);
		free(user);
		exit(1);
	}
	strcpy(user->firstName, buffer);//copy into user the first name
	detailCopy(buffer, *fp, flagFile); //LAST NAME copy from file into buffer array
	user->lastName = (char*)malloc(sizeof(char) * (strlen(buffer) + 1));
	if (user->lastName == NULL)
	{
		free(user);
		exit(1);
	}
	strcpy(user->lastName, buffer);//copy into user the LAST name
	detailCopy(buffer, *fp, flagFile); //age
	strcpy(user->age, buffer);
	user->gender = fgetc(*fp); //gender
	fgetc(*fp); //skip ';'
	detailCopy(buffer, *fp, flagFile);//getting user name
	user->userName = (char*)malloc(sizeof(char) * (strlen(buffer) + 1));
	if (user->userName == NULL)
	{
		free(user);
		exit(1);
	}
	strcpy(user->userName, buffer);
	detailCopy(buffer, *fp, flagFile); //password
	user->password = (char*)malloc(sizeof(char) * (strlen(buffer) + 1));
	if (user->password == NULL)
	{
		free(user);
		exit(1);
	}
	strcpy(user->password, buffer);
	(*user).hobbies = 0;
	for (index = 0; index < 8 && (*flagFile); index++) //hobbies
	{
		buffer[0] = fgetc(*fp); //getting 1st hobbie as char
		buffer[1] = '\0';
		hobbNum = atoi(buffer); //casting as int
		getHobbie(user, hobbNum - 1); //go to function to put hobbie in user
		if (fgetc(*fp) == ';') //skips ',' or exiting and skipping ';'
		{
			break;
		}
	}
	detailCopy(buffer, *fp, flagFile); //description
	user->description = (char*)malloc(sizeof(char) * (strlen(buffer) + 1));
	if (user->description == NULL)
	{
		freeProfile(&user);
		free(user);
		exit(1);
	}
	strcpy(user->description, buffer);
	if (user->gender == 'M')
	{
		*maleList = insertToDynamicArr(*maleList, size, user);
	}
	if (user->gender == 'F')
	{
		*femaleList = createNewNode(*femaleList, user);
	}
	freeProfile(&user);
	free(user);
	return;
}

/************************************************************************
* function name: detailCopy 							    			*
* The Input: file pointer, flag int num, buffer char array				*
* The output:													       	*
* The Function operation: the function scans from file with file pointer*
						  and scans chars from it into buffer with c tmp*
						  char.											*
						  if it reached end file it'll flag it as'false'*
						  if it reaches enter (\n) it'll delete it from *
						  string and return.							*
						  if it reaches ';' it'l delete it from string  *
						  and return	 							 	*
*************************************************************************/

void detailCopy(char buffer[], FILE* fp, int* flagFile)
{
	int index;
	char c;
	//loop that goes untill reaches demilier ';'
	for (index = 0; buffer[index - 1] != ';'; index++)
	{
		c = fgetc(fp);
		if (c == EOF)
		{
			*flagFile = 0; //changes flag that marks to main function that we reached end file
			return;
		}
		buffer[index] = c; //put char in buffer array
		if (buffer[index] == '\n')
		{
			buffer[index] = '\0'; //deleting \n
			return;
		}
	}
	buffer[index - 1] = '\0'; //if reached ';' - deleting it
	return;
}

/************************************************************************
* function name: femaleListOrg 							    			*
* The Input: address of femaleList link list							*
* The output:													       	*
* The Function operation: the function orranges female users by their   *
						  last name										*
*************************************************************************/
void femaleListOrg(profile** femaleList)
{
	int nameCheck;
	if (((*femaleList)->next) == NULL) //stopping condition - reached final user
	{
		return;
	}
	profile* tmpPtr;
	profile* nextTmp;
	nameCheck = strcmp((*femaleList)->lastName, (*femaleList)->next->lastName);
	if (nameCheck > 0) //if the 1st last name is bigger, replace
	{
		nextTmp = (*femaleList)->next->next; //tmp pointer for next next 
		tmpPtr = (*femaleList); //tmp pointer for current user
		(*femaleList) = (*femaleList)->next;
		(*femaleList)->next = tmpPtr;
		(*femaleList)->next->next = nextTmp;
	}
	femaleListOrg(&((*femaleList)->next)); //recurtion for next user check
	return;
}

/************************************************************************
* function name: insertToDynamicArr 							   		*
* The Input: profile pointer array of male users, address of int male	*
			 array size and profile pointer of user to enter			*
* The output:address of first array member						       	*
* The Function operation: the function creates array if there are no	*
						  members, and if there are - it'll realloc the *
						  array according to the new size and updated	*
						  new place with the user						*
*************************************************************************/

profile** insertToDynamicArr(profile** head, int* size, profile* user)
{
	if (*size == 0) //if the are no users, create array
	{
		head = (profile**)malloc(sizeof(profile*));
	}
	else //if there are users, add a place for 1 more
	{
		head = (profile**)realloc(head, (*size + 1) * sizeof(profile*));
	}
	if (head == NULL)
	{
		exit(1);
	}
	updateUser(&head[*size], user); //putting into the place in array the user
	*size += 1; //changes the num marked for array
	return head;
}
/************************************************************************
* function name: updateUser 									   		*
* The Input: address of current profile pointer user, user data			*
* The output:													       	*
* The Function operation: the function allocates memory for the new		*
						  user, and copies data into it					*
*************************************************************************/
void updateUser(profile** head, profile* user)
{
	*head = (profile*)malloc(sizeof(profile)); //allocating memory for specific user
	copyUser(head, user); //copies data

}
/************************************************************************
* function name: copyUser 										   		*
* The Input: address of dest. user, data of source user					*
* The output:													       	*
* The Function operation: the function allocates memory for the dest.	*
						  user data and copies source user data into it	*
*************************************************************************/
void copyUser(profile** head, profile* user)
{
	strcpy((*head)->ID, user->ID); //copies ID
	(*head)->firstName = (char*)malloc(sizeof(char) * (strlen(user->firstName) + 1));//1st name allocation
	if ((*head)->firstName == NULL)
	{
		exit(1);
	}
	strcpy((*head)->firstName, user->firstName);// copies 1st name
	(*head)->lastName = (char*)malloc(sizeof(char) * (strlen(user->lastName) + 1));//last name allocation
	if ((*head)->lastName == NULL)
	{
		exit(1);
	}
	strcpy((*head)->lastName, user->lastName); //copies last name
	strcpy((*head)->age, user->age);//copies age
	(*head)->gender = user->gender;//copies gender
	(*head)->userName = (char*)malloc(sizeof(char) * (strlen(user->userName) + 1));//memory for username
	if ((*head)->userName == NULL)
	{
		exit(1);
	}
	strcpy((*head)->userName, user->userName);//copies username
	(*head)->password = (char*)malloc((strlen(user->password) + 1) * sizeof(char));//memory for password
	if ((*head)->password == NULL)
	{
		exit(1);
	}
	strcpy((*head)->password, user->password); //copies password
	(*head)->description = (char*)malloc(sizeof(char) * (strlen(user->description) + 1)); //desc. memory
	if ((*head)->description == NULL)
	{
		exit(1);
	}
	strcpy((*head)->description, user->description); //copies desc.
	(**head).hobbies = (*user).hobbies; //copies hobbies
	(*head)->next = NULL; //reseting next pointer
	return;
}

/************************************************************************
* function name: printArr 										   		*
* The Input: profile pointer user										*
* The output:													       	*
* The Function operation: the function prints user's full name, age,    *
						  hobbies and description						*
*************************************************************************/
void printArr(profile* user)
{
	int index, counter = 0, letCount = 1, bitCheck;
	printf("Name: %s %s ", user->firstName, user->lastName);
	printf("Age: %s ", user->age);
	printf("Hobbies: ");
	for (index = 1; index <= 8; index++)
	{
		bitCheck = (letCount) & (user->hobbies); //new tmp int that get common value
		if (bitCheck == letCount) //if common value is same as checking value
		{
			printHobbies(index); //print hobbie (index is the same num as hobbie num)
			counter++;
			if (counter < 4)
			{
				printf(", ");
			}
			else //reached 4 hobbies - with is exect num of hobbies
			{
				break;
			}
			letCount = letCount << 1; //shifts checking int left
		}
		else //if hobbie is not compatibale
		{
			letCount = letCount << 1; //shifts checking int left
		}
	}
	//printf("\n");
	printf(" Description: %s\n", user->description);
	printf("\n");
	return;
}

/************************************************************************
* function name: createNewNode 									   		*
* The Input: member of femaleList link list and user to enter			*
* The output: the current user address							       	*
* The Function operation: the function allocates memory for new user,	*
						  and link previous user's 'next' pointer to	*
						  new user, and sends it to new function to		*
						  arrange link linst by users last names		*
*************************************************************************/
profile* createNewNode(profile* femaleList, profile* user)
{
	profile* node;
	node = (profile*)malloc(sizeof(profile)); //creates user for link list
	if (node == NULL)
	{
		exit(1);
	}
	copyUser(&node, user); //copies data for new user
	if (femaleList == NULL) //if there is no user
	{
		return node;
	}
	else
	{
		femaleList = insertNodeToTree(femaleList, node); //putting new user into list
	}
	femaleListOrg(&femaleList); //organizing list by last names

	return femaleList;
}

/************************************************************************
* function name: resetUser	 									   		*
* The Input: profile pointer user										*
* The output:													       	*
* The Function operation: the function NULLS all pointer types in		*
						  profile struct								*
*************************************************************************/
void resetUser(profile* user)
{
	user->firstName = NULL;
	user->lastName = NULL;
	user->userName = NULL;
	user->password = NULL;
	user->description = NULL;
	user->next = NULL;
}

/************************************************************************
* function name: insertNodeToTree								   		*
* The Input: femaleList link list, user to enter						*
* The output: returns current link list member					       	*
* The Function operation: the function searches in recurtion the		*
						  last place in link list and assigns the		*
						  new member there							    *
*************************************************************************/

profile* insertNodeToTree(profile* femaleList, profile* node)
{
	if (femaleList == NULL) //if there is no user in this place (stopping condition)
	{
		return node;
	}
	else //if there is a user here
	{
		//continue in a recurs. until the end, and put there the user
		femaleList->next = insertNodeToTree(femaleList->next, node);
	}
	return femaleList; //return the current address
}

/************************************************************************
* function name: logIn								   					*
* The Input: flag int, male array int size address, address of			*
			 male pointers array and address of femaleList link list	*
* The output:													       	*
* The Function operation: the function scans user for username and		*
						  password. if username is wrong, it'll restart *
						  the function with 0 as flag num so if user	*
						  be wrong with username again he'll return to  *
						  last function. if password is wrong it'll also*
						  get out. if both right - it'll move to		*
						  mainmenu function								*
*************************************************************************/
void logIn(int flag, int* size, profile*** maleList, profile** femaleList)
{
	profile* tmpUser; //tmp pointer for potential user
	char buffer[16];
	printf("Please enter your username:\n");
	scanf("%s", buffer);
	tmpUser = searchUserByName(buffer, *maleList, *femaleList, *size);
	if (tmpUser == NULL) //if there is no user the func returns NULL
	{
		if (flag == false) //if its the 2nd time trying
		{
			return;
		}
		printf("User do not exist in the system, please try again\n");
		logIn(false, size, maleList, femaleList); //1st time trying, trying again
		return;
	}
	printf("Please enter your password:\n");
	scanf("%s", buffer);
	if (strcmp(buffer, tmpUser->password) == 0) //if the password entered is correct
	{
		printf("Hello %s!\n", tmpUser->firstName);
		mainMenu(tmpUser, maleList, femaleList, size);
		return;
	}
	else
	{
		printf("Wrong password\n");
		return; //end function
	}
}

/************************************************************************
* function name: searchUserByName										*
* The Input: username char array, male list pointers array, femaleList  *
			 link list and male array size int							*
* The output: user's adrress if exist, NULL if dont				       	*
* The Function operation: the function compares with strcmp function	*
						  the username string with all users untill it	*
						  finds a registered user with same username	*
						  and returns the user's address. if it doesnt	*
						  find any user it returns NULL					*
*************************************************************************/
profile* searchUserByName(char userName[], profile** maleList, profile* femaleList, int size)
{
	int index;
	for (index = 0; index < size; index++) //checking male array
	{
		if (strcmp(userName, maleList[index]->userName) == 0)
		{
			return maleList[index]; //returns the found user
		}
	}
	femaleList = femaleSearch(userName, femaleList); //checking female list
	if (femaleList != NULL) //if the func found a female user
	{
		return femaleList;
	}
	return NULL; //didnt find any user
}

/************************************************************************
* function name: femaleSearch											*
* The Input: username char array, femaleList link list 					*
* The output: user's adrress if exist, NULL if dont				       	*
* The Function operation: the function compares with strcmp function	*
						  the username string with all users untill it	*
						  finds a registered user with same username	*
						  and returns the user's address. if it doesnt	*
						  find any user it returns NULL					*
*************************************************************************/

profile* femaleSearch(char userName[], profile* femaleList)
{
	if (femaleList == NULL) //reached end - didnt find any compatible user
	{
		return NULL;
	}
	if (strcmp(userName, femaleList->userName) == 0) //if user is correct, return it
	{
		return femaleList;
	}
	return femaleSearch(userName, femaleList->next); //recurs till the end
}

/************************************************************************
* function name: register												*
* The Input: male array int size address, address of male pointers array*
			 and address of femaleList link list						*
* The output:													       	*
* The Function operation: the function creates a new user and allocates *
						  memory accordingly, checks for legallity of	*
						  inputs and if all is legal:					*
						  if the user is female: puts in femaleList		*
						  if the user is male: puts in maleList array	*
						  than goes to main menu function				*
						  if not all legal - goes back to 1st menu.		*
*************************************************************************/

void Register(profile*** maleList, profile** femaleList, int* size)
{
	char buffer[descriptionSize] = { 0 }, dummy;
	int check, index;
	profile* user = (profile*)malloc(sizeof(profile)); //creates tmp user
	if (user == NULL)
	{
		free(user);
		exit(1);
	}
	resetUser(user);
	printf("Please enter your ID:\n");
	scanf("%c %s", &dummy, user->ID);
	check = searchForID(user->ID, *maleList, *femaleList, *size);
	if (check == false)
	{
		freeProfile(&user);
		free(user);
		return;
	}
	printf("Please enter your first name:\n");
	scanf("%c %s", &dummy, buffer);
	user->firstName = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
	if (user->firstName == NULL)
	{
		freeProfile(&user);
		free(user);
		exit(1);
	}
	strcpy(user->firstName, buffer);
	printf("Please enter your last name:\n");
	scanf("%s", buffer);
	user->lastName = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
	if (user->lastName == NULL)
	{
		freeProfile(&user);
		free(user);
		exit(1);
	}
	strcpy(user->lastName, buffer);
	printf("Please enter your age (18 to 100):\n");
	scanf("%s", user->age);
	int ageCheck = atoi(user->age); //casting recieved age to int 
	if (ageCheck > highestAge || ageCheck < lowestAge) //if age is not in legal range
	{
		freeProfile(&user);
		free(user);
		return;
	}
	printf("Please enter your gender (F-female, M-male):\n");
	scanf("%c %c", &dummy, &(user->gender));
	printf("Choose a username (3-10 characters):\n");
	scanf("%s", buffer);
	if (strlen(buffer) < 3 || strlen(buffer) > 10) //if username is not in legal range
	{
		freeProfile(&user);
		free(user);
		return;
	}
	//if first letter is not a word (1sts checks for upper case)
	if ((buffer[0] <= 'A') || (buffer[0] >= 'Z'))
	{
		if ((buffer[0] <= 'a') || (buffer[0] >= 'z'))
		{
			freeProfile(&user);
			free(user);
			return;
		}
	}
	//if first letter is not a word (1sts checks for loswer case)
	if ((buffer[0] <= 'a') || (buffer[0] >= 'z'))
	{
		if ((buffer[0] <= 'A') || (buffer[0] >= 'Z'))
		{
			freeProfile(&user);
			free(user);
			return;
		}
	}
	user->userName = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
	if (user->userName == NULL)
	{
		freeProfile(&user);
		free(user);
		exit(1);
	}
	strcpy(user->userName, buffer);
	user->hobbies = 0; //resets tmp user hobbie
	printf("please choose 4 hobbies: Baseball=1, Basketball=2, Bicycle=3, Books=4,  ");
	printf("Drawing=5, Gym=6, Movies=7, Poetry=8\n");
	scanf("%c", &dummy); //scans \n
	while (true)
	{
		scanf("%c", &dummy); //scans for hobbie in char so it find \n
		if (dummy == '\n') // if entered \n
		{
			break; //exit while loop
		}
		index = atoi(&dummy); //changes value to int
		getHobbie(user, index - 1);//implimanting hobbie in user
	}
	printf("Choose a password (attention-minimum 3 characters):\n");
	scanf("%s", buffer);
	if (strlen(buffer) < 3) //if password not in legal range
	{
		freeProfile(&user);
		free(user);
		return;
	}
	user->password = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
	if (user->password == NULL)
	{
		freeProfile(&user);
		free(user);
		exit(1);
	}
	strcpy(user->password, buffer);
	printf("Some words about yourself:\n");
	scanf("%c %[^\n]s", &dummy, buffer);
	user->description = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
	if (user->password == NULL)
	{
		freeProfile(&user);
		free(user);
		exit(1);
	}
	strcpy(user->description, buffer);
	if (user->gender == 'M')
	{
		*maleList = insertToDynamicArr(*maleList, size, user); //insert user in male array
	}
	if (user->gender == 'F')
	{
		*femaleList = createNewNode(*femaleList, user); //insert females into link list
	}
	printf("Hi %s, lets find love!\n", user->firstName); //greets and enters main menu
	mainMenu(user, maleList, femaleList, size); //enters with tmp user
	//frees tmp user data
	freeProfile(&user);
	free(user);
	return;
}

/************************************************************************
* function name: searchForID											*
* The Input: male array int size, male pointers array, femaleList		*
			 link list and ID string char array							*
* The output: false if user exist, true if user doesnt			       	*
* The Function operation: the function compares with strcmp function	*
						  the ID string with all users untill it finds a*
						  registered user with same ID.					*
						  if it doesnt find any user it returns false	*
*************************************************************************/
int searchForID(char ID[], profile** maleList, profile* femaleList, int size)
{
	int index, flag = true;
	for (index = 0; index < size; index++)
	{
		if ((strcmp(ID, maleList[index]->ID)) == 0) //checks for same ID in male array
		{
			printf("Error: User already exists\n");
			return false; //user exists
		}
	}
	flag = femaleIDSearch(ID, femaleList); //checks for same ID in female users
	if (flag == false)
	{
		printf("Error: User already exists\n");
		return false; //user exists
	}
	return true; //there ID is legal
}

/************************************************************************
* function name: searchForID											*
* The Input:femaleList link list and ID string char array				*
* The output: false if user exist, true if user doesnt			       	*
* The Function operation: the function compares with strcmp function	*
						  the user id string with all female users   	*
						  untill it finds a registered user with same ID*
						  and returns the user exist. if it doesnt		*
						  find any user it returns false				*
*************************************************************************/

int femaleIDSearch(char ID[], profile* femaleList)
{
	int numCheck;
	if (femaleList == NULL) //if reached last user
	{
		return true;
	}
	if ((strcmp(ID, femaleList->ID)) == 0)
	{
		return false;
	}
	numCheck = femaleIDSearch(ID, femaleList->next);//checks next user
	return numCheck; //true if doesnt exist, false if is

}

/************************************************************************
* function name: mainMenu												*
* The Input:male array int size address, address of male pointers array *
			profile pointer current user and address of femaleList		*
			link list													*
* The output:													       	*
* The Function operation: the function scans from user an int num from	*
						  1 to 3 and accordingly goes through functions:*
						  1 - finds a match								*
						  2 - deletes user								*
						  3 - goes back to 1st menu						*
*************************************************************************/
void mainMenu(profile* user, profile*** maleList, profile** femaleList, int* size)
{
	int optionNum, flag = true;
	while (flag == true) //loop for optionNum not in range
	{
		printf("Please choose an option:\n");
		printf("1. Find a match\n2. I found love, DELETE me\n3. Log out\n");
		scanf("%d", &optionNum);
		switch (optionNum)
		{
		case (1):
			findAMatch(user, *maleList, *femaleList, *size);
			break;
		case (2):
			deleteMe(user, maleList, femaleList, size);
			return;
			break;
		case(3):
			return;
			break;
		default:
			printf("Bad choice, please try again\n");
			break;
		}
	}
}

/************************************************************************
* function name: findAMatch												*
* The Input:male array int size, address of male pointers array		    *
			profile pointer current user and address of femaleList		*
			link list													*
* The output:													       	*
* The Function operation: the function scans from user two int nums from*
						  user as minimum age and max age and according *
						  to user's gender finds a mate					*
*************************************************************************/

void findAMatch(profile* user, profile** maleList, profile* femaleList, int size)
{
	int minAge, maxAge;
	printf("Please choose ages range:\n");
	scanf("%d %d", &minAge, &maxAge); //reads for min and max ages
	if (user->gender == 'M')
	{
		findAWoman(user, femaleList, minAge, maxAge);
	}
	if (user->gender == 'F')
	{
		findAMan(user, maleList, minAge, maxAge, size);
	}
	return;
}

/************************************************************************
* function name: findAWoman											*
* The Input:profile pointer current user, address of femaleList			*
			link list, 2 ints representing min age and max age			*
* The output:													       	*
* The Function operation: the functions checks if the potential mate is	*
						  in age range and with at least 2 similar		*
						  hobbies, it'll print the potential user		*
						  the function returns if there is no female	*
*************************************************************************/
void findAWoman(profile* user, profile* femaleList, int minAge, int maxAge)
{
	if (femaleList == NULL)
	{
		return;
	}
	int hobbiesGood, ageCheck = 0;
	ageCheck = atoi(femaleList->age); //casts current female user age to int type
	if ((minAge <= ageCheck) && (maxAge >= ageCheck)) //checks for age in range
	{
		hobbiesGood = hobbiesCheck(user, femaleList); //checks for 2 hobbies at least
		if (hobbiesGood == true) //if there are - prints user
		{
			printArr(femaleList);
		}
	}
	findAWoman(user, femaleList->next, minAge, maxAge); //checks next user in list
	return;
}

/************************************************************************
* function name: hobbiesCheck											*
* The Input:profile pointer current user, profile pointer potential user*
* The output:returns true if there are at least 2 similar hobbies,		*
					 false if there is less								*
* The Function operation: the functions does 'and' operator with both	*
						  users hobbies into A int, and runs from 1-8	*
						  and does the & operator with A and letcount	*
						  int, and if its the same as letcount it counts*
						  it, then shifts it left and again until it	*
						  counts 2 and than returns true. if the &		*
						  operator isnt equal to letCount - it shifts	*
						  it left and checks again for approximatly 8	*
						  times, if it doesnt count 2 at all -			*
						  it returns false								*
*************************************************************************/

int hobbiesCheck(profile* user, profile* potentialMate)
{
	int counter = 0, index;
	unsigned int bitCheckA, bitCheckB, letCount = 1;
	bitCheckA = ((*user).hobbies) & ((*potentialMate).hobbies); //new int marking common hobbies in ints
	for (index = 0; index < 8; ++index)
	{
		bitCheckB = ((bitCheckA) & (letCount)); //checks for common hobbie
		if (bitCheckB == letCount) //same hobbie
		{
			++counter;
			if (counter >= 2)
			{
				return true; //found enough hobbies
			}
			letCount = (letCount << 1); //shifts checking num
		}
		else //hobbie is not the same
		{
			letCount = (letCount << 1); //shifts
		}
	}
	return false; //didnt have enough hobbies
}

/************************************************************************
* function name: findAMan												*
* The Input:male array int size, male pointers array profile pointer    *
			current user and 2 ints of min age and max age				*
* The output:													       	*
* The Function operation: the functions checks if the potential mate is	*
						  in age range and with at least 2 similar		*
						  hobbies, it'll print the potential user		*
						  the function returns if there is no female	*
*************************************************************************/

void findAMan(profile* user, profile** maleList, int minAge, int maxAge, int size)
{
	int index, hobbiesGood;

	for (index = 0; index < size; index++)
	{
		int ageCheck = atoi(maleList[index]->age); //casts user's age to int

		if (minAge <= ageCheck && maxAge >= ageCheck) //checks for age range
		{
			hobbiesGood = hobbiesCheck(user, maleList[index]); //checks for enough common hobbies
			if (hobbiesGood == true) //if there are
			{
				printArr(maleList[index]); //print user
			}
		}
	}
	return;
}

/************************************************************************
* function name: deleteMe												*
* The Input:male array int size address, address of male pointers array *
			profile pointer current user and address of femaleList		*
			link list													*
* The output:													       	*
* The Function operation: the functions deletes user from list or array	*
						  according to gender						    *
*************************************************************************/

void deleteMe(profile* user, profile*** maleList, profile** femaleList, int* size)
{
	if (user->gender == 'M')
	{
		*maleList = deleteFromArr(user, *maleList, size); //delete male user from array
	}
	if (user->gender == 'F')
	{
		*femaleList = delFromList(user, *femaleList); //delete female user from list
	}
	return;
}

/************************************************************************
* function name: deleteFromArr											*
* The Input:male array int size address, address of male pointers array *
			profile pointer current user 								*
* The output: returns male pointer array after realloc (profile**)	  	*
* The Function operation: the functions changes the user's place in		*
						  array to become in last place, than frees it 	*
						  and realloc with size -1 thus deleting user	*
*************************************************************************/

profile** deleteFromArr(profile* user, profile** maleArr, int* size)
{
	int isCheck, index;
	for (index = 0; index < (*size); index++)
	{
		isCheck = strcmp(user->ID, maleArr[index]->ID); //searches for user in array
		if (isCheck == 0) //found
		{
			//chenges users place so current user will be in the end
			arrPlaceChanger(maleArr, index, *size);
			break;
		}
	}
	freeProfile(&(maleArr[*size - 1])); //free profile data
	free(maleArr[*size - 1]); //free user
	(*size)--; //changes size amount
	maleArr = (profile**)realloc(maleArr, (*size) * sizeof(profile*)); //realloc new amount of male users
	return maleArr;
}

/************************************************************************
* function name: deleteFromArr											*
* The Input:male array int size, male pointers array					*
			int index of current user in array							*
* The output:														 	*
* The Function operation: the functions changes the user's place in		*
						  array to become in last place					*
*************************************************************************/

void arrPlaceChanger(profile** maleArr, int index, int size)
{
	profile* tmpUser;
	if (index == (size - 1)) //if user is in already final position
	{
		return;
	}
	for (;index < (size - 1); index++)
	{
		tmpUser = maleArr[index]; //tmp user points at current indexed user
		maleArr[index] = maleArr[index + 1]; //next user is now at current place
		maleArr[index + 1] = tmpUser; //next user is current user
	}
	return;
}

/************************************************************************
* function name: delFromList											*
* The Input:profile pointer current user and address of femaleList		*
			link list													*
* The output:													       	*
* The Function operation: if the current member of the link list is		*
						  the same as the user's address:				*
						  function puts in tmp profile pointer the		*
						  address of the member, put the next member as *
						  the current one, than makes it point next		*
						  member, than frees user as tmpPtr				*
*************************************************************************/

profile* delFromList(profile* user, profile* femaleList)
{
	profile* tmpPtr;
	if (femaleList == NULL) //if reached end list
	{
		return femaleList;
	}
	//if current user in link list is the same address as the user
	if (femaleList == user)
	{
		tmpPtr = femaleList; //tmp user points at curresnt user
		femaleList = femaleList->next; //current place is replace to next place
		freeProfile(&tmpPtr); //frees requested user
		free(tmpPtr); //frees place
		return femaleList; //returns current user new address
	}
	//implimanting next user into next pointer of current user
	femaleList->next = delFromList(user, femaleList->next);
	return femaleList; //returns current place of user
}

/************************************************************************
* function name: freeProfile											*
* The Input:profile pointer user address (profile**)					*
* The output:													       	*
* The Function operation: the function frees all dynamic memory data	*
						  inside user									*
*************************************************************************/

void freeProfile(profile** user)
{
	if (*user != NULL) //if the user exist
	{
		if ((*user)->firstName != NULL)
		{
			free((*user)->firstName);
		}
		if ((*user)->lastName != NULL)
		{
			free((*user)->lastName);
		}
		if ((*user)->userName != NULL)
		{
			free((*user)->userName);
		}
		if ((*user)->password != NULL)
		{
			free((*user)->password);
		}
		if ((*user)->description != NULL)
		{
			free((*user)->description);
		}
	}
}

/************************************************************************
* function name: exitProgram											*
* The Input: address of maleList pointer array, address of femaleList	*
			 link list first member, address of male array size			*
* The output:													       	*
* The Function operation: the function frees all dynamic memory data	*
						  inside user									*
*************************************************************************/

void exitProgram(profile*** maleList, profile** femaleList, int* size)
{
	writeFile(*maleList, *femaleList, *size); //writes users
	deleteList(*femaleList); //frees link list
	deleteArr(*maleList, size); //frees male array 
	return;
}

/************************************************************************
* function name: writeFile												*
* The Input: maleList pointer array,femaleList link list first member	*
			 maleList array int size									*
* The output:													       	*
* The Function operation: the function open a txt file writes all		*
						  users details									*
*************************************************************************/

void writeFile(profile** maleList, profile* femaleList, int size)
{
	int index;
	FILE* output = NULL;
	output = fopen("out.txt", "w+"); //opens file
	if (output == NULL) //didnt succeed to open file
	{
		printf("Failed opening files\n");
		return;
	}
	for (index = 0; index < size; index++)  //writes men
	{
		writeUser(maleList[index], output);
	}
	writeFemales(femaleList, output); //writes women
	fclose(output); //close file
	return;
}

/************************************************************************
* function name: writeFemales											*
* The Input: femaleList link list first member, pointer to file to write*
			 on															*
* The output:													       	*
* The Function operation: the function writes by recurtion all the		*
						  female users									*
*************************************************************************/

void writeFemales(profile* femaleList, FILE* output)
{
	if (femaleList == NULL) //reached end list
	{
		return;
	}
	writeUser(femaleList, output);//write female user
	writeFemales(femaleList->next, output); //writes next female user
}

/************************************************************************
* function name: writeUser												*
* The Input: profile* current user to write, file pointer to write on	*
* The output:													       	*
* The Function operation: the function writes on the pointered file		*
						  the user's details							*
*************************************************************************/

void writeUser(profile* user, FILE* output)
{
	char tmpHob;
	int index, letCount = 1, bitCheck, counter = 0;
	fputs(user->ID, output); //writes ID
	fputc(';', output); //puts demilter
	fputs(user->firstName, output); //writes first name
	fputc(';', output);
	fputs(user->lastName, output); //writes last name
	fputc(';', output);
	fputs(user->age, output); //writes age
	fputc(';', output);
	fputc(user->gender, output); //writes gender
	fputc(';', output);
	fputs(user->userName, output); //writes username
	fputc(';', output);
	fputs(user->password, output); //writes password
	fputc(';', output);
	for (index = 1; index <= 8; index++) //writes hobbie
	{
		//tmp bit check int for common hobbie in same bit space
		bitCheck = (letCount) & (user->hobbies);
		if (bitCheck == letCount)
		{
			tmpHob = (index + '0'); //convert char to int
			fputc(tmpHob, output); //writes hobbie
			counter++; //counts hobbie
			if (counter < 4) //if didnt write 4 hobbies yet
			{
				fputc(',', output);
			}
			else //wrote 4 hobbies
			{
				fputc(';', output);
				break;
			}
			letCount = letCount << 1; //shifts checking num
		}
		else //hobbie not compatible
		{
			letCount = letCount << 1; //shifts checking num
		}
	}
	fputs(user->description, output); //writes desc.
	fputc('\n', output);
}

/************************************************************************
* function name: deleteArr												*
* The Input: male pointer array, address of array int size				*
* The output:													       	*
* The Function operation: if the user is NULL it returns				*
						  else it frees the data of last array member,	*
						  than reduces size number and again until size *
						  is 0, than releases the array					*
*************************************************************************/

void deleteArr(profile** maleList, int* size)
{
	if (maleList == NULL) //if there is no array
	{
		return;
	}
	while ((*size) > 0)
	{
		freeProfile(&(maleList[(*size) - 1])); //frees user's data in place from the end to 1
		free(maleList[(*size) - 1]); //frees user place
		(*size)--; //changes size value
	}
	free(maleList); //frees pointers array
}

/************************************************************************
* function name: deleteList												*
* The Input: profile pointer user			     						*
* The output:													       	*
* The Function operation: if the user is NULL it returns				*
						  else it frees the data, and goes to next		*
						  member untill it reaches the end, than free	*
						  the user itself and goes back					*
*************************************************************************/

void deleteList(profile* user)
{
	if (user == NULL) //if reached final female user
	{
		return;
	}
	freeProfile(&user);
	deleteList(user->next); //delete next user
	free(user);
}