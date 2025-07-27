#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

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

/* =============== FUNCTION IMPLEMENTATIONS ================== */

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

int add_book(Library *lib) {
    if(lib->book_count >= lib->capacity) {
        int new_capacity = 0;
        printf("The array is full you need to add more space: ");
        scanf("%d", &new_capacity);
        new_capacity += lib->capacity;

        Book *new_books = realloc(lib->books, sizeof(Book) * new_capacity);
        if(new_books == NULL) {
            printf("Memory allocation failed\n");
            return 0;
        }
        lib->books = new_books;
        lib->capacity = new_capacity;
    }

    printf("\n\n╔══════════════════════════════════════════════════════════╗\n");
    printf("║                    📚 ADD NEW BOOK 📚                    ║\n");
    printf("╚══════════════════════════════════════════════════════════╝\n\n");
    
    char temp_title[256];
    printf("📖 Enter the book title: ");
    scanf(" %255[^\n]", temp_title);
    lib->books[lib->book_count].title = malloc(strlen(temp_title) + 1);
    strcpy(lib->books[lib->book_count].title, temp_title);

    int num_authors;
    printf("✍️  How many authors? ");
    scanf("%d", &num_authors);
    printf("\n");

    if(num_authors > 10) {
        printf("⚠️  Too many authors! MAX 10 allowed: ");
        scanf("%d", &num_authors);
        printf("\n");
    }

    // Allocate array of char* pointers
    lib->books[lib->book_count].authors = malloc(sizeof(char*) * num_authors);
    lib->books[lib->book_count].author_count = num_authors;

    // Now allocate each individual author name - FIXED to handle spaces
    for (int i = 0; i < num_authors; i++) {
        char temp_author[256];
        printf("👤 Enter author %d: ", i + 1);
        scanf(" %255[^\n]", temp_author);
            
        lib->books[lib->book_count].authors[i] = malloc(strlen(temp_author) + 1);
        strcpy(lib->books[lib->book_count].authors[i], temp_author);
    }

    int temp_year = 0;
    printf("📅 Enter the book's year: ");
    scanf("%d", &temp_year);
    lib->books[lib->book_count].year = temp_year;

    int temp_pages = 0;
    printf("📜 Enter the total number of pages: ");
    scanf("%d", &temp_pages);
    lib->books[lib->book_count].pages = temp_pages;

    // Initialize availability fields
    lib->books[lib->book_count].is_available = 1;  // Book is available by default
    lib->books[lib->book_count].borrowed_by = NULL; // No one has borrowed it yet

    lib->book_count++;
    
    return 1;
}

void display_all_books(Library *lib) {
    printf("\n\n╔═════════════════════════════════════════════════════════╗\n");
    printf("║                   📋 ALL BOOKS DISPLAY 📋                ║\n");
    printf("╚══════════════════════════════════════════════════════════╝\n\n");
    
    if(lib->book_count == 0) {
        printf("⚠️  No books in the library yet.\n");
        return;
    }
    
    for(int i = 0; i < lib->book_count; i++) {
        printf("┌────────────────────────────────────────────────────┐\n");
        printf("│               📚 BOOK #%d 📚                │\n", i + 1);
        printf("└────────────────────────────────────────────────────┘\n");

        printf("📖 Title: %s\n", lib->books[i].title);
        int num_authors = lib->books[i].author_count;
        printf("✍️  Authors (%d):\n", num_authors);
        for(int j = 0; j < num_authors; j++) {
            printf("   👤 %d. %s\n", j + 1, lib->books[i].authors[j]);
        }
        printf("📅 Year: %d\n", lib->books[i].year);
        printf("📜 Pages: %d\n", lib->books[i].pages);
        
        // Display availability status
        if(lib->books[i].is_available) {
            printf("✅ Status: Available\n\n");
        } else {
            printf("📚 Status: Borrowed by %s\n\n", lib->books[i].borrowed_by);
        }
    }
}

