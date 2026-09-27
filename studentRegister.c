#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_NAME 50
#define MAX_STUDENTS 100
#define FILE_NAME "student_details.txt"

struct Student
{
    char name[MAX_NAME];
    int id;
    int class_number;
    char grade;
    double math_marks;
    double science_marks;
    double english_marks;
    double total_marks;
    double avg_marks;
};

void clearInputBuffer(void)
{
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF)
    {
    }
}

void calculateStudentPerformance(struct Student *student)
{
    student->total_marks = student->math_marks + student->science_marks + student->english_marks;
    student->avg_marks = student->total_marks / 3.0;

    if (student->avg_marks >= 90.0)
        student->grade = 'A';
    else if (student->avg_marks >= 80.0)
        student->grade = 'B';
    else if (student->avg_marks >= 70.0)
        student->grade = 'C';
    else if (student->avg_marks >= 60.0)
        student->grade = 'D';
    else
        student->grade = 'F';
}

static void trimWhitespace(char *text)
{
    size_t start = 0;
    size_t end;
    size_t length;

    while (text[start] != '\0' && isspace((unsigned char)text[start]))
    {
        start++;
    }

    if (start > 0)
    {
        memmove(text, text + start, strlen(text + start) + 1);
    }

    end = strlen(text);
    while (end > 0 && isspace((unsigned char)text[end - 1]))
    {
        text[end - 1] = '\0';
        end--;
    }

    length = strlen(text);
    for (size_t i = 0; i < length; i++)
    {
        if (text[i] == '\t' || text[i] == '\r')
        {
            text[i] = ' ';
        }
    }
}

int loadStudents(struct Student students[], int *pcount)
{
    FILE *file = fopen(FILE_NAME, "r");
    if (file == NULL)
    {
        return 0;
    }

    int count = 0;
    char line[300];

    while (count < MAX_STUDENTS && fgets(line, sizeof(line), file) != NULL)
    {
        char *token;
        char *rest = line;
        struct Student student = {0};

        token = strtok(rest, "|");
        if (token == NULL)
            continue;
        strncpy(student.name, token, MAX_NAME - 1);
        student.name[MAX_NAME - 1] = '\0';
        trimWhitespace(student.name);

        token = strtok(NULL, "|");
        if (token == NULL)
            continue;
        student.id = atoi(token);

        token = strtok(NULL, "|");
        if (token == NULL)
            continue;
        student.class_number = atoi(token);

        token = strtok(NULL, "|");
        if (token == NULL)
            continue;
        student.grade = token[0];
        if (student.grade >= 'a' && student.grade <= 'z')
            student.grade = (char)toupper((unsigned char)student.grade);

        token = strtok(NULL, "|");
        if (token == NULL)
            continue;
        student.math_marks = strtod(token, NULL);

        token = strtok(NULL, "|");
        if (token == NULL)
            continue;
        student.science_marks = strtod(token, NULL);

        token = strtok(NULL, "|");
        if (token == NULL)
            continue;
        student.english_marks = strtod(token, NULL);

        token = strtok(NULL, "|");
        if (token != NULL)
            student.total_marks = strtod(token, NULL);

        token = strtok(NULL, "|");
        if (token != NULL)
            student.avg_marks = strtod(token, NULL);

        calculateStudentPerformance(&student);
        students[count++] = student;
    }

    fclose(file);
    *pcount = count;
    printf("Loaded %d student(s) from %s.\n", count, FILE_NAME);
    return 1;
}

void saveStudents(struct Student students[], int count)
{
    FILE *file = fopen(FILE_NAME, "w");
    if (file == NULL)
    {
        printf("Error: Could not open file for saving students.\n");
        return;
    }

    for (int i = 0; i < count; i++)
    {
        fprintf(file, "%s|%d|%d|%c|%.2lf|%.2lf|%.2lf|%.2lf|%.2lf|\n",
                students[i].name,
                students[i].id,
                students[i].class_number,
                students[i].grade,
                students[i].math_marks,
                students[i].science_marks,
                students[i].english_marks,
                students[i].total_marks,
                students[i].avg_marks);
    }

    fclose(file);
    printf("Data saved successfully to %s.\n", FILE_NAME);
}

int displayMenu(void)
{
    int choice;

    printf("\n========================================\n");
    printf("          STUDENT REGISTER SYSTEM\n");
    printf("========================================\n");
    printf("  1. Add a new student\n");
    printf("  2. Delete a student\n");
    printf("  3. Edit student details\n");
    printf("  4. Display all students\n");
    printf("  5. Sort students by name\n");
    printf("  6. Save changes to file\n");
    printf("  7. Exit program\n");
    printf("========================================\n");

    while (1)
    {
        printf("Select an option (1-7): ");
        if (scanf("%d", &choice) == 1 && choice >= 1 && choice <= 7)
        {
            clearInputBuffer();
            return choice;
        }

        clearInputBuffer();
        printf("Invalid choice. Please enter a number from 1 to 7.\n");
    }
}

