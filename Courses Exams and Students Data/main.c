#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define Max_Courses 50
#define Max_Students 50

int Number_Courses = 0 ;
int Number_Students = 0;

struct Courses {
    int ID;
    char Date[20];
    char Hall;
    int Number_Students;
    int Students_ID[Max_Students];
};

struct Students {
    int ID;
    int CoursesID[Max_Courses];
    int Number_Courses ;
};

struct Courses Course[Max_Courses]; // Making array of Struct Courses
struct Students Student[Max_Students]; // Making array of Struct Students

void fillStuctures (char CoursesExams[500] , char StudentsText[1000]); // fill the Stuctures of Courses and Students with given strings
int Number_Halls (); // return number of halls
int Student_ID_Min (); // return min student ID
int Student_ID_Max (); // return max student ID
int Exams_Period_InDays(); // return number of days of exams
int isIDAvailable(int ID); // return 1 if ID is available otherwise return 0
void Course_Students (int Course_ID,int * Students_ID , int * Number_Students_In_Course ); // edit array and fill it with students ID that take a certain course
void List_Course_Students_More (int Number , int * Courses_ID , int * Number_Courses_More ); // edit array and fill it with students ID have course more than certain number
void List_Student_Courses_Less (int Number , int * Students_ID , int * Number_Students_Less ); //edit array and fill it with Courses ID have students less than certain number
void List_Hall_Students (char ExamHall , char ExamDate[]  , int * Student_ID , int * Number_Students_At ); //edit array and fill it with students ID that have exam at a given hall and date
void List_Hall_Students_InAnyday (char ExamHall ,int * Student_ID , int * Number_Students_At ); // edit array and fill it with students id that have exam at given all at any day

int main()
{
    // Reading data from file called Data.txt and put it's first line at CoursesExams and copy second line and place it at StudentText

    char CoursesExams[500]; //= "CoursesExams=[101,28/4/2016,A;201,3/5/2016,A;110,5/5/2016,C;103,5/5/2016,A;120,6/5/2016,D;132,7/5/2016,B]";
    char StudentsText[1000] ; //= "Students=[191001,(201,101,110);191002,(201,110,103);191003,(110,120,132);191006,(103,132)]";

    FILE* coursesAndStudentsFile = fopen("Data.txt", "a+");

    fscanf(coursesAndStudentsFile, "%s %s", &CoursesExams , &StudentsText );

    fclose(coursesAndStudentsFile);

    // fillStuctures the function which is filter the two string and place it at both Structs ( Courses , Students )
    fillStuctures(CoursesExams,StudentsText);

    char Command_Operations[100];

    while (1)
    {
        printf("Enter Operation : ");
        scanf(" %s",Command_Operations);

        if (strcmp(Command_Operations,"Number_Students") == 0) { // 1 Operation

            printf("%d\n",Number_Students);

        } else if (strcmp(Command_Operations,"Number_Halls") == 0 ) { // 2 Operation

            printf("%d\n",Number_Halls());

        } else if (strcmp(Command_Operations,"Student_ID_Min")== 0) { // 3 Operation

            printf("%d\n",Student_ID_Min());

        } else if (strcmp(Command_Operations,"Students_Dropped_ID")== 0) { // 4 Operation
            int Min = Student_ID_Min(); // Smallest ID
            int Max = Student_ID_Max(); // Biggest ID
            // Loop throw them and check if the numbers between them was in the struct of students
            for (int i = Min ; i < Max ;i++)
            {
                if (isIDAvailable(i) == 0 )
                {
                    printf("%d\n",i);
                }
            }

        } else if (strcmp(Command_Operations,"Exams_Period_InDays")== 0) { // 5 Operation

            printf("%d\n",Exams_Period_InDays());

        } else if (strcmp(Command_Operations,"Course_Students")== 0) { // 6 Operation
            // Making empty array to make it fill it with the called function
            int CourseCode; scanf("%d",&CourseCode);
            int Students_ID[Max_Students] , Number_Students_In_Course;
            Course_Students(CourseCode,Students_ID,&Number_Students_In_Course);
            if (Students_ID[0] == -1)
            {
                printf("None\n");
            } else {
                for (int i = 0 ; i < Number_Students_In_Course ;i++)
                {
                    printf("%d\n",Students_ID[i]);
                }
            }


        } else if (strcmp(Command_Operations,"List_Course_Students_More")== 0) { // 7 Operation
            // Making empty array to make it fill it with the called function
            int Number; scanf("%d",&Number);
            int Courses_ID[Max_Students] , Number_Courses_More;
            List_Course_Students_More(Number,Courses_ID,&Number_Courses_More);

            if (Courses_ID[0] == -1)
            {
                printf("None\n");
            } else {
                for (int i = 0 ; i < Number_Courses_More ;i++)
                {
                    printf("%d\n",Courses_ID[i]);
                }
            }

        } else if (strcmp(Command_Operations,"List_Student_Courses_Less")== 0) { // 8 Operation
            // Making empty array to make it fill it with the called function
            int Number; scanf("%d",&Number);
            int Students_ID[Max_Students] , Number_Students_Less;
            List_Student_Courses_Less(Number,Students_ID,&Number_Students_Less);

            if (Students_ID[0] == -1)
            {
                printf("None\n");
            } else {
                for (int i = 0 ; i < Number_Students_Less ;i++)
                {
                    printf("%d\n",Students_ID[i]);
                }
            }

        } else if (strcmp(Command_Operations,"List_Hall_Students")== 0) { //9 Operation
            // Making empty array to make it fill it with the called function
            char ExamHall , ExamDate[Max_Courses] ; scanf(" %s %s",&ExamHall,&ExamDate);
            int Students_ID[Max_Students] , Number_Students_At;
            List_Hall_Students(ExamHall,ExamDate,Students_ID,&Number_Students_At);

            if (Students_ID[0] == -1)
            {
                printf("None\n");
            } else {
                for (int i = 0 ; i < Number_Students_At ;i++)
                {
                    printf("%d\n",Students_ID[i]);
                }
            }


        } else if (strcmp(Command_Operations,"List_Hall_Students_InAnyday")== 0) { // 10 Operation
            // Making empty array to make it fill it with the called function
            char ExamHall ; scanf(" %c",&ExamHall);
            int Students_ID[Max_Students] , Number_Students_At;
            List_Hall_Students_InAnyday(ExamHall,Students_ID,&Number_Students_At);

            if (Students_ID[0] == -1)
            {
                printf("None\n");
            } else {
                for (int i = 0 ; i < Number_Students_At ;i++)
                {
                    printf("%d\n",Students_ID[i]);
                }
            }

        } else if (strcmp(Command_Operations,"Quit")== 0) { // 11 Operation
            printf("Thanks!");
            break; // Break loop to end the program
        } else {
            printf("\n");
        }
    }

    return 0;
}

