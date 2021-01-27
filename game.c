#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void placeBombs(char **pin, int bombs, int rows, int cols) {
    int  i, temp_rows, temp_cols;
    for (i = 0; i < bombs; i++){
        do {
            temp_rows = (rand() % rows);
            temp_cols = (rand() % cols);
        } while (pin[temp_rows][temp_cols] == '*');
        pin[temp_rows][temp_cols] = '*';
    }
}

char **mallocTheArray(int rows, int cols) {
    char **pin;
    int i;
    pin = (char **) malloc(rows*sizeof(char*));
    for(i = 0; i < rows; i++) {
        pin[i] = (char *) calloc(cols, 1);
        if (pin == NULL) {
            printf("Δεν υπάρχει αρκετός χώρος!!");
            exit(1);
        }
    }
    return pin;
}


void calculateNums(char **pin, int row, int col) {
    int i, j, sum;
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



void printMine(int rows, int cols, char **board, int **showC, int num) {
    int i, j;
    
    for(j = 0; j < cols; j++){
        printf("-----");
    }
    printf("-\n");
    for (i = 0; i < rows; i++){
        printf("|");
        for (j = 0; j < cols; j++){
            if (showC[i][j] == 1 || num == 1){
                printf(" %c  |", board[i][j]);
            } else if(showC[i][j] == 0) {
                printf("    |");
            } else {
                printf(" F  |");
            }
        }
        printf("\n");
        for(j = 0; j < cols; j++){
            printf("-----");
        }
        printf("-\n");
    }
}

void check(int **showC, char **board, int rows, int cols, int x, int y, int *sum) {

    if ((x != rows - 1) && (y != cols - 1) && (board[x+1][y+1] != '*') && (showC[x+1][y+1] != 1)){
        (*sum)++;
        showC[x+1][y+1] = 1;
        if(board[x+1][y+1] == '0') {
            check(showC, board, rows, cols, x+1, y+1, sum);
        }
    }
    if ((x != 0) && (y != cols - 1) && (board[x-1][y+1] != '*') && (showC[x-1][y+1] != 1)) {
        (*sum)++;
        showC[x-1][y+1] = 1;
        if(board[x-1][y+1] == '0') {
            check(showC, board, rows, cols, x-1, y+1, sum);
        }
        
    if ((x != 0) && (board[x-1][y] != '*') && (showC[x-1][y] != 1)){
        (*sum)++;
        showC[x-1][y] = 1;
        if(board[x-1][y] == '0') {
            check(showC, board, rows, cols, x-1, y, sum);
        }
    }
  
    }
    if ((x != rows - 1) && (y != 0) && (board[x+1][y-1] != '*') && (showC[x+1][y-1] != 1)){
        (*sum)++;
        showC[x+1][y-1] = 1;
        if(board[x+1][y-1] == '0') {
            check(showC, board, rows, cols, x+1, y-1, sum);
        }
    }
    
    if ((y != cols - 1) && (board[x][y+1] != '*') && (showC[x][y+1] != 1)){
        (*sum)++;
        showC[x][y+1] = 1;
        if(board[x][y+1] == '0') {
            check(showC, board, rows, cols, x, y+1, sum);
        }
    }
    
    if ((y != 0) && (board[x][y-1] != '*') && (showC[x][y-1] != 1)) {
        (*sum)++;
        showC[x][y-1] = 1;
        if(board[x][y-1] == '0') {
            check(showC, board, rows, cols, x, y-1, sum);
        }
    }
    
  
    if ((x != 0) && (y != 0) && (board[x-1][y-1] != '*') && (showC[x-1][y-1] != 1)){
        (*sum)++;
        showC[x-1][y-1] = 1;
        if(board[x-1][y-1] == '0') {
            check(showC, board, rows, cols, x-1, y-1, sum);
        }
    }
    if ((x != rows - 1) && (board[x+1][y] != '*') && (showC[x+1][y] != 1)) {
        (*sum)++;
        showC[x+1][y] = 1;
        if(board[x+1][y] == '0') {
            check(showC, board, rows, cols, x+1, y, sum);
        }
    }
}


void play(int **stateOfCells, char **board, int M, int N, int bombs) {
    int rows, cols, choice, *pin_sum, sum = 0;
    pin_sum = &sum;
    do {
        printMine(M, N, board, stateOfCells, 0);
        printf("Πάτα 1 για άνοιγμα κουτιού ή 2 για να τοποθετήσεις ή να βγάλεις την σημαία: \n");
        scanf("%d", &choice);
        while (choice != 1 && choice != 2) {
            printf("Λάθος είσοδος παρακαλώ εισάγετε ξανά: ");
            scanf("%d", &choice);
        }
        if (choice == 1){
            printf("Δώσε τις συντεταγμένες του κουτιού που θες να ανοίξεις \n");
            printf("Δώσε γραμμή: ");
            scanf("%d", &rows);
            printf("Δώσε στήλη: ");
            scanf("%d", &cols);
            
            while(rows < 1 || cols < 1 || rows > M || cols > N || stateOfCells[rows-1][cols-1] == 1) {
                printf("Λάθος είσοδοι δοκιμάστε ξανά\n");
                printf("Δώσε γραμμή: ");
                scanf("%d", &rows);
                printf("Δώσε στήλη: ");
                scanf("%d", &cols);
            }
                
        } else {
                printf("Δώστε τις συντεταγμένες του κουτιού που θες να τοποθετήσεις την σημαία: \n");
                printf("Δώσε γραμμή: ");
                scanf("%d", &rows);
                printf("Δώσε στήλη: ");
                scanf("%d", &cols);
                while(rows < 0 || cols < 0 || rows > M || cols > N || stateOfCells[rows-1][cols-1] == 1) {
                    printf("Λάθος είσοδοι δοκιμάστε ξανά\n");
                    printf("Δώσε γραμμή: ");
                    scanf("%d", &rows);
                    printf("Δώσε στήλη: ");
                    scanf("%d", &cols);

                }
            }
             
            if(board[rows - 1][cols - 1] == '*' && choice == 1){
                printf("Έχασες!\n");
                break;
            }
            
            if(sum == M * N - bombs) {
                printf("Νίκησες!\n");
                break;
            }
        
            if(choice == 1) {
                (*pin_sum)++;
                if(board[rows-1][cols-1] == '0') {
                    check(stateOfCells, board, M, N, rows-1, cols-1, pin_sum);
                }
            }
        
            if(choice == 2 && stateOfCells[rows-1][cols-1] == 2){
                stateOfCells[rows-1][cols-1] = 0;
            } else {
                stateOfCells[rows - 1][cols - 1] = choice;
            }
            
    } while(1);
    printMine(M, N, board, stateOfCells, 1);
}
    
void dimensions(int *rows, int *cols,int *bombs_num) {
    do {
        printf("Δώσε γραμμές: ");
        scanf("%d", rows);
        printf("Δώσε στήλες: ");
        scanf("%d", cols);
        printf("Δώσε βόμβες: ");
        scanf("%d", bombs_num);
        if(*rows <= 0 || *cols <= 0 || *bombs_num <= 0 || *cols**rows < *bombs_num) {
            if(*bombs_num > *rows**cols) {
                printf("Οι βόμβες είναι παραπάνω από τις γραμμές και στήλες του του ναρκαλιευτή\n");
            }
            if (*bombs_num <= 0) {
                printf("Οι βομβες δεν είναι θετικός αριθμός\n");
            }
            if(*rows <= 0) {
                printf("Οι γραμμές δεν είναι θετικός αριθμός\n");
            }
            if(*cols <= 0) {
                printf("Οι στήλες δεν είναι θετικός αριθμός\n");
            }
            printf("Προσπάθησε ξανά\n");
        }
       
    } while(*rows <= 0 || *cols <= 0 || *bombs_num <= 0 || *cols**rows < *bombs_num);
}
int main() {
    int i, rows, cols, **stateOfCells, bomb_num;
    char **board;
    
    dimensions(&rows, &cols, &bomb_num);
    board = mallocTheArray(rows, cols);
    stateOfCells = (int **) malloc(rows * sizeof(int*));
    for (i = 0; i < rows; i++) {
        stateOfCells[i] = (int *) calloc(cols, sizeof(int));
        if (stateOfCells == NULL) {
            printf("Δεν υπάρχει αρκετός χώρος!!");
            exit(1);
        }
    }
    srand(time(NULL));
    placeBombs(board, bomb_num, rows, cols);
    calculateNums(board, rows, cols);
    play(stateOfCells, board, rows, cols, bomb_num);
    free(stateOfCells);
    free(board);
}

