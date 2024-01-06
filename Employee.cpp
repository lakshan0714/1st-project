
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <ctime>
#include <sys/stat.h>
#include <dirent.h>


#ifdef _WIN32
    #include <direct.h> // For _mkdir on Windows
#else
    #include <sys/stat.h> // For mkdir on UNIX-like systems
#endif



using namespace std;

class Employee {
private:
    string username;
    string password;
    int Balance=0;

public:
    Employee(const string& pass) : password(pass) {}

    bool authenticate() const {
        string inputPassword;
        cout << "Enter your password: ";
        getline(cin, inputPassword);

        return inputPassword == password;
    }

    string setEmployeeUsername() {
        cout << "Enter your username: ";
        getline(cin, username);
        return username;
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
                 << "6. Set overdraft value\n"
                 << "7. Exit\n"
                 << "Enter your choice: ";
            cin >> choice;
            cin.ignore();  // Clear the newline character from the buffer

            switch (choice) {
                case 1:
                    createAccount();
                    break;
                case 2:
                    //closeAccount();
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
                    
                    break;
                    
                case 7:
                    cout << "Exiting Employee Operations." << endl;
                    break;
                default:
                    cout << "Invalid choice. Try again." << endl;
            }

        } while (choice != 7);
    }

private:
    void createAccount() {
        
        string customerName;
        cout << "Enter customer name:(Ex-Customer001,Customer002) ";
        getline(cin, customerName);

        
        int accountNumber;
        cout << "Enter account number: ";
        cin >> accountNumber;
        cin.ignore(); // Clear the newline character from the buffer

        
        string contactNumber;
        cout << "Enter customer contact number: ";
        getline(cin, contactNumber);

        // Prompt for account type
        int accountType;
        cout << "Enter account type saving or current(if saving press 1 ,if current press 2) : ";
        cin>>accountType;
        
        if(customerName.length()>=8&&customerName.substr(0,8)=="Customer")
        {
        	  if(accountType==1)
              {
        	
        	
              string folderName = "Savings_ACC";

              // Check if the folder exists, and create it if not
              #ifdef _WIN32
              _mkdir(folderName.c_str());
              #else
              mkdir(folderName.c_str(), 0777); // UNIX-like systems
               #endif
		    
		    
		      ofstream accountFile(folderName+"/"+customerName);

              if (accountFile.is_open()) {
              accountFile << "Account Number: " << accountNumber << endl;
              accountFile << "Customer Name: " << customerName << endl;
              accountFile << "Contact Number: " << contactNumber << endl;
              accountFile<<"Created By "<<username<<endl<<endl;
            


              cout << "Account created successfully. Account Number: " <<customerName  << endl;
              } 
           
		      else {
               cout << "Error creating customer account file." << endl;
              }

              accountFile.close();
			
			
			
	     	}
	     	
	     	else if(accountType==2)
	     	{
	     		
              string folderName = "Current_ACC";

              // Check if the folder exists, and create it if not
              #ifdef _WIN32
              _mkdir(folderName.c_str());
              #else
              mkdir(folderName.c_str(), 0777); // UNIX-like systems
               #endif
		    
		    
		      ofstream accountFile(folderName+"/"+customerName);

              if (accountFile.is_open()) {
              accountFile << "Account Number: " << accountNumber << endl;
              accountFile << "Customer Name: " << customerName << endl;
              accountFile << "Contact Number: " << contactNumber << endl;
            


              cout << "Account created successfully. CustomerName: " <<customerName  << endl;
              setOverdraftLimit(accountFile);
              
              } 
           
		      else {
               cout << "Error creating customer account file." << endl;
              }

              accountFile.close();
			
	     		
	     		
			}
			 
			else
			{
				cout<<"Accountype value is incorrect recreate customer"<<endl;
				createAccount();
			}
        	
		}
		
		else{
			cout<<"Failed to create customer create again"<<endl;
			createAccount() ;
			
		}
       
       
    }

    void setOverdraftLimit(ofstream& accountFile) {
        double overdraftLimit;
        cout << "Enter overdraft limit for the current account: $";
        cin >> overdraftLimit;
        cin.ignore();

        accountFile << "Overdraft Limit: $" << overdraftLimit << endl;
        cout << "Overdraft limit set successfully." << endl;
    }