int search_books(Library *lib) {
    char search_term[256];
    int matches = 0;

    printf("\n\n╔══════════════════════════════════════════════════════════╗\n");
    printf("║                    🔍 BOOK SEARCH 🔍                     ║\n");
    printf("╚══════════════════════════════════════════════════════════╝\n\n");

    printf("🔎 Enter search term: ");
    scanf(" %255[^\n]", search_term);  // FIXED to handle multi-word search terms

    printf("\n🔍 Searching for: '%s'\n\n", search_term);
    
    for(int i = 0; i < lib->book_count; i++) {
        // Check title
        if(case_insensitive_search(lib->books[i].title, search_term)) {
            printf("✅ 📖 Found book: '%s'\n", lib->books[i].title);
            matches++;
        } else {
            // Check all authors
            for(int j = 0; j < lib->books[i].author_count; j++) {
                if(case_insensitive_search(lib->books[i].authors[j], search_term)) {
                    printf("✅ 👤 Found author: '%s' wrote '%s'\n", 
                           lib->books[i].authors[j], lib->books[i].title);
                    matches++;
                    break;
                }
            }
        }
    }

    return matches;
}

int remove_book(Library *lib) {

    printf("\n\n╔══════════════════════════════════════════════════════════╗\n");
    printf("║                   🗑️ REMOVE BOOK 🗑️                      ║\n");
    printf("╚══════════════════════════════════════════════════════════╝\n\n");
    
    char title_to_remove[256];
    printf("📖 Enter title to remove: ");
    scanf(" %255[^\n]", title_to_remove);
        
    // Find the book
    int found_index = -1;
    for (int i = 0; i < lib->book_count; i++) {
        if (case_insensitive_search(lib->books[i].title, title_to_remove)) {
            found_index = i;
            break;
        }
    }
    
    if (found_index == -1) return 0; // Not found
    
    cleanup_book(&lib->books[found_index]);
    
    // Shift all books after this one to the left
    for (int i = found_index; i < lib->book_count - 1; i++) {
        lib->books[i] = lib->books[i + 1]; // Copy struct
    }
    
    lib->book_count--;
    return 1;
}

void display_statistics(Library *lib) {
    printf("\n\n╔══════════════════════════════════════════════════════════╗\n");
    printf("║                   📊 BOOK STATISTICS 📊                  ║\n");
    printf("╚══════════════════════════════════════════════════════════╝\n\n");
    
    if(lib->book_count == 0) {
        printf("⚠️  No books in the library to show statistics.\n");
        return;
    }

    printf("📚 Total number of books: %d\n", lib->book_count);

    int tot_authors = 0;
    for(int i = 0; i < lib->book_count; i++) {
        tot_authors += lib->books[i].author_count;
    }
    printf("✍️  Total number of authors: %d\n", tot_authors);

    int tot_pages_all = 0;
    for(int i = 0; i < lib->book_count; i++) {
        tot_pages_all += lib->books[i].pages;
    }
    int avr_pages = tot_pages_all / lib->book_count;
    printf("📜 Average number of pages: %d\n", avr_pages);

    // Find newest and oldest books
    int newest = 0;
    int oldest = 0;

    for(int i = 1; i < lib->book_count; i++) {
        if(lib->books[i].year > lib->books[newest].year) {
            newest = i;
        }
        if(lib->books[i].year < lib->books[oldest].year) {
            oldest = i;
        }
    }

    printf("✨ Newest book: '%s' from %d\n", lib->books[newest].title, lib->books[newest].year);
    printf("🕰️ Oldest book: '%s' from %d\n", lib->books[oldest].title, lib->books[oldest].year);
}

void cleanup_library(Library *lib) {
    if(lib == NULL) return;

    printf("\n\n╔══════════════════════════════════════════════════════════╗\n");
    printf("║                  🧹 FREEING MEMORY 🧹                    ║\n");
    printf("╚══════════════════════════════════════════════════════════╝\n\n");
    
    for(int i = 0; i < lib->book_count; i++) {
        cleanup_book(&lib->books[i]);
        printf("✅ Memory freed for book #%d\n", i + 1);
    }
    
    free(lib->books);
    lib->books = NULL;
    printf("✅ Memory freed for books array\n");
    
    free(lib);
    printf("✅ Memory freed for the library\n");
}