void fillStuctures (char CoursesExams[500] , char StudentsText[1000])
{
    int Start = 0;
    int Datatype_Num = 0; // 0 = Id , 1 = Date , 2 = Hall
    char CollectedChars[1000];
    int CollectedCharIndex = 0 ;
    // loop through each char at CoursesExams
    for (int i = 0 ; CoursesExams[i] ;i++)
    {
        // Once char is equal to '[' means the filter could start now
        if (CoursesExams[i] == '[')
        {
            Start = 1;
            continue;
        // Once char is equal to ']' means the filter should end now
        } else if (CoursesExams[i] == ']') {
            // Placeing last char at Struct hall
            Course[Number_Courses].Hall = CoursesExams[i-1];
            Number_Courses++;
            break;
        }
        if (Start)
        {
            // Char ',' means end of collected a part from data
            if (CoursesExams[i] == ',')
            {
                // ending each collection of data with \0 so string dosen't have junk values
                CollectedChars[CollectedCharIndex] = '\0';

                // Collected ID
                if (Datatype_Num == 0)
                {
                    Course[Number_Courses].ID = atoi(CollectedChars);
                    Datatype_Num = 1;
                // Collected Date
                } else if (Datatype_Num == 1) {
                    strcpy(Course[Number_Courses].Date,CollectedChars);
                    Datatype_Num = 2;
                }
                // Reset the value of array of chars and reset value of CollectedCharIndex
                memset(CollectedChars,0,sizeof(CollectedChars));
                CollectedCharIndex = 0;

            } else if (CoursesExams[i] == ';') {
                // Char ; Means end of course data so last char should be the course exam hall
                Course[Number_Courses].Hall = CoursesExams[i-1];
                Datatype_Num = 0 ;
                Number_Courses++;
            } else if (Datatype_Num < 2) {
                // Collected chars and place it at CollectedChar array of chars in order to extract it's data in above statments
                CollectedChars[CollectedCharIndex] = CoursesExams[i];
                CollectedCharIndex++;
            }
        }
    }

    Start = 0;
    Datatype_Num = 0; // 0 = Id , 1 = Courses
    CollectedCharIndex = 0 ;
    memset(CollectedChars,0,sizeof(CollectedChars));
    int TotalCoursesPerStudent;
    // loop through each char at StudentsText
    for (int i = 0 ; StudentsText[i] ;i++)
    {
        // Once char is equal to '[' means the filter could start now
        if (StudentsText[i] == '[')
        {
            Start = 1;
            Datatype_Num = 0;
            TotalCoursesPerStudent = 0;
            continue;

        }
        if (Start)
        {
            // If previous chat was ',' and current one is '(' that's means that start of courses id of the student
            if ( (StudentsText[i] == ',') || StudentsText[i] == ';' || StudentsText[i] == ']' )
            {
                // ending each collection of data with \0 so string dosen't have junk values
                CollectedChars[CollectedCharIndex] = '\0';
                // Datatype_Num equal 0 means the collected was ID number
                if (Datatype_Num == 0)
                {
                    Student[Number_Students].ID = atoi(CollectedChars);
                    Datatype_Num = 1;
                // Datatype_Num equal 1 means the collected course ID
                } else if (Datatype_Num == 1) {
                    Student[Number_Students].CoursesID[TotalCoursesPerStudent] = atoi(CollectedChars);
                    TotalCoursesPerStudent++;
                    Student[Number_Students].Number_Courses = TotalCoursesPerStudent;
                }
                // Reset the value of array of chars and reset value of CollectedCharIndex
                CollectedCharIndex = 0;
                memset(CollectedChars,0,sizeof(CollectedChars));
                // Char ; Means end of student data
                if (StudentsText[i] == ';')
                {
                    Datatype_Num = 0 ;
                    Number_Students++;
                    TotalCoursesPerStudent = 0 ;
                 // Once char is equal to ']' means the filter should end now
                } else if (StudentsText[i] == ']') {
                    Number_Students++;
                    break;
                }
            } else {
                // Collected chars and place it at CollectedChar array of chars in order to extract it's data in above statments
                CollectedChars[CollectedCharIndex] = StudentsText[i];
                CollectedCharIndex++;
            }
        }
    }

    int counter;
    // Loop through number of courses
    for (int i = 0 ; i < Number_Courses ; i++)
    {
        counter = 0;
        // Loop through number of students
        for (int j = 0 ; j < Number_Students ;j++)
        {
            // Loop through number of courses that each student have
            for (int k = 0 ; k < Student[j].Number_Courses ; k++)
            {
                // check if Student have course id as the current course loop run (i)
                if ( Student[j].CoursesID[k] == Course[i].ID )
                {
                    // Add student Id at array at struct Course which knowen as Students_ID
                    Course[i].Students_ID[counter] = Student[j].ID ;
                    counter++;
                    // Set Number_Students at course with number of students at this course
                    Course[i].Number_Students = counter ;
                }
            }
        }
    }
}


