#include<iostream>
//#include<customer.h>
#include "administer.cpp"
#include "Employee.cpp"
#include "customer.cpp"


using namespace std;

int main()
{
	int a;

          cout<<"\t\t-----WELCOME TO ABC BANK-------\t"<<endl<<endl;
		  cout<<"\t\t-----------MAIN PAGE-----------\t"<<endl;
		  cout<<"\t------------------------------------------------\t"<<endl;
		  
		  cout<<"\t|**PRESS 1,2 or 3 to COUNTINUE** \t\t|"<<endl;
		  cout<<"\t|\t\t\t\t\t\t|" << endl;
		  cout<<"\t| 1)Administer                    \t\t|"<<endl;
		  cout<<"\t| 2)Employee                      \t\t|" << endl;
		  cout<<"\t| 3)Customer                      \t\t|" << endl;
          cout<<"\t|\t\t\t\t\t\t|" << endl;
          cout<<"\t------------------------------------------------" << endl;	
          cin>>a;
          system("CLS");

          switch(a){
          	case 1:
          		
          		administer_function();
          		
          		break;
          	case 2:
          	     Employee_function();
          	     break;
          	case 3:
          		customer_function();
          		break;
          	default:
          		cout<<"invalid";
          		
		  }
          
          return 0;
}