/*
    void closeAccount() {
        int accountNumber;
        cout << "Enter account number: ";
        cin >> accountNumber;
        cin.ignore(); // Clear the newline character from the buffer

        string accountFileName = to_string(accountNumber) + "_account.txt";

        if (remove(accountFileName.c_str() == 0) {
            cout << "Account closed successfully." << endl;
        } else {
            cout << "Error closing account. Account does not exist." << endl;
        }
    }*/

    void depositMoney() {
        string CustomerName;
        int a;
        string foldername;
        cout << "Enter CustomerName: ";
        cin >> CustomerName;
        cin.ignore(); // Clear the newline character from the buffer
        cout<<"Enter your Accout Type Saving or Current(press 1 if saving or press 2 if current)"<<endl;
        cin>>a;
        if(a==1)
         foldername="Savings_ACC";
        else if(a==2)
         foldername="Current_ACC";
        else{
        	cout<<"invalid account type ";
        	depositMoney() ;
		}
          

     

        if (isAccountOpen(foldername+"/"+CustomerName)) {
            ofstream accountFile(foldername+"/"+CustomerName, ios::app);

            if (accountFile.is_open()) {
                double depositAmount;
                cout << "Enter deposit amount: $";
                cin >> depositAmount;
                Balance+=depositAmount;
                cin.ignore();

                // Record the employee's username in the transaction history
                accountFile << "Employee: " << username << endl;
                accountFile << "Deposit: $" << depositAmount << endl;
                accountFile << "Balance:$" <<Balance<<endl;
                cout << "Money deposited successfully." << endl;
            } else {
                cout << "Error opening customer account file." << endl;
            }

            accountFile.close();
        }
    }

    void withdrawMoney() {
        string CustomerName;
        int a;
        string foldername;
        cout << "Enter CustomerName: ";
        cin >> CustomerName;
        cin.ignore(); // Clear the newline character from the buffer
        cout<<"Enter your Accout Type Saving or Current(press 1 if saving or press 2 if current)"<<endl;
        cin>>a;
        if(a==1)
         foldername="Savings_ACC";
        else if(a==2)
         foldername="Current_ACC";
        else{
        	cout<<"invalid account type ";
        	withdrawMoney() ;
		}
          
         if (isAccountOpen(foldername+"/"+CustomerName)) {
            ofstream accountFile(foldername+"/"+CustomerName, ios::app);
        

            if (accountFile.is_open()) {
                double withdrawAmount;
                cout << "Enter withdrawal amount: $";
                cin >> withdrawAmount;
                
                
                Balance-=withdrawAmount;
                cin.ignore();

                // Record the employee's username in the transaction history
                accountFile << "Employee: " << username << endl;
                accountFile << "Withdrawal: $" << withdrawAmount << endl;
                accountFile<<"Balance: $"<<Balance<<endl;
                cout << "Money withdrawn successfully." << endl;
            } else {
                cout << "Error opening customer account file." << endl;
            }

            accountFile.close();
        }
    }

    void viewTransactions() {
        string CustomerName;
        int a;
        string foldername;
        cout << "Enter CustomerName: ";
        cin >> CustomerName;
        cin.ignore(); // Clear the newline character from the buffer
        cout<<"Enter your Accout Type Saving or Current(press 1 if saving or press 2 if current)"<<endl;
        cin>>a;
        if(a==1)
         foldername="Savings_ACC";
        else if(a==2)
         foldername="Current_ACC";
        else{
        	cout<<"invalid account type ";
        	depositMoney() ;
		}

        if (isAccountOpen(foldername+"/"+CustomerName)) {
            ifstream accountFile(foldername+"/"+CustomerName);

            if (accountFile.is_open()) {
                string line;
                cout << "\nTransaction History for Account " << CustomerName << ":\n";
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
bool is_regular_file(const std::string& path) {
    struct stat path_stat;
    stat(path.c_str(), &path_stat);
    return S_ISREG(path_stat.st_mode);
}

void Employee_function()
{
	string empPassword = "Password@1234";

    Employee emp(empPassword);
    string name=emp.setEmployeeUsername();
    
    string folderPath = "C:\\Users\\LAKSHAN\\1st-project\\Employee"; 

    DIR* dir;
    struct dirent* entry;

    if ((dir = opendir(folderPath.c_str())) != nullptr) {
        while ((entry = readdir(dir)) != nullptr) {
            // Check if it is a regular file
            if (is_regular_file(folderPath + "\\" + entry->d_name)) {
                if(name==entry->d_name)
                {
                	emp.employeeOperations();
                	break;
				}
				
				else
				{
					cout<<"Invalid username"<<endl;
				}
            }
        }

        closedir(dir);
    } else {
        cerr << "Error opening folder" << endl;
    }
    
}


    


