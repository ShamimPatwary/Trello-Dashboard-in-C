# Trello Dashboard in C

A console-based task management system inspired by Trello, built in C. Manage your tasks with priorities, due dates, and status tracking - all from your terminal.


## 🧠 Core Data Structures

1. **Doubly Linked List**
   - Primary structure for task storage and manipulation
   - Each node contains:
     ```c
     typedef struct Task {
         uint8_t id;
         char title[MAX_TITLE_LENGTH];
         char description[MAX_DESCRIPTION_LENGTH];
         TaskStatus status;
         TaskPriority priority;
         Time create_date;
         Time due_date;
         struct Task* next;  // Forward pointer
         struct Task* prev;  // Backward pointer
     } Task;
     ```
   - Advantages:
     - O(1) insertion/deletion at head
     - Bidirectional traversal for efficient updates
     - Dynamic memory allocation for flexible sizing

2. **Bitfield Date Structure**
   - Compact date representation:
     ```c
     typedef struct {
         unsigned int year : 12;  // 0-4095
         unsigned int month : 4;  // 1-12
         unsigned int day : 5;    // 1-31
     } Time;
     ```
   - Memory efficient (only 3 bytes per date)
   - Built-in validation through bit limits

3. **File-Based Persistent Storage**
   - Binary file format with:
     - Header section (metadata)
     - Sequential task records
   - Memory-to-disk mapping:
     ```c
     fwrite(&task, sizeof(Task), 1, file);
     ```

## 🔧 System Architecture

1. **Memory Management**
   - Dynamic allocation via `malloc()` for tasks
   - Manual cleanup with `free()` on deletion
   - Reference counting for multi-ownership cases

2. **Algorithmic Complexities**
   | Operation        | Complexity | Notes                     |
   |-----------------|------------|---------------------------|
   | Add Task        | O(1)       | Insert at head            |
   | Delete Task     | O(n)       | Linear search by ID       |
   | Update Task     | O(n)       | Linear search             |
   | List All Tasks  | O(n)       | Full traversal            |
   | Search by Title | O(n)       | Linear scan               |

3. **Date Processing**
   - Overdue detection algorithm:
     ```c
     void update_overdue_tasks() {
         Time now = current_date();
         Task* current = tasks;
         while(current) {
             if(compare_days(current->due_date, now) < 0 
                && current->status != COMPLETED) {
                 current->status = OVERDUE;
             }
             current = current->next;
         }
     }
     ```

## 🚀 Advanced Features

1. **Priority-Based Scheduling**
   - Three-tier priority system (LOW/MEDIUM/HIGH)
   - Color-coded display in terminal

2. **Status Workflow Engine**
   ```mermaid
   stateDiagram
       [*] --> PENDING
       PENDING --> IN_PROGRESS: Start work
       IN_PROGRESS --> COMPLETED: Finish
       PENDING --> OVERDUE: Deadline passed
       IN_PROGRESS --> OVERDUE: Deadline passed

## ✨ Key Features
- **Task Management**
  - Add, view, edit, and delete tasks
  - Set priorities (Low/Medium/High)
  - Track status (Pending/In Progress/Completed/Overdue)
- **Smart Date Handling**
  - Automatic overdue detection
  - Date validation
- **Data Persistence**
  - Tasks saved between sessions
  - Secure credential storage

## 🛠️ Prerequisites
- C compiler (GCC recommended)
- Git (for cloning)
- Windows (for `system("cls")` compatibility)


## 🚀 Getting Started

### Installation
```bash
# Clone the repository
git clone https://github.com/your-username/trello-dashboard-c.git

# Navigate to project directory
cd trello-dashboard-c
