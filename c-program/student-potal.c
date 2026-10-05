#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// =========================================
// STUDENT STRUCTURE
// =========================================

struct Student {
    int id;
    char name[50];
    int age;
    char course[50];
    float marks;
    int totalClasses;
    int presentClasses;
};


// =========================================
// SAVE STUDENTS TO FILE
// =========================================

void saveStudents(struct Student students[], int n) {

    FILE *file = fopen("students.dat", "wb");

    if (file == NULL) {
        printf("\nError opening file!\n");
        return;
    }

    fwrite(&n, sizeof(int), 1, file);
    fwrite(students, sizeof(struct Student), n, file);

    fclose(file);

    printf("\nStudent records saved successfully!\n");
}


// =========================================
// LOAD STUDENTS FROM FILE
// =========================================

int loadStudents(struct Student students[]) {

    FILE *file = fopen("students.dat", "rb");
    int n;

    if (file == NULL) {
        return 0;
    }

    fread(&n, sizeof(int), 1, file);
    fread(students, sizeof(struct Student), n, file);

    fclose(file);

    return n;
}


// =========================================
// DISPLAY GRADE
// =========================================

void displayGrade(float marks) {

    if (marks >= 90) {
        printf("Grade      : A+\n");
    }
    else if (marks >= 80) {
        printf("Grade      : A\n");
    }
    else if (marks >= 70) {
        printf("Grade      : B\n");
    }
    else if (marks >= 60) {
        printf("Grade      : C\n");
    }
    else if (marks >= 50) {
        printf("Grade      : D\n");
    }
    else {
        printf("Grade      : F\n");
    }
}


// =========================================
// LOGIN FUNCTION
// =========================================

int login() {

    char username[30];
    char password[30];

    int attempts = 0;

    // Login details
    char correctUsername[] = "admin";
    char correctPassword[] = "1234";

    while (attempts < 3) {

        printf("\n====================================\n");
        printf("       CAMPUS STUDENT PORTAL\n");
        printf("              LOGIN\n");
        printf("====================================\n");

        printf("\nUsername: ");
        scanf("%29s", username);

        printf("Password: ");
        scanf("%29s", password);

        if (strcmp(username, correctUsername) == 0 &&
            strcmp(password, correctPassword) == 0) {

            printf("\nLogin successful!\n");

            return 1;
        }

        attempts++;

        printf("\nIncorrect username or password!\n");
        printf("Attempts remaining: %d\n", 3 - attempts);
    }

    printf("\nToo many failed attempts.\n");
    printf("Access denied.\n");

    return 0;
}


// =========================================
// MAIN FUNCTION
// =========================================

