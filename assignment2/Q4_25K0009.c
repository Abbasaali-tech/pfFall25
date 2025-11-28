#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void PUSH(int stack[],int *top,int maxSize){
    int num;

    printf("Enter the number to insert: ");
    scanf("%d",&num);

    if (*top < maxSize)
    {
        stack[*top] = num;
        (*top)++;
        printf("Number added Successfully!\n");
    }
    else{
        printf("No space left!\n");
        return;
    } 
}

void POP(int stack[],int *top){

    int num;

    if (*top > 0)
    {
        num = stack[*top - 1];
        printf("%d number removed successfully!\n",num); 
        (*top)--;   
    }
    else{
        printf("No element found!\n");
        return;
    }  
}

void PEEK(int stack[],int *top){
    int num;

    if (*top > 0)
    {
        printf("Number: %d\n",stack[*top - 1]);  
    }
    else{
        printf("No element found!\n");
        return;
    }  
}

void DISPLAY(int stack[],int *top){

    if (*top > 0)
    {
        printf("Stack elements (top to bottom): ");
        for (int i = *top - 1; i >= 0; i--)
        {
            printf("%d ",stack[i]); 
        }
        printf("\n");
    }
    else{
        printf("No element found to display!\n");
        return;
    }
}

int main(){

    int maxSize = 10;
    int stack[10] = {0};
    int choice;
    int top = 0;

    while (1)
    {
        printf("----- Stack Elements -----\n1. PUSH(add element)\n2. POP(removes element)\n3. PEEK(displays top elemnt)\n4. DISPLAY(Show all elements)\n5. EXIT\n");
        printf("Enter choice: ");
        scanf("%d",&choice);

        switch (choice)
        {
        case 1:
            PUSH(stack,&top,maxSize);
            break;
        case 2:
            POP(stack,&top);
            break;
        case 3:
            PEEK(stack,&top);
            break;
        case 4:
            DISPLAY(stack,&top);
            break;
        case 5:
            printf("Exiting...\n");
            return 0;
        default:
            printf("Invalid Choice!!\n");
        }    
    }
    

}