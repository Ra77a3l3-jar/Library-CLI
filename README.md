# 🏛️ Advanced Library Management System

<div align="center">

![Library Management](https://img.shields.io/badge/Library-Management-4A90E2?style=for-the-badge&logo=bookstack&logoColor=white)
![C Language](https://img.shields.io/badge/Language-C-00599C?style=for-the-badge&logo=c&logoColor=white)
![Memory Management](https://img.shields.io/badge/Memory-Dynamic-FF6B35?style=for-the-badge&logo=memory&logoColor=white)
![Status](https://img.shields.io/badge/Status-Production_Ready-28A745?style=for-the-badge)
![Version](https://img.shields.io/badge/Version-2.0-9B59B6?style=for-the-badge)

**🎯 A Production-Grade C Library Management System**

*Featuring advanced memory management, sophisticated data structures, and professional-grade console interface*

[![GitHub](https://img.shields.io/badge/GitHub-Repository-181717?style=flat-square&logo=github)](https://github.com)
[![MIT License](https://img.shields.io/badge/License-MIT-blue.svg?style=flat-square)](LICENSE)

</div>

---

## 📑 Table of Contents

<div align="center">

| Section | Description |
|---------|-------------|
| [🎯 **Project Overview**](#-project-overview) | System introduction and key features |
| [🏗️ **System Architecture**](#️-system-architecture) | Modular design and component interaction |
| [🧠 **Memory Management**](#-memory-management) | Advanced allocation strategies and safety |
| [📊 **Data Structures**](#-data-structures) | Core structures and their relationships |
| [⚡ **Core Implementation**](#-core-implementation) | Function details and algorithms |
| [🎨 **User Interface**](#-user-interface) | Console design and interaction flow |
| [🚀 **Quick Start Guide**](#-quick-start-guide) | Installation and basic usage |
| [💼 **Professional Usage**](#-professional-usage) | Advanced scenarios and examples |
| [📈 **Performance Analysis**](#-performance-analysis) | Complexity and optimization details |
| [🔬 **Technical Deep Dive**](#-technical-deep-dive) | Implementation internals |
| [🛣️ **Development Roadmap**](#️-development-roadmap) | Future enhancements and goals |

</div>

---

## 🎯 Project Overview

### 🌟 Executive Summary

The **Advanced Library Management System** represents a sophisticated approach to library automation using pure C programming. This system demonstrates enterprise-level software engineering principles while maintaining simplicity and efficiency.

<div align="center">

### 🏆 Key Achievements

| Achievement | Impact |
|-------------|--------|
| **🎨 Professional UI** | Beautiful console interface with Unicode graphics |
| **🔄 Dynamic Scaling** | Intelligent memory management with automatic resizing |
| **👥 Multi-User Support** | Complete student registration and book borrowing system |
| **🔍 Advanced Search** | Fast, case-insensitive search across multiple fields |
| **📊 Rich Analytics** | Comprehensive statistical reporting and insights |
| **🛡️ Memory Safety** | Zero-leak architecture with comprehensive cleanup |
| **⚡ High Performance** | Optimized algorithms for large-scale library operations |

</div>

### 🎪 Feature Showcase

---

## ✨ Features

### 🌟 Core Capabilities

- **📚 Book Management**: Add, remove, and display books with multiple authors
- **🔍 Advanced Search**: Search by title or author with case-insensitive matching
- **📊 Statistical Analysis**: Generate comprehensive library statistics
- **🔄 Dynamic Memory**: Automatic memory allocation and expansion
- **👥 Student Management**: Register students and manage their book borrowing
- **🛡️ Memory Safety**: Comprehensive cleanup and leak prevention

---

## 🏗️ Architecture

### 📐 System Design

The system follows a modular architecture with clear separation of concerns:

```
┌─────────────────────────────────────────────────────────┐
│                    MAIN PROGRAM                         │
├─────────────────────────────────────────────────────────┤
│  🎮 User Interface  Menu System                        │
└─────────────────────────────────────────────────────────┘
                              │
┌─────────────────────────────────────────────────────────┐
│                LIBRARY MANAGEMENT                       │
├─────────────────────────────────────────────────────────┤
│  📚 Library Operations                                  │
│  • create_library()    • add_book()                     │
│  • display_all_books() • search_books()                 │
│  • remove_book()       • display_statistics()           │
└─────────────────────────────────────────────────────────┘
                              │
┌─────────────────────────────────────────────────────────┐
│                STUDENT MANAGEMENT                       │
├─────────────────────────────────────────────────────────┤
│  👥 Student Operations                                  │
│  • create_student_system()  • add_student()             │
│  • borrow_book()            • return_book()             │
│  • display_all_students()   • display_student_books()   │
└─────────────────────────────────────────────────────────┘
                              │
┌─────────────────────────────────────────────────────────┐
│                 MEMORY MANAGEMENT                       │
├─────────────────────────────────────────────────────────┤
│  🧠 Memory Operations                                   │
│  • Dynamic allocation   • Automatic resizing            │
│  • Memory cleanup      • Leak prevention                │
└─────────────────────────────────────────────────────────┘
                              │
┌─────────────────────────────────────────────────────────┐
│                  UTILITY FUNCTIONS                      │
├─────────────────────────────────────────────────────────┤
│  🔧 Helper Functions                                    │
│  • case_insensitive_search()  • cleanup_book()          │
│  • resize_library_if_needed()                           │
└─────────────────────────────────────────────────────────┘
```

---

## 🧠 Memory Management

### 🏗️ Memory Architecture Visualization

```
Library Structure Memory Layout:
═══════════════════════════════════════════════════════════════

┌─────────────────┐
│     Library     │ ← Main library structure
├─────────────────┤
│ books: ptr ──┐  │ ← Pointer to dynamic book array
│ book_count: 3│  │ ← Current number of books
│ capacity: 5  │  │ ← Maximum capacity
└──────────────┼──┘
               │
               ▼
    ┌─────────────────────────────────────────────────┐
    │              Books Array                        │
    ├─────────────┬─────────────┬─────────────┬───────┤
    │   Book[0]   │   Book[1]   │   Book[2]   │  ...  │
    └─────────────┴─────────────┴─────────────┴───────┘
           │
           ▼
    ┌─────────────────┐
    │      Book       │ ← Individual book structure
    ├─────────────────┤
    │ title: ptr ──┐  │ ← Pointer to title string
    │ authors: ptr─┼┐ │ ← Pointer to authors array
    │ author_count ││ │ ← Number of authors
    │ year: 2023   ││ │
    │ pages: 300   ││ │
    └──────────────┼┼─┘
                   ├┘
                   ▼
            ┌─────────────┐
            │ "Book Title"│ ← Dynamically allocated title
            └─────────────┘
                   │
                   ▼
    ┌────────────────────────────────────────┐
    │           Authors Array                │
    ├──────────┬──────────┬──────────┬───────┤
    │ ptr[0] ──┤ ptr[1] ──┤ ptr[2] ──┤  ...  │
    └──────────┴──────────┴──────────┴───────┘
         │          │          │
         ▼          ▼          ▼
    ┌─────────┐ ┌─────────┐ ┌──────────┐
    │"Author1"│ │"Author2"│ │"Author3" │ ← Individual author names
    └─────────┘ └─────────┘ └──────────┘
```

### 🔄 Dynamic Memory Allocation Process

| Step | Operation | Memory State |
|------|-----------|--------------|
| 1️⃣ | **Initial Allocation** | `malloc(sizeof(Library))` |
| 2️⃣ | **Book Array Creation** | `malloc(sizeof(Book) * capacity)` |
| 3️⃣ | **Title Allocation** | `malloc(strlen(title) + 1)` |
| 4️⃣ | **Authors Array** | `malloc(sizeof(char*) * author_count)` |
| 5️⃣ | **Individual Authors** | `malloc(strlen(author) + 1)` for each |
| 6️⃣ | **Dynamic Resize** | `realloc()` when capacity exceeded |

### 🛡️ Memory Safety Features

```c
// Memory cleanup hierarchy ensures no leaks
cleanup_library(Library *lib) {
    ├── cleanup_book() for each book {
    │   ├── free(book->title)
    │   ├── free(book->authors[i]) for each author
    │   └── free(book->authors)
    │   }
    ├── free(lib->books)
    └── free(lib)
}
```

---

## 📊 Data Structures

### 🏗️ Structure Definitions

#### 📚 Library Structure
```c
typedef struct {
    Book *books;        // 🔗 Dynamic array of books
    int book_count;     // 📊 Current number of books
    int capacity;       // 📏 Maximum capacity
} Library;
```

**Memory Efficiency**: Uses dynamic allocation to grow as needed, preventing waste.

#### 📖 Book Structure
```c
typedef struct {
    char *title;           // 🏷️  Dynamic title string
    char **authors;        // 👥 Array of author pointers
    int author_count;      // 🔢 Number of authors
    int year;              // 📅 Publication year
    int pages;             // 📄 Page count
    int is_available;      // ✅ Availability status (1=available, 0=borrowed)
    char *borrowed_by;     // 👤 Borrower information (student name)
} Book;
```

**Flexibility**: Supports multiple authors per book with dynamic allocation and tracks borrowing status.

#### 👥 Student Structure
```c
typedef struct {
    int student_id;        // 🏷️  Unique student identifier
    char *name;           // 👤 Dynamic student name
    char **borrowed_books; // 📚 Array of borrowed book titles
    int borrowed_count;    // 🔢 Current books borrowed
    int max_books;         // 📈 Maximum borrowing limit
} Student;
```

**Features**: Dynamic borrowing tracking with configurable limits and memory-efficient storage.

---

## 🔧 Core Functions

### 📚 Library Management Functions

#### 🏗️ create_library(int initial_capacity)

```c
Library* create_library(int initial_capacity)
```

**Purpose**: Creates and initializes a new library with specified capacity.

**Memory Operations**:
1. Allocates memory for `Library` structure
2. Allocates memory for initial `Book` array
3. Initializes counters and capacity

**Error Handling**: Returns `NULL` if allocation fails, cleans up partial allocations.

#### ➕ add_book(Library *lib)

```c
int add_book(Library *lib)
```

**Purpose**: Adds a new book to the library with dynamic memory allocation.

**Process Flow**:
1. Check Capacity → Resize if Needed → Get Title → Allocate Title Memory
2. Get Author Count → Allocate Authors Array → Get Each Author → Allocate Author Memory
3. Get Year & Pages → Increment Book Count → Return Success

**Memory Operations**:
- Dynamic title allocation based on input length
- Dynamic authors array allocation
- Individual author string allocation
- Automatic library resizing when needed

#### 🔍 search_books(Library *lib)

```c
int search_books(Library *lib)
```

**Purpose**: Performs case-insensitive search across titles and authors.

**Algorithm**:
1. Get search term from user
2. Iterate through all books
3. Check title match using `case_insensitive_search()`
4. If no title match, check all authors
5. Return total matches found

**Features**:
- Case-insensitive matching
- Searches both titles and authors
- Returns match count

### 🧠 Memory Management Functions

#### 🔄 resize_library_if_needed(Library *lib)

```c
Book* resize_library_if_needed(Library *lib)
```

**Purpose**: Dynamically expands library capacity when full.

**Process**:
1. Check if current capacity is exceeded
2. Request additional capacity from user
3. Use `realloc()` to expand book array
4. Update library capacity
5. Return pointer to resized array

**Safety**: Checks for `realloc()` failure and handles gracefully.

#### 🧹 cleanup_library(Library *lib)

```c
void cleanup_library(Library *lib)
```

**Purpose**: Comprehensive memory cleanup to prevent leaks.

**Cleanup Hierarchy**:
```
Library
├── For each Book
│   ├── Free title string
│   ├── Free each author string
│   └── Free authors array
├── Free books array
└── Free library structure
```

---

## 🚀 Getting Started

### 📋 Prerequisites

```bash
# Required
gcc (GNU Compiler Collection)
make (optional, for build automation)

# System Requirements
- C99 compatible compiler
- Minimum 1MB RAM
- POSIX-compliant system (Linux/macOS/Windows with MinGW)
```

### 🔨 Compilation

```bash
# Basic compilation
gcc -o library_system library_system.c

# With debugging symbols
gcc -g -o library_system library_system.c

# With optimization
gcc -O2 -o library_system library_system.c

# With all warnings
gcc -Wall -Wextra -o library_system library_system.c -lm
```

### ▶️ Execution

```bash
# Ensure you are in the correct directory
cd /home/raffaele/Documenti/Coding/Library

# Run the program
./library_system
```

---

## 💡 Usage Examples

### 📚 Adding a Book

```
╔══════════════════════════════════════════════════════════╗
║                    📖 LIBRARY MENU 📖                    ║
╠══════════════════════════════════════════════════════════╣
║  📖 BOOK MANAGEMENT                                      ║
║  1. 📚 Add Book                                          ║
║  2. 📋 Display All Books                                 ║
║  3. 🔍 Search Books                                      ║
║  4. 🗑️  Remove Book                                      ║
║  5. 📊 Display Statistics                                ║
║                                                          ║
║  👥 STUDENT MANAGEMENT                                   ║
║  7. 👤 Add Student                                       ║
║  8. 👥 Display All Students                              ║
║                                                          ║
║  📖 BORROWING SYSTEM                                     ║
║  9. 📤 Borrow Book                                       ║
║  10. 📥 Return Book                                      ║
║  11. 📚 Display Student's Books                          ║
║                                                          ║
║  📈 REPORTS & CLEANUP                                    ║
║  12. 📊 Enhanced Statistics                              ║
║  6. 🚪 Exit                                              ║
╚══════════════════════════════════════════════════════════╝

🎯 Enter your choice: 1

╔══════════════════════════════════════════════════════════╗
║                    📚 ADD NEW BOOK 📚                    ║
╚══════════════════════════════════════════════════════════╝

📖 Enter the book title: The C Programming Language
✍️  How many authors? 2

👤 Enter author 1: Brian W. Kernighan
👤 Enter author 2: Dennis M. Ritchie
📅 Enter the book's year: 1978
📜 Enter the total number of pages: 272

✅ ═══════════════════════════════════════════════════════
   📚 BOOK ADDED SUCCESSFULLY! 📚
   ═══════════════════════════════════════════════════════
```

### 🔍 Searching Books

```
🎯 Enter your choice: 3

╔══════════════════════════════════════════════════════════╗
║                    🔍 BOOK SEARCH 🔍                     ║
╚══════════════════════════════════════════════════════════╝

🔎 Enter search term: kernighan

🔍 Searching for: 'kernighan'

✅ 👤 Found author: 'Brian W. Kernighan' wrote 'The C Programming Language'

🔍 ═══════════════════════════════════════════════════════
   📊 SEARCH COMPLETED: 1 MATCHING BOOK(S) FOUND
   ═══════════════════════════════════════════════════════
```

### 📊 Viewing Statistics

```
🎯 Enter your choice: 5

╔══════════════════════════════════════════════════════════╗
║                   📊 BOOK STATISTICS 📊                  ║
╚══════════════════════════════════════════════════════════╝

📚 Total number of books: 5
✍️  Total number of authors: 8
📜 Average number of pages: 425
✨ Newest book: 'Modern C++' from 2020
🕰️ Oldest book: 'The C Programming Language' from 1978
```

### 👤 Adding a Student

```
🎯 Enter your choice: 7

╔══════════════════════════════════════════════════════════╗
║                   👤 ADD STUDENT 👤                      ║
╚══════════════════════════════════════════════════════════╝

🏷️  Enter the student ID: 12345
👤 Enter the student's name: John Doe

✅ ═══════════════════════════════════════════════════════
   👤 STUDENT ADDED SUCCESSFULLY! 👤
   ═══════════════════════════════════════════════════════
```

### 📤 Borrowing a Book

```
🎯 Enter your choice: 9

╔══════════════════════════════════════════════════════════╗
║                   📤 BORROW BOOK 📤                      ║
╚══════════════════════════════════════════════════════════╝

👤 Enter student's name: John Doe
📖 Enter book title: The C Programming Language
✅ Book borrowed successfully!

✅ ═══════════════════════════════════════════════════════
   📤 BOOK BORROWED SUCCESSFULLY! 📤
   ═══════════════════════════════════════════════════════
```

---

## 📈 Performance

### ⚡ Time Complexity

| Operation | Best Case | Average Case | Worst Case |
|-----------|-----------|--------------|------------|
| **Add Book** | O(1) | O(1) | O(n)* |
| **Search** | O(1) | O(n) | O(n×m) |
| **Remove** | O(1) | O(n) | O(n) |
| **Display** | O(n) | O(n×m) | O(n×m) |

*\*When resizing is needed*

### 💾 Space Complexity

- **Base Library**: O(1) + O(capacity)
- **Per Book**: O(title_length + Σ(author_lengths))
- **Total System**: O(n × average_book_size)

### 🚀 Performance Optimizations

```c
// Efficient memory usage
- Dynamic allocation prevents waste
- Exponential growth strategy for resizing
- Immediate cleanup prevents memory leaks
- Case-insensitive search with early termination
```

---

## 🛠️ Advanced Features

### 🔮 Current Implementation Status

| Feature | Status | Description |
|---------|--------|-------------|
| 👥 **Student Management** | ✅ Implemented | Full student registration and tracking |
| 📚 **Book Borrowing** | ✅ Implemented | Complete lending system with limits |
| 🎨 **Enhanced Visuals** | ✅ Implemented | Beautiful console interface |
| 💾 **File Persistence** | 🔴 Future | Save/load library data |
| 🌐 **Network Support** | 🔴 Future | Multi-user access |

### 🏗️ Student System Architecture (Implemented)

```c
// Student management structures (fully implemented)
typedef struct {
    int student_id;        // Unique student identifier
    char *name;           // Dynamic student name
    char **borrowed_books; // Array of borrowed book titles
    int borrowed_count;    // Current number of borrowed books
    int max_books;         // Maximum borrowing limit (default: 3)
} Student;

typedef struct {
    Student *students;     // Dynamic array of students
    int student_count;     // Current number of students
    int student_capacity;  // Maximum student capacity
} StudentSystem;
```

---

## 🔮 Future Enhancements

### 📅 Roadmap

#### Phase 1: Student Management 👥 (✅ COMPLETED)
- [x] Implement student registration
- [x] Book borrowing/returning system
- [x] Student borrowing limits and tracking
- [x] Enhanced student statistics
- [x] Beautiful visual interface enhancements

#### Phase 2: Data Persistence 💾 (NEXT PRIORITY)
- [ ] File-based storage (CSV/JSON)
- [ ] Database integration (SQLite)
- [ ] Backup and restore functionality
- [ ] Data import/export
- [ ] Configuration file support

#### Phase 3: Advanced Features 🌟
- [ ] GUI interface (GTK/Qt)
- [ ] Web interface (HTML/CSS/JavaScript)
- [ ] Network multi-user support
- [ ] Advanced reporting and analytics
- [ ] Book reservation system
- [ ] Overdue book tracking with fines

#### Phase 4: Enterprise Features 🏢
- [ ] User authentication and authorization
- [ ] Role-based access control (Admin/Librarian/Student)
- [ ] Audit logging and activity tracking
- [ ] RESTful API development
- [ ] Integration with external library systems

---

<div align="center">

## 🤝 Contributing

Contributions are welcome! Please feel free to submit a Pull Request.

## 📄 License

This project is open source and available under the [MIT License](LICENSE).

## 👨‍💻 Author

**Raffaele** - *Library_System Creator*

---

*Built with ❤️ and lots of ☕ using C programming language*

**⭐ Star this repository if you liked it**

</div>
