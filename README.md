# Student Register System

A beginner-friendly C project for managing student records. This program allows you to add, edit, delete, sort, and display student information with automatic grade calculation based on subject marks.

## ✨ Features

- **Add Student**: Add new students with name, class, and marks in Math, Science, and English
- **Delete Student**: Remove students by their ID
- **Edit Student**: Update student name, class number, or marks
- **Display All Students**: View all student records in a formatted table
- **Sort by Name**: Sort students alphabetically by name
- **Save Data**: Persist all changes to a file
- **Auto Grade Calculation**: Automatically calculate total marks, average, and letter grade
- **Data Persistence**: Load and save student data from/to a file

## 📁 Project Structure

```
c-student-register/
├── studentRegister.c       # Main program file
├── student_details.txt     # Data file (auto-created/loaded)
└── README.md              # Project documentation
```

## 🔧 How to Compile

### On Linux/macOS:
```bash
gcc studentRegister.c -o studentRegister
```

### On Windows (MinGW):
```bash
gcc studentRegister.c -o studentRegister.exe
```

### Using any standard C compiler:
```bash
cc studentRegister.c -o studentRegister
```

## ▶️ How to Run

### On Linux/macOS:
```bash
./studentRegister
```

### On Windows:
```bash
studentRegister.exe
```

## 📖 How to Use

When you run the program, you'll see a menu with 7 options. Here's a sample session:

### Sample Output:

#### 1. Program Start and Menu
```
========================================
          WELCOME TO STUDENT REGISTER
========================================
Loaded 0 student(s) from student_details.txt.

========================================
          STUDENT REGISTER SYSTEM
========================================
  1. Add a new student
  2. Delete a student
  3. Edit student details
  4. Display all students
  5. Sort students by name
  6. Save changes to file
  7. Exit program
========================================
Select an option (1-7): 
```

#### 2. Adding a Student (Option 1)
```
Select an option (1-7): 1

----------------------------------------
          ADD NEW STUDENT
----------------------------------------
Enter student name: Ravi Kumar
Enter class number (1-12): 10
Enter Math marks (0-100): 85.5
Enter Science marks (0-100): 92.0
Enter English marks (0-100): 78.5
Student added successfully.
```

#### 3. Adding Another Student
```
Select an option (1-7): 1

----------------------------------------
          ADD NEW STUDENT
----------------------------------------
Enter student name: Priya Singh
Enter class number (1-12): 10
Enter Math marks (0-100): 88.0
Enter Science marks (0-100): 90.5
Enter English marks (0-100): 95.0
Student added successfully.
```

#### 4. Displaying All Students (Option 4)
```
Select an option (1-7): 4

+-----------------------------------------------+
|                 STUDENT LIST                  |
+----+--------------------+-------+-------+--------+---------+---------+-------+---------+
| ID | Name               | Class | Grade | Math   | Science | English | Total | Average |
+----+--------------------+-------+-------+--------+---------+---------+-------+---------+
| 1  | Ravi Kumar         | 10    | B     | 85.50  | 92.00   | 78.50   | 256.00| 85.33   |
| 2  | Priya Singh        | 10    | A     | 88.00  | 90.50   | 95.00   | 273.50| 91.17   |
+----+--------------------+-------+-------+--------+---------+---------+-------+---------+
```

### Grade Scale
- **A**: 90 and above
- **B**: 80 to 89.99
- **C**: 70 to 79.99
- **D**: 60 to 69.99
- **F**: Below 60

## 💻 C Concepts Used

### 1. **Structures (structs)**
Stores related student data in one container:
```c
struct Student {
    char name[MAX_NAME];
    int id;
    int class_number;
    char grade;
    double math_marks;
    // ... other fields
};
```
This groups all student information together instead of using separate arrays.

### 2. **Arrays**
Stores multiple student records in memory:
```c
struct Student students[MAX_STUDENTS];
```
Allows handling up to 100 students at once.

### 3. **File I/O (Input/Output)**
Reads from and writes to `student_details.txt` to save data permanently:
- `fopen()` - Opens files for reading/writing
- `fprintf()` - Writes formatted data to files
- `fgets()` - Reads data from files

### 4. **String Handling**
Manages text data like student names:
- `strcpy()` / `strncpy()` - Copies strings safely
- `strtok()` - Splits strings using delimiters
- `strlen()` - Gets string length
- `trimWhitespace()` - Removes extra spaces

### 5. **Pointers and Pass-by-Reference**
Modifies variables in functions:
```c
void addStudent(struct Student students[], int *pcount)
```
The `int *pcount` allows the function to modify the student count.