Book* resize_library_if_needed(Library *lib) {
    // Check if resize is needed
    if (lib->book_count >= lib->capacity) {
        int new_capacity = 0;

        printf("\n\n╔══════════════════════════════════════════════════════════╗\n");
        printf("║                   📏 RESIZING LIBRARY 📏                 ║\n");
        printf("╚══════════════════════════════════════════════════════════╝\n\n");

        printf("⚠️  Library capacity is full! Current capacity: %d books\n", lib->capacity);
        printf("📚 Current books in library: %d\n\n", lib->book_count);
        printf("📈 How much additional space do you want to add? ");
        scanf("%d", &new_capacity);
        
        if (new_capacity <= 0) {
            printf("❌ Invalid capacity! Please enter a positive number.\n");
            return NULL;
        }
        
        new_capacity += lib->capacity;
        
        printf("\n🔄 Attempting to resize library from %d to %d books...\n", lib->capacity, new_capacity);
        
        // Reallocate with new capacity
        Book *new_books = realloc(lib->books, sizeof(Book) * new_capacity);
        
        if (new_books == NULL) {
            printf("\n❌ ═══════════════════════════════════════════════════════\n");
            printf("   💥 MEMORY ALLOCATION FAILED! 💥\n");
            printf("   Unable to resize library. Please try again later.\n");
            printf("   ═══════════════════════════════════════════════════════\n");
            return NULL;
        }
        
        // Update library structure
        lib->books = new_books;
        lib->capacity = new_capacity;
        
        printf("\n✅ ═══════════════════════════════════════════════════════\n");
        printf("   🎉 LIBRARY SUCCESSFULLY RESIZED! 🎉\n");
        printf("   📊 New capacity: %d books\n", new_capacity);
        printf("   📈 Additional space: %d books\n", new_capacity - lib->book_count);
        printf("   ═══════════════════════════════════════════════════════\n");
    }
    
    return lib->books;
}

void cleanup_book(Book *book) {
    if (book->title != NULL) {
        free(book->title);
        book->title = NULL;
    }
    
    // Free each author name string
    if (book->authors != NULL) {
        for (int i = 0; i < book->author_count; i++) {
            if (book->authors[i] != NULL) {
                free(book->authors[i]);
                book->authors[i] = NULL;
            }
        }
        
        free(book->authors);
        book->authors = NULL;
    }

    // Free borrowed_by field if it exists
    if (book->borrowed_by != NULL) {
        free(book->borrowed_by);
        book->borrowed_by = NULL;
    }

    book->author_count = 0;
    book->is_available = 1;
}

int case_insensitive_search(const char *haystack, const char *needle) {
    int haystack_len = strlen(haystack);
    int needle_len = strlen(needle);
    
    // Check each possible starting position
    for (int i = 0; i <= haystack_len - needle_len; i++) {
        int match = 1;
        
        // Compare characters at this position
        for (int j = 0; j < needle_len; j++) {
            if (tolower(haystack[i + j]) != tolower(needle[j])) {
                match = 0;
                break;
            }
        }
        
        if (match) return 1;
    }
    
    return 0;
}

StudentSystem* create_student_system(int initial_capacity) {
    StudentSystem *student_sys = malloc(sizeof(StudentSystem));
    if(student_sys == NULL) {
        printf("Failed to allocate memory for Student_sys\n");
        return NULL;
    }

    student_sys->students = malloc(sizeof(Student) * initial_capacity);
    if(student_sys->students == NULL) {
        printf("Failed to allocate memory for array of students\n");
        free(student_sys);
        return NULL;
    }

    student_sys->student_count = 0;
    student_sys->student_capacity = initial_capacity;
    return student_sys;
}

