#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int studentID;
    char fullName[100];
    char batch[20];
    char membershipType[10];
    char registrationDate[11];
    char dateOfBirth[11];
} Student;

Student *studentDatabase = NULL;
int totalStudents = 0;
void loadDatabase(const char *filename);
void saveDatabase(const char *filename);
void addStudent(Student s, const char *filename);
void updateStudent(int studentID);
void deleteStudent(int studentID);
void displayAllStudents();
void generateBatchReport();
int isDuplicateID(int studentID);
void clearInputBuffer();
void freeMemory();
void displayMenu() {
    printf("  IEEE/ACM MEMBERSHIP REGISTRATION\n");
    printf("1. Register a new student\n");
    printf("2. Update student information\n");
    printf("3. Delete student registration\n");
    printf("4. View all registrations\n");
    printf("5. Generate batch-wise report\n");
    printf("6. Exit program\n");
    printf("Enter your choice: ");
}

int main() {
    const char *filename = "members.dat";
    int choice;
    Student newStudent;
    int studentID;

    loadDatabase(filename);

    while (1) {
        displayMenu();
        scanf("%d", &choice);
        clearInputBuffer();

        switch (choice) {
            case 1:
                printf("\n--- Register New Student ---\n");
                
                printf("Enter Student ID: ");
                scanf("%d", &newStudent.studentID);
                clearInputBuffer();

                if (isDuplicateID(newStudent.studentID)) {
                    printf("Error: Student ID already exists!\n");
                    break;
                }

                printf("Enter Full Name: ");
                fgets(newStudent.fullName, 100, stdin);
                newStudent.fullName[strcspn(newStudent.fullName, "\n")] = 0;

                printf("Enter Batch (CS/SE/Cyber Security/AI): ");
                fgets(newStudent.batch, 20, stdin);
                newStudent.batch[strcspn(newStudent.batch, "\n")] = 0;

                printf("Enter Membership Type (IEEE/ACM/Both): ");
                fgets(newStudent.membershipType, 10, stdin);
                newStudent.membershipType[strcspn(newStudent.membershipType, "\n")] = 0;

                printf("Enter Registration Date (YYYY-MM-DD): ");
                fgets(newStudent.registrationDate, 11, stdin);
                newStudent.registrationDate[strcspn(newStudent.registrationDate, "\n")] = 0;

                printf("Enter Date of Birth (YYYY-MM-DD): ");
                fgets(newStudent.dateOfBirth, 11, stdin);
                newStudent.dateOfBirth[strcspn(newStudent.dateOfBirth, "\n")] = 0;

                addStudent(newStudent, filename);
                printf("Student registered successfully!\n");
                break;

            case 2:
                printf("\n--- Update Student Information ---\n");
                printf("Enter Student ID to update: ");
                scanf("%d", &studentID);
                clearInputBuffer();
                updateStudent(studentID);
                break;

            case 3:
                printf("\n--- Delete Student Registration ---\n");
                printf("Enter Student ID to delete: ");
                scanf("%d", &studentID);
                clearInputBuffer();
                deleteStudent(studentID);
                break;

            case 4:
                displayAllStudents();
                break;

            case 5:
                generateBatchReport();
                break;

            case 6:
                printf("\nSaving data and exiting...\n");
                saveDatabase(filename);
                freeMemory();
                printf("Thank you for using the system!\n");
                return 0;

            default:
                printf("Invalid choice! Please try again.\n");
        }
    }

    return 0;
}

void loadDatabase(const char *filename) {
    FILE *file = fopen(filename, "rb");
    
    if (file == NULL) {
        printf("No existing database found. Starting fresh.\n");
        return;
    }

    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    totalStudents = fileSize / sizeof(Student);
    fseek(file, 0, SEEK_SET);

    studentDatabase = (Student *)malloc(totalStudents * sizeof(Student));
    
    if (studentDatabase == NULL) {
        printf("Error: Memory allocation failed!\n");
        fclose(file);
        return;
    }

    int recordsRead = fread(studentDatabase, sizeof(Student), totalStudents, file);
    
    if (recordsRead != totalStudents) {
        printf("Warning: Could not read all records from file.\n");
        totalStudents = recordsRead;
    } else {
        printf("Loaded %d student records from database.\n", totalStudents);
    }

    fclose(file);
}

void saveDatabase(const char *filename) {
    FILE *file = fopen(filename, "wb");
    
    if (file == NULL) {
        printf("Error: Cannot save database to file!\n");
        return;
    }

    int recordsWritten = fwrite(studentDatabase, sizeof(Student), totalStudents, file);
    
    if (recordsWritten != totalStudents) {
        printf("Error: Could not save all records!\n");
    } else {
        printf("Database saved successfully (%d records).\n", totalStudents);
    }

    fclose(file);
}

void addStudent(Student s, const char *filename) {
    Student *temp = (Student *)realloc(studentDatabase, (totalStudents + 1) * sizeof(Student));
    
    if (temp == NULL) {
        printf("Error: Memory allocation failed!\n");
        return;
    }

    studentDatabase = temp;
    studentDatabase[totalStudents] = s;
    totalStudents++;

    saveDatabase(filename);
}

