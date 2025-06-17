#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERS 3
#define MAX_LENGTH 20

char names[MAX_USERS][MAX_LENGTH] = {"john", "jane", "abdullah"};
int pins[MAX_USERS] = {1111, 2222, 1234};
float balances[MAX_USERS] = {1000.0, 1500.0, 2000.0};

void clear_screen() {
    system("cls"); 
}

void print_line() {
    printf("=====================================\n");
}

void show_menu() {
    print_line();
    printf("              ATM MENU\n");
    print_line();
    printf("1. Check Balance\n");
    printf("2. Deposit Money\n");
    printf("3. Withdraw Money\n");
    printf("4. Change PIN\n");
    printf("5. Exit\n");
    print_line();
    printf("Enter your choice: ");
}

int login(int *user_index) {
    char entered_name[MAX_LENGTH];
    int entered_pin;
    int tries = 3;

    while (tries > 0) {
        clear_screen();
        print_line();
        printf("           ATM LOGIN\n");
        print_line();
        printf("Enter username: ");
        scanf("%s", entered_name);
        printf("Enter PIN: ");
        scanf("%d", &entered_pin);

        for (int i = 0; i < MAX_USERS; i++) {
            if (strcmp(names[i], entered_name) == 0 && pins[i] == entered_pin) {
                *user_index = i;
                return 1;
            }
        }

        printf("Incorrect username or PIN. Tries left: %d\n", tries - 1);
        tries--;
        system("pause");
    }

    return 0;
}

void check_balance(int index) {
    printf("Your current balance is: %.2f\n", balances[index]);
}

void deposit_money(int index) {
    float amount;
    printf("Enter amount to deposit: ");
    scanf("%f", &amount);

    if (amount > 0) {
        balances[index] += amount;
        printf("Amount deposited successfully.\n");
    } else {
        printf("Invalid amount.\n");
    }
}

void withdraw_money(int index) {
    float amount;
    printf("Enter amount to withdraw: ");
    scanf("%f", &amount);

    if (amount > 0 && amount <= balances[index]) {
        balances[index] -= amount;
        printf("Please collect your cash.\n");
    } else {
        printf("Invalid or insufficient balance.\n");
    }
}

void change_pin(int index) {
    int old_pin, new_pin;
    printf("Enter current PIN: ");
    scanf("%d", &old_pin);

    if (old_pin == pins[index]) {
        printf("Enter new PIN: ");
        scanf("%d", &new_pin);
        pins[index] = new_pin;
        printf("PIN changed successfully.\n");
    } else {
        printf("Incorrect current PIN. Cannot change.\n");
    }
}

int main() {
    int user_index;

    if (!login(&user_index)) {
        printf("Too many failed attempts. Exiting.\n");
        return 0;
    }

    int choice;
    do {
        clear_screen();
        show_menu();
        scanf("%d", &choice);
        clear_screen();

        if (choice == 1) {
            check_balance(user_index);
        } else if (choice == 2) {
            deposit_money(user_index);
        } else if (choice == 3) {
            withdraw_money(user_index);
        } else if (choice == 4) {
            change_pin(user_index);
        } else if (choice == 5) {
            printf("Thank you for using our ATM.\n");
        } else {
            printf("Invalid choice. Try again.\n");
        }

        if (choice != 5) {
            system("pause");
        }

    } while (choice != 5);

    return 0;
}