int findStudentById(const struct Student students[], int count, int id)
{
    for (int i = 0; i < count; i++)
    {
        if (students[i].id == id)
            return i;
    }
    return -1;
}

void readName(char name[], int size)
{
    char buffer[MAX_NAME];

    if (fgets(buffer, sizeof(buffer), stdin) == NULL)
    {
        printf("Invalid input.\n");
        name[0] = '\0';
        return;
    }

    buffer[strcspn(buffer, "\n")] = '\0';
    trimWhitespace(buffer);

    if (buffer[0] == '\0')
    {
        name[0] = '\0';
        return;
    }

    strncpy(name, buffer, size - 1);
    name[size - 1] = '\0';
}

double readMarks(const char *subject)
{
    double marks;

    while (1)
    {
        printf("Enter %s marks (0-100): ", subject);
        if (scanf("%lf", &marks) == 1 && marks >= 0.0 && marks <= 100.0)
        {
            clearInputBuffer();
            return marks;
        }

        clearInputBuffer();
        printf("Invalid marks. Please enter a value between 0 and 100.\n");
    }
}

static int getNextStudentId(const struct Student students[], int count)
{
    int highest = 0;

    for (int i = 0; i < count; i++)
    {
        if (students[i].id > highest)
            highest = students[i].id;
    }

    return highest + 1;
}

int addStudent(struct Student students[], int *pcount)
{
    int index;
    char name[MAX_NAME];

    if (*pcount >= MAX_STUDENTS)
    {
        printf("Maximum limit of students reached. Cannot add more.\n");
        return 0;
    }

    index = *pcount;
    printf("\n----------------------------------------\n");
    printf("          ADD NEW STUDENT\n");
    printf("----------------------------------------\n");

    while (1)
    {
        printf("Enter student name: ");
        readName(name, sizeof(name));
        if (name[0] != '\0')
        {
            strncpy(students[index].name, name, MAX_NAME - 1);
            students[index].name[MAX_NAME - 1] = '\0';
            break;
        }
        printf("Name cannot be empty. Please try again.\n");
    }

    students[index].id = getNextStudentId(students, *pcount);

    while (1)
    {
        printf("Enter class number (1-12): ");
        if (scanf("%d", &students[index].class_number) == 1 &&
            students[index].class_number >= 1 && students[index].class_number <= 12)
        {
            clearInputBuffer();
            break;
        }

        clearInputBuffer();
        printf("Invalid class number. Please enter a value between 1 and 12.\n");
    }

    students[index].math_marks = readMarks("Math");
    students[index].science_marks = readMarks("Science");
    students[index].english_marks = readMarks("English");

    calculateStudentPerformance(&students[index]);
    (*pcount)++;

    printf("Student added successfully.\n");
    return 1;
}

void deleteStudent(struct Student students[], int *pcount)
{
    int id;
    int index;

    if (*pcount == 0)
    {
        printf("No students available to delete.\n");
        return;
    }

    printf("Enter the student ID to delete: ");
    if (scanf("%d", &id) != 1)
    {
        clearInputBuffer();
        printf("Invalid student ID entered.\n");
        return;
    }
    clearInputBuffer();

    index = findStudentById(students, *pcount, id);
    if (index == -1)
    {
        printf("Student with ID %d was not found.\n", id);
        return;
    }

    for (int i = index; i < *pcount - 1; i++)
    {
        students[i] = students[i + 1];
    }

    (*pcount)--;
    for (int i = 0; i < *pcount; i++)
    {
        students[i].id = i + 1;
    }

    printf("Student with ID %d deleted successfully.\n", id);
}