void updateStudent(int studentID) {
    int found = 0;
    
    for (int i = 0; i < totalStudents; i++) {
        if (studentDatabase[i].studentID == studentID) {
            found = 1;
            printf("\nCurrent Information:\n");
            printf("Name: %s\n", studentDatabase[i].fullName);
            printf("Batch: %s\n", studentDatabase[i].batch);
            printf("Membership: %s\n", studentDatabase[i].membershipType);
            
            printf("\n--- Update Options ---\n");
            printf("1. Update Batch\n");
            printf("2. Update Membership Type\n");
            printf("3. Update Both\n");
            printf("Enter choice: ");
            
            int updateChoice;
            scanf("%d", &updateChoice);
            clearInputBuffer();

            if (updateChoice == 1 || updateChoice == 3) {
                printf("Enter new Batch (CS/SE/Cyber Security/AI): ");
                fgets(studentDatabase[i].batch, 20, stdin);
                studentDatabase[i].batch[strcspn(studentDatabase[i].batch, "\n")] = 0;
            }

            if (updateChoice == 2 || updateChoice == 3) {
                printf("Enter new Membership Type (IEEE/ACM/Both): ");
                fgets(studentDatabase[i].membershipType, 10, stdin);
                studentDatabase[i].membershipType[strcspn(studentDatabase[i].membershipType, "\n")] = 0;
            }

            saveDatabase("members.dat");
            printf("Student information updated successfully!\n");
            break;
        }
    }

    if (!found) {
        printf("Error: Student ID not found!\n");
    }
}

void deleteStudent(int studentID) {
    int found = -1;
    
    for (int i = 0; i < totalStudents; i++) {
        if (studentDatabase[i].studentID == studentID) {
            found = i;
            break;
        }
    }

    if (found == -1) {
        printf("Error: Student ID not found!\n");
        return;
    }

    printf("Deleting student: %s\n", studentDatabase[found].fullName);

    for (int i = found; i < totalStudents - 1; i++) {
        studentDatabase[i] = studentDatabase[i + 1];
    }

    totalStudents--;

    if (totalStudents > 0) {
        Student *temp = (Student *)realloc(studentDatabase, totalStudents * sizeof(Student));
        if (temp != NULL) {
            studentDatabase = temp;
        }
    } else {
        free(studentDatabase);
        studentDatabase = NULL;
    }

    saveDatabase("members.dat");
    printf("Student deleted successfully!\n");
}

void displayAllStudents() {
    if (totalStudents == 0) {
        printf("\nNo students registered yet.\n");
        return;
    }

    printf("  ALL REGISTERED STUDENTS\n");
    for (int i = 0; i < totalStudents; i++) {
        printf("\nStudent #%d\n", i + 1);
        printf("ID: %d\n", studentDatabase[i].studentID);
        printf("Name: %s\n", studentDatabase[i].fullName);
        printf("Batch: %s\n", studentDatabase[i].batch);
        printf("Membership: %s\n", studentDatabase[i].membershipType);
        printf("Registration Date: %s\n", studentDatabase[i].registrationDate);
        printf("Date of Birth: %s\n", studentDatabase[i].dateOfBirth);
    }

    printf("Total Students: %d\n", totalStudents);
}

void generateBatchReport() {
    if (totalStudents == 0) {
        printf("\nNo students registered yet.\n");
        return;
    }

    printf("\n--- Select Batch ---\n");
    printf("1. CS\n");
    printf("2. SE\n");
    printf("3. Cyber Security\n");
    printf("4. AI\n");
    printf("Enter choice: ");

    int batchChoice;
    scanf("%d", &batchChoice);
    clearInputBuffer();

    char selectedBatch[20];
    switch (batchChoice) {
        case 1: strcpy(selectedBatch, "CS"); break;
        case 2: strcpy(selectedBatch, "SE"); break;
        case 3: strcpy(selectedBatch, "Cyber Security"); break;
        case 4: strcpy(selectedBatch, "AI"); break;
        default:
            printf("Invalid choice!\n");
            return;
    }

    printf("\n--- Select Membership Filter ---\n");
    printf("1. IEEE only\n");
    printf("2. ACM only\n");
    printf("3. Both\n");
    printf("4. All memberships\n");
    printf("Enter choice: ");

    int membershipChoice;
    scanf("%d", &membershipChoice);
    clearInputBuffer();

    char selectedMembership[10];
    int showAll = 0;
    
    switch (membershipChoice) {
        case 1: strcpy(selectedMembership, "IEEE"); break;
        case 2: strcpy(selectedMembership, "ACM"); break;
        case 3: strcpy(selectedMembership, "Both"); break;
        case 4: showAll = 1; break;
        default:
            printf("Invalid choice!\n");
            return;
    }

    printf("  BATCH REPORT: %s\n", selectedBatch);
    if (!showAll) {
        printf("  Membership: %s\n", selectedMembership);
    }

    int count = 0;
    for (int i = 0; i < totalStudents; i++) {
        int batchMatch = (strcmp(studentDatabase[i].batch, selectedBatch) == 0);
        int membershipMatch = showAll || (strcmp(studentDatabase[i].membershipType, selectedMembership) == 0);

        if (batchMatch && membershipMatch) {
            count++;
            printf("\nStudent #%d\n", count);
            printf("ID: %d\n", studentDatabase[i].studentID);
            printf("Name: %s\n", studentDatabase[i].fullName);
            printf("Membership: %s\n", studentDatabase[i].membershipType);
            printf("Registration Date: %s\n", studentDatabase[i].registrationDate);
        }
    }

    if (count == 0) {
        printf("\nNo students found matching the criteria.\n");
    } else {
        printf("\nTotal Students: %d\n", count);
    }
}

int isDuplicateID(int studentID) {
    for (int i = 0; i < totalStudents; i++) {
        if (studentDatabase[i].studentID == studentID) {
            return 1;
        }
    }
    return 0;
}

void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void freeMemory() {
    if (studentDatabase != NULL) {
        free(studentDatabase);
        studentDatabase = NULL;
    }
    totalStudents = 0;
}