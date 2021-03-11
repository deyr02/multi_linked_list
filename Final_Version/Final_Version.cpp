// version_2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <conio.h>
#define ARRAYSIZE(X) (sizeof(X) /sizeof(*(X)))


typedef struct node {
	//contrunton of node

	unsigned int ID;
	char name[50];
	char lastName[50];
	char email[50];
	char countryofBirth[50];
	node* pid;
	node* pln;
}NODE;

typedef struct {
	//constructon of header
	int counter;
	NODE* PID;
	NODE* PLN;
}MLL;

MLL * CreateMultiLinkedList() {
	//creating the head node
	// set the pid as null 
	//set the pLn as null
	MLL* myList = new MLL();
	myList->counter = 0;
	myList->PID = NULL;
	myList->PLN = NULL;
	return myList; // the memory address of the list header
}



bool validate_ID(MLL* mylist, unsigned int ID) {
	// As the assignment rule id should be unique
	//  this function  will check for valid id

	unsigned int a = INT_MAX;
	if ((ID < 1) || (ID > a)) {
		printf("Invalid ID\n");
		return false;
	}
	else {
		//checking the id whether exist in list or not
		if (mylist->counter != 0) {
			NODE *PLOC = mylist->PID; //header pointer
			while (PLOC != NULL) // accessing the list
			{
				if (PLOC->ID == ID) { // checking for id
					printf("This ID %d is already exist in the list \n", ID);
					return false;
					break;

				}
				PLOC = PLOC->pid;
			}
		}
		return true;
	}

}

bool validate_name(char name[]) {
	//validating name 
	// name should not be empty
	// and length of string should not be over 50
	if ((strlen(name) > 50) || (strlen(name) == 0))
	{
		printf("Invalid Name\n");
		return false;
	}
	return true;
}
bool validate_LastName(char LastName[]) {
	//validating last name
	if ((strlen(LastName) > 50) || (strlen(LastName) == 0))
	{
		printf("Invalid Last Name\n");
		return false;
	}
	return true;
}

bool validate_email(char email[]) {
	//validating email

	if ((strlen(email) > 50) || (strlen(email) == 0))
	{
		printf("Invalid Email\n");
		return false;
	}
	return true;
}

bool validate_Country(char Country[]) {
	//vaildating country
	if ((strlen(Country) > 50) || (strlen(Country) == 0))
	{
		printf("Invalid Country\n");
		return false;
	}
	return true;
}
void InsertNode(MLL* mylist, unsigned int ID, char name[], char LastName[], char Email[], char country[]) {
	bool v_id = validate_ID(mylist, ID); //checking id
	bool v_name = validate_name(name); // checking name
	bool v_LastName = validate_LastName(LastName); // checking last name
	bool v_Email = validate_email(Email); //checking email
	bool V_Country = validate_Country(country); // checking country

	if ((v_id) && (v_name) && (v_LastName) && (v_Email) && (V_Country)) { // validating data
		NODE* pNew = new NODE();
		NODE* pLoc;
		NODE* pCur;
		NODE* CURR;
		NODE* LAST;
		pNew->ID = ID; // adding id into node
		strcpy_s(pNew->name, name); // adding name to node
		strcpy_s(pNew->lastName, LastName);
		strcpy_s(pNew->email, Email);
		strcpy_s(pNew->countryofBirth, country);
		pNew->pid = NULL;// making the pid pointer null
		pNew->pln = NULL; //making the pln pointer null
		if (mylist->counter == 0) { // ckecking the firt item in the list
									// ordering by ID
			mylist->PID = pNew; // if the list is null then add the node the list in pID pointer
			pLoc = pNew; //
						 //ordering by id
			mylist->PLN = pNew; // adding the node into pln pointer 

			mylist->counter++;

		}
		else {

			//ordering by id
			pLoc = mylist->PID; //accessing the list
			pCur = NULL;
			while (pLoc != NULL)
			{
				if (pLoc->ID > pNew->ID) { //comparing the id
					if (pCur == NULL) { // determing current node null or not
						mylist->PID = pNew; //swapping the memory address
						pNew->pid = pLoc;
						break;
					}
					else
					{

						pCur->pid = pNew;
						pNew->pid = pLoc;
						break;
					}
				}
				else
				{
					pCur = pLoc;
					pLoc = pLoc->pid;
				}
			}
			if (pLoc == NULL) {
				pCur->pid = pNew;
			}

			//ordering by alphabetically

			CURR = mylist->PLN;
			LAST = mylist->PLN;
			while (CURR  && strcmp(CURR->lastName, pNew->lastName) < 0)
			{
				LAST = CURR;
				CURR = CURR->pln;

			}
			if (CURR == mylist->PLN) {
				pNew->pln = CURR;
				mylist->PLN = pNew;
			}
			else
			{
				LAST->pln = pNew;
				pNew->pln = CURR;
			}
			mylist->counter++;


		}

	}

}
void PrintByID(MLL *myList) {
	// this function  will print the list in ordery by id
	NODE* pLoc = myList->PID; //settin pid pointer
	if (pLoc == NULL) {// checking the list is empty or not
		printf("There is no record in the list\n");
	}
	else { // printing all the node 
		printf(".........ORDER BY ID.........\n");
		while (pLoc != NULL) {
			printf("ID        : %d\n", pLoc->ID);
			printf("NAME      : %s\n", pLoc->name);
			printf("Last Name : %s\n", pLoc->lastName);
			printf("Email     : %s\n", pLoc->email);
			printf("Country   : %s\n", pLoc->countryofBirth);
			printf("\n");

			pLoc = pLoc->pid; // pointing to the next memory address
		}
		printf("\n\n\n");
	}

}