int Number_Halls ()
{
    char HallsArray[Max_Courses];
    int counter = 0 ;
    int flag;
    // loop through number of courses
    for (int i = 0 ; i < Number_Courses ; i++)
    {
        flag = 0;
        // counter means number of elements in HallsArray
        for (int j = 0 ; j < counter ; j++)
        {
            // Check if Course hall was at Array before so we don't duplicate adding same hall twice
            if (Course[i].Hall == HallsArray[j])
            {
                flag = 1;
                break;
            }
        }
        // Flag equal 0 means the current course hall was not placed at the array before
        if (flag == 0)
        {
            // Add hall to array
            HallsArray[counter] = Course[i].Hall;
            counter++;
        }
    }
    return counter;
}

int Student_ID_Min ()
{
    int Lowest = Student[0].ID;
    // Loop through number of students
    for (int i = 0 ; i < Number_Students ; i++)
    {
        // check if current element have less id number than the lowest then we replace the lowest value with the current one
        if (Student[i].ID < Lowest)
        {
            Lowest = Student[i].ID;
        }
    }
    return Lowest;
}

int Student_ID_Max ()
{
    int Max = Student[0].ID;
    // Loop through number of students
    for (int i = 0 ; i < Number_Students ; i++)
    {
        // check if current element have more id number than the max one then we replace the max value with the current one
        if (Student[i].ID > Max)
        {
            Max = Student[i].ID;
        }
    }
    return Max;
}

