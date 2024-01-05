
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <ctime>

using namespace std;

class Employee {
private:
    string username;
    string password;

public:
    Employee(const string& pass) : password(pass) {}

    bool authenticate() const {
        string inputPassword;
        cout << "Enter your password: ";
        getline(cin, inputPassword);

        return inputPassword == password;
    }

    void setEmployeeUsername() {
        cout << "Enter your username: ";
        getline(cin, username);
    }

    void employeeOperations() {
        if (!authenticate()) {
            cout << "Incorrect username or password. Access denied." << endl;
            return;
        }

        cout << "Welcome, " << username << "!" << endl;

        // Perform employee operations
        int choice;
        do {
            cout << "\nEmployee Operations:\n"
                 << "1. Create Account\n"
                 << "2. Close Account\n"
                 << "3. Deposit Money\n"
                 << "4. Withdraw Money\n"
                 << "5. View Transactions\n"
                 << "6. Exit\n"
                 << "Enter your choice: ";
            cin >> choice;
            cin.ignore();  // Clear the newline character from the buffer

            switch (choice) {
                case 1:
                    createAccount();
                    break;
                case 2:
                    closeAccount();
                    break;
                case 3:
                    depositMoney();
                    break;
                case 4:
                    withdrawMoney();
                    break;
                case 5:
                    viewTransactions();
                    break;
                case 6:
                    cout << "Exiting Employee Operations." << endl;
                    break;
                default:
                    cout << "Invalid choice. Try again." << endl;
            }

        } while (choice != 6);
    }

private:
    void createAccount() {
        // Implement logic to create an account
        string customerName;
        cout << "Enter customer name: ";
        getline(cin, customerName);

        // Prompt for account number
        int accountNumber;
        cout << "Enter account number: ";
        cin >> accountNumber;
        cin.ignore(); // Clear the newline character from the buffer

        // Prompt for contact number
        string contactNumber;
        cout << "Enter customer contact number: ";
        getline(cin, contactNumber);

        // Prompt for account type
        string accountType;
        cout << "Enter account type (saving or current): ";
        getline(cin, accountType);

        string accountFileName = to_string(accountNumber) + "_account.txt";
        ofstream accountFile(accountFileName);

        if (accountFile.is_open()) {
            accountFile << "Account Number: " << accountNumber << endl;
            accountFile << "Customer Name: " << customerName << endl;
            accountFile << "Contact Number: " << contactNumber << endl;
            accountFile << "Account Type: " << accountType << endl;
            accountFile << "Employee: " << username << endl;  // Record the employee's username

            if (accountType == "current") {
                setOverdraftLimit(accountFile);
            }

            cout << "Account created successfully. Account Number: " << accountNumber << endl;
        } else {
            cout << "Error creating customer account file." << endl;
        }

        accountFile.close();
    }

    void setOverdraftLimit(ofstream& accountFile) {
        double overdraftLimit;
        cout << "Enter overdraft limit for the current account: $";
        cin >> overdraftLimit;
        cin.ignore();

        accountFile << "Overdraft Limit: $" << overdraftLimit << endl;
        cout << "Overdraft limit set successfully." << endl;
    }

    void closeAccount() {
        int accountNumber;
        cout << "Enter account number: ";
        cin >> accountNumber;
        cin.ignore(); // Clear the newline character from the buffer

        string accountFileName = to_string(accountNumber) + "_account.txt";

        if (remove(accountFileName.c_str()) == 0) {
            cout << "Account closed successfully." << endl;
        } else {
            cout << "Error closing account. Account does not exist." << endl;
        }
    }

    void depositMoney() {
        int accountNumber;
        cout << "Enter account number: ";
        cin >> accountNumber;
        cin.ignore(); // Clear the newline character from the buffer

        string accountFileName = to_string(accountNumber) + "_account.txt";

        if (isAccountOpen(accountFileName)) {
            ofstream accountFile(accountFileName, ios::app);

            if (accountFile.is_open()) {
                double depositAmount;
                cout << "Enter deposit amount: $";
                cin >> depositAmount;
                cin.ignore();

                // Record the employee's username in the transaction history
                accountFile << "Employee: " << username << endl;
                accountFile << "Deposit: $" << depositAmount << endl;
                cout << "Money deposited successfully." << endl;
            } else {
                cout << "Error opening customer account file." << endl;
            }

            accountFile.close();
        }
    }

    void withdrawMoney() {
        int accountNumber;
        cout << "Enter account number: ";
        cin >> accountNumber;
        cin.ignore(); // Clear the newline character from the buffer

        string accountFileName = to_string(accountNumber) + "_account.txt";

        if (isAccountOpen(accountFileName)) {
            ofstream accountFile(accountFileName, ios::app);

            if (accountFile.is_open()) {
                double withdrawAmount;
                cout << "Enter withdrawal amount: $";
                cin >> withdrawAmount;
                cin.ignore();

                // Record the employee's username in the transaction history
                accountFile << "Employee: " << username << endl;
                accountFile << "Withdrawal: $" << withdrawAmount << endl;
                cout << "Money withdrawn successfully." << endl;
            } else {
                cout << "Error opening customer account file." << endl;
            }

            accountFile.close();
        }
    }

    void viewTransactions() {
        int accountNumber;
        cout << "Enter account number: ";
        cin >> accountNumber;
        cin.ignore(); // Clear the newline character from the buffer

        string accountFileName = to_string(accountNumber) + "_account.txt";

        if (isAccountOpen(accountFileName)) {
            ifstream accountFile(accountFileName);

            if (accountFile.is_open()) {
                string line;
                cout << "\nTransaction History for Account " << accountNumber << ":\n";
                while (getline(accountFile, line)) {
                    cout << line << endl;
                }
            } else {
                cout << "Error opening customer account file." << endl;
            }

            accountFile.close();
        }
    }

    bool isAccountOpen(const string& accountFileName) const {
        ifstream accountFile(accountFileName);
        if (accountFile) {
            accountFile.close();
            return true;
        } else {
            cout << "Error: Account does not exist or is closed." << endl;
            return false;
        }
    }
};

int main() {
    string empPassword = "Password@1234";

    Employee emp(empPassword);
    emp.setEmployeeUsername();  // Employee enters their username
    emp.employeeOperations();

    return 0;
}
