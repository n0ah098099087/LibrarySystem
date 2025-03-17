#include <iostream>
#include <vector>
#include <ctime>
#include <list>
#include <string>

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
		string RentedBy = "none";
		

		void PrintInfo()
		{
			cout << "BookTitle: " << BookTitle << ": :" << "Author: " << BookAuthor << ": :" <<"ID Number: " << BookIDNumber << ": :";
			if (borrowed == true) 
			{
				cout << "Unavalable" << endl;

			}
			else 
			{
				cout << "Avalable"<< endl;
			}

		}
		void PrintReportInfo() 
		{
			cout << "BookTitle: " << BookTitle << ": :" << "Author: " << BookAuthor << ": :" << "ID Number: " << BookIDNumber << ": :" << RentedBy;
			if (borrowed == true)
			{
				cout << "Unavalable" << endl;

			}
			else
			{
				cout << "Avalable" << endl;
			}

		}


};







//===================================================================================

class User
{

protected:

string Password;

public:

	string Username;
	bool Active = false;
	int NumberOfBooksRented = 0;
	
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

	

};

//===================================================      VECTOR LIBRARIES      ===================================================      

//===================================================       MAIN SYSTEM FUNCTIONS        ===================================================      
std::vector<Customer*> customers;
std::vector<Librarian*> librarians;
std::vector<Admin*> admins;
std::vector<Books*> books;

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


void CreateBook() 
{
	string Title;
	string Author;
	string IDnum;
	cout << "-- Book creation --" << endl;
	cout << "please enter the title of the book you wish to add to the system ";cin >> Title;
	cin.ignore();
	cout << "please enter the Author of the book you wish to add to the system ";cin >> Author;
	cin.ignore();
	cout << "please enter a new ID number for this book ";cin >> IDnum;
	Books* Excisting = GetBookIDNumber(IDnum);
	if (Excisting != nullptr)
	{
		cout << CLEAR;
		cout << "sorry but a book with this ID number already excists, please choose a new ID number" << endl;
		CreateBook();
	}
	else 
	{
		string choice;
		Books* book = new Books();
		book->BookIDNumber = IDnum;
		book->BookTitle = Title;
		book->BookAuthor = Author;
		books.push_back(book);
		
		cout << "Book sucesfully created, press any button to return to admin screen" << endl;
		cin >> choice;
	}
}

void UserInfo(User*user) 
{
	string choice;
	cout << CLEAR;
	cout << "-- User Info --" << endl;
	cout << "username: " << user->Username << endl;
	cout << "passowrd: " << user->GetPassword() << endl;
	cout << " books currently borrowed: " << user->NumberOfBooksRented << endl;
	cin >> choice;
	return;


}



void ReturnBooks(User* user) 
{
	cout << CLEAR;
	cout << "-- Currently borrowed books--";
	bool FoundBook = false;
	for (int i = 0; i < books.size(); i++) 
	{
		Books* book = books[i];

		if (book->RentedBy == user->Username) 
		{
			book->PrintInfo();
			cout << endl;
			FoundBook = true;
		}
		
	}
	if (FoundBook == false) 
	{
		string choice;
		cout << "you have no borrowerd books so far" << endl;
		cin >> choice;
		return;

	}

	string choice;
	cout << "if you would like to returrn a book please enter its ID number" << endl;
	cout << "if you would like to go back to the main screen please enter Back" << endl;
	cin >> choice;
	
	Books* book = GetBookIDNumber(choice);
	if (book == nullptr) 
	{
		string choice;
		cout << CLEAR;
		cout << "There is no book in our system with that ID number" << endl;
		cin >> choice;
		ReturnBooks(user);
	}
	else 
	{
		if (book->RentedBy == user->Username)
		{
			string choice;
			user->NumberOfBooksRented--;
			book->RentedBy = "none";
			book->borrowed = false;
			cout << "Book returned sucessfully" << endl;
			cout << "press any key and enter to return to the main menu" << endl;
			cin >> choice;
			return;
		}
		else 
		{
			string choice;
			cout << "this ID number is for a book you have not currently borrowed, please try again" << endl;
			cin >>choice;
			ReturnBooks(user);

		}
	}
}