void editStudent(struct Student students[], int count)
{
    int id;
    int index;
    int choice;

    if (count == 0)
    {
        printf("No students to edit.\n");
        return;
    }

    printf("Enter the student ID to edit: ");
    if (scanf("%d", &id) != 1)
    {
        clearInputBuffer();
        printf("Invalid ID.\n");
        return;
    }
    clearInputBuffer();

    index = findStudentById(students, count, id);
    if (index == -1)
    {
        printf("Student with ID %d not found.\n", id);
        return;
    }

    printf("\n----------------------------------------\n");
    printf("Edit student: %s\n", students[index].name);
    printf("----------------------------------------\n");
    printf("  1. Update name\n");
    printf("  2. Update class\n");
    printf("  3. Update marks\n");
    printf("----------------------------------------\n");
    printf("Select an option: ");
    if (scanf("%d", &choice) != 1)
    {
        clearInputBuffer();
        printf("Invalid option selected.\n");
        return;
    }
    clearInputBuffer();

    switch (choice)
    {
        case 1:
            {
                char newName[MAX_NAME];
                printf("Enter new student name: ");
                readName(newName, sizeof(newName));
                if (newName[0] == '\0')
                {
                    printf("Name cannot be empty.\n");
                    return;
                }
                strncpy(students[index].name, newName, MAX_NAME - 1);
                students[index].name[MAX_NAME - 1] = '\0';
            }
            break;

        case 2:
            while (1)
            {
                printf("Enter new class number (1-12): ");
                if (scanf("%d", &students[index].class_number) == 1 &&
                    students[index].class_number >= 1 && students[index].class_number <= 12)
                {
                    clearInputBuffer();
                    break;
                }
                clearInputBuffer();
                printf("Invalid class number. Please enter a value between 1 and 12.\n");
            }
            break;

        case 3:
            students[index].math_marks = readMarks("Math");
            students[index].science_marks = readMarks("Science");
            students[index].english_marks = readMarks("English");
            calculateStudentPerformance(&students[index]);
            break;

        default:
            printf("Invalid option selected.\n");
            return;
    }

    printf("Student details updated successfully.\n");
}

void displayStudents(const struct Student students[], int count)
{
    if (count == 0)
    {
        printf("No students found.\n");
        return;
    }

    printf("\n+-----------------------------------------------+\n");
    printf("|                 STUDENT LIST                  |\n");
    printf("+----+--------------------+-------+-------+--------+---------+---------+-------+---------+\n");
    printf("| ID | Name               | Class | Grade | Math   | Science | English | Total | Average |\n");
    printf("+----+--------------------+-------+-------+--------+---------+---------+-------+---------+\n");

    for (int i = 0; i < count; i++)
    {
        printf("| %-2d | %-18s | %-5d | %-5c | %-6.2lf | %-7.2lf | %-7.2lf | %-5.2lf | %-7.2lf |\n",
               students[i].id,
               students[i].name,
               students[i].class_number,
               students[i].grade,
               students[i].math_marks,
               students[i].science_marks,
               students[i].english_marks,
               students[i].total_marks,
               students[i].avg_marks);
    }

    printf("+----+--------------------+-------+-------+--------+---------+---------+-------+---------+\n");
}

static int compareStudentNames(const void *left, const void *right)
{
    const struct Student *studentA = (const struct Student *)left;
    const struct Student *studentB = (const struct Student *)right;
    char nameA[MAX_NAME];
    char nameB[MAX_NAME];
    int i = 0;

    strncpy(nameA, studentA->name, MAX_NAME - 1);
    nameA[MAX_NAME - 1] = '\0';
    strncpy(nameB, studentB->name, MAX_NAME - 1);
    nameB[MAX_NAME - 1] = '\0';

    for (i = 0; nameA[i] != '\0' || nameB[i] != '\0'; i++)
    {
        unsigned char chA = (unsigned char)nameA[i];
        unsigned char chB = (unsigned char)nameB[i];

        if (nameA[i] == '\0')
            return -1;
        if (nameB[i] == '\0')
            return 1;

        chA = (unsigned char)tolower(chA);
        chB = (unsigned char)tolower(chB);

        if (chA < chB)
            return -1;
        if (chA > chB)
            return 1;
    }

    return 0;
}

void sortStudentsByName(struct Student students[], int count)
{
    qsort(students, (size_t)count, sizeof(struct Student), compareStudentNames);

    for (int i = 0; i < count; i++)
    {
        students[i].id = i + 1;
    }

    printf("Students sorted by name successfully.\n");
}

int main(void)
{
    struct Student students[MAX_STUDENTS];
    int count = 0;
    int choice;

    printf("\n========================================\n");
    printf("          WELCOME TO STUDENT REGISTER\n");
    printf("========================================\n");
    loadStudents(students, &count);

    while (1)
    {
        choice = displayMenu();

        switch (choice)
        {
            case 1:
                addStudent(students, &count);
                break;

            case 2:
                deleteStudent(students, &count);
                break;

            case 3:
                editStudent(students, count);
                break;

            case 4:
                displayStudents(students, count);
                break;

            case 5:
                sortStudentsByName(students, count);
                break;

            case 6:
                saveStudents(students, count);
                break;

            case 7:
                saveStudents(students, count);
                printf("Exiting the program.\n");
                return 0;
        }
    }
}
