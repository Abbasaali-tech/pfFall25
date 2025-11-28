#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

typedef struct BookStruct {
    int id;
    int score;
} Book;

int bookCount = 0;

int findBook(Book *shelf, int targetId) {
    for (int i = 0; i < bookCount; i++) {
        if (shelf[i].id == targetId)
            return i;
    }
    return -1;
}

void addBook(Book *shelf, const int capacity, int bookId, int bookScore) {
    int index = findBook(shelf, bookId);

    if (index != -1) {
        shelf[index].score = bookScore;

        Book temp = shelf[index];
        for (int i = index; i < bookCount - 1; i++) {
            shelf[i] = shelf[i + 1];
        }
        shelf[bookCount - 1] = temp;
        return;
    }

    if (bookCount == capacity) {
        for (int i = 0; i < capacity - 1; i++) {
            shelf[i] = shelf[i + 1];
        }
        shelf[capacity - 1].id = bookId;
        shelf[capacity - 1].score = bookScore;
    } else {
        shelf[bookCount].id = bookId;
        shelf[bookCount].score = bookScore;
        bookCount++;
    }
}

int accessBook(Book *shelf, int bookId) {
    int index = findBook(shelf, bookId);

    if (index == -1)
        return -1;

    int bookScore = shelf[index].score;
    Book temp = shelf[index];

    for (int i = index; i < bookCount - 1; i++) {
        shelf[i] = shelf[i + 1];
    }
    shelf[bookCount - 1] = temp;

    return bookScore;
}

int main() {
    int capacity, operations;
    scanf("%d %d", &capacity, &operations);

    Book *shelf = (Book*) malloc(sizeof(Book) * capacity);

    int bookId, bookScore, choice;

    for (int i = 0; i < operations; i++) {
        printf("Choose option (1:ADD/2:ACCESS): ");
        scanf("%d",&choice);
         
        while (choice < 1 || choice > 2)
        {
            printf("Incorret Option!! Choose option (1:ADD/2:ACCESS): ");
            scanf("%d",&choice);            
        }
        
        if (choice == 1)
        {
            printf("Enter Book ID and Popularity Score\n");
            scanf("%d %d", &bookId, &bookScore);
            addBook(shelf, capacity, bookId, bookScore);
        }
        else{
            printf("Enter BookID: ");
            scanf("%d", &bookId);
            int scoreVal = accessBook(shelf, bookId);
            printf("%d\n", scoreVal);
        }
        
    }

    free(shelf);
    return 0;
}