void Borrow(Books* Books, User* User)
{
	User->NumberOfBooksRented ++;
	Books->RentedBy = User->Username;
	Books->borrowed = true;
	string MainMenu;
	cout << "--Finalaized borrowing--" << endl;
	cout << "your request to borrow " << Books->BookTitle << " has been sucessful" << endl;
	cout << "you currently have borrowed " << User->NumberOfBooksRented << " books" << endl;
	cout << "press enter to return to the main logged in screen" << endl;
	cin >> MainMenu;
	
	
	

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


void RentBook(User* user)
	{
		string BookSearchMethod;

		cout << "--Book rental--" << endl;
		cout << "How would you like to seach for your book" << endl;
		cout << "1. ID number" << endl;
		cout << "2. Book title" << endl;
		cout << "3. Book author" << endl;
		cin >> BookSearchMethod;

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
					string barry;
					cout << CLEAR;
					cout << "No book with this ID number is regesterd in our system, please try again";
					cin >> barry;
					
				}
				else if (book->borrowed == true)
				{
					string barry;
					cout << "sorry but " << book->BookTitle << " is currently unavalable, feel free to borrow other books in the mean time." << endl;
					cin >> barry;
				}
				else
				{
					cout << CLEAR;
					Borrow(bookchoice, user);


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
				string barry;
				cout << CLEAR;
				cout << "No book with this title is regestered in our system, please try again" << endl;
				cin >> barry;

			}
			else if (title->borrowed == true)
			{
				string barry;
				cout << "sorry but " << title->BookTitle << " is currently unavalable, feel free to borrow other books in the mean time." << endl;
				cin >> barry;
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
					string barry;
					cout << CLEAR;
					cout << "No book with this ID number is regesterd in our system, please try again";
					cin >> barry;

				}
				else
				{
					cout << CLEAR;
					Borrow(title, user);

				}
			}
		}
		else if (BookSearchMethod == "3")
		{
			string BookAuthor;
			cout << CLEAR;
			cout << "--Book Author Search--" << endl;
			cout << "Please enter Authors name" << endl;
			cin >> BookAuthor;

			Books* author = GetBookAuthor(BookAuthor);
			if (author == nullptr)
			{
				string barry;
				cout << CLEAR;
				cout << "No book with this title is regestered in our system, please try again" << endl;
				cin >> barry;
				

			}
			else if (author->borrowed == true)
			{
				string barry;
				cout << "sorry but " << author->BookTitle << " is currently unavalable, feel free to borrow other books in the mean time." << endl;
				cin >> barry;
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
					Borrow(author, user);
				}

			}
		}
		else
		{
			cout << CLEAR;
			cout << "Please choose a give option" << endl;
		}

	}

	
//====================================================================================================================================
	void MannageAccounts() 
	{


	}
	void RemoveAccounts() 
	{


	}
	void GenerateReports() 
	{


	}


