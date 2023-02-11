#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// all values of student
struct student {
    int roll_no;
    char name[100];
    char email[100];
};

void add_student(FILE *fp, int roll_no) {
    struct student s;

    //First value of student
    s.roll_no = roll_no;

    // second value of student
    printf("Enter student name: ");
    scanf("%s", s.name);

    // third value of student
    printf("Enter student email: ");
    scanf("%s", s.email);

    // writing in file
    fwrite(&s, sizeof(struct student), 1, fp);
    printf("Student added successfully.\n");
}

void read_student(FILE *fp, int roll_no) {
    struct student s;
    int found = 0;

    // set file pointer to beginning of file
    fseek(fp, 0, SEEK_SET);
    while (fread(&s, sizeof(struct student), 1, fp)) {
        if (s.roll_no == roll_no) {
            found = 1;
            break;
        }
    }

    if (found) 
    {
        printf("Name: %s\n", s.name);
        printf("Roll No.: %d\n", s.roll_no);
        printf("Email: %s\n", s.email);
    } else {
        printf("Student with roll number %d not found.\n", roll_no);
    }
}

void delete_student(FILE *fp, int roll_no) {
    struct student s;
    int found = 0;
    FILE *temp_fp;

    temp_fp = fopen("temp.bin", "wb");
    if (temp_fp == NULL) {
        printf("Error opening temporary file.\n");
        return;
    }

    // start from beginning of file
    fseek(fp, 0, SEEK_SET);
    while (fread(&s, sizeof(struct student), 1, fp)) {
        if (s.roll_no != roll_no) {
            fwrite(&s, sizeof(struct student), 1, temp_fp);
        } else {
            found = 1;
        }
    }

    fclose(fp);
    fclose(temp_fp);

    remove("students.bin");
    rename("temp.bin", "students.bin");

    if (found) {
        printf("Student with roll number %d deleted successfully.\n", roll_no);
    } else {
        printf("Student with roll number %d not found.\n", roll_no);
    }
}

int main(int argc, char *argv[])
{
    // option for user & roll_no is the primary key of student
    int option, roll_no;
    FILE *fp;

    // open file in binary read/write mode
    fp = fopen("students.bin", "ab+");
    if (fp == NULL) {
        printf("Error opening file.\n");
        return 1;
    }

    while (option != -1) {
        
    printf("1. Add student\n");
    printf("2. Read student\n");
    printf("3. Delete student\n");
    printf("4. Exit\n");
    printf("Enter your option: ");
    scanf("%d", &option);
        
    
        switch (option) {
            case 1:         // add student
                printf("Enter roll number: ");
                scanf("%d", &roll_no);
                add_student(fp, roll_no);
                break;
            case 2:         // read student database
                printf("Enter roll number: ");
                scanf("%d", &roll_no);
                read_student(fp, roll_no);
                break;
            case 3:         // delete student
                printf("Enter roll number: ");
                scanf("%d", &roll_no);
                delete_student(fp, roll_no);
                break;
            case 4:         // exit
                fclose(fp);
                option=-1;
                printf("\n----Exiting----\n");
                break;
                //exit(0);
            default:        // invalid option
                printf("Invalid option.\n");
        }
    }
    return 0;
}
