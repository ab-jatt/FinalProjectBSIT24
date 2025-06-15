#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERS 3

struct account {
    char name[20];
    int pin;
    float balance;
};

void clear_screen() {
    system("cls"); // for Windows, use "clear" on Linux/Mac
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

int login(struct account users[], int *index) {
    char entered_name[20];
    int entered_pin;
    int tries = 3;

    while (tries--) {
        clear_screen();
        print_line();
        printf("           ATM LOGIN\n");
        print_line();
        printf("Enter username: ");
        scanf("%s", entered_name);
        printf("Enter PIN: ");
        scanf("%d", &entered_pin);

        for (int i = 0; i < MAX_USERS; i++) {
            if (strcmp(users[i].name, entered_name) == 0 && users[i].pin == entered_pin) {
                *index = i;
                return 1; // login success
            }
        }

        printf("Wrong username or PIN. Tries left: %d\n", tries);
        system("pause");
    }

    return 0; // login failed
}

void check_balance(struct account *user) {
    printf("Your current balance is: %.2f\n", user->balance);
}

void deposit_money(struct account *user) {
    float amount;
    printf("Enter amount to deposit: ");
    scanf("%f", &amount);

    if (amount > 0) {
        user->balance += amount;
        printf("Amount deposited successfully.\n");
    } else {
        printf("Invalid amount.\n");
    }
}

void withdraw_money(struct account *user) {
    float amount;
    printf("Enter amount to withdraw: ");
    scanf("%f", &amount);

    if (amount > 0 && amount <= user->balance) {
        user->balance -= amount;
        printf("Please collect your cash.\n");
    } else {
        printf("Invalid or insufficient balance.\n");
    }
}

void change_pin(struct account *user) {
    int old_pin, new_pin;
    printf("Enter current PIN: ");
    scanf("%d", &old_pin);

    if (old_pin == user->pin) {
        printf("Enter new PIN: ");
        scanf("%d", &new_pin);
        user->pin = new_pin;
        printf("PIN changed successfully.\n");
    } else {
        printf("Incorrect current PIN. Cannot change.\n");
    }
}

int main() {
    struct account users[MAX_USERS] = {
        {"john", 1111, 1000.0},
        {"jane", 2222, 1500.0},
        {"abdullah", 1234, 2000.0}
    };

    int user_index;

    if (!login(users, &user_index)) {
        printf("Too many failed attempts. Exiting.\n");
        return 0;
    }

    int choice;
    do {
        clear_screen();
        show_menu();
        scanf("%d", &choice);
        clear_screen();

        switch (choice) {
            case 1:
                check_balance(&users[user_index]);
                break;
            case 2:
                deposit_money(&users[user_index]);
                break;
            case 3:
                withdraw_money(&users[user_index]);
                break;
            case 4:
                change_pin(&users[user_index]);
                break;
            case 5:
                printf("Thank you for using our ATM.\n");
                break;
            default:
                printf("Invalid choice. Try again.\n");
        }

        if (choice != 5) {
            system("pause");
        }

    } while (choice != 5);

    return 0;
}
