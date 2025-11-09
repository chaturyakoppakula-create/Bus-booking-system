#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 100
#define STRLEN 50

typedef struct {
    int ticket_no;
    char passenger[STRLEN];
    char route[STRLEN];
    int seat_no;
    double fare;
} Ticket;

Ticket tickets[MAX];
int count = 0;

void read_line(char *buf, int n) {
    if (fgets(buf, n, stdin)) {
        size_t len = strlen(buf);
        if (len && buf[len-1] == '\n') buf[len-1] = '\0';
    }
}

int find_index_by_ticket(int ticket_no) {
    for (int i = 0; i < count; ++i)
        if (tickets[i].ticket_no == ticket_no) return i;
    return -1;
}

void add_booking() {
    if (count >= MAX) { printf("Storage full.\n"); return; }
    Ticket t;
    char buf[STRLEN];

    printf("Enter Ticket No (integer): ");
    read_line(buf, sizeof buf);
    t.ticket_no = atoi(buf);
    if (find_index_by_ticket(t.ticket_no) != -1) { printf("Ticket number already exists.\n"); return; }

    printf("Enter Passenger Name: ");
    read_line(t.passenger, STRLEN);
    printf("Enter Route: ");
    read_line(t.route, STRLEN);

    printf("Enter Seat No (integer): ");
    read_line(buf, sizeof buf);
    t.seat_no = atoi(buf);

    printf("Enter Fare: ");
    read_line(buf, sizeof buf);
    t.fare = atof(buf);

    tickets[count++] = t;
    printf("Booking added.\n");
}

void display_all() {
    if (count == 0) { printf("No bookings.\n"); return; }
    printf("\n%-8s %-20s %-20s %-8s %8s\n", "Ticket", "Passenger", "Route", "Seat", "Fare");
    printf("---------------------------------------------------------------\n");
    for (int i = 0; i < count; ++i) {
        printf("%-8d %-20s %-20s %-8d %8.2f\n",
               tickets[i].ticket_no, tickets[i].passenger, tickets[i].route, tickets[i].seat_no, tickets[i].fare);
    }
}

void search_by_route() {
    char key[STRLEN];
    printf("Enter route to search: ");
    read_line(key, STRLEN);
    int found = 0;
    for (int i = 0; i < count; ++i) {
        if (strstr(tickets[i].route, key) != NULL) {
            if (!found) printf("Matches:\n");
            printf("%d: %s, Seat %d, Fare %.2f\n",
                   tickets[i].ticket_no, tickets[i].passenger, tickets[i].seat_no, tickets[i].fare);
            found = 1;
        }
    }
    if (!found) printf("No bookings found for that route.\n");
}

void cancel_ticket() {
    char buf[STRLEN];
    printf("Enter Ticket No to cancel: ");
    read_line(buf, sizeof buf);
    int tno = atoi(buf);
    int idx = find_index_by_ticket(tno);
    if (idx == -1) { printf("Ticket not found.\n"); return; }
    for (int i = idx; i < count - 1; ++i) tickets[i] = tickets[i+1];
    count--;
    printf("Ticket canceled.\n");
}

void update_fare() {
    char buf[STRLEN];
    printf("Enter Ticket No to update fare: ");
    read_line(buf, sizeof buf);
    int tno = atoi(buf);
    int idx = find_index_by_ticket(tno);
    if (idx == -1) { printf("Ticket not found.\n"); return; }
    printf("Current fare: %.2f\n", tickets[idx].fare);
    printf("Enter new fare: ");
    read_line(buf, sizeof buf);
    tickets[idx].fare = atof(buf);
    printf("Fare updated.\n");
}

void menu() {
    printf("\n=== Bus Ticket Management ===\n");
    printf("1. Add Booking\n2. Display All\n3. Search by Route\n4. Cancel Ticket\n5. Update Fare\n6. Exit\n");
    printf("Choose option: ");
}

int main() {
    char buf[STRLEN];
    while (1) {
        menu();
        read_line(buf, sizeof buf);
        int opt = atoi(buf);
        switch (opt) {
            case 1: add_booking(); break;
            case 2: display_all(); break;
            case 3: search_by_route(); break;
            case 4: cancel_ticket(); break;
            case 5: update_fare(); break;
            case 6: printf("Goodbye!\n"); return 0;
            default: printf("Invalid option.\n");
        }
    }
    return 0;
}