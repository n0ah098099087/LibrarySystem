#include <iostream>
#include <vector>
#include <ctime>

using namespace std;


bool CustomerAccount;
bool LibrarianAccount = false;
bool AdminAccount = false;

const string CLEAR = "\x1B[2J\x1B[1;1H";

string LoginOrCreateAccount;
string AccountLoginType;
string AccountTypeChoice;

//=====================================================      CLASSES AND SUB CLASSES     =====================================================      




class Books
{

public:
		string BookIDNumber;
		string BookTitle;
		string BookAuthor;
		bool borrowed = false;
		bool reserved = false;
		string RentedBy;
		

		void PrintInfo()
		{
			cout << "BookTitle: " << BookTitle << ": :" << "Author: " << BookAuthor << ": :" <<"ID Number: " << BookIDNumber << ": :";
			if (borrowed or reserved == true) 
			{
				cout << "Unavalable for rental" << endl;

			}
			else 
			{
				cout << "Avalable for rental"<< endl;
			}
		}
};

void CreateBook() 
{

}



//===================================================================================

class User
{

protected:

string Password;

public:
	string Username;
	bool Active = false;
	
	virtual int getType() = 0;

	void SetPassword(string password) 
	{
		this->Password = password;
	}
	string GetPassword() 
	{
		return string(Password);
	}
};


//==================================================================================================


class Customer : public User
{
    public:
		int getType() {
			return 1;
		}
	
};


//====================================================================================================

class Librarian : public User 
{

    public:
		int getType() {
			return 2;
		}

	void ManageRequests() 
	{


	}

};


//=====================================================================================================

class Admin : public User 
{


    public:
		int getType() {
			return 3;
		}

	void MannageAccouts() 
	{


	}

};

//===================================================      VECTOR LIBRARIES      ===================================================      

std::vector<Customer*> customers;
std::vector<Librarian*> librarians;
std::vector<Admin*> admins;
std::vector<Books*> books;

//===================================================       MAIN SYSTEM FUNCTIONS        ===================================================      

void Borrow(Books* Books, User* User)
{
	cout << "--Book Rental finalization--";
	string bob;
	cout << "BEANZ";
	cout << User->Username;
	cin >> bob;


}

Books* GetBookIDNumber(string IDNumber) 
{
	for (int i = 0; i < books.size(); i++) 
	{
		Books* Books = books[i];

		if (Books->BookIDNumber == IDNumber) 
		{
			return Books;

		}

	}
	return nullptr;
}

Books* GetBookTitle(string BookTitle) 
{
	for (int i = 0; i < books.size(); i++)
	{
		Books* Books = books[i];

		if (Books->BookTitle.find(BookTitle) !=string :: npos)
		{
			return Books;

		}

	}
	return nullptr;

}

Books* GetBookAuthor(string BookAuthor) 
{
	for (int i = 0; i < books.size(); i++)
	{
		Books* Books = books[i];

		if (Books->BookAuthor.find(BookAuthor) != string::npos)
		{
			return Books;

		}

	}
	return nullptr;


}


