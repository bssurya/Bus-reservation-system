#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SEATS 30
#define MAX_NAME_LENGTH 50

// Enum for seating classes
typedef enum {
    ECONOMY,
    BUSINESS,
    FIRST_CLASS,
    SENIOR
} SeatClass;

// Enum for food options
typedef enum {
    NO_FOOD,
    SNACKS,
    MEAL,
    LUXURY_MEAL
} FoodOption;

// Structure to represent a booking
struct Booking {
    int seatNumber;
    char passengerName[MAX_NAME_LENGTH];
    SeatClass seatClass;
    FoodOption foodOption;
    char startingPlace[50];
    char destinationPlace[50];
};

// Function prototypes
void displayMenu();
void bookSeat(struct Booking bookings[], bool seats[], int *numBookings);
void cancelBooking(struct Booking bookings[], bool seats[], int *numBookings);
void displaySeats(bool seats[]);
void displayBookings(struct Booking bookings[], int numBookings);
SeatClass selectSeatClass();
FoodOption selectFoodOption();

int main() {
    bool seats[MAX_SEATS] = {false}; // Initialize all seats as available
    struct Booking bookings[MAX_SEATS]; // Array to store bookings
    int numBookings = 0; // Number of current bookings

    int choice;
    do {
        displayMenu();
        scanf("%d", &choice);
        getchar(); // Clear newline from input buffer

        switch (choice) {
            case 1:
                bookSeat(bookings, seats, &numBookings);
                break;
            case 2:
                cancelBooking(bookings, seats, &numBookings);
                break;
            case 3:
                displaySeats(seats);
                break;
            case 4:
                displayBookings(bookings, numBookings);
                break;
            case 5:
                printf("Thank you, Please Visit Again...\n");
                break;
            default:
                printf("Invalid choice. Please enter again.\n");
        }
    } while (choice != 5);

    return 0;
}

// Function to display menu options
void displayMenu() {
    printf("\nWelcome to Bus Reservation System\n");
    printf("1. Book a seat\n");
    printf("2. Cancel booking\n");
    printf("3. Display seat availability\n");
    printf("4. Display bookings\n");
    printf("5. Exit\n");
    printf("Enter your choice: ");
}

// Function to book a seat
void bookSeat(struct Booking bookings[], bool seats[], int *numBookings) {
    if (*numBookings == MAX_SEATS) {
        printf("Sorry, the bus is fully booked.\n");
        return;
    }

    int seatNum;
    printf("Enter seat number (1-%d): ", MAX_SEATS);
    scanf("%d", &seatNum);
    getchar(); // Clear newline from input buffer

    if (seatNum < 1 || seatNum > MAX_SEATS) {
        printf("Invalid seat number.\n");
        return;
    }

    if (seats[seatNum - 1]) {
        printf("Seat %d is already booked.\n", seatNum);
    } else {
        struct Booking newBooking;
        printf("Enter passenger name: ");
        fgets(newBooking.passengerName, MAX_NAME_LENGTH, stdin);
        newBooking.passengerName[strcspn(newBooking.passengerName, "\n")] = '\0'; // Remove trailing newline
        newBooking.seatNumber = seatNum;
        newBooking.seatClass = selectSeatClass();
        newBooking.foodOption = selectFoodOption();
        printf("Enter starting place: ");
        fgets(newBooking.startingPlace, 50, stdin);
        newBooking.startingPlace[strcspn(newBooking.startingPlace, "\n")] = '\0'; // Remove trailing newline
        printf("Enter destination place: ");
        fgets(newBooking.destinationPlace, 50, stdin);
        newBooking.destinationPlace[strcspn(newBooking.destinationPlace, "\n")] = '\0'; // Remove trailing newline
        seats[seatNum - 1] = true;
        bookings[*numBookings] = newBooking;
        (*numBookings)++;
        printf("Seat %d booked successfully for %s.\n", seatNum, newBooking.passengerName);
    }
}

// Function to cancel a booking
void cancelBooking(struct Booking bookings[], bool seats[], int *numBookings) {
    if (*numBookings == 0) {
        printf("No bookings to cancel.\n");
        return;
    }

    int seatNum;
    printf("Enter seat number to cancel booking: ");
    scanf("%d", &seatNum);
    getchar(); // Clear newline from input buffer

    if (seatNum < 1 || seatNum > MAX_SEATS) {
        printf("Invalid seat number.\n");
        return;
    }

    bool found = false;
    for (int i = 0; i < *numBookings; ++i) {
        if (bookings[i].seatNumber == seatNum) {
            found = true;
            printf("Booking for seat %d (Passenger: %s) canceled successfully.\n", seatNum, bookings[i].passengerName);
            seats[seatNum - 1] = false;
            for (int j = i; j < *numBookings; ++j) {
                bookings[j] = bookings[j + 1];
            }
            (*numBookings)--;
            break;
        }
    }
    if (!found) {
        printf("No booking found for seat %d.\n", seatNum);
    }
}

// Function to display seat availability
void displaySeats(bool seats[]) {
    printf("Seat Availability:\n");
    for (int i = 0; i < MAX_SEATS; ++i) {
        if (seats[i]) {
            printf("Seat %d: Booked\n", i + 1);
        } else {
            printf("Seat %d: Available\n", i + 1);
        }
    }
}

// Function to display current bookings
void displayBookings(struct Booking bookings[], int numBookings) {
    printf("Current Bookings:\n");
    if (numBookings == 0) {
        printf("No bookings.\n");
    } else {
        for (int i = 0; i < numBookings; ++i) {
            printf("Seat %d: %s (Class: ", bookings[i].seatNumber, bookings[i].passengerName);
            switch (bookings[i].seatClass) {
                case ECONOMY:
                    printf("Economy");
                    break;
                case BUSINESS:
                    printf("Business");
                    break;
                case FIRST_CLASS:
                    printf("First Class");
                    break;
                case SENIOR:
                    printf("Senior");
                    break;
            }
            printf(", Food: ");
            switch (bookings[i].foodOption) {
                case NO_FOOD:
                    printf("None");
                    break;
                case SNACKS:
                    printf("Snacks");
                    break;
                case MEAL:
                    printf("Meal");
                    break;
                case LUXURY_MEAL:
                    printf("Luxury Meal");
                    break;
            }
            printf(", Starting Place: %s, Destination: %s)\n", bookings[i].startingPlace, bookings[i].destinationPlace);
        }
    }
}

// Function to select seat class
SeatClass selectSeatClass() {
    int choice;
    printf("Select seat class:\n");
    printf("1. Economy\n");
    printf("2. Business\n");
    printf("3. First Class\n");
    printf("4. Senior\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);
    getchar(); // Clear newline from input buffer

    switch (choice) {
        case 1:
            return ECONOMY;
        case 2:
            return BUSINESS;
        case 3:
            return FIRST_CLASS;
        case 4:
            return SENIOR;
        default:
            printf("Invalid choice, defaulting to Economy class.\n");
            return ECONOMY;
    }
}

// Function to select food option
FoodOption selectFoodOption() {
    int choice;
    printf("Select food option:\n");
    printf("1. No Food\n");
    printf("2. Snacks\n");
    printf("3. Meal\n");
    printf("4. Luxury Meal\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);
    getchar(); // Clear newline from input buffer

    switch (choice) {
        case 1:
            return NO_FOOD;
        case 2:
            return SNACKS;
        case 3:
            return MEAL;
        case 4:
            return LUXURY_MEAL;
        default:
            printf("Invalid choice, defaulting to No Food.\n");
            return NO_FOOD;
    }
}