int add_student(StudentSystem *sys) {
    if(sys->student_count >= sys->student_capacity) {
        int new_capacity = 0;
        printf("⚠️  The student array is full! Add more space: ");
        scanf("%d", &new_capacity);
        new_capacity += sys->student_capacity;

        Student *new_student = realloc(sys->students, sizeof(Student) * new_capacity);
        if(new_student == NULL) {
            printf("❌ Memory allocation failed\n");
            return 0;
        }
        sys->students = new_student;
        sys->student_capacity = new_capacity;
    }

    printf("\n\n╔══════════════════════════════════════════════════════════╗\n");
    printf("║                   👤 ADD STUDENT 👤                      ║\n");
    printf("╚══════════════════════════════════════════════════════════╝\n\n");

    int ID_temp = 0;
    printf("🏷️  Enter the student ID: ");
    scanf("%d", &ID_temp);
    sys->students[sys->student_count].student_id = ID_temp;

    char name_temp[256];
    printf("👤 Enter the student's name: ");
    scanf(" %255[^\n]", name_temp);
    sys->students[sys->student_count].name = malloc(strlen(name_temp) + 1);
    strcpy(sys->students[sys->student_count].name, name_temp);

    sys->students[sys->student_count].max_books = 3;
    sys->students[sys->student_count].borrowed_books = malloc(sizeof(char*) * 3); // dont know why i cant use MAX_BOOk
    sys->students[sys->student_count].borrowed_count = 0;

    sys->student_count ++;
    return 1;
}

void display_all_students(StudentSystem *sys) {
    printf("\n\n╔══════════════════════════════════════════════════════════╗\n");
    printf("║                 👥 ALL STUDENTS DISPLAY 👥               ║\n");
    printf("╚══════════════════════════════════════════════════════════╝\n\n");
    
    if(sys->student_count == 0) {
        printf("⚠️  No students registered yet.\n");
        return;
    }

    for(int i = 0; i < sys->student_count; i++) {
        printf("┌────────────────────────────────────────────────────┐\n");
        printf("│             👤 STUDENT #%d 👤              │\n", i + 1);
        printf("└────────────────────────────────────────────────────┘\n");

        printf("🏷️  Student ID: %d\n", sys->students[i].student_id);
        printf("👤 Name: %s\n", sys->students[i].name);
        printf("📚 Books borrowed: %d/%d\n", sys->students[i].borrowed_count, sys->students[i].max_books);

        if(sys->students[i].borrowed_count > 0) {
            printf("📋 Borrowed books:\n");
            for(int j = 0; j < sys->students[i].borrowed_count; j++) {
                printf("   📖 %d. %s\n", j + 1, sys->students[i].borrowed_books[j]);
            }
        } else {
            printf("✅ No books currently borrowed\n");
        }
        printf("\n");
    }
}

int borrow_book(Library *lib, StudentSystem *sys) {
    char student_name[256];
    char book_title[256];

    printf("\n\n╔══════════════════════════════════════════════════════════╗\n");
    printf("║                   📤 BORROW BOOK 📤                      ║\n");
    printf("╚══════════════════════════════════════════════════════════╝\n\n");

    // Prompt for student name
    printf("👤 Enter student's name: ");
    scanf(" %255[^\n]", student_name);

    // Find student
    Student *student = find_student_by_name(sys, student_name);
    if (student == NULL) {
        printf("❌ Student not found.\n");
        return 0; // Failure
    }

    // Prompt for book title
    printf("📖 Enter book title: ");
    scanf(" %255[^\n]", book_title);

    // Find book
    Book *book = find_book_by_title(lib, book_title);
    if (book == NULL) {
        printf("❌ Book not found.\n");
        return 0; // Failure
    }

    // Check if book is available
    if (book->is_available == 0) {
        printf("❌ Book is currently borrowed by someone else.\n");
        return 0; // Failure
    }

    // Check if student can borrow more books
    if (student->borrowed_count >= student->max_books) {
        printf("❌ Student has reached the borrowing limit (%d books).\n", student->max_books);
        return 0; // Failure
    }

    // Borrow the book
    book->is_available = 0;
    book->borrowed_by = malloc(strlen(student->name) + 1);
    strcpy(book->borrowed_by, student->name);

    // Add book to student's borrowed books
    student->borrowed_books[student->borrowed_count] = malloc(strlen(book->title) + 1);
    strcpy(student->borrowed_books[student->borrowed_count], book->title);
    student->borrowed_count++;

    printf("✅ Book borrowed successfully!\n");
    return 1; // Success
}

