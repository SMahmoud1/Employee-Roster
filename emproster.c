/*
CS 222 Fall 2014

Homework 10

File: emproster.c

*/


#include <string.h>
 #include <stdio.h>
 #include <stdlib.h>
 #define MAX_LENGTH (100)
 #define FALSE (0)
 #define TRUE (1)
 
 typedef struct EmployeeStruct
{
	char LastName[MAX_LENGTH];
	char FirstName[MAX_LENGTH];
	int EmployeeNumber; // Holds the employee's ID. This value is equal to the number of employees
} 
EmployeeS;

typedef struct nodeStruct 
{ 
	EmployeeS Employee;
	struct nodeStruct *Next; 
} EmployeeSt;


EmployeeSt* hireEmployee(EmployeeSt* Top, char LastName[MAX_LENGTH], char FirstName[MAX_LENGTH]) 
{
	int integer;
	//define new employee/allocate memory
	EmployeeSt* newemp=(EmployeeSt*) malloc(sizeof(EmployeeSt)); 
	
	//check if the newemp profile exists
	if (newemp == NULL) 
	{
		printf("\nError allocating memory\n");
		exit(1);
	}
	//create struct from user input/ stores employee profile with first/last name and ID number
	printf("Employee Profile\n");
	printf("\nFirst Name: ");
	scanf("%s", newemp -> Employee.FirstName);  
	getchar();
	printf("Last Name: ");
	scanf("%s", newemp -> Employee.LastName);
	getchar();
	printf("Employee ID number: ");
	scanf("%d", &integer);
	
	newemp -> Employee.EmployeeNumber=integer;
	
	if (Top == NULL) //if the list is empty
	{
		//assign the top node to the values of newemp. newemp is the first node
		Top = newemp; 
		Top -> Next = NULL;
	}
	else 
	{
		//links new node to the list then links the top to the new node
		newemp -> Next = Top; 
		Top = newemp; 
	}
	return (Top);
} 



EmployeeSt* getLastEmployee(EmployeeSt* Top)
{
	//if Top is equal to  NULLm then it is printed that there isn't anything in the list
	if (Top == NULL)
	{
		printf("\nThere are no employees in this list!\n"); 
	}
	//print the most recently hired employee at the top of the stack
	else 
	{
		printf("\nThe most recently hired employee: \n");
		printf("\nFirst Name: %s", Top->Employee.FirstName);
		printf("\nLast Name: %s", Top->Employee.LastName);
		printf("\nEmployee ID Number: %d", Top->Employee.EmployeeNumber);
	}
	return(Top);
	
} 


EmployeeSt* fireEmployee(EmployeeSt* Top) //popping
{	
	//declare new pointer for top pointer?
	EmployeeSt* temp; 
	
	//Top = getLastEmployee(Top); //function call to print the most recently hired employee
	printf("\nThe most recently hired employee: \n");
	printf("\nFirst Name: %s", Top->Employee.FirstName);
	printf("\nLast Name: %s", Top->Employee.LastName);
	printf("\nEmployee ID Number: %d", Top->Employee.EmployeeNumber);
	//if it is found that there are no employees on the list
	if (Top == NULL) 
	{
		printf ("\nThere are no employees in this list to fire!\n");
	}
	//if something is in the stack/list then...
	else 
	{
	//set Top to a temp value so we dont lose Top, move the pointer, clear temp, then properly deallocate the temp
		temp = Top; 
		Top = Top -> Next; 
		temp -> Next = NULL; 
		free(temp); 
		temp  = NULL;	
		printf("\n\nThe most recently hired employee has been fired.\n");
	}
	return(Top);
}


void printEmployees(EmployeeSt* Top)
{
	//set a temp value equal to the top node of the stack
	EmployeeSt *temp = Top;
	//if there isn't anything in the list, print that it's empty
	if (temp == NULL)
	{
		printf("\nThere are no employees in this list!\n"); 
	}
	else
	{
		printf("\nList of employee profiles:\n");
		//while temp does not equal NULL, print out the all employee profiles in the list
		while (temp != NULL) 
		{ 
			printf("\n\nFirst Name: %s", temp->Employee.FirstName);
			printf("\nLast Name: %s", temp->Employee.LastName);
			printf("\nEmployee ID Number: %d", temp->Employee.EmployeeNumber);
			temp = temp->Next;
		}
	}
}


void DeleteRoster(EmployeeSt* Top)
{
	//delete the entire linked list and free the memory
	EmployeeSt *ptr = Top; 
	while (Top != NULL)
	{
		Top = ptr->Next;
		free(ptr);
	}
	printf("Employee list deleted.");
}
int main()
{
	char item, LastName[MAX_LENGTH], FirstName[MAX_LENGTH];
    int quit = 0;
	EmployeeSt *Top = NULL;
	//as long as quit does not equal TRUE
    while (quit!=1)
    {
        // Print out the menu
		fflush(stdin);
        printf("\n");
        printf("\nMenu:\n");
        printf("F - Fire an employee\n");
        printf("H - Hire an employee\n");
        printf("P - Print most recently hired employee\n");
        printf("A - Print complete employee roster\n");
		printf("Q - Quit\n");
		//allow user to input an option then save into item 
        printf("Enter A Choice From The Option Above: ");
        scanf(" %c", &item);
        // Get rid of extra characters (such as the Enter Key) from the input stream
        fflush(stdin); 
        // Act upon the user's choice, based upon the input character
        switch (item)
        {
            case 'F':
            case 'f':
                Top = fireEmployee(Top);
                break;
            case 'H':
            case 'h':
               Top = hireEmployee(Top, LastName, FirstName);
				break;
            case 'P':
            case 'p':
                Top = getLastEmployee(Top);
                break;
			case 'A':
            case 'a':
                printEmployees(Top);
                break;
			case 'D':
            case 'd':
				DeleteRoster(Top);
                break;
            case 'Q':
            case 'q':
				DeleteRoster(Top);
				printf("\nEmployee list deleted.\n");
                printf("\nQuitting Program\n\n");
				quit = 1;
                break;
            default:
                printf("\n %c is not a valid menu choice\n", item);
		} 
    } 
}	