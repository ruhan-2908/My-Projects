#include <stdio.h>
#include <string.h>

#define MAX_SEATS 10

struct Passenger {
    char name[50];
    int age;
    char gender[10];
    int seatNumber;
    char travelDate[15];
    int booked;
};

struct Passenger train[MAX_SEATS];
char trainName[50];

void initializeTrain();
void bookTicket();
void checkAvailability();
void cancelTicket();
void prepareChart();
void recursiveMenu();
int getNextAvailableSeat();

int main() {
    printf("\033[35mEnter Train Name: \033[0m");
    scanf(" %49[^\n]", trainName);
    initializeTrain();
    recursiveMenu();
    return 0;
}

void recursiveMenu() {
    int choice;
    printf("\n\033[36m--- Railway Reservation System ---\033[0m\n");
    printf("\033[33mTrain:\033[0m \033[32m%s\033[0m\n", trainName);
    printf("\033[34m1. Book Ticket\033[0m\n");
    printf("\033[34m2. Check Availability\033[0m\n");
    printf("\033[34m3. Cancel Ticket\033[0m\n");
    printf("\033[34m4. Prepare Chart\033[0m\n");
    printf("\033[34m5. Exit\033[0m\n");
    printf("\033[36mEnter your choice: \033[0m");
    scanf("%d", &choice);
    getchar();

    switch (choice) {
        case 1:
            bookTicket();
            break;
        case 2:
            checkAvailability();
            break;
        case 3:
            cancelTicket();
            break;
        case 4:
            prepareChart();
            break;
        case 5:
            printf("\033[32mThank you for using the Railway Reservation System.\033[0m\n");
            return;
        default:
            printf("\033[31mInvalid choice. Try again.\033[0m\n");
    }
    recursiveMenu();
}

void initializeTrain() {
    for (int i = 0; i < MAX_SEATS; i++) {
        train[i].booked = 0;
        train[i].seatNumber = i + 1;
        strcpy(train[i].name, "");
        strcpy(train[i].gender, "");
        strcpy(train[i].travelDate, "");
        train[i].age = 0;
    }
}

void bookTicket() {
    int seat = getNextAvailableSeat();
    if (seat == -1) {
        printf("\033[31mAll seats are booked.\033[0m\n");
        return;
    }

    printf("\033[35mEnter passenger name: \033[0m");
    scanf(" %49[^\n]", train[seat].name);

    printf("\033[35mEnter gender (Male/Female/Other): \033[0m");
    scanf(" %9[^\n]", train[seat].gender);

    printf("\033[35mEnter age: \033[0m");
    scanf("%d", &train[seat].age);
    getchar();

    printf("\033[35mEnter travel date (DD-MM-YYYY): \033[0m");
    scanf(" %14[^\n]", train[seat].travelDate);

    train[seat].booked = 1;

    printf("\033[32mTicket booked successfully! Seat number: %d\033[0m\n", train[seat].seatNumber);
}

void checkAvailability() {
    int available = 0;
    printf("\033[36mAvailable seats:\033[0m\n");
    for (int i = 0; i < MAX_SEATS; i++) {
        if (train[i].booked == 0) {
            printf("\033[32mSeat %d is available.\033[0m\n", train[i].seatNumber);
            available = 1;
        }
    }
    if (!available) {
        printf("\033[31mNo seats available.\033[0m\n");
    }
}

void cancelTicket() {
    int seatNum;
    printf("\033[35mEnter seat number to cancel (1 to %d): \033[0m", MAX_SEATS);
    scanf("%d", &seatNum);
    getchar();

    if (seatNum < 1 || seatNum > MAX_SEATS || train[seatNum - 1].booked == 0) {
        printf("\033[31mInvalid seat number or seat not booked.\033[0m\n");
        return;
    }

    train[seatNum - 1].booked = 0;
    strcpy(train[seatNum - 1].name, "");
    strcpy(train[seatNum - 1].gender, "");
    strcpy(train[seatNum - 1].travelDate, "");
    train[seatNum - 1].age = 0;

    printf("\033[32mTicket cancelled for seat %d.\033[0m\n", seatNum);
}

void prepareChart() {
    int found = 0;
    printf("\n\033[36m--- Reservation Chart ---\033[0m\n");
    printf("\033[33mTrain: \033[0m\033[32m%s\033[0m\n", trainName);
    for (int i = 0; i < MAX_SEATS; i++) {
        if (train[i].booked == 1) {
            printf("\033[34mSeat %d:\033[0m \033[35m%s\033[0m | \033[36mAge:\033[0m %d | \033[36mGender:\033[0m %s | \033[36mDate:\033[0m %s\n",
                   train[i].seatNumber,
                   train[i].name,
                   train[i].age,
                   train[i].gender,
                   train[i].travelDate);
            found = 1;
        }
    }
    if (!found) {
        printf("\033[31mNo bookings yet.\033[0m\n");
    }
}

int getNextAvailableSeat() {
    for (int i = 0; i < MAX_SEATS; i++) {
        if (train[i].booked == 0) {
            return i;
        }
    }
    return -1;
}