### 6. **Input Validation**
Ensures user enters correct data:
- Checks if input is valid before using it
- Repeats prompts if input is wrong
- Prevents marks outside 0-100 range

### 7. **Sorting (qsort function)**
Sorts students alphabetically by name:
```c
qsort(students, count, sizeof(struct Student), compareStudentNames);
```
Uses the standard library sorting algorithm.

### 8. **Character and Type Conversion**
- `atoi()` - Converts text to integer
- `strtod()` - Converts text to decimal number
- `toupper()` - Converts lowercase to uppercase

## 🔄 Program Flow

```
Start Program
    ↓
Load students from file (if exists)
    ↓
Show Menu
    ↓
User selects option (1-7)
    ├─→ Option 1: Add Student → Calculate grade → Store in array
    ├─→ Option 2: Delete Student → Shift array → Reassign IDs
    ├─→ Option 3: Edit Student → Find student → Update fields
    ├─→ Option 4: Display Students → Print formatted table
    ├─→ Option 5: Sort Students → Sort by name → Reassign IDs
    ├─→ Option 6: Save Data → Write to file
    └─→ Option 7: Save and Exit → Save → End program
    ↓
Repeat from "Show Menu" (unless Exit selected)
```

## 🛠️ Major Functions Explained

### 1. `addStudent(struct Student students[], int *pcount)`
**Purpose**: Add a new student to the system
- Takes student name, class number, and marks for three subjects
- Automatically assigns next student ID
- Calls `calculateStudentPerformance()` to compute grade
- Increases student count

### 2. `deleteStudent(struct Student students[], int *pcount)`
**Purpose**: Remove a student by ID
- Finds student by ID
- Shifts remaining students forward in array
- Reassigns all IDs sequentially (1, 2, 3...)
- Decreases student count

### 3. `editStudent(struct Student students[], int count)`
**Purpose**: Modify student information
- Finds student by ID
- Offers three edit options: name, class, or marks
- Recalculates grade if marks are changed

### 4. `displayStudents(const struct Student students[], int count)`
**Purpose**: Show all students in a formatted table
- Prints header and column names
- Displays each student's record
- Shows ID, name, class, grade, marks, total, and average

### 5. `sortStudentsByName(struct Student students[], int count)`
**Purpose**: Arrange students alphabetically by name
- Uses `qsort()` library function
- Calls `compareStudentNames()` for comparison
- Reassigns IDs after sorting

### 6. `calculateStudentPerformance(struct Student *student)`
**Purpose**: Calculate total, average, and assign grade
- Adds three subject marks for total
- Divides by 3 for average
- Assigns letter grade based on average (A/B/C/D/F)

### 7. `loadStudents(struct Student students[], int *pcount)`
**Purpose**: Read student data from file
- Opens `student_details.txt`
- Parses pipe-separated data
- Loads each student into array
- Returns count of loaded students

### 8. `saveStudents(struct Student students[], int count)`
**Purpose**: Write all students to file
- Opens file in write mode
- Saves each student in pipe-separated format
- Preserves data between program runs

## 📄 Sample Input File Format

The program saves and loads data in pipe-separated format. Here's an example of `student_details.txt`:

```
Ravi Kumar|1|10|B|85.50|92.00|78.50|256.00|85.33|
Priya Singh|2|10|A|88.00|90.50|95.00|273.50|91.17|
Amit Patel|3|9|C|72.00|68.50|75.25|215.75|71.92|
```

**Format**: `Name|ID|Class|Grade|Math|Science|English|Total|Average|`

You can manually create this file before running the program, or the program creates an empty one if it doesn't exist.

## 🚀 Possible Improvements

- **Search by Name or ID**: Add feature to search specific students without displaying all
- **Filter by Grade**: Show only students with grade A, B, C, etc.
- **Statistics**: Calculate class average, highest/lowest marks, pass/fail count
- **Backup Feature**: Create automatic backups of the data file
- **Better File Format**: Use CSV instead of pipe-separated, or try JSON
- **Input Validation**: Prevent duplicate student names or IDs
- **Marks History**: Keep track of previous marks to show improvement
- **Subject-wise Performance**: Show which subject has highest/lowest average marks
- **Sorting Options**: Sort by marks, grade, class number, or average
- **Export to PDF**: Generate PDF reports of student data

## 📝 License

This project is licensed under the MIT License - see the LICENSE file for details.

---

**Author**: chaitanya-425050  
**Created**: 2026  
**Status**: Complete (No future updates planned)
