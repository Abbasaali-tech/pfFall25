#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ROWS 3
#define COLS 3
#define POWER_ON 1
#define OVERLOAD_WARNING 2
#define MAINTENANCE_REQ 4

void updateSector(int grid[ROWS][COLS],int row,int col,int flag,int set){
    if (set){
        grid[row][col] |= flag;
    }
    else{
        grid[row][col] &= ~flag;
    }
}

void querySector(int grid[ROWS][COLS], int row,int col){
    int value = grid[row][col];
    printf("Sector (%d,%d):\n", row, col);
    printf(" Power: %s\n", (value & POWER_ON) ? "ON" : "OFF");
    printf(" Overload: %s\n", (value & OVERLOAD_WARNING) ? "YES" : "NO");
    printf(" Maintenance: %s\n", (value & MAINTENANCE_REQ) ? "YES" : "NO");  
}

void runDiagnostic(int grid[ROWS][COLS]){
    int overloadCount = 0, maintenanceCount = 0;
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            if (grid[i][j] & OVERLOAD_WARNING)
                overloadCount++;
            if (grid[i][j] & MAINTENANCE_REQ)
                maintenanceCount++;           
        }
        
    }
    printf("System Diagnostic:\n");
    printf(" Total Overloaded Sectors: %d\n", overloadCount);
    printf(" Total Maintenance Required: %d\n", maintenanceCount);   
}

int main(){
    int grid[ROWS][COLS] = {0};
    int choice,row,col,flag,set;

    while(1){
        printf("---- IESCO Power Grid Menu ----\n1. Update Sector Status\n2. Query Sector Status\n3. Run System Diagnostic\n4. Exit\n");
        printf("Enter Choice: ");
        scanf("%d",&choice);

        switch (choice)
        {
        case 1:
            printf("Enter sector (row,col): ");
            scanf("%d %d",&row,&col);
            if (row < 0 || row >= ROWS || col < 0 || col >= COLS) {
                printf("Invalid sector coordinates!\n");
                break;
            }
            printf("Enter status to modify:\n");
            printf(" 1. Power\n 2. Overload\n 3. Maintenance\n");
            printf("Choice: ");
            scanf("%d",&flag);
            if (flag == 1)
            {
                flag = POWER_ON;
            }
            else if (flag == 2)
            {
                flag = OVERLOAD_WARNING;
            }
            else if (flag == 3)
            {
                flag = MAINTENANCE_REQ;
            }
            printf("Set(1) or Clear(0): ");
            scanf("%d",&set);
            updateSector(grid,row,col,flag,set);
            break;
        case 2:
            printf("Enter sector (row,col): ");
            scanf("%d %d",&row,&col);
            if (row < 0 || row >= ROWS || col < 0 || col >= COLS) {
                printf("Invalid sector coordinates!\n");
                break;
            }
            querrySector(grid,row,col);
            break;
        case 3:
            runDiagnostic(grid);
            break;
        case 4:
            printf("Exiting...\n");
            return 0;
        default:
            printf("Invalid Choice.\n");
        }

    }
}