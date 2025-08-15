#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Account {
    int accountNumber;
    char name[100];
    char accountType;
    float balance;
};

// Function declarations
void newAccount();
void depositAccount();
void withdrawAccount();
void balanceAccount();
void allAccountHoldList();
void closeAnAccount();
void modifyAnAccount();

int main() {
    int option;

    do {
        printf("\n\n\t\t\t\tBANKING RECORD SYSTEM\n");
        printf("\t\t\t\t---------------------\n");

        printf("\nMAIN MENU");
        printf("\n01. NEW ACCOUNT");
        printf("\n02. DEPOSIT AMOUNT");
        printf("\n03. WITHDRAW AMOUNT");
        printf("\n04. BALANCE ENQUIRY");
        printf("\n05. ALL ACCOUNT HOLDER LIST");
        printf("\n06. CLOSE AN ACCOUNT");
        printf("\n07. MODIFY AN ACCOUNT");
        printf("\n08. EXIT");
        printf("\n\nSelect Your Option <1-8>: ");
        scanf("%d", &option);

        switch(option) {
            case 1: newAccount(); break;
            case 2: depositAccount(); break;
            case 3: withdrawAccount(); break;
            case 4: balanceAccount(); break;
            case 5: allAccountHoldList(); break;
            case 6: closeAnAccount(); break;
            case 7: modifyAnAccount(); break;
            case 8: printf("Exiting the system. Goodbye!\n"); break;
            default: printf("Enter a valid option (1-8).\n");
        }

    } while(option != 8);

    return 0;
}

// Create a new account
void newAccount() {
    struct Account acc;
    FILE *fp = fopen("accounts.dat", "ab");

    if (!fp) {
        printf("Error opening file.\n");
        return;
    }

    printf("Enter Account Number: ");
    scanf("%d", &acc.accountNumber);
    getchar(); // Clear newline from buffer
    printf("Enter Name: ");
    fgets(acc.name, sizeof(acc.name), stdin);
    acc.name[strcspn(acc.name, "\n")] = '\0'; // Remove trailing newline
    printf("Enter Account Type (S for Savings / C for Current): ");
    scanf(" %c", &acc.accountType);
    printf("Enter Initial Deposit: ");
    scanf("%f", &acc.balance);

    fwrite(&acc, sizeof(acc), 1, fp);
    fclose(fp);

    printf("Account created successfully.\n");
}

// Deposit amount to account
void depositAccount() {
    int acn;
    float amount;
    int found = 0;
    struct Account acc;
    FILE *fp = fopen("accounts.dat", "rb+");

    if (!fp) {
        printf("File not found.\n");
        return;
    }

    printf("Enter Account Number: ");
    scanf("%d", &acn);

    while (fread(&acc, sizeof(acc), 1, fp)) {
        if (acc.accountNumber == acn) {
            printf("Enter amount to deposit: ");
            scanf("%f", &amount);
            acc.balance += amount;
            fseek(fp, -(long)sizeof(acc), SEEK_CUR);
            fwrite(&acc, sizeof(acc), 1, fp);
            printf("Amount deposited successfully. New Balance: %.2f\n", acc.balance);
            found = 1;
            break;
        }
    }

    if (!found)
        printf("Account not found.\n");

    fclose(fp);
}

// Withdraw amount from account
void withdrawAccount() {
    int acn;
    float amount;
    int found = 0;
    struct Account acc;
    FILE *fp = fopen("accounts.dat", "rb+");

    if (!fp) {
        printf("File not found.\n");
        return;
    }

    printf("Enter Account Number: ");
    scanf("%d", &acn);

    while (fread(&acc, sizeof(acc), 1, fp)) {
        if (acc.accountNumber == acn) {
            printf("Enter amount to withdraw: ");
            scanf("%f", &amount);
            if (acc.balance >= amount) {
                acc.balance -= amount;
                fseek(fp, -(long)sizeof(acc), SEEK_CUR);
                fwrite(&acc, sizeof(acc), 1, fp);
                printf("Amount withdrawn successfully. New Balance: %.2f\n", acc.balance);
            } else {
                printf("Insufficient balance.\n");
            }
            found = 1;
            break;
        }
    }

    if (!found)
        printf("Account not found.\n");

    fclose(fp);
}

// Check balance of an account
void balanceAccount() {
    int acn;
    int found = 0;
    struct Account acc;
    FILE *fp = fopen("accounts.dat", "rb");

    if (!fp) {
        printf("File not found.\n");
        return;
    }

    printf("Enter Account Number: ");
    scanf("%d", &acn);

    while (fread(&acc, sizeof(acc), 1, fp)) {
        if (acc.accountNumber == acn) {
            printf("\nAccount Number: %d\nName: %s\nAccount Type: %c\nBalance: %.2f\n",
                    acc.accountNumber, acc.name, acc.accountType, acc.balance);
            found = 1;
            break;
        }
    }

    if (!found)
        printf("Account not found.\n");

    fclose(fp);
}

// List all accounts
void allAccountHoldList() {
    struct Account acc;
    FILE *fp = fopen("accounts.dat", "rb");

    if (!fp) {
        printf("File not found.\n");
        return;
    }

    printf("\n%-15s %-25s %-15s %-10s\n", "Account No", "Name", "Type", "Balance");
    printf("---------------------------------------------------------------------\n");

    while (fread(&acc, sizeof(acc), 1, fp)) {
        printf("%-15d %-25s %-15c %-10.2f\n",
               acc.accountNumber, acc.name, acc.accountType, acc.balance);
    }

    fclose(fp);
}

// Close an account
void closeAnAccount() {
    int acn, found = 0;
    struct Account acc;
    FILE *fp = fopen("accounts.dat", "rb");
    FILE *temp = fopen("temp.dat", "wb");

    if (!fp || !temp) {
        printf("Error opening file.\n");
        return;
    }

    printf("Enter Account Number to close: ");
    scanf("%d", &acn);

    while (fread(&acc, sizeof(acc), 1, fp)) {
        if (acc.accountNumber == acn) {
            found = 1;
            continue; // skip writing this record
        }
        fwrite(&acc, sizeof(acc), 1, temp);
    }

    fclose(fp);
    fclose(temp);

    remove("accounts.dat");
    rename("temp.dat", "accounts.dat");

    if (found)
        printf("Account closed successfully.\n");
    else
        printf("Account not found.\n");
}

// Modify account details
void modifyAnAccount() {
    int acn, found = 0;
    struct Account acc;
    FILE *fp = fopen("accounts.dat", "rb+");

    if (!fp) {
        printf("File not found.\n");
        return;
    }

    printf("Enter Account Number to modify: ");
    scanf("%d", &acn);

    while (fread(&acc, sizeof(acc), 1, fp)) {
        if (acc.accountNumber == acn) {
            printf("Enter New Name: ");
            getchar(); // clear buffer
            fgets(acc.name, sizeof(acc.name), stdin);
            acc.name[strcspn(acc.name, "\n")] = '\0';
            printf("Enter New Account Type (S/C): ");
            scanf(" %c", &acc.accountType);
            printf("Enter New Balance: ");
            scanf("%f", &acc.balance);

            fseek(fp, -(long)sizeof(acc), SEEK_CUR);
            fwrite(&acc, sizeof(acc), 1, fp);
            printf("Account modified successfully.\n");
            found = 1;
            break;
        }
    }

    if (!found)
        printf("Account not found.\n");

    fclose(fp);
}
