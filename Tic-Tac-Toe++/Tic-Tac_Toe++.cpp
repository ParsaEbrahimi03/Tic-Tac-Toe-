#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <conio.h>
#include <time.h>
#include <string.h>


void gotoxy(int x, int y);
void clearScrean();

char board[10][10];
int full[10] = { 0 };
char Player, Coumputer;
char x, y;
char name1[10];
char name2[10];
int row, column;
int bombP1 = 2, bomb11 = 2, bomb21 = 2;
int bombP2 = 2, bomb12 = 2, bomb22 = 2;

void resetBord()
{
    for (int i = 0; i < column; i++) {
        for (int j = 0; j < row; j++)
            board[i][j] = ' ';
    }
}

void printboard()
{
    printf("\tTIC_TAC_TOE\n\n");

    for (int i = row - 1; i >= 0; i--) {
        printf("|");
        for (int j = 0; j < column; j++)
            printf(" %c |", board[j][i]);
        
        printf("\n ");
        for (int j = 0; j < column; j++)
            printf("--- ");
        printf("\n");
    }
    
    for (int i = 0; i < column; i++) {
        printf("  ");
        printf("%i", i + 1);
        printf(" ");
    }
    printf("\n\n");
    
    return;
}

int chackFreeSpace()
{
    int freeSpace = row * column;

    for (int i = 0; i < column; i++) {
        for (int j = 0; j < row; j++) {

            if (board[i][j] != ' ')
                freeSpace--;
        }
    }

    return (freeSpace);
}

void printWinner(char winner)
{
    if (winner == Player)
        printf("YOU WIN!!  :)");
    else if (winner == Coumputer)
        printf("YOU LOSE!!  :(");
    else
        printf("YOU ARE EQUAL!!  :|");

    return;
}

int moveInGrand(int  i)
{
    i = 0;
    printf("\n\n\n\nPlease enter just 'D' or 'A'");
    char move = _getch();
    int y = 14;
    for (int i = 6; i < row; i++)
        y += 2;
    int x = 2;
    int z = ((column - 1) * 4) + x;

    while (move != 13)
    {

        switch (move)
        {
        case('d'):
        case('D'):
            x += 4;
            i++;
            if (x > z) {
                x = 2;
                i = 0;
            }
            gotoxy(x, y);
            break;
        case('a'):
        case('A'):
            x -= 4;
            i--;
            if (x < 2) {
                x = z;
                i = 5;
            }
            gotoxy(x, y);
            break;
        default:
            printf("\n\n\n\n\n\n\nPlease enter the right character");
            break;
        }
        move = _getch();
    }

    return i;
}

void bombOne(int k)
{
    full[k] = { 0 };
    for (int i = 0; i < row; i++)
        board[k][i] = ' ';
    
    return;
}

void bombTwo(int j)
{
    for (; j < row - 1; j++) {
        int i;
        for (i = 0; i < column; i ++) {
            board[i][j] = board[i][j + 1];

        }
    }

    int help = row - 1;
    for (int i = 0; i < column; i++) {
        full[i]--;
        board[i][help] = ' ';
    }

    return;
}

void putBombOne(int i)
{
    i = 0;
    printf("\n\n\n\nPlease enter just 'D' or 'A'");
    char move = _getch();
    int y = 14;
    for (int i = 6; i < row; i++)
        y += 2;
    int x = 2;
    int z = ((column - 1) * 4) + x;

    while (move != 13)
    {

        switch (move)
        {
            case('d'):
            case('D'):
                x += 4;
                i++;
                if (x > z) {
                    x = 2;
                    i = 0;
                }
                gotoxy(x, y);
                break;
            case('a'):
            case('A'):
                x -= 4;
                i--;
                if (x < 2) {
                    x = z;
                    i = 5;
                }
                gotoxy(x, y);
                break;
            default:
                printf("\n\n\n\n\n\n\nPlease enter the right character");
                break;
        }
        move = _getch();
    }

    bombOne(i);

    return;
}

