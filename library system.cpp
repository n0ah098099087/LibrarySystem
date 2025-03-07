#include <iostream>
using namespace std;

bool Logged_In = false;
const string CLEAR = "\x1B[2J\x1B[1;1H";

string Username;
string Password;
string LoginOrCreateAccount;
string AccountLoginType;

void LogInType()
{
	cout << "Who would you like to log in as? " << endl;
	cout << "1.Customer" << endl;
	cout << "2.Librarian" << endl;
	cout << "3.Admin" << endl;
	cout << "please selct a option "; cin >> ""


}


void AccountTypeSelection() 
{

	cout << "which type of account wout you like to create? " << endl;
	cout << "options" << endl;
	cout << "customer" << endl;
	cout << "librarian" << endl;
	cout << "Admin" << endl;


}
void CreateCustomerAccount() 
{


}

void CreateLibrarianAccount() 
{


}

void CreateAdminAcount() 
{


}
class User
{
public:
	string Username;
	string Password;
	string Email;

	
};

class Customer : public User
{
	void CustomerLogin() 
	{


	}


};

class Librarian : public User 
{
	void StaffLogin()
	{

	}

};

class Admin : public User 
{
	void AdminLogin() 
	{

	}

};

int main() 

{
	cout << "hello we see you are not logged in would you like to log in?" << endl;
	cout << "dont have a account? create one here" << endl;
	cout << "options" << endl;
	cout << "1.log in" << endl;
	cout << "2.create account" << endl;
	cout << "which option would you like to choose? "; cin >> LoginOrCreateAccount;
	if (LoginOrCreateAccount == "1") 
	{
		LogInType();
	}




	return 0;
}

/*cout << "please enter Username " << endl;
	cin >> Username ;
	cout << "Please enter Password" << endl;
	cin >> Password;
    cout << CLEAR;
	cout << Username << endl;
	cout << Password << endl;
	cout << "nearly there" << endl;
	cin;*/
