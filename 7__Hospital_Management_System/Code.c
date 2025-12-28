#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include<time.h>
void Date_Day(){
    time_t t;
    time(&t);

    struct tm *now = localtime(&t);
        char *days[] = {
        "Sunday", "Monday", "Tuesday",
        "Wednesday", "Thursday", "Friday", "Saturday"
    };

    printf("Day : %s __", days[now->tm_wday]);


    printf("Date : %d-%d-%d\n",
        now->tm_mday,
        now->tm_mon + 1,
        now->tm_year + 1900);
}

void Time(){
    time_t t;
    time(&t);
    struct tm *now = localtime(&t);
        printf("Time : %d:%d:%d\n",
           now->tm_hour,
           now->tm_min,
           now->tm_sec);
}


#define Max 100

struct pataint{
    int ID;
    float age;
    char name[50];
    int priority; // only use for EMERGENCY case
};

int front = 0;
int rear = -1;
struct pataint NormalQueue[Max];

void addNormal(){
    struct pataint q;

    printf("\n==============================\n");
    printf("        Pataint Data Fill       \n");
    printf("==============================\n");
    printf("TIME :- ");
    Time();

    printf("ID :- ");
    scanf("%d",&q.ID);
    printf("AGE :- ");
    scanf("%f",&q.age);
    printf("NAME :- ");
    scanf("%s",&q.name);

    NormalQueue[++rear] = q;
    printf("===============================\n");
    printf("Successfully Data Insert");
}

struct pataint EmegencyQueue[Max];
int epqSize = 0;
void addEnergency(){
    struct pataint q;

    printf("\n==============================\n");
    printf("        Pataint Data Fill       \n");
    printf("==============================\n");
    printf("TIME :- ");
    Time();

    printf("ID :- ");
    scanf("%d",&q.ID);
    printf("AGE :- ");
    scanf("%f",&q.age);
    printf("NAME :- ");
    scanf("%s",&q.name);
    printf("Priority :-\n 1.critical\n 2.serious\n 3.modarate\n");
    scanf("%d",&q.priority);

    EmegencyQueue[epqSize++] = q;

    /* Sort by priority (min first) */
    for (int i = 0; i < epqSize - 1; i++) {
        for (int j = i + 1; j < epqSize; j++) {
            if (EmegencyQueue[i].priority > EmegencyQueue[j].priority) {
                struct pataint temp = EmegencyQueue[i];
                EmegencyQueue[i] = EmegencyQueue[j];
                EmegencyQueue[j] = temp;
            }
        }
    }
    printf("Emergency patient added\n");
}

// Call next pataint to check-up
void callNext(){
    printf("TIME :- ");
    Time();

    if(epqSize>0){
        printf("========= Emergency Pataint ==========\n");
        struct pataint p = EmegencyQueue[0];
        printf("%d--%f--%s--(%d)\n",p.ID,p.age,p.name,p.priority);
        for (int i = 0; i < epqSize - 1; i++)
            EmegencyQueue[i] = EmegencyQueue[i + 1];
        epqSize--;
    }
    else if (front <= rear) {
        struct pataint p = NormalQueue[front++];
        printf("Calling NORMAL patient: %s\n", p.name);
    }
    else {
        printf("No patients waiting\n");
    }
}

void panding(){
    printf("Date & Day :- ");
    Date_Day();
    printf("TIME :- ");
    Time();

    if(epqSize > 0){
        printf("\n--- Emergency Patients ---\n");
        for (int i = 0; i < epqSize; i++)
            printf("%d--%f--%s--(%d)\n",EmegencyQueue[i].ID, EmegencyQueue[i].age,EmegencyQueue[i].name, EmegencyQueue[i].priority);
    }
    else if(front <= rear){        
        printf("\n--- Normal Patients ---\n");
        for (int i = front; i <= rear; i++)
            printf("%d--%s\n", NormalQueue[i].ID,NormalQueue[i].name);
    }
    else{
        printf("--------- Empty Pataint ------------");
    }
}

int main(){
    int choise;

    while(1){
    printf("\n==============================\n");
    printf("              Menu       \n");
    printf("==============================\n");
        printf("\n1. Add Normal Patient");
        printf("\n2. Add Emergency Patient");
        printf("\n3. Call Next Patient");
        printf("\n4. Show Pending List");
        printf("\n5. Exit\n");
        printf("Enter choice: \n");

        scanf("%d",&choise);

        switch (choise){
            case 1: addNormal(); 
                break;
            case 2: addEnergency();
                break;
            case 3: callNext(); 
                break;
            case 4: panding(); 
                break;
            case 5: exit(0);
        
            default: printf("Invalid choice\n");
        }
    }
}
