#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void inputCode(char code[],int *counter,int *length){
    char ch;

    printf("Enter the string to encode/decode: ");
    while (*counter < 50)
    {
        ch = getchar();
        if (ch == '\n')
        {
            break;
        }
        else{
            code[*counter] = ch;
            (*counter)++;
        }
    }
    code[*counter] = '\0';
    *length = *counter;
}

void reverseCode(char code[],char codeReversal[],int *length){
    
    for (int i = 0; i < *length; i++)
    {
        codeReversal[i] = code[(*length) - i - 1]; 
    }
    codeReversal[*length] = '\0';   
    // printf("Reversed String: %s\n",codeReversal);
}

void bitToggleCode(char codeReversal[],char toggleCode[],int *length){

    for (int i = 0; i < *length; i++)
    {
        char ch = codeReversal[i];

        ch = ch ^ ((1 << 1) | (1 << 4));
        toggleCode[i] = ch;
    }

    toggleCode[*length] = '\0';
    printf("\nThe Encoded message: %s\n",toggleCode);
}

void reverseBitCode(char toggleCode[],char reverseToggleCode[],int *length){
    for (int i = 0; i < *length; i++)
    {
        char ch = toggleCode[i];

        ch = ch ^ ((1 << 1) | (1 << 4));
        reverseToggleCode[i] = ch;
    }

    reverseToggleCode[*length] = '\0';

}

void decipherCode(char reverseToggleCode[],char decryptCode[],int *length){
        for (int i = 0; i < *length; i++)
    {
        decryptCode[i] = reverseToggleCode[(*length) - i - 1]; 
    }
    decryptCode[*length] = '\0';   
    printf("Original Message: %s\n",decryptCode);
}

int main(){

    char code[50];
    char codeReversal[50];
    char toggleCode[50];
    int counter = 0;
    int length = 0;
    int choice;

    char reverseToggleCode[50];
    char decryptCode[50];

    while (1)
    {
        printf("\n------  TCS  ------\n1. Encode Message\n2. Decode Message\n3. Exit\n");
        printf("Enter choice: ");
        scanf("%d",&choice);
        while (getchar() != '\n');

        switch (choice)
        {
        case 1:
        counter = 0;
            inputCode(code,&counter,&length);
            reverseCode(code,codeReversal,&length);
            bitToggleCode(codeReversal,toggleCode,&length);
            break;
        case 2:
            inputCode(toggleCode, &counter, &length);
            reverseBitCode(toggleCode,reverseToggleCode,&length);    
            decipherCode(reverseToggleCode,decryptCode,&length);
            break;
        case 3:
            printf("Final Output\n");
            reverseBitCode(toggleCode,reverseToggleCode,&length);    
            decipherCode(reverseToggleCode,decryptCode,&length);
            printf("Exiting...\n");
            return 0;
        default:
            printf("Invalid choice\n");
        }
    }
}
    
