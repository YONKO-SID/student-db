/**
 * @file studentdb.c
 * @brief A simple command-line student database management system.
 *
 * This program allows users to perform basic CRUD (Create, Read, Update, Delete)
 * operations on a binary file acting as a database for student records.
 * It features adding, searching, displaying, deleting students, and calculating
 * basic statistics like average GPA.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @struct Student
 * @brief Represents a single student record.
 *
 * This structure is a custom data type that groups all the related
 * information for a student into a single unit.
 */
typedef struct {
    int student_id;
    char name[50];
    char course[30];
    float gpa;
    int year;
} Student;

// --- Function Prototypes ---
// Declaring all functions that will be used in the program.
// This allows them to be called before they are defined in the file.
void displayMenu();
int addStudent();
int searchStudent();
int displayAllStudents();
int deleteStudent();
void calculateStats();

// --- Global Variables ---
const char* DATABASE_FILE = "students.dat";

int main() {
    int choice;

    printf("=== StudentDB Management System ===\n");
    printf("Welcome to your personal database system!\n\n");
    
    do {
        displayMenu();
        printf("Enter your choice: ");
        scanf("%d", &choice);

        // The switch statement directs the program to the correct function
        // based on the user's menu choice.
        switch (choice) {
            case 1: // Add Student
                if (addStudent()) {
                    printf("Student added successfully!\n");
                } else {
                    printf("Failed to add student.\n");
                }
                break;
                
            case 2: // Search Student
                if (!searchStudent()) {
                    printf("Student not found.\n");
                }
                break;
                
            case 3: // Display All Students
                displayAllStudents();
                break;
                
            case 4: // Delete Student
                if (deleteStudent()) {
                    printf("Student deleted successfully!\n");
                } else {
                    printf("Failed to delete student.\n");
                }
                break;
                
            case 5: // Calculate Statistics
                calculateStats();
                break;
                
            case 6: // Exit
                printf("Thank you for using StudentDB!\n");
                break;
                
            default: // Invalid Input
                printf("Invalid choice. Please try again.\n");
        }
        
        // This block handles the "Press Enter to continue..." prompt.
        // It's important for pausing the program and improving user experience.
        printf("\nPress Enter to continue...");

        // --- Input Buffer Clearing ---
        // The first getchar() consumes the newline character left by scanf().
        // The second getchar() waits for the user to press Enter.
        // This prevents the loop from continuing unintentionally.
        while (getchar() != '\n'); 
        getchar(); 
        
    } while (choice != 6);
    
    return 0;
}

/**
 * @brief Displays the main menu options to the user.
 */
void displayMenu() {
    printf("\n=== MENU ===\n");
    printf("1. Add Student\n");
    printf("2. Search Student\n");
    printf("3. Display All Students\n");
    printf("4. Delete Student\n");
    printf("5. Calculate Statistics\n");
    printf("6. Exit\n");
    printf("==============\n");
}

/**
 * @brief Adds a new student record to the database file.
 * @return 1 on success, 0 on failure.
 *
 * Prompts the user for student details, then appends the new record
 * to the binary data file.
 */
int addStudent() {
    Student new_student;
    FILE* file;
    
    // Get student information from user
    printf("\n=== Add New Student ===\n");
    
    printf("Enter Student ID: ");
    scanf("%d", &new_student.student_id);
    
    // Clear the input buffer before reading string input.
    // scanf leaves a newline character in the buffer which would be
    // immediately consumed by fgets, skipping the name input.
    printf("Enter Name: ");
    while (getchar() != '\n'); 
    fgets(new_student.name, sizeof(new_student.name), stdin);
    new_student.name[strcspn(new_student.name, "\n")] = 0; // Remove trailing newline from fgets
    
    printf("Enter Course: ");
    fgets(new_student.course, sizeof(new_student.course), stdin);
    new_student.course[strcspn(new_student.course, "\n")] = 0; // Remove trailing newline
    
    printf("Enter GPA (0.0 - 4.0): ");
    scanf("%f", &new_student.gpa);
    
    printf("Enter Year (1-4): ");
    scanf("%d", &new_student.year);

    // Open the database file in "ab" (append binary) mode.
    // This adds the new record to the end of the file without deleting existing data.
    file = fopen(DATABASE_FILE, "ab");
    if (file == NULL) {
        printf("Error: Cannot open database file.\n");
        return 0;
    }
    
    // Write the student record to file
    fwrite(&new_student, sizeof(Student), 1, file);
    fclose(file);
    
    return 1; // Success
}

/**
 * @brief Searches for a student by their ID.
 * @return 1 if the student is found, 0 otherwise.
 *
 * Prompts the user for a student ID, then reads through the database
 * file record by record to find a match. If found, it prints the
 * student's details.
 */
