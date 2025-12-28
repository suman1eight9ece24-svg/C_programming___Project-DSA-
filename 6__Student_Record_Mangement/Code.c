#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct student {
    int roll;
    char name[100];
    float cgpa;
    struct student *next;
};

struct student *head = NULL;


void addStudent() {
    struct student *newNode = malloc(sizeof(struct student));

    printf("Enter roll: ");
    scanf("%d", &newNode->roll);

    printf("Enter name: ");
    scanf("%s", newNode->name);

    printf("Enter CGPA: ");
    scanf("%f", &newNode->cgpa);

    newNode->next = NULL;

    if (head == NULL)
        head = newNode;
    else {
        struct student *temp = head;
        while (temp->next != NULL)
            temp = temp->next;
        temp->next = newNode;
    }
}

void deleteStudent() {
    int Roll;
    printf("Enter roll to delete: ");
    scanf("%d", &Roll);

    struct student *temp = head, *prev = NULL;

    if (temp != NULL && temp->roll == Roll) {
        head = temp->next;
        free(temp);
        return;
    }

    while (temp != NULL && temp->roll != Roll) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("Student not found\n");
        return;
    }

    prev->next = temp->next;
    free(temp);
}

void searchStudent() {
    int roll;
    printf("Enter roll to search: ");
    scanf("%d", &roll);

    struct student *temp = head;
    while (temp != NULL) {
        if (temp->roll == roll) {
            printf("Found: %s %.2f\n", temp->name, temp->cgpa);
            return;
        }
        temp = temp->next;
    }
    printf("Student not found\n");
}

void updateMarks() {
    int Roll;
    printf("Enter roll number: ");
    scanf("%d", &Roll);

    struct student *temp = head;
    while (temp != NULL) {
        if (temp->roll == Roll) {
            printf("Enter new CGPA: ");
            scanf("%f", &temp->cgpa);
            return;
        }
        temp = temp->next;
    }
}

void sortByMarks() {
    struct student *i, *j;
    int tempRoll;
    float tempCGPA;
    char tempName[100];

    for (i = head; i != NULL; i = i->next) {
        for (j = i->next; j != NULL; j = j->next) {
            if (i->cgpa > j->cgpa) {
                tempRoll = i->roll;
                i->roll = j->roll;
                j->roll = tempRoll;

                strcpy(tempName, i->name);
                strcpy(i->name, j->name);
                strcpy(j->name, tempName);

                tempCGPA = i->cgpa;
                i->cgpa = j->cgpa;
                j->cgpa = tempCGPA;
            }
        }
    }
}

void display() {
    struct student *temp = head;
    while (temp != NULL) {
        printf("Roll:%d Name:%s CGPA:%.2f\n",
               temp->roll, temp->name, temp->cgpa);
        temp = temp->next;
    }
}


int main() {
    int choice;
    do {
        printf("\n1.Add 2.Delete 3.Search 4.Update 5.Sort 6.Display 0.Exit\n");
        scanf("%d", &choice);

        switch (choice) {
        case 1: addStudent(); break;
        case 2: deleteStudent(); break;
        case 3: searchStudent(); break;
        case 4: updateMarks(); break;
        case 5: sortByMarks(); break;
        case 6: display(); break;
        }
    } while (choice != 0);

    return 0;
}
