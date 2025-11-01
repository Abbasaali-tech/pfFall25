#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define maxBooks 100
void addNewBook(char title[][50],int isbn[],float prices[], int quantities[], int *count){
	char name[50];
	int isbnNum,i = 0,flag = 0;
	float price;
	int quantity;
	
	if (*count >= maxBooks){
		printf("Inventory full! Cannot add more books\n");      
		return;
	}
	
	
	printf("Enter the isbn number\n");
	scanf("%d",&isbnNum);
	
	for (i = 0;i < *count;i++){
		if (isbnNum == isbn[i]){
			printf("Error: A book with this ISBN exists\n");   
			return;
		}
	}
	
	printf("Enter the title of book\n");
	getchar();
	fgets(name, sizeof(name), stdin);
	name[strcspn(name,"\n")] = '\0';
	
	printf("Enter the price of %s\n",name);
	scanf("%f",&price);
	
	printf("Enter the quantity of that book\n");
	scanf("%d",&quantity);
	
    isbn[*count] = isbnNum;                               
    strcpy(title[*count], name);
    prices[*count] = (float)price;
    quantities[*count] = quantity;

    (*count)++;
    
    printf("Book Added Successfully!\n");
	
}

void processSale(int isbn[],int quantities[],float prices[],int *count){
	int isbnNum;
	int numCopySales;
	
	int i;
	
	printf("Enter the isbn number\n");
	scanf("%d",&isbnNum);
	
	printf("Enter the quantity of book to sale\n");
	scanf("%d",&numCopySales);
	
	for(i = 0;i < *count;i++){
		if (isbnNum == isbn[i]){                     
			if (numCopySales > quantities[i]){
				printf("Error: %d number of copies cannot be sold\n",numCopySales);
				return;
			}
			else{
				quantities[i] -= numCopySales;
				printf("Total price of books are: %.2f",prices[i] * numCopySales);
				printf("\nBooks sold Successfully!\n");
				return;
			}
		}
	}	
}

void generateReport(int isbn[],char title[][50],int quantities[],float prices[],int *count){
	printf("Isbn\tNames\t\tQuantities\tPrice\n");
 	printf("---------------------------------------------------------------\n");
	
	int i;
	
	for (i = 0;i < *count;i++){                                
		if (quantities[i] < 5){
			printf("%d\t%-20s\t%d\t%.2f\n",isbn[i],title[i],quantities[i],prices[i]);
		}
	}
	printf("\n");
	return;	
}

int main(){
	
	int isbn[100];
	char title[100][50];
	float prices[100];
	int quantities[100];
	
	int count = 0;
	int choice; 
	
	printf("----- MENU ----- \n1. Add New Book\n2. Process a Sale\n3. Generate Low-Stock Report\n4. Exit\n");
	printf("------------------------------------\n");
	scanf("%d",&choice);
	
	if (choice == 4){
		printf("Exiting.....\n");
		return 0;
	}
	
	while (choice != 4){
		
		switch(choice){
		
			case 1:
				addNewBook(title,isbn,prices,quantities,&count);
				break;
			case 2:
				processSale(isbn,quantities,prices,&count);
				break;
			case 3:
				generateReport(isbn,title,quantities,prices,&count);
				break;
			case 4:
				printf("Exiting.....\n");
				break;
			default:
				printf("Invalid number input\n");	
		}
		printf("----- MENU ----- \n1. Add New Book\n2. Process a Sale\n3. Generate Low-Stock Report\n4. Exit\n\n");
		printf("------------------------------------\n");	
		scanf("%d",&choice);			
	}
}

