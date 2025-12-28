#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME 50

// Task structure
typedef struct Task {
    int id;
    char name[MAX_NAME];
    int priority;
    struct Task* next;
} Task;

// Stack node for undo functionality
typedef struct StackNode {
    Task task;
    struct StackNode* next;
} StackNode;

// Queue structure for processing tasks
typedef struct Queue {
    Task* front;
    Task* rear;
} Queue;

// Global variables
Task* taskList = NULL;  // Linked list of tasks
StackNode* undoStack = NULL;  // Stack for undo
Queue* processQueue = NULL;  // Queue for processing
int taskCounter = 1;

// Function prototypes
void initQueue();
void addTask(char* name, int priority);
void displayTasks();
void undoLastTask();
void pushToStack(Task task);
Task popFromStack();
void enqueue(Task task);
Task dequeue();
void processNextTask();
void processBatch();
void displayQueue();
int isQueueEmpty();
void freeMemory();

// Initialize queue
void initQueue() {
    processQueue = (Queue*)malloc(sizeof(Queue));
    processQueue->front = NULL;
    processQueue->rear = NULL;
}

// Push task to undo stack
void pushToStack(Task task) {
    StackNode* newNode = (StackNode*)malloc(sizeof(StackNode));
    newNode->task = task;
    newNode->next = undoStack;
    undoStack = newNode;
}

// Pop task from undo stack
Task popFromStack() {
    Task task;
    task.id = -1;  // Invalid task
    
    if (undoStack == NULL) {
        return task;
    }
    
    StackNode* temp = undoStack;
    task = temp->task;
    undoStack = undoStack->next;
    free(temp);
    return task;
}

// Add task to linked list
void addTask(char* name, int priority) {
    Task* newTask = (Task*)malloc(sizeof(Task));
    newTask->id = taskCounter++;
    strcpy(newTask->name, name);
    newTask->priority = priority;
    newTask->next = NULL;
    
    // Add to end of linked list
    if (taskList == NULL) {
        taskList = newTask;
    } else {
        Task* temp = taskList;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newTask;
    }
    
    // Push to undo stack
    pushToStack(*newTask);
    
    printf("\n✓ Task added: [ID: %d] %s (Priority: %d)\n", 
           newTask->id, newTask->name, newTask->priority);
}

// Display all tasks in the list
void displayTasks() {
    if (taskList == NULL) {
        printf("\n Task list is empty.\n");
        return;
    }
    
    printf("\n Current Task List:\n");
    printf("%-5s %-30s %-10s\n", "ID", "Task Name", "Priority");
    printf("--------------------------------------------------\n");
    
    Task* temp = taskList;
    while (temp != NULL) {
        printf("%-5d %-30s %-10d\n", temp->id, temp->name, temp->priority);
        temp = temp->next;
    }
}

// Undo last added task
void undoLastTask() {
    Task lastTask = popFromStack();
    
    if (lastTask.id == -1) {
        printf("\n⚠ Nothing to undo!\n");
        return;
    }
    
    // Remove from linked list
    if (taskList == NULL) {
        printf("\n⚠ Task list is empty!\n");
        return;
    }
    
    Task* temp = taskList;
    Task* prev = NULL;
    
    // Find and remove the task
    while (temp != NULL && temp->id != lastTask.id) {
        prev = temp;
        temp = temp->next;
    }
    
    if (temp != NULL) {
        if (prev == NULL) {
            taskList = temp->next;
        } else {
            prev->next = temp->next;
        }
        free(temp);
        printf("\n↶ Undone: [ID: %d] %s\n", lastTask.id, lastTask.name);
    }
}

// Enqueue task for processing
void enqueue(Task task) {
    Task* newTask = (Task*)malloc(sizeof(Task));
    *newTask = task;
    newTask->next = NULL;
    
    if (processQueue->rear == NULL) {
        processQueue->front = processQueue->rear = newTask;
    } else {
        processQueue->rear->next = newTask;
        processQueue->rear = newTask;
    }
}