int Exams_Period_InDays ()
{
    int MinDay = -1,MinMonth = -1 ;
    int MaxDay = -1,MaxMonth = -1 ;
    int DataType ; // 0 = Day , 1 = Month
    char CollectedChars[1000];
    int CollectedCharIndex;
    int CurrentDay, CurrentMonth;
    // Loop through number of courses
    for (int i = 0 ; i < Number_Courses ; i++)
    {
        // Reset variable values
        DataType = 0 ;
        CollectedCharIndex = 0;
        memset(CollectedChars,0,sizeof(CollectedChars));
        // loop through date of each course char by char
        for (int j = 0 ; Course[i].Date[j] ; j++ )
        {
            if (Course[i].Date[j] == '/')
            {
                CollectedChars[CollectedCharIndex] = '\0';
                if (DataType == 1)
                {
                    CurrentMonth = atoi(CollectedChars);
                    break;
                } else if (DataType == 0) {
                    CurrentDay = atoi(CollectedChars);
                }
                CollectedCharIndex = 0;
                memset(CollectedChars,0,sizeof(CollectedChars));
                DataType++;
            } else {
                CollectedChars[CollectedCharIndex] = Course[i].Date[j];
                CollectedCharIndex++;
            }
        }

        // Check if MinDay has no value (-1) or MinDay is greatest than Current day and MinMonth greater than or equal CurrentMonth
        if (MinDay == -1 || ( ( MinDay > CurrentDay && MinMonth == CurrentMonth ) || MinMonth > CurrentMonth ) )
        {
            MinDay = CurrentDay;
            MinMonth = CurrentMonth;
        }
        // Check if MaxDay has no value (-1) or MaxDay is smaller than Current day and MaxDay greater less than CurrentMonth
        if (MaxDay == -1 || ( ( MaxDay < CurrentDay && MaxMonth == CurrentMonth ) || MaxMonth < CurrentMonth) )
        {
            MaxDay = CurrentDay;
            MaxMonth = CurrentMonth;
        }

    }
    // Same month means different calculation
    if (MinMonth == MaxMonth)
    {
        return (MaxDay-MinDay+1) ;
    } else  {
        return ( (30-MinDay) + MaxDay + 1 );
    }
}

int isIDAvailable(int ID)
{
    // Loop through number of students
    for (int i = 0 ; i < Number_Students ;i++)
    {
        // Check if given ID at struct of students
        if (Student[i].ID == ID)
        {
            return 1;
        }
    }
    return 0;
}

void Course_Students (int Course_ID,int * Students_ID , int * Number_Students_In_Course )
{
    Students_ID[0] = -1;
    // loop through number of courses
    for (int i = 0 ; i < Number_Courses ; i++)
    {
        // Check if course id is same as given ID
        if (Course[i].ID == Course_ID)
        {
            *Number_Students_In_Course = Course[i].Number_Students;
            // loop through students at this course
            for (int j = 0 ; j < *Number_Students_In_Course ; j++)
            {
                Students_ID[j] = Course[i].Students_ID[j];
            }
            break;
        }
    }
}

void List_Course_Students_More (int Number , int * Courses_ID , int * Number_Courses_More )
{
    Courses_ID[0] = -1;
    int counter = 0 ;
    // loop through number of courses
    for (int i = 0 ; i < Number_Courses ; i++)
    {
        // check if number of students in course is more than given number
        if (Course[i].Number_Students > Number)
        {
            Courses_ID[counter++] = Course[i].ID ;
        }
    }
    *Number_Courses_More = counter ;
}

void List_Student_Courses_Less (int Number , int * Students_ID , int * Number_Students_Less )
{
    Students_ID[0] = -1;
    int counter = 0 ;
    // loop through number of students
    for (int i = 0 ; i < Number_Students ; i++)
    {
        // Check if number of course that the student take is less than the given number;
        if (Student[i].Number_Courses < Number)
        {
            Students_ID[counter++] = Student[i].ID ;
        }
    }
    *Number_Students_Less = counter ;
}

void List_Hall_Students (char ExamHall , char ExamDate[]  , int * Student_ID , int * Number_Students_At )
{
    Student_ID[0] = -1;
    int counter = 0 ;
    // Loop through number of courses
    for (int i = 0 ; i < Number_Courses ; i++)
    {
        // Check if course hall is same as given hall and check if course date is same as given date
        if (Course[i].Hall == ExamHall && strcmp(Course[i].Date,ExamDate) == 0  )
        {
            // loop through course students id
            for (int j = 0 ; j < Course[i].Number_Students; j++)
            {
                // add student id to array
                Student_ID[counter++] = Course[i].Students_ID[j];
            }
        }
    }
    *Number_Students_At = counter ;
}

void List_Hall_Students_InAnyday (char ExamHall ,int * Student_ID , int * Number_Students_At )
{
    Student_ID[0] = -1;
    int counter = 0 ;
    int found ;
    // Loop through number of courses
    for (int i = 0 ; i < Number_Courses ; i++)
    {
        // Check if given hall is same as the current course hall
        if (Course[i].Hall == ExamHall)
        {
            // loop through students ID inside this course
            for (int j = 0 ; j < Course[i].Number_Students; j++)
            {
                found = 0 ;
                // Loop through counter which have number of elements in Student_ID
                for (int k = 0 ; k < counter ; k++ )
                {
                    // Check if student id was at array before in order to not duplicate
                    if (Student_ID[k] == Course[i].Students_ID[j])
                    {
                        found = 1;
                        break;
                    }
                }
                // if student id wasn't at Array before then we add it
                if (found == 0)
                    Student_ID[counter++] = Course[i].Students_ID[j];
            }
        }
    }
    *Number_Students_At = counter ;
}