void RentBook(User*user) 
{
	string BookSearchMethod;
	
	cout << "--Book rental--" << endl;
	cout << "How would you like to seach for your book" << endl;
	cout << "1. ID number" << endl;
	cout << "2. Book title" << endl;
	cout << "3. Book author" << endl;
	cin  >> BookSearchMethod;

	if (BookSearchMethod == "1")
	{
		string IDnum;
		cout << CLEAR;
		cout << "--Book ID number search--" << endl;
		cout << "Please enter book ID number" << endl;
		cin >> IDnum;

		Books* book = GetBookIDNumber(IDnum);
		if (book == nullptr)
		{
			cout << CLEAR;
			cout << "No book with this ID number is regesterd in our system, please try again";
			RentBook(user);


		}
		else
		{
			string choice;
			cout << "Books found with matching data" << endl;
			cout << endl;
			book->PrintInfo();
			cout << endl;
			cout << "if you wish to rent one of these books and it is avalable please enter its ID number" << endl;
			cin >> choice;
			Books* bookchoice = GetBookIDNumber(choice);
			if (bookchoice == nullptr) 
			{
				cout << CLEAR;
				cout << "No book with this ID number is regesterd in our system, please try again";
				RentBook(user);
			}
			else 
			{
				cout << CLEAR;
				Borrow(bookchoice,user);

			}
			
		}

	}
	else if (BookSearchMethod == "2")
	{
		string BookTitle;
		cout << CLEAR;
		cout << "--Book title search--" << endl;
		cout << "Please enter book title" << endl;
		cin >> BookTitle;
		//is case senative
		
		Books* title = GetBookTitle(BookTitle);
		if (title == nullptr) 
		{
			cout << CLEAR;
			cout << "No book with this title is regestered in our system, please try again" << endl;
			RentBook(user);

		}
		else 
		{
			string choice;
			cout << "Books found with a matching title" << endl;
			cout << endl;
			title->PrintInfo();
			cout << endl;
			cout << "if you wish to rent one of these books and it is avalable please enter its ID number" << endl;
			cin >> choice;

			Books* title = GetBookTitle(choice);
			if (title == nullptr) 
			{
				cout << CLEAR;
				cout << "No book with this ID number is regesterd in our system, please try again";
				RentBook(user);

			}
			else
			{
				cout << CLEAR;
				Borrow(title,user);

			}
		}
	}
	else if(BookSearchMethod == "3")
	{
		string BookAuthor;
		cout << CLEAR;
		cout << "--Book Author Search--" << endl;
		cout << "Please enter Authors name" << endl;
		cin >> BookAuthor;

		Books* author = GetBookAuthor(BookAuthor);
		if (author == nullptr)
		{
			cout << CLEAR;
			cout << "No book with this title is regestered in our system, please try again" << endl;
			RentBook(user);

		}
		else
		{
			string choice;
			cout << "Books found with a matching title" << endl;
			cout << endl;
			author->PrintInfo();
			cout << endl;
			cout << "if you wish to rent one of these books and it is avalable please enter its ID number" << endl;
			cin >> choice;
			Books* author = GetBookAuthor(choice);
			if (author == nullptr) 
			{
				cout << CLEAR;
				cout << "No book with this title is regestered in our system, please try again" << endl;
				Borrow(author,user);

			}

		}
	


	}
	else
	{
		cout << CLEAR;
		cout << "Please choose a give option" << endl;
		RentBook(user);
	}

}

//====================================================================================================================================



void MainSystem(User*user) 
{
	string beanz;
	//cout << CLEAR;
	if (user->getType() == 1) 
	{
		CustomerAccount = true;
	}
	else if (user->getType() == 2) 
	{
		LibrarianAccount = true;
	}
	else if (user->getType() == 3) 
	{
		AdminAccount = true;
	}

	if (CustomerAccount == true) 
	{
		string option;
		


		cout << CLEAR;
		cout << "--Main System--" << endl;
		cout << "1. Rent book" << endl;
		cout << "2. Reserve book" << endl;
		cout << "3. Return book" << endl;
		cout << "4. Log out" << endl;
		cin >> option;
		if (option == "1")
		{
			cout << CLEAR;
			RentBook(user);
			

		}
		else if (option == "2") 
		{


		}
		else if (option == "3") 
		{


		}
		else if (option == "4") 
		{


		}
		else 
		{
			

		}
		return;
	}

}


// ===========================================      LOGIN AND ACCOUNT CREATION FUNCTIONS        ===========================================      


void CreateCustomerAccount() 
{
	string choice;
	string Username;
	string Password;
	cout << CLEAR;
	cout << "--Customer account creation--" << endl;
	cout << "Please enter username "; cin >> Username;
	cout << "please enter password "; cin >> Password;
	
	Customer* customer = new Customer();
	customer->Username = Username;
	customer -> SetPassword(Password);
	customers.push_back(customer);

	cout << "user created" << endl;
	cout << "1. Log in" << endl;
	cout << "2. Create another account" << endl;
	cin >> choice;
	if (choice == "1") 
	{
		cout << CLEAR;
		return;
	}
	else if (choice == "2")
	{
		CreateCustomerAccount();
	}
}
//=========================================================================