void PrintByLN(MLL *myList) {
	//this function will access the list by pln pointer and print the list in order by last name
	NODE* pLoc = myList->PLN; // intialize the variable and point the mermory address
	if (pLoc == NULL) { //checking the list is null or not
		printf("There is no record in the list\n");
	}
	else {
		printf(".........ORDER BY LAST NAME.........\n");
		while (pLoc != NULL) { // printing all the record
			printf("ID        : %d\n", pLoc->ID);
			printf("NAME      : %s\n", pLoc->name);
			printf("Last Name : %s\n", pLoc->lastName);
			printf("Email     : %s\n", pLoc->email);
			printf("Country   : %s\n", pLoc->countryofBirth);
			printf("\n");

			pLoc = pLoc->pln; // pointing to the next memory address
		}
		printf("\n\n\n");
	}
}

NODE * RetrieveNodeByID(MLL *myList, unsigned int ID) {
	//this function will retrieve data by Id and return the memory address of particular node otherwill will return null value
	NODE * pLoc = myList->PID; //access the list by id
	NODE * Retrival; // this variable will return value

	int check = 0; // this variable will help to print data
	Retrival = NULL;
	if (pLoc == NULL) { // checking the list empyt or not
		printf("List is empty\n");
	}
	else {
		while (pLoc != NULL) {//triversing the list
			if (pLoc->ID == ID) { // comapring id 

				check = 1;
				Retrival = pLoc; //refter memory address to retrival
				break;
			}

			pLoc = pLoc->pid; // repointing the memory address
		}
		if (check == 0) {
			printf("\n------NOT-FOUND------\n");
		}
		else {
			printf("\n---------FOUND-----------\n");
			printf("ID        : %d\n", Retrival->ID);
			printf("NAME      : %s\n", Retrival->name);
			printf("Last Name : %s\n", Retrival->lastName);
			printf("Email     : %s\n", Retrival->email);
			printf("Country   : %s\n", Retrival->countryofBirth);
			printf("\n");
			printf("\n");
		}
	}

	return Retrival;


}
int stringcompare(char s1[], char s2[]) {
	// the way i have design this function, s1 have to be string from the list not from the user input
	// this function will compare two strings and it will ignore the case 
	int counter = 0;
	int i = 0;
	for (i = 0; i<strlen(s1); i++) { // this loop will go throuch each char and compare between two to strings
		if (toupper(s1[i]) == toupper(s2[i])) { // this line help to avoid case sensivity
			counter++; // in the above line will compare each char between to string if the result is true then the counter will be incresed
					   // so that we can comer between  string size and counter to get the exact result

		}

	}
	if (counter == strlen(s1)) { // justifying between counter and length of the s1 string
		return 0;
	}



	return 1;
}