void putBombTwo(int i)
{
    i = 0;
    printf("\n\n\n\nPlease enter just 'D' or 'A'");
    char move = _getch();
    int y = 14;
    for (int i = 6; i < row; i++)
        y += 2;
    int x = 2;
    int z = ((column - 1) * 4) + x;

    int j;
    while (move != 13)
    {

        switch (move)
        {
            case('d'):
            case('D'):
                x += 4;
                i++;
                if (x > z) {
                    x = 2;
                    i = 0;
                }
                gotoxy(x, y);
                break;
            case('a'):
            case('A'):
                x -= 4;
                i--;
                if (x < 2) {
                    x = z;
                    i = 5;
                }
                gotoxy(x, y);
                break;
            default:
                printf("\n\n\n\n\n\n\nPlease enter the right character");
                break;
        }
        move = _getch();
    }

        j = full[i];

    bombTwo(j);

    return;
}

void putNut()
{
    printf("YOUR TURN!!");
    
    int k = 0;
    int j;
    do {
        k = moveInGrand(k);
        j = full[k];

    } while (j >= row);

    board[k][j] = Player;
    full[k]++;
    
    clearScrean();
    printboard();

    return;
}

void computerMove()
{
    if (Player == 'X')
        Coumputer = 'O';
    else
        Coumputer = 'X';

    srand(time_t(0));

    int j, k;
    if (chackFreeSpace() > 0) {
    do
    {
        do {
            k = rand() % column;
            } while (k >= column);

            j = full[k];
        } while (board[k][j] != ' ' || board[k][j] == Player || j > row - 1);

        board[k][j] = Coumputer;
        full[k]++;
        
    }
    else
        printWinner(' ');

    srand(time_t(0));

    return;
}

char checkWinner()
{
    char z;
    int count = 0;
    //check column
    for (int i = 0; i < column; i++) {
        for (int j = 0; j < row - 1; j++) {
            z = board[i][j];
            if (board[i][j] == board[i][j + 1])
                count++;
            else
                count = 0;
        }
        if (count >= 5)
            return(z);
    }

    count = 0;
    //check row
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < column - 1; j++) {
            z = board[i][j];
            if (board[j][i] == board[j + 1][i])
                count++;
            else
                count = 0;
        }
        if (count >= 5)
            return(z);
    }

    count = 0;
    //check diagnols
    for (int k = 0; k < row; k++) {
        for (int h = 0; h < column; h++) {
            int j, i;
            for (i = k, j = h; i < row && j < column - 4; i++, j++) {
                if (board[h][k] == board[j][i])
                    count++;
                else
                    count = 0;
            }
            if (count >= 5)
                return(board[h][k]);
        }
    }

    count = 0;
    for (int k = row; k >= 4; k--) {
        for (int h = column - 1; h >= 0; h--) {
            int i, j;
            for (i = k, j = h; j >= 4 && i >= 0; i--, j--) {
                if (board[h][k] == board[j][i])
                    count++;
                else
                    count = 0;
            }
            if (count >= 5)
                return(board[h][k]);
        }
    }

    return(' ');
}

void playGameWithComputer()
{
    clearScrean();
    printf("Please choose your nut 'X' or 'O' (Please enter the capital letter) : ");
    scanf_s("%c", &Player);
    clearScrean();
    printf("Please enter row #(6-10) and column #(6-10) : ");
    scanf_s("%d %d", &row, &column);
    clearScrean();

    char winner = ' ';
    resetBord();

    while (winner == ' ' && chackFreeSpace != 0) {
        printboard();

        putNut();
        winner = checkWinner();
        if (winner != ' ' || chackFreeSpace == 0) 
            break;

        computerMove();
        winner = checkWinner();
        if (winner != ' ' || chackFreeSpace == 0)
            break;

        clearScrean();
    }

    clearScrean();
    printboard();
    printf("\n");
    printWinner(winner);

    return;
}

void easyComputerMove()
{
    if (Player == 'X')
        Coumputer = 'O';
    else
        Coumputer = 'X';

    srand(time_t(0));

    int j, k;
    if (chackFreeSpace() > 0) {
        do
        {
            do {
                k = rand() % 6;
            } while (k >= column);

            j = full[k];
        } while (board[k][j] != ' ' || board[k][j] == Player || j > row - 1);

        board[k][j] = Coumputer;
        full[k]++;

    }
    else
        printWinner(' ');

    return;
}

