#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define Max_Name_Chars 20
#define Max_Accounts 100

char Name_Array[Max_Accounts][Max_Name_Chars];
int Money_Array[Max_Accounts];
int NumberOfElements ;

void getDatabasesData (FILE* Name_Database , FILE* Money_Database);
int getPlayerIndexFromName(char Name [Max_Name_Chars]);
void edit_score (char Name [Max_Name_Chars] , int Money );
void saveDataBase(FILE* Name_Database , FILE* Money_Database);
int show_record(char Name [Max_Name_Chars]);
void show_score();
void reset_score();
void Help();

int main()
{
    FILE* Name_Database = fopen("Name_Database.txt", "a+");
    FILE* Money_Database = fopen("Money_Database.txt", "a+");

    getDatabasesData(Name_Database, Money_Database);

    const char * Questions[][2] = {
        {"The scanfstandard library function displays information on the screen","f"},
        {"Every C program begins execution at the function main.","t"},
        {"(X =+ 1) is C statements that add 1 to integer variable x","f"},
        {"The whilerepetition statement specifies that a statement or group of statements is to be executed repeatedly while some condition remains true","t"},
        {"The forstatement is used to make decisions","f"},
        {"The escape sequence \trepresents thenewline character, which causes the cursorto position to the beginning of the next line on the screen","f"},
        {"All variables must be given a type when they’re defined","t"},
        {"A variable that is known only within the function in which it’s defined is called a global variable","f"},
        {"A function prototype declares the return type of the function and declares the number, the types, and order of the parameters the function expects to receive.","t"},
        {"Keywords externand staticare used to declare identifiers for variables and functions of static storage duration.","t"},
    };

    char User_Command ;
    char User_Name[Max_Name_Chars];

    while(1)
    {
        printf("\n          C Program Quiz          \n");
        printf("__________________________________\n");
        printf("             Welcome              \n");
        printf("               to                 \n");
        printf("            The Game              \n");
        printf("__________________________________\n");
        printf("__________________________________\n");
        printf("        BECOME A MILLIONAIRE      \n");
        printf("__________________________________\n");
        printf("__________________________________\n");
        printf(" > Press S to start the game      \n");
        printf(" > Press U to view the highest score\n");
        printf(" > Press R to Reset score         \n");
        printf(" > Press H to for help            \n");
        printf(" > Press Q to quit game           \n");
        printf("__________________________________\n");

        scanf(" %c",&User_Command);
        if (User_Command == 'S' || User_Command == 's' ) { // Start Game
            // Take the user name
            printf("Enter your name...\n");
            scanf(" %s",&User_Name);

            // The second welcome screen with the rules:
            Help();
            printf("Press Y to start the game !\n");
            printf("Press Any key to return the main menu !\n");
            scanf(" %c",&User_Command);
            if (User_Command == 'Y' || User_Command == 'y') // Start the game
            {
                int Questions_Index = 0;
                int TotalWrong = 0;
                int TotalMoney = 0;
                printf("Please answer the following questions to win cash prize (up to $1 million)\n");
                printf("Please state if True or False:\n");
                while (Questions_Index < 10)
                {
                    printf("%d) %s\n",Questions_Index+1,Questions[Questions_Index][0]);
                    printf("Your answer is ");
                    scanf(" %c",&User_Command);


                    char Answer = Questions[Questions_Index][1][0];
                    if (Answer != User_Command)
                    {
                        TotalWrong++;
                        printf("\n***Wrong Answer\n");
                    } else {
                        TotalMoney += 100000;
                        printf("\n***Correct Answer\n");
                    }


                    if (Questions_Index == 2)
                    {
                        if (TotalWrong >= 2)
                        {
                            printf("SORRY YOUR NOT ELIGIBLE TO PLAY THIS GAME, BETTER LUCK NEXT TIME \n");
                            break;
                        } else {
                            printf("*** Congratulations sf you are eligible to play the game ***\n");
                            printf("Press any key to start the game\n");
                            scanf(" %c",&User_Command);
                        }
                    }
                    Questions_Index++;
                }

                if (Questions_Index == 10)
                {
                    printf("\n********** CONGRATULATIONS **********\n");
                    printf("YOU WON $%d \n\n",TotalMoney);
                    edit_score(User_Name,TotalMoney+show_record(User_Name));
                }
            }
        } else if (User_Command == 'U' || User_Command == 'u') { // View highest score
            show_score();
        } else if (User_Command == 'R' || User_Command == 'r') { // Reset Score
            reset_score();
        } else if (User_Command == 'H' || User_Command == 'h') { // Help show rules
            Help();
        } else if (User_Command == 'Q' || User_Command == 'q') { // Quit game
            break;
        }
    }

    saveDataBase(Name_Database,Money_Database);
    return 0;
}