int main() {

    struct Student students[200];

    int n = loadStudents(students);
    int choice;

    // =====================================
    // LOGIN
    // =====================================

    if (login() == 0) {
        return 0;
    }


    // =====================================
    // MAIN MENU
    // =====================================

    do {

        printf("\n====================================\n");
        printf("       CAMPUS STUDENT PORTAL\n");
        printf("====================================\n");

        printf("1. Add Students\n");
        printf("2. Display Students\n");
        printf("3. Search Student\n");
        printf("4. Update Student\n");
        printf("5. Delete Student\n");
        printf("6. Mark Attendance\n");
        printf("7. View Attendance\n");
        printf("8. Save Records\n");
        printf("9. Exit\n");

        printf("\nEnter your choice: ");
        scanf("%d", &choice);


        switch (choice) {

            // =================================
            // ADD STUDENTS
            // =================================

            case 1: {

                int number;

                printf("\nHow many students do you want to add? ");
                scanf("%d", &number);

                if (number <= 0) {
                    printf("\nInvalid number of students.\n");
                    break;
                }

                if (n + number > 200) {
                    printf("\nMaximum 200 students can be stored.\n");
                    break;
                }

                for (int i = 0; i < number; i++) {

                    printf("\n----- Student %d -----\n", n + 1);

                    printf("Enter Student ID: ");
                    scanf("%d", &students[n].id);

                    printf("Enter Student Name: ");
                    scanf(" %[^\n]", students[n].name);

                    printf("Enter Student Age: ");
                    scanf("%d", &students[n].age);

                    printf("Enter Course: ");
                    scanf(" %[^\n]", students[n].course);

                    printf("Enter Marks: ");
                    scanf("%f", &students[n].marks);

                    students[n].totalClasses = 0;
                    students[n].presentClasses = 0;

                    n++;
                }

                printf("\nStudents added successfully!\n");

                saveStudents(students, n);

                break;
            }


            // =================================
            // DISPLAY STUDENTS
            // =================================

            case 2:

                if (n == 0) {

                    printf("\nNo student records found.\n");

                } else {

                    printf("\n====================================\n");
                    printf("         STUDENT DETAILS\n");
                    printf("====================================\n");

                    for (int i = 0; i < n; i++) {

                        printf("\n----- Student %d -----\n", i + 1);

                        printf("Student ID : %d\n", students[i].id);
                        printf("Name       : %s\n", students[i].name);
                        printf("Age        : %d\n", students[i].age);
                        printf("Course     : %s\n", students[i].course);
                        printf("Marks      : %.2f\n", students[i].marks);

                        displayGrade(students[i].marks);
                    }
                }

                break;


            // =================================
            // SEARCH STUDENT
            // =================================

            case 3: {

                int searchId;
                int found = 0;

                printf("\nEnter Student ID to search: ");
                scanf("%d", &searchId);

                for (int i = 0; i < n; i++) {

                    if (students[i].id == searchId) {

                        printf("\n----- Student Found -----\n");

                        printf("Student ID : %d\n", students[i].id);
                        printf("Name       : %s\n", students[i].name);
                        printf("Age        : %d\n", students[i].age);
                        printf("Course     : %s\n", students[i].course);
                        printf("Marks      : %.2f\n", students[i].marks);

                        displayGrade(students[i].marks);

                        found = 1;
                        break;
                    }
                }

                if (!found) {
                    printf("\nStudent not found.\n");
                }

                break;
            }


            // =================================
            // UPDATE STUDENT
            // =================================

            case 4: {

                int updateId;
                int found = 0;

                printf("\nEnter Student ID to update: ");
                scanf("%d", &updateId);

                for (int i = 0; i < n; i++) {

                    if (students[i].id == updateId) {

                        printf("\n----- Update Student -----\n");

                        printf("Enter New Name: ");
                        scanf(" %[^\n]", students[i].name);

                        printf("Enter New Age: ");
                        scanf("%d", &students[i].age);

                        printf("Enter New Course: ");
                        scanf(" %[^\n]", students[i].course);

                        printf("Enter New Marks: ");
                        scanf("%f", &students[i].marks);

                        printf("\nStudent updated successfully!\n");

                        saveStudents(students, n);

                        found = 1;
                        break;
                    }
                }

                if (!found) {
                    printf("\nStudent not found.\n");
                }

                break;
            }


            // =================================
            // DELETE STUDENT
            // =================================

            case 5: {

                int deleteId;
                int found = 0;

                printf("\nEnter Student ID to delete: ");
                scanf("%d", &deleteId);

                for (int i = 0; i < n; i++) {

                    if (students[i].id == deleteId) {

                        for (int j = i; j < n - 1; j++) {
                            students[j] = students[j + 1];
                        }

                        n--;

                        printf("\nStudent deleted successfully!\n");

                        saveStudents(students, n);

                        found = 1;
                        break;
                    }
                }

                if (!found) {
                    printf("\nStudent not found.\n");
                }

                break;
            }


            // =================================
            // MARK ATTENDANCE
            // =================================

            case 6: {

                int attendanceId;
                int status;
                int found = 0;

                printf("\nEnter Student ID: ");
                scanf("%d", &attendanceId);

                for (int i = 0; i < n; i++) {

                    if (students[i].id == attendanceId) {

                        printf("\nStudent: %s\n", students[i].name);

                        printf("\n1. Present\n");
                        printf("2. Absent\n");

                        printf("\nEnter attendance status: ");
                        scanf("%d", &status);

                        if (status == 1) {

                            students[i].presentClasses++;
                            students[i].totalClasses++;

                            printf("\nAttendance marked as PRESENT.\n");

                            saveStudents(students, n);
                        }
                        else if (status == 2) {

                            students[i].totalClasses++;

                            printf("\nAttendance marked as ABSENT.\n");

                            saveStudents(students, n);
                        }
                        else {

                            printf("\nInvalid attendance choice.\n");
                        }

                        found = 1;
                        break;
                    }
                }

                if (!found) {
                    printf("\nStudent not found.\n");
                }

                break;
            }


            // =================================
            // VIEW ATTENDANCE
            // =================================

            case 7: {

                int attendanceId;
                int found = 0;
                float percentage;

                printf("\nEnter Student ID: ");
                scanf("%d", &attendanceId);

                for (int i = 0; i < n; i++) {

                    if (students[i].id == attendanceId) {

                        printf("\n====================================\n");
                        printf("         ATTENDANCE DETAILS\n");
                        printf("====================================\n");

                        printf("Student ID    : %d\n", students[i].id);
                        printf("Name          : %s\n", students[i].name);
                        printf("Total Classes : %d\n",
                               students[i].totalClasses);

                        printf("Present       : %d\n",
                               students[i].presentClasses);

                        printf("Absent        : %d\n",
                               students[i].totalClasses -
                               students[i].presentClasses);

                        if (students[i].totalClasses > 0) {

                            percentage =
                                (students[i].presentClasses * 100.0)
                                / students[i].totalClasses;

                            printf("Attendance    : %.2f%%\n",
                                   percentage);

                        } else {

                            printf("Attendance    : 0.00%%\n");
                        }

                        found = 1;
                        break;
                    }
                }

                if (!found) {
                    printf("\nStudent not found.\n");
                }

                break;
            }


            // =================================
            // SAVE RECORDS
            // =================================

            case 8:

                saveStudents(students, n);

                break;


            // =================================
            // EXIT
            // =================================

            case 9:

                saveStudents(students, n);

                printf("\nThank you for using Campus Student Portal!\n");

                break;


            // =================================
            // INVALID CHOICE
            // =================================

            default:

                printf("\nInvalid choice! Please try again.\n");
        }

    } while (choice != 9);

    return 0;
}