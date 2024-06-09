#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>

void clrscr()
{
    system("cls");
}

void addStudent();
void studentRecord();
void searchStudent();
void deleteStudent(); // Corrected function name

struct student
{
    char first_name[20];
    char last_name[20];
    int roll_no;
    char Class[10];
    char vill[20];
    float per;
};

void main()
{
    int choice = 0; // Initialized choice to 0
    while (choice != 5)
    {
        printf("\t\t\t===STUDENT DATABASE MANAGEMENT SYSTEM ====");
        printf("\n\n\n\t\t\t\t  1. Add Student Record\n");
        printf("\t\t\t\t  2. View Student Records\n");
        printf("\t\t\t\t  3. Search Student\n");
        printf("\t\t\t\t  4. Delete Record\n");
        printf("\t\t\t\t  5. Exit\n");
        printf("\t\t\t\t  ----------------\n");
        printf("\t\t\t\t");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            clrscr();
            addStudent();
            clrscr();
            break;

        case 2:
            clrscr();
            studentRecord();
            printf("\t\t\t Press any key to exit\n");
            getch();
            clrscr();
            break;

        case 3:
            clrscr();
            searchStudent();
            printf("\t\t\t Press any key to exit\n");
            getch();
            clrscr();
            break;

        case 4:
            clrscr();
            deleteStudent();
            printf("\t\t\t Press any key to exit\n");
            getch();
            clrscr();
            break;
        }
    }
}

void addStudent()
{
    char another;
    FILE *fp;
    struct student info;

    do
    {
        clrscr();
        printf("\t\t\t\t ======Add Student info ====\n\n\n");
        fp = fopen("student_info.txt", "a");
        printf("\n\t\t Enter first name: ");
        scanf("%s", info.first_name);
        printf("\n\t\t Enter last name: ");
        scanf("%s", info.last_name);
        printf("\n\t\t Enter roll no: ");
        scanf("%d", &info.roll_no);
        printf("\n\t\t Enter class: ");
        scanf("%s", info.Class);
        printf("\n\t\t Enter address: ");
        scanf("%s", info.vill);
        printf("\n\t\t Enter percentage: ");
        scanf("%f", &info.per);
        printf("\n\t\t\t  ----------------\n");

        if (fp == NULL)
        {
            fprintf(stderr, "\t\t\t Can't open file\n");
        }
        else
        {
            printf("\t\t\t Record stored successfully\n");
        }

        fwrite(&info, sizeof(struct student), 1, fp);
        fclose(fp);

        printf("\t\t\t Do you want to add another record? (y/n): ");
        scanf(" %c", &another); // Added space before %c to consume newline character

    } while (another == 'y' || another == 'Y');
}

void studentRecord()
{
    FILE *fp;
    struct student info;
    fp = fopen("student_info.txt", "r");
    printf("\t\t\t\t ====Student Records ====\n\n\n\n");

    if (fp == NULL)
    {
        fprintf(stderr, "\t\t\t\t Can't open file \n");
    }
    else
    {
        printf("\t\t\t\t Records \n");
        printf("\t\t\t\t =========\n\n");
    }
    while (fread(&info, sizeof(struct student), 1, fp))
    {
        printf("\n\t\t\t\t Student name: %s %s", info.first_name, info.last_name);
        printf("\n\t\t\t\t Roll no: %d", info.roll_no);
        printf("\n\t\t\t\t Class: %s", info.Class);
        printf("\n\t\t\t\t Address: %s", info.vill);
        printf("\n\t\t\t\t Percentage: %.2f", info.per); // Corrected percentage format
        printf("\n\t\t\t  ----------------\n");
    }

    fclose(fp);
    getch();
}

void searchStudent()
{
    FILE *fp;
    struct student info;
    int roll_no, found = 0;
    fp = fopen("student_info.txt", "r");
    printf("\t\t\t\t ====Search Student ====\n\n\n\n");
    printf("\t\t\t Enter roll no: ");
    scanf("%d", &roll_no);
    while (fread(&info, sizeof(struct student), 1, fp))
    {
        if (info.roll_no == roll_no)
        {
            found = 1;
            printf("\n\t\t\t\t Student name: %s %s", info.first_name, info.last_name);
            printf("\n\t\t\t\t Roll no: %d", info.roll_no);
            printf("\n\t\t\t\t Class: %s", info.Class);
            printf("\n\t\t\t\t Address: %s", info.vill);
            printf("\n\t\t\t\t Percentage: %.2f", info.per); // Corrected percentage format
            printf("\n\t\t\t  ----------------\n");
        }
    }

    if (!found)
    {
        printf("\n\t\t\t Record not found \n");
    }

    fclose(fp);
    getch();
}

void deleteStudent()
{
    FILE *fp, *fp1;
    struct student info;
    int roll_no, found = 0;
    printf("\t\t\t\t ====Delete Student ====\n\n\n\n");

    fp = fopen("student_info.txt", "r");
    fp1 = fopen("temp.txt", "w");
    printf("\t\tEnter roll no: ");
    scanf("%d", &roll_no);

    if (fp == NULL || fp1 == NULL)
    {
        fprintf(stderr, "\t\t\t\t Can't open file\n");
        return;
    }

    while (fread(&info, sizeof(struct student), 1, fp))
    {
        if (info.roll_no == roll_no)
        {
            found = 1;
        }
        else
        {
            fwrite(&info, sizeof(struct student), 1, fp1);
        }
    }

    fclose(fp);
    fclose(fp1);

    if (found)
    {
        remove("student_info.txt");
        rename("temp.txt", "student_info.txt");
        printf("\n\t\t\t Record deleted successfully");
    }
    else
    {
        printf("\n\t\t\t Record not found");
    }

    getch();
}