void getDatabasesData (FILE* Name_Database , FILE* Money_Database)
{
    NumberOfElements = 0;
    // Add to Name_Array
    while(fgets(Name_Array[NumberOfElements], Max_Accounts, Name_Database)) {
        Name_Array[NumberOfElements][strlen(Name_Array[NumberOfElements]) - 1] = '\0';
        NumberOfElements++;
    }

    // Add to Money_Array
    for (int i = 0; i < NumberOfElements; i++)
    {
        fscanf(Money_Database, "%d,", &Money_Array[i] );
    }
}

int getPlayerIndexFromName(char Name [Max_Name_Chars])
{
    for (int i = 0 ; i < NumberOfElements ; i++)
    {
        if (strcmp(Name_Array[i],Name) == 0)
        {
            return i;
        }
    }
    return -1;
}

int show_record(char Name [Max_Name_Chars])
{
    for (int i = 0 ; i < NumberOfElements ; i++)
    {
        if (strcmp(Name_Array[i],Name) == 0)
        {
            return Money_Array[i];
        }
    }
    return 0;
}

void edit_score (char Name [Max_Name_Chars] , int Money )
{
    int Database_Player_Index = getPlayerIndexFromName(Name);
    if (Database_Player_Index == -1)
    {
        strcpy(Name_Array[NumberOfElements],Name);
        Money_Array[NumberOfElements] = Money;
        NumberOfElements++;
    } else {
        Money_Array[Database_Player_Index] = Money;
    }
}

void saveDataBase(FILE* Name_Database , FILE* Money_Database)
{
    fclose(Name_Database);
    fclose(Money_Database);

    remove("Name_Database.txt");
    remove("Money_Database.txt");

    Name_Database = fopen("Name_Database.txt", "a+");
    Money_Database = fopen("Money_Database.txt", "a+");

    for (int i = 0 ; i < NumberOfElements ; i++)
    {
        fprintf(Name_Database,"%s\n",Name_Array[i]);
        fprintf(Money_Database,"%d ",Money_Array[i]);
    }

    fclose(Name_Database);
    fclose(Money_Database);
}

void show_score()
{
    int Best_Score = -1 ;
    char Best_Score_Name[Max_Name_Chars] = "None";
    for (int i = 0 ; i < NumberOfElements ; i++)
    {
        if (Money_Array[i] > Best_Score)
        {
            Best_Score = Money_Array[i];
            strcpy(Best_Score_Name,Name_Array[i]);
        }
    }
    printf("\n**********************************\n");
    printf("%s has secured the Highest score %d\n",Best_Score_Name,Best_Score);
    printf("**********************************\n");
}

void reset_score()
{
    int Best_Score = -1 ;
    char Best_Score_Name[Max_Name_Chars] = "None";
    int Best_Score_Index = -1;
    for (int i = 0 ; i < NumberOfElements ; i++)
    {
        if (Money_Array[i] > Best_Score)
        {
            Best_Score = Money_Array[i];
            strcpy(Best_Score_Name,Name_Array[i]);
            Best_Score_Index = i;
        }
    }
    if (Best_Score_Index != -1)
    {
        Money_Array[Best_Score_Index] = 0;
        printf("\n**********************************\n");
        printf("%s score had been rested which was %d\n",Best_Score_Name,Best_Score);
        printf("**********************************\n");
    } else {
        printf("\n**********************************\n");
        printf("There is no score at database in order to reset!!\n");
        printf("**********************************\n");
    }
}

void Help()
{
    printf("\n-----------------Welcome to C program Quiz----------------------\n");
    printf("Here are some tips you might wanna knowbefor playing:\n");
    printf("----------------------------------------------------------------\n");
    printf("There are 2 rounds in this quiz game, WARM-UP round & CHALLANGE round.\n");
    printf("In warm-up round you will be asked a total of 3 question to test your general knowledge.\n");
    printf("You are eligible to play the game if you give atleast 2 right answers, Otherwise you can't proceed further to the challenge round.\n");
    printf("your game starts with challange round.\n In this round you will ask total of 10 questions. Each right answer will be awarded 100,000$!!\n");
    printf("By this way you can win up to ONE MILLION cash prize.!!\n");
    printf("You will be asked questions continuously, till right answers are given, No negative marking for wrong answers\n");
    printf("!!!!!ALL THE BEST!!!!\n");
}
