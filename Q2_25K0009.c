#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void customerInfo(char name[],long long *cnic){
	char names[50];
	
	printf("Enter your name\n");
	getchar();
	fgets(names, sizeof(names), stdin);
	names[strcspn(names,"\n")] = '\0';
	
	strcpy (name,names);
	
	printf("Enter your CNIC number\n");
	scanf("%lld",cnic);

}

void displayInventory(int productCode[],int quantityInStock[],float pricePerProduct[],int *index){
	
	printf("------------------------------------------------------------\n");
	printf("Product code\t Quantity in stock\t Price per product\n");
	printf("------------------------------------------------------------\n");
	
	int i;
	
	for(i = 0;i < *index;i++){
		printf("%d\t\t %d\t\t\t %.2f\n",productCode[i],quantityInStock[i],pricePerProduct[i]);
	}
	
}

void addItem(int productCode[],int quantityInStock[],int cart[],int cartQuantity[],float cartPrice[],float pricePerProduct[],int *index,int *item){
	
	int p_Code,quantity;
	int flag = 1,i,choice,found = 0;
	while (flag == 1){

		printf("Enter the product code\n");
		scanf("%d",&p_Code);
		
		for (i = 0;i < *index;i++){
			if (p_Code == productCode[i]){
				found = 1;
				cart[*item] = p_Code;
				printf("Enter the quanitity\n");
				scanf("%d",&quantity);
				
				cartPrice[*item] = pricePerProduct[i];
				
				if (quantity > quantityInStock[i]){
				 	printf("Error: Quantity entered is greater that stock quantity!!\n");
					return;
				}
				else{
					cartQuantity[*item] = quantity;
					quantityInStock[i] -= quantity;
					(*item)++;
				}					
			}
		}	
		printf("Enter (1. More item to enter/0. Exit)\n");
		scanf("%d",&choice);
		
		if (found == 0){
			printf("Error: Product code not found\n");
		}
		if (choice == 0){
			printf("Exiting....\n\n");
			return;
		}
		else if(choice != 1){
			printf("Wrong Input\n");
			return;
		}
	}	
}

void totalBill(int cartQuantity[],float cartPrice[],float *totalPrice,int *item){
	
	int i;
	char promoCode[20];
	
	*totalPrice = 0.0;
	
	for (i = 0;i < *item;i++){
		*totalPrice += cartQuantity[i] * cartPrice[i];
	}
	float originalTotal = *totalPrice;
	
	printf("Enter promo code (or press Enter to skip)\n");
	getchar();
	fgets(promoCode, sizeof(promoCode), stdin);
	promoCode[strcspn(promoCode,"\n")] = '\0';
	
	if (strcmp(promoCode, "Eid2025") == 0){
		*totalPrice *= .75;
		printf("Promo applied! 25%% discount given.\n");
	}
	else if (strlen(promoCode) > 0) {
        printf("Invalid promo code! No discount applied.\n");
    }
    printf("Total (without discount): %.2f\n", originalTotal);
	printf("Final Total (after discount, if any): %.2f\n", *totalPrice);
}

void displayInvoice(char name[],int cart[],int cartQuantity[],float cartPrice[],float *totalPrice,long long *CNIC,int *item){
	
	printf("\n--------------- INVOICE ---------------\n");
	printf("Customer Name: %s\t CNIC number: %lld\n",name,*CNIC);
	printf("---------------------------------------------------------\n");
	printf("Product Code\t Quantity\t Price\t Price Per Product\n");
	printf("---------------------------------------------------------\n");
	
	int i;
	
	for (i = 0;i < *item;i++){
		printf("\n%d\t %d\t\t\t %.2f\t %.2f\n",cart[i],cartQuantity[i],cartPrice[i],cartQuantity[i]*cartPrice[i]);		
	}
	
	printf("\nTotal price: %.2f\n",*totalPrice);
}

int main(){
	
	char name[50];
	long long CNIC;
	int productCode[] = {1, 2, 3, 4};
	int quantityInStock[] = {50, 10, 20, 8};
	int cart[4];
	int cartQuantity[4];
	float cartPrice[4];
	float pricePerProduct[] = {100.0, 200.0, 300.0, 150.0};
	float totalPrice;
	
	int choice;
	int item = 0;
	int index = 4;
	int flag = 0;
	
	
	printf("----- MENU -----\n1. Customer Information\n2. Display Inventory\n3. Add Item To Cart\n4. Total Bill\n5. Display Invoice\n6. Exit\n");
	printf("\nEnter your choice:");
	scanf("%d",&choice);
	
	while (choice != 6){
		switch (choice) {
			case 1:
				customerInfo(name, &CNIC);
				break;
			case 2:
				displayInventory(productCode, quantityInStock, pricePerProduct, &index);
				break;
			case 3:
				displayInventory(productCode, quantityInStock, pricePerProduct, &index);
				addItem(productCode, quantityInStock, cart, cartQuantity, cartPrice, pricePerProduct, &index, &item);
				break;
			case 4:
				totalBill(cartQuantity, cartPrice, &totalPrice, &item);
				break;
			case 5:
				displayInvoice(name, cart, cartQuantity, cartPrice, &totalPrice, &CNIC, &item);
				break;
			case 6:
				printf("Exiting system...\n");
				return 0;
			default:
				printf("Invalid choice! Try again.\n");
		}
		printf("----- MENU -----\n1. Add Item To Cart\n2. Total Bill\n3. Display Invoice\n");
		printf("\nEnter your choice:");
		scanf("%d",&choice);
	}
}