Customer* getCustomer(string LoginUsername, string LoginPassword) 
{
	
	for (int i = 0; i < customers.size(); i++) {
		Customer* Customer = customers[i];

		if (Customer->Username == LoginUsername and Customer->GetPassword()== LoginPassword)
		{
			return Customer;
		}
	}
	return nullptr;
}




void CustomerLogin()
{
	cout << CLEAR;
	string LoginUsername;
	string LoginPassword;
	cout << "--Customer Login--" << endl;
	cout << "please enter username "; cin >> LoginUsername;
	cout << "please enter password "; cin >> LoginPassword;

	

	Customer* customer = getCustomer(LoginUsername, LoginPassword);

	if (customer == nullptr) 
	{
		cout << CLEAR;
		cout << "Invalid username or password please try again" << endl;
		//return;

	}
	else  
	{
		MainSystem(customer);

	}


}

//========================================================================================

void CreateLibrarianAccount() 
{
	


}

void LibrarianLogin() 
{
	string LoginPassword;


}


//========================================================================================


void CreateAdminAcount() 
{


}


void AdminLogin() 
{
	string LoginPassword;

}


//==========================================================================================


void AccountCreation() 
{
	cout << CLEAR;
	cout << "-Account type selection-" << endl;
	cout << " which kind of account would you like to create" << endl;
	cout << "1. Customer" << endl;
	cout << "2. Librarian" << endl;
	cout << "3. Admin" << endl;
	cout << "4. Previous page" << endl;
	cin >> AccountTypeChoice;
	if (AccountTypeChoice == "1") 
	{
		CreateCustomerAccount();
	}
	else if (AccountTypeChoice == "2") 
	{
		CreateLibrarianAccount();

	}
	else if (AccountTypeChoice == "3") 
	{
		CreateAdminAcount();

	}
	else if (AccountTypeChoice == "4") 
	{
		
		return;

	}
	else 
	{
		cout << CLEAR;
		cout << "Please select a option" << endl;
		AccountCreation();
	}
}


void LogInType()
{
	cout << CLEAR;
	cout << "-What kind of account would you like to log into?-" << endl;
	cout << "1.Customer" << endl;
	cout << "2.Librarian" << endl;
	cout << "3.Admin" << endl;
	cout << "please select a option "; cin >> AccountLoginType;
	if (AccountLoginType == "1") 
	{
		CustomerLogin();

	}
	else if (AccountLoginType == "2")
	{
		LibrarianLogin();
	}
	else if (AccountLoginType == "3")
	{
		AdminLogin();
	} 

	else 
	{
		cout << CLEAR;
		cout << "please choose a given option" << endl;
		LogInType();

	}
	
}


//==============================================================================


int main() 

{   
	//============================      PRE MADE ACCOUNTS FOR TESTING PURPOSES      ============================ 


	Customer* customer = new Customer();
	customer -> Username = "seanItaly";
	customer -> SetPassword("pastasanwich");
	customers.push_back(customer);

	Librarian* librarian = new Librarian();
	librarian->Username = "harryknowls";
	librarian-> SetPassword("pinkballthing"); //idk how tf to spell it
	librarians.push_back(librarian);

	Admin* admin = new Admin();
	admin->Username = "elliot";
	admin->SetPassword("pocketband");

	Books* book = new Books();
	book->BookIDNumber = "1";
	book->BookTitle = "Normal People";
	book->BookAuthor = "Sally Rooney";
	books.push_back(book);

	// =================================      MAIN LOOP      =================================      

	while (true) {
		//cout << CLEAR;
		cout << "-Login or create account-" << endl;
		cout << "hello we see you are not logged in would you like to log in?" << endl;
		cout << "dont have a account? create one here" << endl;
		cout << "options" << endl;
		cout << "1.log in" << endl;
		cout << "2.create account" << endl;
		cout << "which option would you like to choose? "<< endl; 
		cout << "(type the number corosponding to the option)";
		cin >> LoginOrCreateAccount;
			if (LoginOrCreateAccount == "1")
		{
			LogInType();
		}
		else if (LoginOrCreateAccount == "2")
		{
			AccountCreation();

		}
		else
		{
			cout << CLEAR;
			cout << "Please choose a given option" << endl;
			main();
		}

	}
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