void easyPlayGameWithComputer()
{
    clearScrean();
    printf("Please choose your nut 'X' or 'O' (Please enter the capital letter) : ");
    scanf_s("%c", &Player);
    clearScrean();

    row = 6;
    column = 6;

    char winner = ' ';
    resetBord();

    while (winner == ' ' && chackFreeSpace != 0) {
        printboard();

        putNut();
        winner = checkWinner();
        if (winner != ' ' || chackFreeSpace == 0)
            break;

        easyComputerMove();
        winner = checkWinner();
        if (winner != ' ' || chackFreeSpace == 0)
            break;

        clearScrean();
    }

    clearScrean();
    printboard();
    printf("\n");
    printWinner(winner);

    return;
}

void putNormalNutPlayer(char c)
{
    int k = 0;
    int j;
    do {
        k = moveInGrand(k);
        j = full[k];
    } while (j >= row);

    board[k][j] = c;
    full[k]++;

    clearScrean();
    printboard();
}

void hardPlayer()
{
    printf("YOUR TURN!!\n");
    
    if (bombP1 > 0 || bombP2 > 0) {
        if (bombP1 > 0 && bombP2 > 0) {
            printf("Choose your nut #(1-3):\n");
            printf("1. Normal nut\t2. %i Bomb 1\t3. %i Bomb 2", bombP1, bombP2);
        }
        else if (bombP1 == 0 && bombP2 > 0) {
            printf("Choose your nut #(1-3):\n");
            printf("1. Normal nut\t2. Your Bomb Type 1 is Over!!\t3. %i Bomb 2", bombP2);
        }
        else if (bombP1 > 0 && bombP2 == 0) {
            printf("Choose your nut #(1-3):\n");
            printf("1. Normal nut\t2. %i Bomb 1\t3. Your Bomb Type 2 is Over!!", bombP1);
        }
        
        char b = _getch();

        int i;

        switch (b)
        {
        case('1'):
            putNormalNutPlayer(Player);
            break;
        case('2'):
            i = 0;
            putBombOne(i);
            clearScrean();
            printboard();
            break;
        case('3'):
            i = 0;
            putBombTwo(i);
            clearScrean();
            printboard();
            break;
        }
    }
    else {
        printf("Your Bomb is over!!\n");
        printf("You can just use the Normal Nut");
        putNormalNutPlayer(Player);
    }

    return;
}

void putNormalNutComputer(char c)
{
    int j, k;
    if (chackFreeSpace() > 0) {
        do
        {
            do {
                k = rand() % column;
            } while (k >= column);

            j = full[k];
        } while (board[k][j] != ' ' || board[k][j] == Player || j > row - 1);

        board[k][j] = Coumputer;
        full[k]++;

    }
    else
        printWinner(' ');

    return;
}

void hardComputerMove()
{
    if (Player == 'X')
        Coumputer = 'O';
    else
        Coumputer = 'X';

    srand(time_t(0));

    int cmp = rand() % 10;
    int i = 0;
    if (cmp % 3 == 0)
        putBombTwo(i);
    else if (cmp % 2 == 0)
        putBombOne(i);
    else
        putNormalNutComputer(Coumputer);

    return;
}

void hardPlayGameWithComputer()
{
    clearScrean();
    printf("Please choose your nut 'X' or 'O' (Please enter the capital letter) : ");
    scanf_s("%c", &Player);
    clearScrean();
    printf("Please enter rows #(6-10) and columns #(6-10) : ");
    scanf_s("%d %d", &row, &column);
    clearScrean();

    char winner = ' ';
    resetBord();

    while (winner == ' ' && chackFreeSpace != 0) {
        printboard();

        hardPlayer();
        winner = checkWinner();
        if (winner != ' ' || chackFreeSpace == 0)
            break;

        hardComputerMove();
        winner = checkWinner();
        if (winner != ' ' || chackFreeSpace == 0)
            break;

        clearScrean();
    }

    clearScrean();
    printboard();
    printf("\n");
    printWinner(winner);

    return;
}