int searchStudent() {
    int search_id;
    Student student;
    FILE* file;
    int found = 0;
    
    printf("\n=== Search Student ===\n");
    printf("Enter Student ID to search: ");
    scanf("%d", &search_id);
    
    // Open the file in "rb" (read binary) mode.
    file = fopen(DATABASE_FILE, "rb");
    if (file == NULL) {
        printf("Database file not found. No students in system.\n");
        return 0;
    }
    
    // Loop through the file, reading one Student struct at a time.
    while (fread(&student, sizeof(Student), 1, file)) {
        // If the student ID in the record matches the search ID
        if (student.student_id == search_id) {
            printf("\n=== Student Found ===\n");
            printf("ID: %d\n", student.student_id);
            printf("Name: %s\n", student.name);
            printf("Course: %s\n", student.course);
            printf("GPA: %.2f\n", student.gpa);
            printf("Year: %d\n", student.year);
            found = 1;
            break; // Exit the loop once the student is found
        }
    }
    
    fclose(file);
    return found;
}

/**
 * @brief Displays all student records currently in the database.
 * @return The total number of students displayed.
 *
 * Reads every record from the database file and prints them in a
 * formatted table.
 */
int displayAllStudents() {
    Student student;
    FILE* file;
    int count = 0;
    
    printf("\n=== All Students ===\n");
    
    // Open the file in "rb" (read binary) mode.
    file = fopen(DATABASE_FILE, "rb");
    if (file == NULL) {
        printf("No database file found. No students in system.\n");
        return 0;
    }
    
    // Print table headers for formatted output.
    printf("%-6s %-20s %-15s %-6s %-4s\n", "ID", "Name", "Course", "GPA", "Year");
    printf("-----------------------------------------------------------\n");
    
    // Read and print each student record until the end of the file.
    while (fread(&student, sizeof(Student), 1, file)) {
        printf("%-6d %-20s %-15s %-6.2f %-4d\n", 
               student.student_id, student.name, student.course, 
               student.gpa, student.year);
        count++;
    }
    
    fclose(file);
    printf("\nTotal students: %d\n", count);
    return count;
}

/**
 * @brief Deletes a student record from the database by ID.
 * @return 1 if the student was deleted, 0 otherwise.
 *
 * This function works by creating a temporary file. It reads records
 * from the original database file and writes every student—*except* the
 * one to be deleted—to the temporary file. Finally, it deletes the
 * original file and renames the temporary file to take its place.
 * This is a common and safe pattern for "deleting" from a file.
 */
int deleteStudent() {
    int delete_id;
    Student student;
    FILE* file, *temp_file;
    int found = 0;
    
    printf("\n=== Delete Student ===\n");
    printf("Enter Student ID to delete: ");
    scanf("%d", &delete_id);
    
    // Open the original database file for reading.
    file = fopen(DATABASE_FILE, "rb");
    if (file == NULL) {
        printf("Database file not found.\n");
        return 0;
    }
    
    // Create a new temporary file for writing.
    temp_file = fopen("temp.dat", "wb");
    if (temp_file == NULL) {
        printf("Error creating temporary file.\n");
        fclose(file);
        return 0;
    }
    
    // Loop through the original file.
    while (fread(&student, sizeof(Student), 1, file)) {
        if (student.student_id != delete_id) {
            fwrite(&student, sizeof(Student), 1, temp_file);
        } else {
            found = 1;
        }
    }
    
    fclose(file);
    fclose(temp_file);
    
    if (found) {
        // If the student was found and skipped, delete the original file...
        remove(DATABASE_FILE);
        // ...and rename the temporary file to become the new database file.
        rename("temp.dat", DATABASE_FILE);
    } else {
        // If no student with the given ID was found, just delete the temp file.
        remove("temp.dat");
        printf("Student with ID %d not found.\n", delete_id);
    }
    
    return found;
}

/**
 * @brief Calculates and displays statistics about the student data.
 *
 * Reads all student records to calculate the total number of students,
 * average GPA, highest GPA, and lowest GPA.
 */
void calculateStats() {
    Student student;
    FILE* file;
    int count = 0;
    float total_gpa = 0.0;
    float highest_gpa = 0.0;
    float lowest_gpa = 4.0;
    
    printf("\n=== Statistics ===\n");
    
    // Open the file for reading.
    file = fopen(DATABASE_FILE, "rb");
    if (file == NULL) {
        printf("No database file found.\n");
        return;
    }
    
    // Loop through all records to gather data for statistics.
    while (fread(&student, sizeof(Student), 1, file)) {
        total_gpa += student.gpa;
        count++;    
        
        // Check for a new highest GPA.
        if (student.gpa > highest_gpa) {
            highest_gpa = student.gpa;
        }
        // Check for a new lowest GPA.
        if (student.gpa < lowest_gpa) {
            lowest_gpa = student.gpa;
        }
    }
    
    fclose(file);
    
    // Display the calculated statistics, avoiding division by zero if no students exist.
    if (count > 0) {
        printf("Total Students: %d\n", count);
        printf("Average GPA: %.2f\n", total_gpa / count);
        printf("Highest GPA: %.2f\n", highest_gpa);
        printf("Lowest GPA: %.2f\n", lowest_gpa);
    } else {
        printf("No students in database.\n");
    }
}