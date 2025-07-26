#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

typedef struct {
    char *title;
    char **authors;        // Dynamic array of author name strings
    int author_count;
    int year;
    int pages;
    int is_available;      // 1 if available, 0 if borrowed
    char *borrowed_by;     // Student name who borrowed it (NULL if available)
} Book;

typedef struct {
    int student_id;
    char *name;
    char **borrowed_books; // Dynamic array of borrowed book titles
    int borrowed_count;
    int max_books;         // Maximum books this student can borrow (default 3)
} Student;

typedef struct {
    Book *books;           // Dynamic array of books
    int book_count;
    int capacity;          // Current array capacity
} Library;

typedef struct {
    Student *students;     // Dynamic array of students
    int student_count;
    int student_capacity;
} StudentSystem;

/* ================ FUNCTION DECLARATIONS ================== */

// Library Management Functions
Library* create_library(int initial_capacity);
int add_book(Library *lib);
void display_all_books(Library *lib);
int search_books(Library *lib);
int remove_book(Library *lib);
void display_statistics(Library *lib);
void cleanup_library(Library *lib);

// Helper Functions
Book* resize_library_if_needed(Library *lib);
void cleanup_book(Book *book);
int case_insensitive_search(const char *haystack, const char *needle);

// Student Management Functions (TODO: Implement these)
StudentSystem* create_student_system(int initial_capacity);
int add_student(StudentSystem *sys);
void display_all_students(StudentSystem *sys);
int borrow_book(Library *lib, StudentSystem *sys);
int return_book(Library *lib, StudentSystem *sys);
void display_student_books(StudentSystem *sys);
void display_enhanced_statistics(Library *lib, StudentSystem *sys);
void cleanup_student_system(StudentSystem *sys);
void cleanup_student(Student *student);
Student* find_student_by_name(StudentSystem *sys, const char *name);
Book* find_book_by_title(Library *lib, const char *title);

Library* create_library(int initial_capacity) {
    Library *lib = malloc(sizeof(Library));
    if (lib == NULL) {
        printf("Failed to allocate memory for library!\n");
        return NULL;
    }
    
    lib->books = malloc(sizeof(Book) * initial_capacity);
    if (lib->books == NULL) {
        printf("Failed to allocate memory for books array!\n");
        free(lib);
        return NULL;
    }
    
    lib->book_count = 0;
    lib->capacity = initial_capacity;
    
    return lib;
}

int main(void) {
    Library *library = NULL;
    int choice;
    int init_capacity = 2;
    
    printf("=== Dynamic Library Management System ===\n");
    
    library = create_library(init_capacity);
    if (library == NULL) {
        printf("Failed to create library. Exiting.\n");
        return 1;
    }
    
    while (1) {
        printf("\n--- Library Menu ---\n");
        printf("1. Add Book\n");
        printf("2. Display All Books\n");
        printf("3. Search Books\n");
        printf("4. Remove Book\n");
        printf("5. Display Statistics\n");
        printf("6. Exit\n");
        printf("Choice: ");
        
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                if (add_book(library)) {
                    printf("Book added successfully!\n");
                } else {
                    printf("Failed to add book.\n");
                }
                break;
            case 2:
                display_all_books(library);
                break;
            case 3:
                {
                    int matches = search_books(library);
                    printf("Found %d matching book(s).\n", matches);
                }
                break;
            case 4:
                if (remove_book(library)) {
                    printf("Book removed successfully!\n");
                } else {
                    printf("Book not found.\n");
                }
                break;
            case 5:
                display_statistics(library);
                break;
            case 6:
                printf("Cleaning up and exiting...\n");
                cleanup_library(library);
                return 0;
            default:
                printf("Invalid choice!\n");
        }
    }
}