// Dequeue task from processing queue
Task dequeue() {
    Task task;
    task.id = -1;
    
    if (processQueue->front == NULL) {
        return task;
    }
    
    Task* temp = processQueue->front;
    task = *temp;
    processQueue->front = processQueue->front->next;
    
    if (processQueue->front == NULL) {
        processQueue->rear = NULL;
    }
    
    free(temp);
    return task;
}

// Check if queue is empty
int isQueueEmpty() {
    return processQueue->front == NULL;
}

// Display processing queue
void displayQueue() {
    if (isQueueEmpty()) {
        printf("\n Processing queue is empty.\n");
        return;
    }
    
    printf("\n Processing Queue:\n");
    printf("%-5s %-30s %-10s\n", "ID", "Task Name", "Priority");
    printf("--------------------------------------------------\n");
    
    Task* temp = processQueue->front;
    while (temp != NULL) {
        printf("%-5d %-30s %-10d\n", temp->id, temp->name, temp->priority);
        temp = temp->next;
    }
}

// Move all tasks to processing queue
void processBatch() {
    if (taskList == NULL) {
        printf("\n⚠ No tasks to process!\n");
        return;
    }
    
    printf("\n Moving tasks to processing queue...\n");
    
    Task* temp = taskList;
    int count = 0;
    while (temp != NULL) {
        enqueue(*temp);
        count++;
        temp = temp->next;
    }
    
    printf("✓ %d task(s) queued for processing.\n", count);
}

// Process next task from queue
void processNextTask() {
    Task task = dequeue();
    
    if (task.id == -1) {
        printf("\n⚠ No tasks in processing queue!\n");
        return;
    }
    
    printf("\n⚙ Processing: [ID: %d] %s (Priority: %d)\n", 
           task.id, task.name, task.priority);
    printf("✓ Task completed!\n");
}

// Free all allocated memory
void freeMemory() {
    // Free task list
    Task* temp = taskList;
    while (temp != NULL) {
        Task* next = temp->next;
        free(temp);
        temp = next;
    }
    
    // Free undo stack
    while (undoStack != NULL) {
        StackNode* next = undoStack->next;
        free(undoStack);
        undoStack = next;
    }
    
    // Free processing queue
    while (!isQueueEmpty()) {
        dequeue();
    }
    free(processQueue);
}

// Main menu
void displayMenu() {
    printf("\n");
    printf(" =======================================\n");
    printf("||      TASK SCHEDULER SYSTEM          || \n");
    printf(" =======================================\n");
    printf("1. Add Task\n");
    printf("2. Display Task List\n");
    printf("3. Undo Last Task\n");
    printf("4. Move Tasks to Processing Queue\n");
    printf("5. Display Processing Queue\n");
    printf("6. Process Next Task\n");
    printf("7. Exit\n");
    printf("------------------------------------------\n");
    printf("Enter your choice: ");
}

int main() {
    initQueue();
    int choice, priority;
    char name[MAX_NAME];
    
    printf("\n Welcome to Task Scheduler System!\n");
    
    while (1) {
        displayMenu();
        scanf("%d", &choice);
        getchar(); // Consume newline
        
        switch (choice) {
            case 1:
                printf("\nEnter task name: ");
                fgets(name, MAX_NAME, stdin);
                name[strcspn(name, "\n")] = 0; // Remove newline
                
                printf("Enter priority (1-10): ");
                scanf("%d", &priority);
                
                addTask(name, priority);
                break;
                
            case 2:
                displayTasks();
                break;
                
            case 3:
                undoLastTask();
                break;
                
            case 4:
                processBatch();
                break;
                
            case 5:
                displayQueue();
                break;
                
            case 6:
                processNextTask();
                break;
                
            case 7:
                printf("\n Thank you for using Task Scheduler!\n");
                freeMemory();
                exit(0);
                
            default:
                printf("\n⚠ Invalid choice! Please try again.\n");
        }
    }
    
    return 0;
}
