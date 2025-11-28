#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Employee {
    int ID;
    char name[50];
    char designation[30];
    long long salary;
};

void inputEmployee(struct Employee arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("\nEnter details for employee %d:\n", i + 1);
        printf("Name: ");
        scanf("%s", arr[i].name);
        printf("ID: ");
        scanf("%d", &arr[i].ID);
        printf("Designation: ");
        scanf("%s", arr[i].designation);
        printf("Salary: ");
        scanf("%lld", &arr[i].salary);
    }
}

void displayEmployee(struct Employee arr[], int n) {
    printf("\n=======================================================================\n");
    printf("%-20s %-10s %-20s %-15s\n", "Name", "ID", "Designation", "Salary");
    printf("=======================================================================\n");
    for (int i = 0; i < n; i++) {
        printf("%-20s %-10d %-20s %-15lld\n",
               arr[i].name, arr[i].ID, arr[i].designation, arr[i].salary);
        printf("-----------------------------------------------------------------------\n");
    }
}

void findHighSalary(struct Employee arr[], int n) {
    int pos = 0;
    for (int i = 1; i < n; i++) {
        if (arr[i].salary > arr[pos].salary) {
            pos = i;
        }
    }
    printf("\nEmployee with the Highest Salary:\n");
    printf("=======================================================================\n");
    printf("%-20s %-10s %-20s %-15s\n", "Name", "ID", "Designation", "Salary");
    printf("=======================================================================\n");
    printf("%-20s %-10d %-20s %-15lld\n",
           arr[pos].name, arr[pos].ID, arr[pos].designation, arr[pos].salary);
    printf("-----------------------------------------------------------------------\n");
}

void searchEmployee(struct Employee arr[], int n) {
    int choice = 0;
    int searchID = 0;
    char searchName[50];
    printf("\nSearch Employee by ID or Name (1:ID / 2:Name): ");
    scanf("%d", &choice);
    while (choice < 1 || choice > 2) {
        printf("Invalid choice! Enter 1 for ID or 2 for Name: ");
        scanf("%d", &choice);
    }
    if (choice == 1) {
        printf("Enter the ID to search: ");
        scanf("%d", &searchID);
        for (int i = 0; i < n; i++) {
            if (arr[i].ID == searchID) {
                printf("\nEmployee Found:\n");
                printf("Name: %s\n", arr[i].name);
                printf("ID: %d\n", arr[i].ID);
                printf("Designation: %s\n", arr[i].designation);
                printf("Salary: %lld\n", arr[i].salary);
                return;
            }
        }
        printf("ID not found!\n");
    } else {
        printf("Enter the Name to search: ");
        scanf("%s", searchName);
        for (int i = 0; i < n; i++) {
            if (strcmp(arr[i].name, searchName) == 0) {
                printf("\nEmployee Found:\n");
                printf("Name: %s\n", arr[i].name);
                printf("ID: %d\n", arr[i].ID);
                printf("Designation: %s\n", arr[i].designation);
                printf("Salary: %lld\n", arr[i].salary);
                return;
            }
        }
        printf("Name not found!\n");
    }
}

void bonusSalary(struct Employee arr[], int n) {
    for (int i = 0; i < n; i++) {
        if (arr[i].salary < 50000) {
            arr[i].salary += (arr[i].salary * 10) / 100;
        }
    }
}

int main() {
    int n;
    printf("Enter total number of employees: ");
    scanf("%d", &n);
    struct Employee rec[n];
    inputEmployee(rec, n);
    bonusSalary(rec, n);
    displayEmployee(rec, n);
    findHighSalary(rec, n);
    searchEmployee(rec, n);
    return 0;
}