int return_book(Library *lib, StudentSystem *sys) {
    char student_name[256];
    char book_title[256];

    printf("\n\n╔══════════════════════════════════════════════════════════╗\n");
    printf("║                   📥 RETURN BOOK 📥                      ║\n");
    printf("╚══════════════════════════════════════════════════════════╝\n\n");

    printf("👤 Enter student's name: ");
    scanf(" %255[^\n]", student_name);

    Student *student = find_student_by_name(sys, student_name);
    if(student == NULL) {
        printf("❌ Student not found\n");
        return 0;
    }

    printf("📖 Enter book title: ");
    scanf(" %255[^\n]", book_title);

    Book *book = find_book_by_title(lib, book_title);
    if(book == NULL) {
        printf("❌ Book not found\n");
        return 0;
    }

    // Check if book is currently borrowed
    if(book->is_available == 1) {
        printf("❌ Book is not currently borrowed\n");
        return 0;
    }

    // Check if book is borrowed by this student
    if(book->borrowed_by == NULL || !case_insensitive_search(book->borrowed_by, student->name)) {
        printf("❌ Book is not borrowed by this student\n");
        return 0;
    }

    // Find the book in student's borrowed_books array
    int book_index = -1;
    for(int i = 0; i < student->borrowed_count; i++) {
        if(case_insensitive_search(student->borrowed_books[i], book_title)) {
            book_index = i;
            break;
        }
    }

    if(book_index == -1) {
        printf("❌ Book not found in student's borrowed list\n");
        return 0;
    }

    // Update book: make it available and clear borrowed_by
    book->is_available = 1;
    if(book->borrowed_by != NULL) {
        free(book->borrowed_by);
        book->borrowed_by = NULL;
    }

    // Remove book from student's borrowed_books array
    free(student->borrowed_books[book_index]);
    
    // Shift remaining books to fill the gap
    for(int i = book_index; i < student->borrowed_count - 1; i++) {
        student->borrowed_books[i] = student->borrowed_books[i + 1];
    }
    
    // Decrement borrowed count
    student->borrowed_count--;

    printf("✅ Book returned successfully!\n");
    return 1;
}

void display_student_books(StudentSystem *sys) {
    char student_name[256];
    
    printf("\n\n╔══════════════════════════════════════════════════════════╗\n");
    printf("║                📚 STUDENT'S BOOKS 📚                     ║\n");
    printf("╚══════════════════════════════════════════════════════════╝\n\n");
    
    printf("👤 Enter student's name: ");
    scanf(" %255[^\n]", student_name);
    
    Student *student = find_student_by_name(sys, student_name);
    if(student == NULL) {
        printf("❌ Student not found\n");
        return;
    }
    
    printf("┌────────────────────────────────────────────────────┐\n");
    printf("│          📚 %s's BORROWED BOOKS 📚         │\n", student->name);
    printf("└────────────────────────────────────────────────────┘\n\n");
    
    printf("🏷️  Student ID: %d\n", student->student_id);
    printf("👤 Student Name: %s\n", student->name);
    printf("📊 Currently borrowed: %d/%d books\n\n", student->borrowed_count, student->max_books);
    
    if(student->borrowed_count == 0) {
        printf("✅ No books currently borrowed - student is available to borrow up to %d books!\n", student->max_books);
    } else {
        printf("📋 Borrowed Books List:\n");
        printf("┌────────────────────────────────────────────────────┐\n");
        for(int i = 0; i < student->borrowed_count; i++) {
            printf("│ 📖 %d. %-45s │\n", i + 1, student->borrowed_books[i]);
        }
        printf("└────────────────────────────────────────────────────┘\n");
    }
    
    int remaining = student->max_books - student->borrowed_count;
    printf("\n📈 Remaining borrowing capacity: %d books\n", remaining);
    
    if(remaining > 0) {
        printf("💡 This student can borrow %d more book%s!\n", remaining, remaining == 1 ? "" : "s");
    } else {
        printf("⚠️  This student has reached their borrowing limit!\n");
    }
}

