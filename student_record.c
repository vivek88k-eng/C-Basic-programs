#include <stdio.h>
#include <stdlib.h>

struct Student {
    int roll;
    char name[50];
    float marks;
};

void addStudent(FILE *fp) {
    struct Student s;
    printf("\nEnter Roll Number: ");
    scanf("%d", &s.roll);
    printf("Enter Name: ");
    scanf(" %[^\n]", s.name);
    printf("Enter Marks: ");
    scanf("%f", &s.marks);

    fwrite(&s, sizeof(s), 1, fp);
    printf("Student added successfully!\n");
}

void displayStudents(FILE *fp) {
    struct Student s;
    rewind(fp);
    printf("\nList of Students:\n");
    while(fread(&s, sizeof(s), 1, fp)) {
        printf("Roll: %d, Name: %s, Marks: %.2f\n", s.roll, s.name, s.marks);
    }
}

void searchStudent(FILE *fp) {
    struct Student s;
    int roll, found = 0;
    printf("\nEnter Roll Number to Search: ");
    scanf("%d", &roll);
    rewind(fp);
    while(fread(&s, sizeof(s), 1, fp)) {
        if (s.roll == roll) {
            printf("Found: Roll: %d, Name: %s, Marks: %.2f\n", s.roll, s.name, s.marks);
            found = 1;
            break;
        }
    }
    if (!found) {
        printf("Student not found.\n");
    }
}

int main() {
    FILE *fp = fopen("students.dat", "ab+");
    if (fp == NULL) {
        printf("Error opening file!\n");
        return 1;
    }

    int choice;
    do {
        printf("\n===== Student Record System =====\n");
        printf("1. Add Student\n");
        printf("2. Display All Students\n");
        printf("3. Search Student\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1: addStudent(fp); break;
            case 2: displayStudents(fp); break;
            case 3: searchStudent(fp); break;
            case 0: printf("Exiting...\n"); break;
            default: printf("Invalid choice!\n");
        }
    } while(choice != 0);

    fclose(fp);
    return 0;
}
