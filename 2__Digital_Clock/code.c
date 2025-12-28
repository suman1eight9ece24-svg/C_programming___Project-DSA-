#include <stdio.h>
#include <stdlib.h>
#include<time.h>

#ifdef _WIN32
#include <windows.h>
#define SLEEP(x) Sleep(x * 1000) // milliseconds
#define CLEAR "cls"
#else
#include <unistd.h>
#define SLEEP(x) sleep(x) // seconds
#define CLEAR "clear"
#endif

//========================== Count Down ==========================
int count_down(){
    int h=0,m=0,s=0;
    int Total=0;

    system(CLEAR);
//------------------user  input-------------------
    printf("========USER INPUT=========\n");
    printf("Enter hour : ");
    scanf("%d", &h);
    printf("Enter minute : ");
    scanf("%d", &m);
    printf("Enter second : ");
    scanf("%d",&s);

//---------------------------------corner  case  condition ----------------------
    if(h<0 && m<0 || m>59 && s<0 || s>59){
        printf("PLEASE !!  \n  !! recheck your enter value !!\n");
        return 1;
    }
// --------------------------------- total-------------------------------
 Total=h*3600+ m*60 +s;
//---------------------------------corner  case  condition ----------------------
    if (Total == 0) {
        printf("Timer cannot be zero!\n");
        return 1;
    }

    printf("Press Ctrl+C to stop.\n");
    printf("========================\n");
    
    // Countdown loop
    while (Total >= 0) {
        // Convert back to hours, minutes, seconds for display
        h = Total / 3600;
        m = (Total % 3600) / 60;
        s = Total % 60;
        
        // Display countdown
        printf("\rTime Left: %02d:%02d:%02d", h, m, s);
        fflush(stdout);
        
        SLEEP(1); // Wait 1 second
        Total--; // Decrease by 1 second
    }
    
    // Timer finished
    printf("\n\n------------------------\n");
    printf("TIME'S UP! \n");
    printf("========================\n");
    
}

//=========================== Current Time ===========================
void current_time(){
    time_t now; // to ascces current time or date
    struct tm*local; // use the library pointer
    
    time(&now);     // current time
    local = localtime(&now);     // local time reprsentation 

    printf("DATE :- %2d:%2d:%2d\n",local->tm_mday,local->tm_mon+1,local->tm_year+1900);
    printf("TIME :- %2d:%2d:%2d\n",local->tm_hour,local->tm_min,local->tm_sec);

}

//=========================== Stop Watch =============================
void stop_watch() {
    int h = 0, m = 0, s = 0;
    
    // Clear screen once at the beginning
    system(CLEAR);
    
    // Display header (only once)
    printf("Simple Stopwatch\n");
    printf("Press Ctrl+C to stop.\n");
    printf("=====================\n");
    //printf("Time: ");
    
    while (1) {
        // Use \r to overwrite the same line instead of clearing screen
        printf("\rTime: %02d:%02d:%02d", h, m, s);
        fflush(stdout); // Force output to display immediately
        
        SLEEP(1); // wait 1 second
        s++;

        if (s == 60) {
            s = 0;
            m++;
            if (m == 60) {
                m = 0;
                h++;
            }
        }
    }
}

//====================================================================
int main(){
    printf("==========================\n");
    printf("||     Digital Clock    ||\n");
    printf("==========================\n");

    printf("1.Time \n");
    printf("2.Stop Watch \n");
    printf("3.Count Down \n");

    int choise;
    printf("Enter Choise :- ");
    scanf("%d",&choise);

    switch(choise){
        case 1: current_time();
            break;
        case 2: stop_watch();
            break;
        case 3: count_down();
            break;
        default :
            printf("!! Invalid Choise !!\n");
    }

    return 0;
}
