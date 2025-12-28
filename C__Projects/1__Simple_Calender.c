#include<stdio.h>

// Check if a year is a leap year
int LipYear(int year){
    if((year%4==0 && year%100!=0) || year%400==0)
        return 1;
    else
        return 0;
}

// Get the number of days in a month
int GetMonthDays(int month, int year){
    switch(month){
        case 1: case 3: case 5: case 7: case 8: case 10: case 12: 
            return 31;
        
        case 2: 
            if(LipYear(year))
                return 29;
            else
                return 28;
        
        case 4: case 6: case 9: case 11: 
            return 30;
        
        default:
            return 0;
    }
}

// Get the month name
void GetMonthName(int month){
    switch(month){
        case 1: printf("January"); break;
        case 2: printf("February"); break;
        case 3: printf("March"); break;
        case 4: printf("April"); break;
        case 5: printf("May"); break;
        case 6: printf("June"); break;
        case 7: printf("July"); break;
        case 8: printf("August"); break;
        case 9: printf("September"); break;
        case 10: printf("October"); break;
        case 11: printf("November"); break;
        case 12: printf("December"); break;
        default: printf("Invalid Month");
    }
}

// Calculate the starting day of month using Zeller's Congruence
int StartDay(int month, int year){
    if(month < 3){
        month += 12;
        year--;
    }
    int q = 1;
    int k = year % 100;
    int j = year / 100;
    int h = (q + (13*(month+1))/5 + k + k/4 + j/4 + 5*j) % 7;
    return h;
}

// Print calendar for a specific month
void PrintMonthCalendar(int month, int year){
    int firstday = StartDay(month, year);
    int totalDay = GetMonthDays(month, year);
    
    // Header
    printf("\n----------------------------------\n");
    printf("          ");
    GetMonthName(month);
    printf("  %d\n", year);
    printf("==================================\n");
    printf("Sun  Mon  Tue  Wed  Thu  Fri  Sat\n");
    
    // Print spaces before first day
    for(int i = 0; i < firstday; i++){
        printf("     ");
    }
    
    // Print all days of the month
    for(int day = 1; day <= totalDay; day++){
        printf("%4d ", day);
        
        if((day + firstday) % 7 == 0){
            printf("\n");
        }
    }
    
    // End of month
    if((totalDay + firstday) % 7 != 0){
        printf("\n");
    }
    printf("----------------------------------\n\n");
}

// Print full year calendar
void PrintYearCalendar(int year){
    printf("\n");
    printf("====================================\n");
    printf("         CALENDAR - %d\n", year);
    printf("====================================\n");
    
    for(int month = 1; month <= 12; month++){
        PrintMonthCalendar(month, year);
    }
}

int main(){
    int choice, month, year;
    
    printf("\n===== CALENDAR PROGRAM =====\n");
    printf("1. Display a specific month\n");
    printf("2. Display full year calendar\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);
    
    switch(choice){
        case 1:
            printf("Enter month (1-12): ");
            scanf("%d", &month);
            printf("Enter year: ");
            scanf("%d", &year);
            
            if(month < 1 || month > 12){
                printf("Invalid month!\n");
                return 1;
            }
            
            PrintMonthCalendar(month, year);
            break;
            
        case 2:
            printf("Enter year: ");
            scanf("%d", &year);
            PrintYearCalendar(year);
            break;
            
        default:
            printf("Invalid choice!\n");
            return 1;
    }
    
    return 0;
}
