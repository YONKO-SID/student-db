# StudentDB Management System

A simple, lightweight, command-line student database management system written in C. This application allows for basic CRUD (Create, Read, Update, Delete) operations on student records, which are persisted in a binary file (`students.dat`).

## Features

- **Add Student**: Add a new student record with ID, name, course, GPA, and year.
- **Search Student**: Find and display a student's details using their unique ID.
- **Display All Students**: View a formatted list of all students in the database.
- **Delete Student**: Remove a student's record from the database by their ID.
- **Calculate Statistics**: Compute and display key statistics, including total students, average GPA, highest GPA, and lowest GPA.
- **Data Persistence**: All student records are saved to a binary file (`students.dat`), so data is not lost when the program closes.

## How to Compile and Run

You will need a C compiler, such as `gcc`, to build the program.

### 1. Compilation

Open your terminal or command prompt, navigate to the project directory, and run the following command:

```bash
gcc studentdb.c -o studentdb
```

This will compile the `studentdb.c` source file and create an executable named `studentdb` (or `studentdb.exe` on Windows).

### 2. Execution

To run the program, execute the compiled file from your terminal:

```bash
# On Linux or macOS
./studentdb

# On Windows
.\studentdb.exe
```

## Usage

Once the program is running, you will be presented with a menu of options:

```
=== StudentDB Management System ===
Welcome to your personal database system!

=== MENU ===
1. Add Student
2. Search Student
3. Display All Students
4. Delete Student
5. Calculate Statistics
6. Exit
==============
Enter your choice:
```

Simply enter the number corresponding to the action you wish to perform and press `Enter`. Follow the on-screen prompts to manage the student database.

## File Structure

- `studentdb.c`: The main C source code file containing all the logic for the application.
- `students.dat`: The binary data file where all student records are stored. This file is created automatically when you add the first student.
- `README.md`: This file.

## Code Structure

The program is organized into several key functions:

- **`Student` struct**: Defines the data structure for a single student record, containing `student_id`, `name`, `course`, `gpa`, and `year`.
- **`main()`**: The entry point of the program. It contains the main loop that displays the menu and handles user choices via a `switch` statement.
- **`displayMenu()`**: Prints the main menu options to the console.
- **`addStudent()`**: Prompts the user for new student details and appends the record to `students.dat`.
- **`searchStudent()`**: Searches for a student by ID and displays their information if found.
- **`displayAllStudents()`**: Reads and displays all records from `students.dat` in a formatted table.
- **`deleteStudent()`**: Deletes a student record by creating a temporary file, copying all other records to it, and then replacing the original file.
- **`calculateStats()`**: Reads all records to compute and display statistics like average, highest, and lowest GPA.

---