void Player1()
{
    printf("%s\n", name1);

    int k = 0;
    int j;
    do {
        k = moveInGrand(k);
        j = full[k];
    } while (j >= row);

    board[k][j] = x;
    full[k]++;

    clearScrean();
    printboard();

    return;
}

void Player2()
{
    printf("%s\n", name2);

    if (x == 'X')
        y = 'O';
    else
        y = 'X';

    int k = 0;
    int j;
    do {
        k = moveInGrand(k);
        j = full[k];
    } while (j >= row);

    board[k][j] = y;
    full[k]++;
    clearScrean();
    printboard();

    return;
}

void printWin(char winner)
{
    if (winner == x)
        printf("%s WIN  :) //// %s LOSE :( ", name1, name2);
    else if (winner == y)
        printf("%s WIN :) //// %s LOSE :( ", name2, name1);
    else
        printf("YOU ARE EQUAL!!  :|");

    return;
}

void multiPlayer()
{
    clearScrean();
    printf("Please enter the first player's name : \n");
    gets_s(name1);
    printf("Please enter the second player's name : \n");
    gets_s(name2);
    clearScrean();
    printf("%s please choose'X' or 'O' (enter the capital letter) ? ", name1);
    scanf_s("%c", & x);
    clearScrean();
    printf("Please enter row #(6-10) and column #(6-10) : ");
    scanf_s("%d %d", &row, &column);
    clearScrean();

    char winner = ' ';
    resetBord();

    while (winner == ' ' && chackFreeSpace != 0) {
        printboard();

        Player1();
        winner = checkWinner();
        if (winner != ' ' || chackFreeSpace == 0)
            break;

        Player2();
        winner = checkWinner();
        if (winner != ' ' || chackFreeSpace == 0)
            break;

        clearScrean();
    }

    clearScrean();
    printboard();
    printf("\n");
    printWin(winner);

    return;
}

void easyMultiplayer()
{
    clearScrean();
    printf("Please enter the first player's name : \n");
    gets_s(name1);
    printf("Please enter the second player's name : \n");
    gets_s(name2);
    clearScrean();
    printf("%s please choose'X' or 'O' (enter the capital letter) ? ", name1);
    scanf_s("%c", &x);
    clearScrean();

    row = 6;
    column = 6;

    char winner = ' ';
    resetBord();

    while (winner == ' ' && chackFreeSpace != 0) {
        printboard();

        Player1();
        winner = checkWinner();
        if (winner != ' ' || chackFreeSpace == 0)
            break;

        Player2();
        winner = checkWinner();
        if (winner != ' ' || chackFreeSpace == 0)
            break;

        clearScrean();
    }

    clearScrean();
    printboard();
    printf("\n");
    printWin(winner);

    return;
}

void putNormalNut(char c)
{
    int k = 0;
    int j;
    do {
        k = moveInGrand(k);
        j = full[k];
    } while (j >= row);

    board[k][j] = c;
    full[k]++;

    clearScrean();
    printboard();

    return;
}

void hardPlayer1()
{
    printf("%s\n", name1);

    if (bomb11 > 0 || bomb12 > 0) {
        if (bomb11 > 0 && bomb12 > 0) {
            printf("Choose your nut :\n");
            printf("1. Noramal nut\t2. Bomb 1 %d\t3. Bomb 2 %d", bomb11, bomb12);
        }
        else if (bomb11 == 0 && bomb12 > 0) {
            printf("Choose your nut :\n");
            printf("1. Noramal nut\t2. Your Bomb Type 1 is Over!!\t3. %i Bomb 2", bomb12);
        }
        else if (bomb11 > 0 && bomb12 == 0) {
            printf("Choose your nut :\n");
            printf("1. Noramal nut\t2. %i Bomb 1\t3. Your Bomb is Over!!", bomb11);
        }
        char b = _getch();

        int i;

        switch (b)
        {
        case('1'):
            putNormalNut(x);
            break;
        case('2'):
            i = 0;
            putBombOne(i);
            clearScrean();
            printboard();
            bomb11--;
            break;
        case('3'):
            i = 0;
            putBombTwo(i);
            clearScrean();
            printboard();
            bomb12--;
            break;
        }
    }
    else {
        printf("Your Bomb is over!!\n");
        printf("You can just use the Normal Nut");
        putNormalNut(x);
    }

    return;
}

