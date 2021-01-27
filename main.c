#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void giveNums(int *rows, int *cols, int *bombs) {
    do {
    printf("Δώσε γραμμές: ");
    scanf("%d", rows);
    printf("Δώσε στήλες: ");
    scanf("%d", cols);
    printf("Δώσε βόμβες: ");
    scanf("%d", bombs);
    if(*rows <= 0 || *cols <= 0 || *bombs <= 0 || *cols**rows < *bombs) {
        if(*bombs > *rows**cols) {
            printf("Οι βόμβες είναι παραπάνω από τις γραμμές και στήλες του του ναρκαλιευτή\n");
        }
        if (*bombs <= 0) {
            printf("Οι βομβες δεν είναι θετικός αριθμός\n");
        }
        if(*rows <= 0) {
            printf("Οι γραμμές δεν είναι θετικός αριθμός\n");
        }
        if(*cols <= 0) {
            printf("Οι στήλες δεν είναι θετικός αριθμός\n");
        }
        printf("Προσπάθησε ξανά!\n");
    }
       
    } while(*rows <= 0 || *cols <= 0 || *bombs <= 0 || *cols**rows < *bombs);
}

void placeBombs(char **pin2d, int rows, int cols, int bombs) {
    int i, theRows, theCols;
    for(i = 0; i < bombs; i++) {
            do {
                theCols = rand()% cols;
                theRows = rand()% rows;
            } while (pin2d[theRows][theCols] == '*');
            pin2d[theRows][theCols] = '*';
    }
}

void calculateNums(char **pin, int row, int col){
    int i,j, sum;
    for(i = 0; i < row; i++) {
        for(j = 0; j < col; j++) {
            if(pin[i][j] != '*') {
                sum=0;
                                
                sum = ((i != row - 1) && (j != col - 1) && (pin[i+1][j+1] == '*')) ? sum+1 : sum;
                
                sum = ((i != row - 1) && (pin[i+1][j] == '*')) ? sum+1 : sum;
                
                sum = ((i != 0) && (pin[i-1][j] == '*')) ? sum+1 : sum;
                
                sum = ((j != 0) && (pin[i][j-1] == '*')) ? sum+1 : sum;

                sum = ((i != 0) && (j != col - 1) && (pin[i-1][j+1] == '*')) ? sum+1 : sum;

                sum = ((j != col - 1 && (pin[i][j+1] == '*'))) ? sum+1 : sum;

                sum = ((i != row - 1) && (j != 0) && (pin[i+1][j-1] == '*')) ? sum+1 : sum;

                sum = ((i != 0) && (j != 0) && (pin[i-1][j-1] == '*')) ? sum+1 : sum;

                pin[i][j] = sum + '0';
            }
        }
    }
}

void printTheBombs(char **pin2d, int rows, int cols, FILE *fp) {
    int i,j;
    for(i = 0; i < rows; i++) {
        printf("----");
        fprintf(fp, "----");
    }
    printf("-\n");
    fprintf(fp, "-\n");
    
    for (j = 0; j < cols; j++) {
        printf("|");
        fprintf(fp, "|");
        
        for (i = 0; i < rows; i++) {
        printf(" %c |", pin2d[i][j]);
        fprintf(fp, " %c |", pin2d[i][j]);
        }
        printf("\n");
        fprintf(fp, "\n");
        
        for(i = 0; i < rows; i++) {
        printf("----");
        fprintf(fp, "----");
        }
        printf("-\n");
        fprintf(fp, "-\n");
    }
}
char **mallocTheArray(int rows, int cols) {
    char **pin2d;
    int i;
    pin2d = (char **) malloc(rows*sizeof(char*));
    for(i = 0; i < rows; i++) {
        pin2d[i] = (char*) calloc(rows, 1);
        if (pin2d == NULL) {
            printf("Δεν υπάρχει αρκετός χώρος!!");
            exit(1);
        }
    }
    return pin2d;
}

int main() {
    int rows = 0, cols = 0, bombs = 0;
    char **board;
    FILE *fp = fopen("minesweeper.txt", "w");
    if (fp == NULL) {
        printf("Δυστυχώς υπάρχει πρόβλημα στο αρχείο.");
        exit(1);
    }
    srand(time(NULL));
    giveNums(&rows, &cols, &bombs);
    board = mallocTheArray(rows, cols);
    placeBombs(board, rows, cols, bombs);
    calculateNums(board, rows, cols);
    printTheBombs(board, rows, cols, fp);
    free(board);
    fclose(fp);
    return 0;
}
