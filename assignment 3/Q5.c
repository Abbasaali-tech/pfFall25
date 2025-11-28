#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

typedef struct {
    char **lines;
    int count;
    int capacity;
} TextEditor;

void initEditor(TextEditor *ed, int startCapacity) {
    ed->lines = (char**) malloc(startCapacity * sizeof(char*));
    if (!ed->lines) {
        printf("Memory allocation failed: %s\n", strerror(errno));
        exit(1);
    }
    ed->count = 0;
    ed->capacity = startCapacity;
}

void printLines(TextEditor *ed) {
    if (ed->count == 0) {
        printf("No lines to display.\n");
        return;
    }
    for (int i = 0; i < ed->count; i++) {
        printf("%d: %s", i, ed->lines[i]);
    }
}

void growEditor(TextEditor *ed) {
    int newCapacity = ed->capacity * 2;
    char **newArr = (char**) realloc(ed->lines, newCapacity * sizeof(char*));

    if (!newArr) {
        printf("Realloc failed: %s\n", strerror(errno));
        exit(1);
    }

    ed->lines = newArr;
    ed->capacity = newCapacity;
    printf("Capacity doubled to %d\n", newCapacity);
}

void insertLine(TextEditor *ed, int index, const char *text) {
    if (ed->count == ed->capacity)
        growEditor(ed);

    if (index < 0 || index > ed->count)
        index = ed->count;

    for (int i = ed->count; i > index; i--)
        ed->lines[i] = ed->lines[i - 1];

    ed->lines[index] = (char*) malloc(strlen(text) + 1);

    if (!ed->lines[index]) {
        printf("Memory error: %s\n", strerror(errno));
        exit(1);
    }

    strcpy(ed->lines[index], text);
    ed->count++;
}

void deleteLine(TextEditor *ed, int index) {
    if (index < 0 || index >= ed->count) {
        printf("Invalid index.\n");
        return;
    }

    free(ed->lines[index]);

    for (int i = index; i < ed->count - 1; i++)
        ed->lines[i] = ed->lines[i + 1];

    ed->count--;
}

void shrinkToFit(TextEditor *ed) {
    if (ed->count == ed->capacity)
        return;

    char **newArr = (char**) realloc(ed->lines, ed->count * sizeof(char*));

    if (!newArr) {
        printf("Shrink failed: %s\n", strerror(errno));
        exit(1);
    }

    ed->lines = newArr;
    ed->capacity = ed->count;

    printf("Capacity reduced to %d\n", ed->capacity);
}

void saveToFile(TextEditor *ed, const char *filename) {
    FILE *fp = fopen(filename, "w");

    if (!fp) {
        printf("File open error.\n");
        return;
    }

    for (int i = 0; i < ed->count; i++)
        fprintf(fp, "%s", ed->lines[i]);

    fclose(fp);
    printf("Saved!\n");
}

void loadFromFile(TextEditor *ed, const char *filename) {
    FILE *fp = fopen(filename, "r");

    if (!fp) {
        printf("File not found.\n");
        return;
    }

    char buffer[1024];

    for (int i = 0; i < ed->count; i++)
        free(ed->lines[i]);

    ed->count = 0;

    while (fgets(buffer, sizeof(buffer), fp)) {
        insertLine(ed, ed->count, buffer);
    }

    fclose(fp);
    printf("Loaded!\n");
}

void freeEditor(TextEditor *ed) {
    for (int i = 0; i < ed->count; i++)
        free(ed->lines[i]);

    free(ed->lines);
}

int main() {
    TextEditor editor;
    int startCap = 2;

    initEditor(&editor, startCap);

    int choice, index;
    char line[1024];
    char fileName[100];

    while (1) {
        printf("\n--- SIMPLE TEXT EDITOR ---\n");
        printf("1. Insert Line\n");
        printf("2. Delete Line\n");
        printf("3. Print Lines\n");
        printf("4. Save to File\n");
        printf("5. Load from File\n");
        printf("6. Shrink to Fit\n");
        printf("7. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        getchar();

        switch (choice) {

            case 1:
                printf("Enter index: ");
                scanf("%d", &index);
                getchar();

                printf("Enter line: ");
                fgets(line, sizeof(line), stdin);

                insertLine(&editor, index, line);
                break;

            case 2:
                printf("Enter index: ");
                scanf("%d", &index);
                deleteLine(&editor, index);
                break;

            case 3:
                printLines(&editor);
                break;

            case 4:
                printf("Enter filename: ");
                scanf("%s", fileName);
                saveToFile(&editor, fileName);
                break;

            case 5:
                printf("Enter filename: ");
                scanf("%s", fileName);
                loadFromFile(&editor, fileName);
                break;

            case 6:
                shrinkToFit(&editor);
                break;

            case 7:
                freeEditor(&editor);
                return 0;

            default:
                printf("Invalid option.\n");
        }
    }
}
