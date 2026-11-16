#include <iostream>
#include <string>
#include <limits>
using namespace std;

const int USER_COUNT = 3;

// Each position in these arrays belongs to one customer.
string customerNames[USER_COUNT] = {"Lerato Molefe", "Thabo Nkosi", "Amira Daniels"};
string accountNumbers[USER_COUNT] = {"GCC1001", "GCC1002", "GCC1003"};
int accountPins[USER_COUNT] = {1234, 2468, 1357};
double accountBalances[USER_COUNT] = {2500.00, 1800.00, 3200.00};

// Clears invalid keyboard input so the next question can be read correctly.
void clearInput()
{
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// Reads an integer safely and repeats if the input is not a number.
int readInteger(string prompt)
{
    int value;

    cout << prompt;
    while (!(cin >> value))
    {
        cout << "Invalid input. Please enter a whole number: ";
        clearInput();
    }

    clearInput();
    return value;
}

// Reads a money amount and rejects zero, negative or non-numeric values.
double readAmount(string prompt)
{
    double amount;

    cout << prompt;
    while (!(cin >> amount) || amount <= 0)
    {
        cout << "Please enter a valid amount greater than R0.00: ";
        clearInput();
    }

    clearInput();
    return amount;
}

// Finds a customer using the account number. -1 means not found.
int findAccount(string account)
{
    for (int i = 0; i < USER_COUNT; i++)
    {
        if (accountNumbers[i] == account)
        {
            return i;
        }
    }

    return -1;
}

// Checks the account number and PIN before opening the banking menu.
int login()
{
    string enteredAccount;
    int enteredPin;

    cout << "\n========== CUSTOMER LOGIN ==========\n";
    cout << "Demo accounts: GCC1001, GCC1002, GCC1003\n";
    cout << "Enter account number: ";
    cin >> enteredAccount;

    int customerIndex = findAccount(enteredAccount);

    if (customerIndex == -1)
    {
        cout << "Account not found. Please check the account number.\n";
        return -1;
    }

    enteredPin = readInteger("Enter your 4-digit PIN: ");

    if (enteredPin == accountPins[customerIndex])
    {
        cout << "\nWelcome, " << customerNames[customerIndex] << "!\n";
        return customerIndex;
    }

    cout << "Incorrect PIN. Login was not successful.\n";
    return -1;
}

// Displays the menu and returns the option selected by the customer.
int displayMenu()
{
    cout << "\n====================================\n";
    cout << "             GCC SMARTBANK          \n";
    cout << "          Banking Made Simple       \n";
    cout << "====================================\n";
    cout << "1. Deposit money\n";
    cout << "2. Withdraw money\n";
    cout << "3. Send cash\n";
    cout << "4. Check balance\n";
    cout << "5. Exit\n";
    cout << "------------------------------------\n";

    return readInteger("Choose an option: ");
}

// Adds money only after the amount has passed validation.
void deposit(int customerIndex)
{
    double amount = readAmount("Enter deposit amount (R): ");
    accountBalances[customerIndex] += amount;

    cout << "Deposit successful!\n";
    cout << "New balance: R" << accountBalances[customerIndex] << "\n";
}

// Prevents a withdrawal that is greater than the available balance.
void withdraw(int customerIndex)
{
    double amount = readAmount("Enter withdrawal amount (R): ");

    if (amount <= accountBalances[customerIndex])
    {
        accountBalances[customerIndex] -= amount;
        cout << "Withdrawal successful. Please collect your cash.\n";
        cout << "Remaining balance: R" << accountBalances[customerIndex] << "\n";
    }
    else
    {
        cout << "Transaction declined: insufficient funds.\n";
        cout << "Available balance: R" << accountBalances[customerIndex] << "\n";
    }
}

// Transfers money only if the recipient exists and the sender has enough.
void sendCash(int senderIndex)
{
    string recipientAccount;
    cout << "Enter recipient account number: ";
    cin >> recipientAccount;

    int recipientIndex = findAccount(recipientAccount);

    if (recipientIndex == -1)
    {
        cout << "Transfer failed: recipient account does not exist.\n";
        return;
    }

    if (recipientIndex == senderIndex)
    {
        cout << "You cannot send cash to your own account.\n";
        return;
    }

    double amount = readAmount("Enter amount to send (R): ");

    if (amount <= accountBalances[senderIndex])
    {
        accountBalances[senderIndex] -= amount;
        accountBalances[recipientIndex] += amount;

        cout << "\nTransfer successful!\n";
        cout << "Sent to: " << customerNames[recipientIndex] << "\n";
        cout << "Recipient account: " << accountNumbers[recipientIndex] << "\n";
        cout << "Your new balance: R" << accountBalances[senderIndex] << "\n";
    }
    else
    {
        cout << "Transfer declined: insufficient funds.\n";
    }
}

// Shows the signed-in customer's name, account number and balance.
void checkBalance(int customerIndex)
{
    cout << "\n========== ACCOUNT SUMMARY ==========\n";
    cout << "Customer: " << customerNames[customerIndex] << "\n";
    cout << "Account number: " << accountNumbers[customerIndex] << "\n";
    cout << "Current balance: R" << accountBalances[customerIndex] << "\n";
    cout << "=====================================\n";
}

int main()
{
    cout << "====================================\n";
    cout << "       WELCOME TO GCC SMARTBANK     \n";
    cout << "====================================\n";

    int customerIndex = login();

    if (customerIndex == -1)
    {
        cout << "Please restart the program and try again.\n";
        return 0;
    }

    int choice = 0;

    // The while loop keeps the menu running until option 5 is selected.
    while (choice != 5)
    {
        choice = displayMenu();

        switch (choice)
        {
            case 1:
                deposit(customerIndex);
                break;

            case 2:
                withdraw(customerIndex);
                break;

            case 3:
                sendCash(customerIndex);
                break;

            case 4:
                checkBalance(customerIndex);
                break;

            case 5:
                cout << "\nThank you for banking with GCC SmartBank.\n";
                cout << "Have a safe and wonderful day!\n";
                break;

            default:
                cout << "Invalid menu option. Please choose from 1 to 5.\n";
        }
    }

    return 0;
}