void display_enhanced_statistics(Library *lib, StudentSystem *sys) {
    printf("\n\n╔══════════════════════════════════════════════════════════╗\n");
    printf("║                📊 ENHANCED STATISTICS 📊                 ║\n");
    printf("╚══════════════════════════════════════════════════════════╝\n\n");
    
    // Display original library statistics first
    if(lib->book_count == 0) {
        printf("⚠️  No books in the library to show statistics.\n");
        return;
    }
    
    printf("📚 LIBRARY STATISTICS:\n");
    printf("📗 Total number of books: %d\n", lib->book_count);
    
    // Count total authors
    int tot_authors = 0;
    for(int i = 0; i < lib->book_count; i++) {
        tot_authors += lib->books[i].author_count;
    }
    printf("✍️  Total number of authors: %d\n", tot_authors);
    
    // Calculate average pages
    int tot_pages_all = 0;
    for(int i = 0; i < lib->book_count; i++) {
        tot_pages_all += lib->books[i].pages;
    }
    int avr_pages = tot_pages_all / lib->book_count;
    printf("📜 Average number of pages: %d\n", avr_pages);
    
    // Find newest and oldest books
    int newest = 0, oldest = 0;
    for(int i = 1; i < lib->book_count; i++) {
        if(lib->books[i].year > lib->books[newest].year) {
            newest = i;
        }
        if(lib->books[i].year < lib->books[oldest].year) {
            oldest = i;
        }
    }
    printf("✨ Newest book: '%s' from %d\n", lib->books[newest].title, lib->books[newest].year);
    printf("🕰 Oldest book: '%s' from %d\n", lib->books[oldest].title, lib->books[oldest].year);
    
    // Student-related statistics
    printf("\n👥 STUDENT STATISTICS:\n");
    printf("👨‍🎓 Total registered students: %d\n", sys->student_count);
    
    // Count total books currently borrowed
    int total_borrowed = 0;
    for(int i = 0; i < sys->student_count; i++) {
        total_borrowed += sys->students[i].borrowed_count;
    }
    printf("📚 Total books currently borrowed: %d\n", total_borrowed);
    
    // Calculate average books per student
    if(sys->student_count > 0) {
        float avg_books_per_student = (float)total_borrowed / sys->student_count;
        printf("📚 Average books per student: %.2f\n", avg_books_per_student);
    } else {
        printf("📚 Average books per student: 0.00\n");
    }
    
    // Find most active student
    if(sys->student_count > 0) {
        int most_active = 0;
        for(int i = 1; i < sys->student_count; i++) {
            if(sys->students[i].borrowed_count > sys->students[most_active].borrowed_count) {
                most_active = i;
            }
        }
        printf("🏆 Most active student: %s (ID: %d) with %d books\n", 
               sys->students[most_active].name, 
               sys->students[most_active].student_id,
               sys->students[most_active].borrowed_count);
    }
    
    // Books availability ratio
    int available_books = lib->book_count - total_borrowed;
    float availability_ratio = (float)available_books / lib->book_count * 100;
    printf("📊 Books availability ratio: %.1f%% (%d available out of %d)\n", 
           availability_ratio, available_books, lib->book_count);
}

void cleanup_student_system(StudentSystem *sys) {
    if(sys == NULL) return;
    
    printf("\n\n╔══════════════════════════════════════════════════════════╗\n");
    printf("║              🧹 CLEANING STUDENT MEMORY 🧹               ║\n");
    printf("╚══════════════════════════════════════════════════════════╝\n\n");
    
    // Loop through all students and call cleanup_student() for each
    for(int i = 0; i < sys->student_count; i++) {
        cleanup_student(&sys->students[i]);
        printf("✅ Memory freed for student #%d\n", i + 1);
    }
    
    // Free the students array
    free(sys->students);
    sys->students = NULL;
    printf("✅ Memory freed for students array\n");
    
    // Free the StudentSystem structure
    free(sys);
    printf("✅ Memory freed for the student system\n");
}

