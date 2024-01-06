#include<iostream>
#include<fstream>
#include<string>
#include<windows.h>



#ifdef _WIN32
    #include <direct.h> // For _mkdir on Windows
#else
    #include <sys/stat.h> // For mkdir on UNIX-like systems
#endif
using namespace std;




class Adminster{
	
	private:
		float AnnualSavingsIntrest;
		float OverdraftCharge;
		
	public:
		void Add_Employee()
		{
			
			  // Create a folder to store the files
              string folderName = "Employee";

              // Check if the folder exists, and create it if not
              #ifdef _WIN32
              _mkdir(folderName.c_str());
              #else
              mkdir(folderName.c_str(), 0777); // UNIX-like systems
               #endif
		    
		    string password="Password@1234";
			string name;
			cout<<"Enter Employee name (ex-Employee001,Employee002):"<<endl;
			cin>>name;
			
			if(name.length()>=8&&name.substr(0,8)=="Employee")
			{
				    cout<<"Employee Succesfully created"<<endl;
					ofstream out1(folderName+"/"+name);
			
		         	out1<<name<<endl;
		        	out1<<password<<endl;
                    out1.close();
			}
			
			else{
				cout<<"Error to create Employee please add employee again"<<endl;
			    Add_Employee();
				
			}
			 
		
		}
		
		
		void SetIntrest_SetOverDraft()
		{
			cout<<"Enter the intrest value for Annual Savings :"<<endl;
			cin>>AnnualSavingsIntrest;
			cout<<"Enter the Overdraft value for Current account :"<<endl;
			cin>>OverdraftCharge;
			cout<<"Succesfully set the intrest rate and overdraft values"<<endl;
			system("CLS");
		}
		
		void calculate_intrest_for_Savings()
		{
			
		}
		
		void calculate_penalty_for_Overdraft()
		{
			
		}
		
		

};




void administer_function()
{
   Adminster A1;
   
	int a;
	cout<<endl<<endl;
	cout<<"\t\t1)Add Employeee"<<endl;
	cout<<"\t\t2)Set the Annual saving_intrest and Overdraft Charge" <<endl;
    cout<<"\t\t2)Calculate Intrest for savings Account"<<endl;
	cout<<"\t\t3)Calculate penalty for current Account"<<endl;
	cout<<"\t\t4)Exit"<<endl;
	cout<<"\t\tPress 1,2 or 3 to Countinue"<<endl;
	cin>>a;
	system("CLS");
	
	switch(a){
          	case 1:
          		A1.Add_Employee();
          		administer_function();
          		
          		break;
          	case 2:
          	  cout<<"Employee";
          	  A1.SetIntrest_SetOverDraft();
          	  administer_function();
          	  
          	  break;
          	case 3:
          		cout<<"Coustomer";
          		break;
          	case 4:
          		system("CLS");
          		break;
          			
          	default:
          		cout<<"invalid";
          		
		  }

}