void hardPlayer2()
{
    printf("%s\n", name2);

    if (x == 'X')
        y = 'O';
    else
        y = 'X';

    if (bomb21 > 0 || bomb22 > 0) {
        if (bomb21 > 0 && bomb22 > 0) {
            printf("Choose your nut :\n");
            printf("1. Normal nut\t2. %i Bomb 1\t3. %i Bomb 2", bomb21, bomb22);
        }
        else if (bomb21 == 0 && bomb22 > 0) {
            printf("Choose your nut :\n");
            printf("1. Noramal nut\t2. Your Bomb Type 1 is Over!!\t3. Bomb 2 %d", bomb22);
        }
        else if (bomb21 > 0 && bomb22 == 0) {
            printf("Choose your nut :\n");
            printf("1. Noramal nut\t2. Bomb 1 %d\t3. Your Bomb is Over!!", bomb21);
        }
       
        char b = _getch();

        int i;

        switch (b)
        {
        case('1'):
            putNormalNut(y);
            break;
        case('2'):
            i = 0;
            putBombOne(i);
            clearScrean();
            printboard();
            bomb21--;
            break;
        case('3'):
            i = 0;
            putBombTwo(i);
            clearScrean();
            printboard();
            bomb22--;
            break;
        }
    }
    else {
        printf("Your Bomb is over!!\n");
        printf("You can just use the Normal Nut");
        putNormalNut(y);
    }

    return;
}

void hardMultiPlayer()
{
    clearScrean();
    printf("Please enter the first player's name : \n");
    gets_s(name1);
    printf("Please enter the second player's name : \n");
    gets_s(name2);
    clearScrean();
    printf("%s please choose'X' or 'O' (enter the capital letter) ? ", name1);
    scanf_s("%c", &x);
    clearScrean();
    printf("Please enter row #(6-10) and column #(6-10) : ");
    scanf_s("%d %d", &row, &column);
    clearScrean();

    char winner = ' ';
    resetBord();

    while (winner == ' ' && chackFreeSpace != 0) {
        printboard();

        hardPlayer1();
        winner = checkWinner();
        if (winner != ' ' || chackFreeSpace == 0)
            break;

        hardPlayer2();
        winner = checkWinner();
        if (winner != ' ' || chackFreeSpace == 0)
            break;

        clearScrean();
    }

    clearScrean();
    printboard();
    printf("\n");
    printWin(winner);

    return;
}

void gotoxy(int x, int y)
{
    COORD c;
    c.X = x, c.Y = y;
    SetConsoleCursorPosition(GetStdHandle( STD_OUTPUT_HANDLE ), c);

    return;
}

void clearScrean()
{
    system("cls");

    return;
}

void menu()
{
    printf("1. Play New Game\n");
    printf("2. Show the Playgrang\n");
    printf("3. How to Play?\n");
    printf("4. Rules\n");
    printf("5. About Us\n");
    printf("6. Exit the Game\n");

    return;
}

void typeComputerGame()
{
    printf("#(1-3)\n");
    printf("1. Easy\n");
    printf("2. Medium\n");
    printf("3. Hard\n");
    printf("4. Back to the Menu");

    char b = _getch();
    switch (b)
    {
        case('1'):
            easyPlayGameWithComputer();
            break;
        case('2'):
            playGameWithComputer();
            break;
        case('3'):
            hardPlayGameWithComputer();
            break;
        case('4'):
            clearScrean();
            menu();
            break;
    }

    return;
}