NODE * RetrieveNodeByLN(MLL *myList, char LastName[]) {
	NODE * pLoc = myList->PLN; // intialize variable to trivarse the list
	NODE * Retrival; // this variable will return the memory address
	int check = 0;  // this variale will check wheather any data found or not . it will help us to print the output 

	Retrival = NULL; // initialie as null
	if (pLoc == NULL) { // if the list is null it will print the list is null
		printf("List is empty\n");
	}
	else {
		while (pLoc != NULL) {
			char lname[50];
			strcpy_s(lname, pLoc->lastName);
			if ((stringcompare(lname, LastName) == 0)) { //comparing string between lastname from the list and lastname from user input

				Retrival = pLoc; // set value to retrival 
				check++;
				break;
			}

			pLoc = pLoc->pln; // trivarsing 
		}


	}
	if (check == 0) { //check whether data found or not
		printf("\n------NOT-FOUND------\n");
	}
	else { // if found it will print the record
		printf("\n---------FOUND-----------\n");
		printf("\n");
		printf("ID        : %d\n", Retrival->ID);
		printf("NAME      : %s\n", Retrival->name);
		printf("Last Name : %s\n", Retrival->lastName);
		printf("Email     : %s\n", Retrival->email);
		printf("Country   : %s\n", Retrival->countryofBirth);

	}
	return Retrival;


}
void deletebyID(MLL * myList, unsigned int ID) {
	// this function will trivarase by PID
	// search the record by ID
	// if any node found then it will delete the node and join the node between privious on next node
	// then the function will sort by  last name so that we can trivarse the list by lastname later on
	NODE* pLoc; // this variable will triverse the list
	NODE* pPre; // this variable will hold the previous node details
	NODE* pCur; // this veriable will hold current node
	NODE* pNext;// this varibale will hold next memory address
	int checker = 0; // this variable will use to check where any rocord found or not
	int counter = 0; // this variable will help to access through the list that it is first node or not
	if (myList == NULL) {
		printf("List does not exist\n");
	}
	else {
		pLoc = myList->PID; // we will trivarse the list by id;
		pPre = NULL; // set as null
		pPre = pLoc; // hold the previous node address
		while (pLoc != NULL) { // trivarse the list 
			if (pLoc->ID == ID) { //comparing id between user input and id from the list
				checker = 1; //this line determines that record found 
				pCur = pLoc; // holding the current node data
				pNext = pLoc->pid; // hold the next node data
				printf("The record with the ID - %d and name - %s %s has been deleted successfully\n", ID, pLoc->name, pLoc->lastName);
				if (counter == 0) { // if data found at the very begining
					myList->PID = pNext; //
					free(pCur); // free the memory
					myList->counter--; // decreaseing counter 

					break;
				}
				else {
					pPre->pid = pNext;// remove the current node from the list
					free(pCur); // free memory
					myList->counter--;
					break;
				}


			}
			counter++; //increasin counter so that the programm get to know that current node is not the first node
			pPre = pLoc;
			pLoc = pLoc->pid;//trivarsing the list
		}
		if (checker == 0) {
			printf("Ther is no record with ID: %d\n", ID);
		}
		else
		{
			//sorting by name;
			//this list will be accesse throgh Id and sort the list by last name and then add it tol last name pointer in the header
			NODE * loc;

			NODE * pNew;
			NODE * CURR;
			NODE * LAST;
			loc = myList->PID; //triversing the list by id pointer
			int counter1 = 0; // intialize variable to determines the first node 
			while (loc != NULL)
			{
				pNew = loc; // copy the data into a node so 
				pNew->pln = NULL; //setting the pnew lastName pointer to null
				if (counter1 == 0) { // if it is first node when trivarseing through pid pointers
					myList->PLN = pNew; // add new node
					counter1++; // increasint the counter so that next time we can abvoid 
				}
				else
				{
					CURR = myList->PLN; //  intialize the current pointer which will hold the the memory address for the current node
					LAST = myList->PLN; // this variable will hold the memory address that last node has been added
					while (CURR  && strcmp(CURR->lastName, pNew->lastName) < 0) //comapring last name between privious node  and the current node
					{
						LAST = CURR; // set the last node
						CURR = CURR->pln; // this refering to the next node in the list

					}
					if (CURR == myList->PLN) { //swapping memory address
						pNew->pln = CURR;
						myList->PLN = pNew;
					}
					else
					{
						LAST->pln = pNew;
						pNew->pln = CURR;
					}
					counter1++;


				}

				loc = loc->pid; //refer next memory addrese when trivarsing the list by ID
			}
		}

	}

}
void deletebyLN(MLL * myList, char LastName[]) {
	// this function will access the the list and look for node by last name
	// if the any node found  then the function will delete the list from the list
	// then function will sort the list by ID
	NODE* pLoc;
	NODE* pPre;
	NODE* pCur;
	NODE* pNext;
	int checker = 0; // if this value always 0 that means no record found  otherwise found
	int counter = 0;
	if (myList == NULL) {
		printf("List does not exist\n");
	}
	else {
		pLoc = myList->PLN;
		pPre = NULL;
		pPre = pLoc;
		while (pLoc != NULL) { //accessing the list
			if (stringcompare(pLoc->lastName, LastName) == 0) {// compare the lastname 
				checker = 1;// increasing the value so the we can get to know the record found 
				pCur = pLoc;
				pNext = pLoc->pln; // copying the next memory address of the node in the list
				printf("The record with the last name - %s and ID - %d has been deleted successfully\n", pLoc->lastName, pLoc->ID);
				if (counter == 0) { // checkint it first node or not
					myList->PLN = pNext; // adding the next memory addres in the header
					free(pCur); // free the current node
					myList->counter--; // decreasing the node
					break;
				}
				else {
					pPre->pln = pNext; // ading the next memory address and take out the current node from the list
					free(pCur); // free the current node from the memory
					myList->counter--; // decreasing the node
					break;
				}


			}
			counter++; // increasing counter so that next time avoid the first node
			pPre = pLoc;
			pLoc = pLoc->pln; // pointing to the next memory address 
		}
		if (checker == 0) {
			printf("Ther is no record with the last Name: %s\n", LastName);
		}
		else
		{
			//sorting by iD
			NODE *  loc;
			NODE * pLoc1;
			NODE * pCur1;
			NODE * Cur;
			NODE * Next;
			int counter1 = 0;

			loc = myList->PLN; //this variable will hold the list which will be sorted by last name
			while (loc != NULL) {
				Cur = loc; // a
				Cur->pid = NULL;
				Next = Cur->pln;
				if (counter1 == 0) { // confirming that first node or not
					myList->PID = Cur;
					counter1++; // increaseing the counter so that next time we can go forward

				}
				else {
					pLoc1 = myList->PID; //
					pCur1 = NULL;
					while (pLoc1 != NULL)
					{
						if (pLoc1->ID > Cur->ID) { // sorting by id
							if (pCur1 == NULL) {
								myList->PID = Cur;
								Cur->pid = pLoc1;
								break;
							}
							else
							{
								pCur1->pid = Cur;
								Cur->pid = pLoc1;
								break;
							}
						}
						else
						{
							pCur1 = pLoc1;
							pLoc1 = pLoc1->pid;
						}
					}
					if (pLoc1 == NULL) {
						pCur1->pid = Cur;
					}

				}
				loc = loc->pln;
			}
		}
	}
}
void emptyList(MLL * myList) {
	//this function will go throudh the list and free all the nodes form the list and may list empty
	NODE * pCur;
	while (myList->PID != NULL) // accessting the list
	{
		pCur = myList->PID; // copy the memery address of the current node
		myList->PID = myList->PID->pid; // setting the next memory address 
		free(pCur); // freeint the current node

		myList->counter--; // decreasing the couter

	}
	myList->PLN = NULL; // makint the last name pointer null
}