void MainSystem(User*user) 
{
	while (true) 
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
			cout << "2. Return book" << endl;
			cout << "3. account information" << endl;
			cout << "4. Log out" << endl;
			cin >> option;
			if (option == "1")
			{
				cout << CLEAR;
				RentBook(user);
				MainSystem(user);


			}
			else if (option == "2")
			{
				cout << CLEAR;
				ReturnBooks(user);
				MainSystem(user);

			}
			else if (option == "3")
			{
				cout << CLEAR;
				UserInfo(user);
				MainSystem(user);

			}
			else if (option == "4")
			{
				cout << CLEAR;
				CustomerAccount = false;
				return;
			}
			else
			{
				cout << "please enter a valid option" << endl;
				MainSystem(user);


			}

		}
		else if (LibrarianAccount == true) 
		{
			string choice;
			cout << CLEAR;
			cout << "-- Librarian main system --" << endl;
			cout << "1. Create Book" << endl;
			cout << "2. remove book" << endl;
			cout << "3. generate report" << endl;
			cout << "4. Log out" << endl;
			cin >> choice;

			if (choice == "1") 
			{
				cout << CLEAR;
				CreateBook();
				MainSystem(user);


			}
			else if (choice == "2") 
			{
				cout << CLEAR;
				MainSystem(user);
			}
			else if (choice == "3") 
			{
				cout << CLEAR;
				GenerateReport();
				MainSystem(user);
					
			}
			else if (choice == "4") 
			{
				cout << CLEAR;
				LibrarianAccount = false;
				return;

			}
		}
		else if (AdminAccount == true) 
		{
			string choice;
			cout << "-- Admin main system --" << endl;
			cout << "1. Manage accounts " << endl;
			cout << "2. Create accounts " << endl;
			cout << "3. Log out" << endl;
			cin >> choice;

			if (choice == "1") 
			{
				cout << CLEAR;
				MannageAccounts();
				MainSystem(user);

			}
			else if (choice == "2") 
			{
				cout << CLEAR;
				RemoveAccounts();
				MainSystem(user);

			}
			else if (choice == "3") 
			{
				cout << CLEAR;
				AdminAccount == false;
				return;

			}

		}
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
		cout << CLEAR;
		MainSystem(customer);
		

	}


}

//========================================================================================

void CreateLibrarianAccount() 
{
	
	string choice;
	string Username;
	string Password;
	cout << CLEAR;
	cout << "--Librarian account creation--" << endl;
	cout << "Please enter username "; cin >> Username;
	cout << "please enter password "; cin >> Password;
	
	Librarian* librarian = new Librarian();
	librarian->Username = Username;
	librarian -> SetPassword(Password);
	librarians.push_back(librarian);

	cout << "user created" << endl;
	cin >> choice;

}

Librarian* getLibrarian(string LoginUsername, string LoginPassword)
{

	for (int i = 0; i < librarians.size(); i++) {
		Librarian* Librarian = librarians[i];

		if (Librarian->Username == LoginUsername and Librarian->GetPassword() == LoginPassword)
		{
			return Librarian;
		}
	}
	return nullptr;
}

void LibrarianLogin() 
{
	cout << CLEAR;
	string LoginUsername;
	string LoginPassword;
	cout << "--Librarian Login--" << endl;
	cout << "please enter username "; cin >> LoginUsername;
	cin.ignore();
	cout << "please enter password "; cin >> LoginPassword;
	cin.ignore();

	Librarian* librarian = getLibrarian(LoginUsername, LoginPassword);

	if (librarian == nullptr)
	{
		cout << CLEAR;
		cout << "Invalid username or password please try again" << endl;
		//return;

	}
	else
	{
		MainSystem(librarian);

	}


}


//========================================================================================


void CreateAdminAcount() 
{


}

Admin* getAdmin(string LoginUsername, string LoginPassword)
{

	for (int i = 0; i < admins.size(); i++) {
		Admin* admin = admins[i];

		if (admin->Username == LoginUsername and admin->GetPassword() == LoginPassword)
		{
			return admin;
		}
	}
	return nullptr;
}


void AdminLogin() 
{
	cout << CLEAR;
	string LoginUsername;
	string LoginPassword;
	cout << "--Admin Login--" << endl;
	cout << "please enter username "; cin >> LoginUsername;
	cout << "please enter password "; cin >> LoginPassword;



	Admin* admin = getAdmin(LoginUsername, LoginPassword);

	if (admin == nullptr)
	{
		cout << CLEAR;
		cout << "Invalid username or password please try again" << endl;
		//return;

	}
	else
	{
		cout << CLEAR;
		MainSystem(admin);
		


	}

}


//==========================================================================================




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
	librarian-> Username = "harryknowls";
	librarian-> SetPassword("pinkballthing"); //idk how tf to spell it
	librarians.push_back(librarian);

	Admin* admin = new Admin();
	admin->Username = "elliot";
	admin->SetPassword("pocketband");
	admins.push_back(admin);

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
				CreateCustomerAccount();

		}
		else
		{
			cout << CLEAR;
			cout << "Please choose a given option" << endl;
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