void typeMultiplay()
{
    printf("#(1-3)\n");
    printf("1. Easy\n");
    printf("2. Medium\n");
    printf("3. Hard\n");
    printf("4. Back to the Menu");

    char b = _getch();
    switch (b)
    {
        case('1'):
            easyMultiplayer();
            break;
        case('2'):
            multiPlayer();
            break;
        case('3'):
            hardMultiPlayer();
            break;
        case('4'):
            clearScrean();
            menu();
            break;
    }

    return;
}

void typeGamePlay()
{
    clearScrean();

    printf("1. Start New Game with Computer\n");
    printf("2. Start New Game multiplayer\n");
    printf("3. Back to the Menu");

    char b = _getch();

    switch (b)
    {
        case('1'):
            clearScrean();
            typeComputerGame();
            break;
        case('2'):
            clearScrean();
            typeMultiplay();
            break;
        case('3'):
            clearScrean();
            menu();
            break;
    }

    return;
}

void howToPlay()
{
    clearScrean();
    printf("-In the easy level you play the game in the 6 rows and in the 6 column.\n");
    printf("-In the medium level you can play a game in any row and in any column.Actully your rows or column must be between 6 to 10.\n");
    printf("-In the hard level besides the opion that be in the medium, each player have bomb.\n");
    printf("-You can press 'D' to move right on columns and 'A' to move left on columns.\n");
    printf("-By press enter on your keyboard your nut stay on your choosen column.\n");
    printf("-When you select the hard level, you must selet your nut, then you can move by 'D' or 'A' in the keyboard and by press enter your nut stay on the column or your bomb to act\n");
    printf("-You can close the application by press the '0' number on your keyboard.\n");

    char b;
    do {
        printf("\nIf You Want to Back to the Menu Please Enter '1'.");
        b = _getch();
        if (b != '1')
            printf("\nPlease Enter the Correct Number\n");
    } while (b != '1');
    clearScrean();
    menu();

    return;
}

void ruls()
{
    clearScrean();
    printf("You must creat 5 your nut next to each other in the row or in the column or in the diagonal to win the game.\n");

    char b;
    do {
        printf("\nIf You Want to Back to the Menu Please Enter '1'.");
        b = _getch();
        if (b != '1')
            printf("\nPlease Enter the Correct Number\n");
    } while (b != '1');
    clearScrean();
    menu();

    return;
}

void aboutUs()
{
    printf("Student : Parsa Ebahimi\n");
    printf("ID Number : 401440250\n");
    printf("Professor : Dr.Ramin Zarei Sabzevari\n");

    char b;
    do {
        printf("\nIf You Want to Back to the Menu Please Enter '1'.");
        b = _getch();
        if (b != '1')
            printf("\nPlease Enter the Correct Number\n");
    } while (b != '1');
    clearScrean();
    menu();

    return;
}

int main()
{
    menu();

    char a = _getch();
    int i;
    char c;

    while (a != '0') {
        switch (a) {
            case('1'):
                typeGamePlay();
                break;
            case('2'):
                clearScrean();
                do
                {
                    printf("Please enter row #(6-10) and column #(6-10) : ");
                    scanf_s("%d %d", &row, &column);

                    if (row > 10 || row < 6 && column > 10 || column < 6)
                        printf("\nPlease Enter the Correct Row and Column!!\n\n");
                    else if (column > 10 || column < 6)
                        printf("\nPlease Enter the Correct Column!!\n\n");
                    else if (row > 10 || row < 6)
                        printf("\nPleaase Enter the Correct Row\n\n");

                } while (row > 10 || row < 6 || column > 10 || column < 6);

                clearScrean();
                printboard();
                i = 0;
                moveInGrand(i);
                break;
            case('3'):
                howToPlay();
                break;
            case('4'):
                ruls();
                break;
            case('5'):
                clearScrean();
                aboutUs();
                break;
            case('6'):
                clearScrean();
                printf("You want to close the program ?\n0.Yes\t1.No");
                c = _getch();

                if (c == '0')
                    printf("\nPlease enter again '0'");
                else {
                    clearScrean();
                    menu();
                }

                break;
            default:
                clearScrean();
                printf("Please enter the correct number!!");
                char wrongMenu = _getch();
                clearScrean();
                menu();
                break;
        }

        a = _getch();
    }

    return 0;
}