void readFile(MLL * myList) {
	unsigned int id;
	char lastName[50];
	char firstName[50];
	char email[50];
	char country[50];

	const char filename[] = "MOCK_DATA.csv"; // intialize the file name
	FILE * file; // initialize FILE Variable

	if (fopen_s(&file, filename, "r") == 0) { // open the MOCK_DATA file in reading mode and validating that file exists
		char buffer[2048]; // setting up size for each line from the file
		size_t i; // intialize  numbers of lines in the file;
		for (i = 0; i<1000; ++i) {

			char data[2048]; // intialize another variable so the we can copy the line from file and past into it
			strcpy_s(data, fgets(buffer, sizeof buffer, file)); // reading  each line from the file and coping the data into data variable
			if (data != NULL) {
				char* pt; // this variable will hold the vaule of each block of characters which is sperated by comma
				char * context = "\0"; // intialize context of the line
				char delims[] = ","; // sperating line by comma
				pt = strtok_s(data, delims, &context); //spliting the line by comma;
				id = atoi(pt); // set the value for id and converting it into integer
				pt = strtok_s(NULL, delims, &context); //spliting the line
				strcpy_s(firstName, pt);// set the value for firstname
				pt = strtok_s(NULL, delims, &context);//spliting the line
				strcpy_s(lastName, pt); // set value for last name
				pt = strtok_s(NULL, delims, &context); //spliting the line
				strcpy_s(email, pt);
				pt = strtok_s(NULL, delims, &context);//spliting the line
				strcpy_s(country, pt);
				pt = strtok_s(NULL, delims, &context); // moving to next context or line
				InsertNode(myList, id, firstName, lastName, email, country); // adding vaules to the list
			}

		}
		fclose(file);//closing file;
	}
	else {
		printf("File not found\n");
	}
}



