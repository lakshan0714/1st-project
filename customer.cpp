#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class Customer {
private:
    int accountNumber;
    string password;
    string customerName;

public:
    Customer(int accNum, const string& pass) : accountNumber(accNum), password(pass) {}

    bool authenticate() {
        string inputPassword;
        cout << "Enter your password: ";
        getline(cin, inputPassword);

        return inputPassword == password;
    }

    bool login() {
        string accountFileName = to_string(accountNumber) + "_account.txt";

        ifstream accountFile(accountFileName);
        if (accountFile.is_open()) {
            // Read customer name from the file
            getline(accountFile, customerName);
            accountFile.close();

            // Authenticate the customer
            if (authenticate()) {
                cout << "Welcome, " << customerName << "!" << endl;
                return true;
            } else {
                cout << "Incorrect password. Access denied." << endl;
                return false;
            }
        } else {
            cout << "Error: Account does not exist. Please contact the bank." << endl;
            return false;
        }
    }

    void customerOperations() {
        cout << "Enter your account number: ";
        cin >> accountNumber;
        cin.ignore(); // Clear the newline character from the buffer

        if (login()) {
            // Perform customer operations
            int choice;
            do {
                cout << "\nCustomer Operations:\n"
                     << "1. View Transactions\n"
                     << "2. Deposit Money\n"
                     << "3. Withdraw Money\n"
                     << "4. Exit\n"
                     << "Enter your choice: ";
                cin >> choice;
                cin.ignore();  // Clear the newline character from the buffer

                switch (choice) {
                    case 1:
                        viewTransactions();
                        break;
                    case 2:
                        depositMoney();
                        break;
                    case 3:
                        withdrawMoney();
                        break;
                    case 4:
                        cout << "Exiting Customer Operations." << endl;
                        break;
                    default:
                        cout << "Invalid choice. Try again." << endl;
                }

            } while (choice != 4);
        }
    }

private:
    void viewTransactions() const {
        string accountFileName = to_string(accountNumber) + "_account.txt";
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

    void depositMoney() {
        string accountFileName = to_string(accountNumber) + "_account.txt";

        if (isAccountOpen(accountFileName)) {
            ofstream accountFile(accountFileName, ios::app);

            if (accountFile.is_open()) {
                double depositAmount;
                cout << "Enter deposit amount: $";
                cin >> depositAmount;
                cin.ignore();

                // Record the customer's username in the transaction history
                accountFile << "Customer: " << customerName << endl;
                accountFile << "Deposit: $" << depositAmount << endl;
                cout << "Money deposited successfully." << endl;
            } else {
                cout << "Error opening customer account file." << endl;
            }

            accountFile.close();
        }
    }

    void withdrawMoney() {
        string accountFileName = to_string(accountNumber) + "_account.txt";

        if (isAccountOpen(accountFileName)) {
            ofstream accountFile(accountFileName, ios::app);

            if (accountFile.is_open()) {
                double withdrawAmount;
                cout << "Enter withdrawal amount: $";
                cin >> withdrawAmount;
                cin.ignore();

                // Record the customer's username in the transaction history
                accountFile << "Customer: " << customerName << endl;
                accountFile << "Withdrawal: $" << withdrawAmount << endl;
                cout << "Money withdrawn successfully." << endl;
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
    // Example: Customer Operations
    string customerPassword = "Password@1234";

    Customer customer(0, customerPassword);
    customer.customerOperations();

    return 0;
}