void cleanup_student(Student *student) {
    if(student == NULL) return;
    
    // Free the student's name
    if(student->name != NULL) {
        free(student->name);
        student->name = NULL;
    }
    
    // Free each borrowed book title in borrowed_books array
    if(student->borrowed_books != NULL) {
        for(int i = 0; i < student->borrowed_count; i++) {
            if(student->borrowed_books[i] != NULL) {
                free(student->borrowed_books[i]);
                student->borrowed_books[i] = NULL;
            }
        }
        
        // Free the borrowed_books array itself
        free(student->borrowed_books);
        student->borrowed_books = NULL;
    }
    
    student->student_id = 0;
    student->borrowed_count = 0;
    student->max_books = 0;
}

Student* find_student_by_name(StudentSystem *sys, const char *name) {
    if (sys == NULL || name == NULL) {
        return NULL;
    }
    
    for (int i = 0; i < sys->student_count; i++) {
        if (case_insensitive_search(sys->students[i].name, name)) {
            return &sys->students[i];
        }
    }
    
    return NULL; 
}

Book* find_book_by_title(Library *lib, const char *title) {
    if (lib == NULL || title == NULL) {
        return NULL;
    }
    
    for (int i = 0; i < lib->book_count; i++) {
        if (case_insensitive_search(lib->books[i].title, title)) {
            return &lib->books[i];
        }
    }
    
    return NULL; 
}

/* ================== MAIN FUNCTION ==================== */