int main()
{



	int selection = ' ';
	printf("\n\n");
	printf("---------------WELCOME------------------\n");
	printf("\n\n");
	printf("-------------ASSIGNMENT------------------\n\n");
	printf("   THIS ASSIGNMENT IS COMPLETED BY\n");
	printf("\n\n");
	printf("            RAJIB DEY\n");
	printf("        STUDENT ID : 1446112\n");
	printf("\n\n");
	printf("\n\n");
	printf(" PLEASE PRESS ENTER TO RUN THE PROGRAM\n");

	MLL *myList = NULL;

	while (selection) {

		if (selection == '0')
		{
			system("cls");
			printf("\n");
			printf("\n");
			;
			if (myList == NULL) {
				myList = CreateMultiLinkedList(); //creating the list


				printf(" THE NEW LINKED LIST HAS BEEN CREATED SUCCESSFULLY\n");
			}
			else
			{

				printf(" THE LINKED LIST IS ALREADY CREATED\n");
			}
		}
		else if (selection == '1') {
			system("cls");
			printf("\n");
			printf("\n");

			if (myList == NULL) {

				printf(" PLEASE CREATE THE LINKED LIST FIRST\n");
			}
			else {

				readFile(myList);//reading file
				printf(" MOCK_DATA FILE HAS BEEN ADDED SUCCESSFULLY\n");
			}


		}
		else if (selection == '2') {
			system("cls");
			printf("\n");
			printf("\n");
			printf("\n");
			printf("\n");
			if (myList == NULL) {
				printf(" PLEASE CREATE THE LINKED LIST FIRST\n");
			}
			else {
				//getchar();
				printf("\n");
				printf("---------------ADD RECORD--------------------");
				printf("\n");
				unsigned int id;
				char name[100];
				char lastName[100];
				char email[100];
				char country[100];

				printf("\n\nINPUT ID        : ");
				//scanf_s("%d", &id);
				if (scanf_s("%d", &id) != 1) {

					printf("INVALID ID NUMBER\n");
					getchar();
				}
				else {
					getchar();
					printf("INPUT NAME      : ");
					fgets(name, 100, stdin);

					printf("INPUT LAST NAME : ");
					fgets(lastName, 100, stdin);

					printf("INPUT EMAIL     : ");
					fgets(email, 100, stdin);

					printf("INPUT COUNTRY   : ");
					fgets(country, 100, stdin);
					name[strcspn(name, "\n")] = 0;
					lastName[strcspn(lastName, "\n")] = 0;
					email[strcspn(email, "\n")] = 0;
					country[strcspn(country, "\n")] = 0;
					printf("PLEASE PRESS ENTER TO ADD THE DATA IN THE LIST\n");
					InsertNode(myList, id, name, lastName, email, country); // add new node

				}
			}





		}
		else if (selection == '3') {
			system("cls");
			printf("\n");
			printf("\n");
			if (myList == NULL) {
				printf(" PLEASE CREATE THE LINKED LIST FIRST\n");
			}
			else {
				PrintByID(myList); // printing the list
			}
		}
		else if (selection == '4') {
			system("cls");
			printf("\n");
			printf("\n");
			if (myList == NULL) {
				printf(" PLEASE CREATE THE LINKED LIST FIRST\n");
			}
			else {
				PrintByLN(myList); // printing the list in ordery by last name
			}
		}
		else if (selection == '5') {
			system("cls");
			printf("\n");
			printf("\n");
			if (myList == NULL) {
				printf(" PLEASE CREATE THE LINKED LIST FIRST\n");
			}
			else {
				printf("--RETRIEVE DATA BY ID --\n\n");
				getchar();
				unsigned int id;
				printf("\n\nINPUT ID        : ");
				if (scanf_s("%d", &id) != 1) {
					printf("INVALID ID NUMBER\n");
					getchar();

				}
				else {
					NODE * R = RetrieveNodeByID(myList, id); // Retrieve list by id
					printf("MEMORY ADDRESS :%p\n", R);

				}
			}
		}
		else if (selection == '6') {
			system("cls");
			printf("\n");
			printf("\n");
			if (myList == NULL) {
				printf(" PLEASE CREATE THE LINKED LIST FIRST\n");
			}
			else {
				printf("--RETRIEVE DATA BY LAST NAME --\n\n");
				char c = getchar();
				char  lastName[100];
				printf("INPUT LAST NAME : ");

				fgets(lastName, 100, stdin);
				NODE * R = RetrieveNodeByLN(myList, lastName);// retrieve by last name
				printf("MEMORY ADDRESS :%p\n", R);


			}
		}
		else if (selection == '7') {
			system("cls");
			printf("\n");
			printf("\n");
			if (myList == NULL) {
				printf(" PLEASE CREATE THE LINKED LIST FIRST\n");
			}
			else {
				printf("--DELETE DATA BY ID --\n\n");
				getchar();
				unsigned int id;
				printf("\n\nINPUT ID        : ");

				if (scanf_s("%d", &id) != 1) {
					printf("INVALID ID NUMBER\n");
					getchar();

				}
				else {
					deletebyID(myList, id); // delete by id

				}
			}
		}
		else if (selection == '8') {
			system("cls");
			printf("\n");
			printf("\n");
			if (myList == NULL) {
				printf(" PLEASE CREATE THE LINKED LIST FIRST\n");
			}
			else {
				printf("--DELETE DATA BY LAST NAME --\n\n");
				getchar();
				char lastName[100];
				printf("INPUT LAST NAME : ");
				fgets(lastName, 100, stdin);

				deletebyLN(myList, lastName); // delete by last name

			}
		}
		else if (selection == '9') {
			system("cls");
			printf("\n");
			printf("\n");
			if (myList == NULL) {
				printf(" PLEASE CREATE THE LINKED LIST FIRST\n");
			}
			else {
				emptyList(myList); // empty list
				printf("ALL THE THE DATA HAS BEEN ERASED FROM THE LIST SUCCESSFULLY\n");
			}
		}
		else if (toupper(selection) == 'E') {

			return 0;
		}
		else if (toupper(selection) == 'S') {
			system("cls");
			printf("\n");
			printf("\n");
			if (myList == NULL) {
				printf(" PLEASE CREATE THE LINKED LIST FIRST\n");
			}
			else {

				printf("SIZE OF THE LIST: %d\n", myList->counter); //size of the list
			}
		}
		// Menu
		selection = getchar();

		printf("\n.................MENU.........................\n");
		printf("Press-0: TO CREATE THE LIST\n");
		printf("Press-1: TO READ DATA FROM MOCK_DATA FILE AND ADD DATA INTO LIST\n");
		printf("Press-2: TO ADD NEW RECORD\n");
		printf("Press-3: TO PRINT THE LIST IN ORDER BY ID\n");
		printf("Press-4: TO PRINT THE LIST IN ORDER BY LAST NAME\n");
		printf("Press-5: TO RETRIEVE DATA BY ID\n");
		printf("Press-6: TO RETRIEVE DATA BY LAST NAME\n");
		printf("Press-7: TO DELETE DATA BY ID\n");
		printf("Press-8: TO DELETE DATA BY LAST NAME\n");
		printf("Press-9: TO EMPTY THE LIST\n");
		printf("Press-S: TO GET THE SIZE OF THE LIST\n");
		printf("Press-E: TO EXIT THE PROGRAM\n");

		printf("\nOPTION:");


	}

	return 0;

}