int main() {
    Library *library = NULL;
    int choice;
    int init_capacity = 2; 
    int stud_capacity = 2;
    
    printf("\n══════════════════════════════════════════════════════════\n");
    printf("📚 DYNAMIC LIBRARY MANAGEMENT SYSTEM 📚\n");
    printf("══════════════════════════════════════════════════════════\n");
    
    library = create_library(init_capacity);
    if (library == NULL) {
        printf("❌ Failed to create library. Exiting.\n");
        return 1;
    }
    
    StudentSystem *student_sys = create_student_system(stud_capacity);
    
    while (1) {
        printf("\n╔══════════════════════════════════════════════════════════╗\n");
        printf("║                    📖 LIBRARY MENU 📖                    ║\n");
        printf("╠══════════════════════════════════════════════════════════╣\n");
        printf("║  📖 BOOK MANAGEMENT                                      ║\n");
        printf("║  1. 📚 Add Book                                          ║\n");
        printf("║  2. 📋 Display All Books                                 ║\n");
        printf("║  3. 🔍 Search Books                                      ║\n");
        printf("║  4. 🗑️  Remove Book                                      ║\n");
        printf("║  5. 📊 Display Statistics                                ║\n");
        printf("║                                                          ║\n");
        printf("║  👥 STUDENT MANAGEMENT                                   ║\n");
        printf("║  7. 👤 Add Student                                       ║\n");
        printf("║  8. 👥 Display All Students                              ║\n");
        printf("║                                                          ║\n");
        printf("║  📖 BORROWING SYSTEM                                     ║\n");
        printf("║  9. 📤 Borrow Book                                       ║\n");
        printf("║  10. 📥 Return Book                                      ║\n");
        printf("║  11. 📚 Display Student's Books                          ║\n");
        printf("║                                                          ║\n");
        printf("║  📈 REPORTS & CLEANUP                                    ║\n");
        printf("║  12. 📊 Enhanced Statistics                              ║\n");
        printf("║  6. 🚪 Exit                                              ║\n");
        printf("╚══════════════════════════════════════════════════════════╝\n");
        printf("\n🎯 Enter your choice: ");
        
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                if (add_book(library)) {
                    printf("\n\n✅ ═══════════════════════════════════════════════════════\n");
                    printf("   📚 BOOK ADDED SUCCESSFULLY! 📚\n");
                    printf("   ═══════════════════════════════════════════════════════\n");
                } else {
                    printf("\n\n❌ ═══════════════════════════════════════════════════════\n");
                    printf("   📚 FAILED TO ADD BOOK 📚\n");
                    printf("   ═══════════════════════════════════════════════════════\n");
                }
                break;
            case 2:
                display_all_books(library);
                break;
            case 3:
                {
                    int matches = search_books(library);
                    printf("\n\n🔍 ═══════════════════════════════════════════════════════\n");
                    printf("   📊 SEARCH COMPLETED: %d MATCHING BOOK(S) FOUND\n", matches);
                    printf("   ═══════════════════════════════════════════════════════\n");
                }
                break;
            case 4:
                if (remove_book(library)) {
                    printf("\n\n✅ ═══════════════════════════════════════════════════════\n");
                    printf("   🗑️ BOOK REMOVED SUCCESSFULLY! 🗑️\n");
                    printf("   ═══════════════════════════════════════════════════════\n");
                } else {
                    printf("\n\n❌ ═══════════════════════════════════════════════════════\n");
                    printf("   📚 BOOK NOT FOUND\n");
                    printf("   ═══════════════════════════════════════════════════════\n");
                }
                break;
            case 5:
                display_statistics(library);
                break;
            case 6:
                printf("\n\n🚪 ═══════════════════════════════════════════════════════\n");
                printf("   🧹 CLEANING UP AND EXITING... 🧹\n");
                printf("   ═══════════════════════════════════════════════════════\n");
                cleanup_library(library);
                cleanup_student_system(student_sys);
                printf("\n\n👋 ═══════════════════════════════════════════════════════\n");
                printf("   ✨ GOODBYE! THANKS FOR USING MY LIBRARY SYSTEM! ✨\n");
                printf("   ═══════════════════════════════════════════════════════\n\n");
                return 0;
            case 7:
                if (add_student(student_sys)) {
                    printf("\n\n✅ ═══════════════════════════════════════════════════════\n");
                    printf("   👤 STUDENT ADDED SUCCESSFULLY! 👤\n");
                    printf("   ═══════════════════════════════════════════════════════\n");
                } else {
                    printf("\n\n❌ ═══════════════════════════════════════════════════════\n");
                    printf("   👤 FAILED TO ADD STUDENT\n");
                    printf("   ═══════════════════════════════════════════════════════\n");
                }
                break;
            case 8:
                display_all_students(student_sys);
                break;
            case 9:
                if (borrow_book(library, student_sys)) {
                    printf("\n\n✅ ═══════════════════════════════════════════════════════\n");
                    printf("   📤 BOOK BORROWED SUCCESSFULLY! 📤\n");
                    printf("   ═══════════════════════════════════════════════════════\n");
                } else {
                    printf("\n\n❌ ═══════════════════════════════════════════════════════\n");
                    printf("   📤 BOOK BORROWING FAILED\n");
                    printf("   ═══════════════════════════════════════════════════════\n");
                }
                break;
            case 10:
                if (return_book(library, student_sys)) {
                    printf("\n\n✅ ═══════════════════════════════════════════════════════\n");
                    printf("   📥 BOOK RETURNED SUCCESSFULLY! 📥\n");
                    printf("   ═══════════════════════════════════════════════════════\n");
                } else {
                    printf("\n\n❌ ═══════════════════════════════════════════════════════\n");
                    printf("   📥 BOOK RETURN FAILED\n");
                    printf("   ═══════════════════════════════════════════════════════\n");
                }
                break;
            case 11:
                display_student_books(student_sys);
                break;
            case 12:
                display_enhanced_statistics(library, student_sys);
                break;
            default:
                printf("\n\n⚠️  ═══════════════════════════════════════════════════════\n");
                printf("   ❌ INVALID CHOICE! PLEASE TRY AGAIN ❌\n");
                printf("   ═══════════════════════════════════════════════════════\n");
        }
    }
}

