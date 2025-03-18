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
			cout << "BookTitle: " << BookTitle << ": :" << "Author: " << BookAuthor << ": :" << "ID Number: " << BookIDNumber << ": :" << "currently borrowed by"<< ": :" << RentedBy;
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
std::vector<User*> accounts;
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
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	cout << "please enter the Author of the book you wish to add to the system ";cin >> Author;
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	cout << "please enter a new ID number for this book ";cin >> IDnum;
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
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
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
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
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
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
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		return;

	}

	string choice;
	cout << "if you would like to returrn a book please enter its ID number" << endl;
	cout << "if you would like to go back to the main screen please enter Back" << endl;
	cin >> choice;
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	
	Books* book = GetBookIDNumber(choice);
	if (book == nullptr) 
	{
		string choice;
		cout << CLEAR;
		cout << "There is no book in our system with that ID number" << endl;
		cin >> choice;
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
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
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			return;
		}
		else 
		{
			string choice;
			cout << "this ID number is for a book you have not currently borrowed, please try again" << endl;
			cin >>choice;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
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
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	
	
	

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
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');

		if (BookSearchMethod == "1")
		{
			string IDnum;
			cout << CLEAR;
			cout << "--Book ID number search--" << endl;
			cout << "Please enter book ID number" << endl;
			cin >> IDnum;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');

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
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				Books* bookchoice = GetBookIDNumber(choice);
				if (bookchoice == nullptr)
				{
					string barry;
					cout << CLEAR;
					cout << "No book with this ID number is regesterd in our system, please try again";
					cin >> barry;
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');

				}
				else if (user->NumberOfBooksRented >= 5) 
				{



				}
		
				else if (book->borrowed == true)
				{
					string barry;
					cout << "sorry but " << book->BookTitle << " is currently unavalable, feel free to borrow other books in the mean time." << endl;
					cin >> barry;
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
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
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			//is case senative

			Books* title = GetBookTitle(BookTitle);
			if (title == nullptr)
			{
				string barry;
				cout << CLEAR;
				cout << "No book with this title is regestered in our system, please try again" << endl;
				cin >> barry;
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');

			}
			else if (title->borrowed == true)
			{
				string barry;
				cout << "sorry but " << title->BookTitle << " is currently unavalable, feel free to borrow other books in the mean time." << endl;
				cin >> barry;
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
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
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');

				Books* title = GetBookTitle(choice);
				if (title == nullptr)
				{
					string barry;
					cout << CLEAR;
					cout << "No book with this ID number is regesterd in our system, please try again";
					cin >> barry;
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');

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
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');

			Books* author = GetBookAuthor(BookAuthor);
			if (author == nullptr)
			{
				string barry;
				cout << CLEAR;
				cout << "No book with this title is regestered in our system, please try again" << endl;
				cin >> barry;
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				

			}
			else if (author->borrowed == true)
			{
				string barry;
				cout << "sorry but " << author->BookTitle << " is currently unavalable, feel free to borrow other books in the mean time." << endl;
				cin >> barry;
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
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
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
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
	
	User* getUserName(string choice)
	{

		for (int i = 0; i < accounts.size(); i++) {
			User* account = (User*)accounts[i];

			if (account->Username == choice)
			{
				return account;
			}
		}
		return nullptr;
	}


	void RemoveBooks() 
	{

		string choice;
		cout << "-- Book removal --" << endl;
		cout << "Please enter the ID number you wish to remove" << endl;
		cin >> choice;

		Books* book = GetBookIDNumber(choice);
		if (book == nullptr)
		{
			cout << "There is no book with this ID number in the system please try again" << endl;
			RemoveBooks();

		}
		else
		{
			string choice;
			auto it = find_if(books.begin(), books.end(), [book](Books* books) {return books == book; });
			books.erase(it);
			cout << "Book sucessfully removed" << endl;
			cin >> choice;
		}


	}



	void RemoveAccounts(User*user) 
	{
		string choice;
		cout << "-- Account removal --" << endl;
		cout << "Please enter the username of the account you wish to remove" << endl;
		cin >> choice;

		User* account = getUserName(choice);
		if (account == nullptr) 
		{
			cout << "There is no account with this username in the system please try again" << endl;
			RemoveAccounts(user);

		}
		else if (user->Username == choice) 
		{
			cout << CLEAR;
			cout << "A Admin cannout delete there own account" << endl;
			RemoveAccounts(user);


		}
		else 
		{
			string choice;
			auto it = find_if(accounts.begin(), accounts.end(), [account](User* user) {return user == account; });
			accounts.erase(it);
			cout << "account sucessfully deleted" << endl;
			cin >> choice;
		}
	}
	void CreateAccount(User*user) 
	{
		string choice;
		cout << "-- Admin account creation --" << endl;
		cout << "1. Create admin" << endl;
		cout << "2. Create Librarian account" << endl;
		cin >> choice;
		if (choice == "1") 
		{
			string username;
			string password;
			cout << CLEAR;
			cout << "-- Admin account creation--" << endl;
			cout << "please enter username for the new account";
			cin >> username;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "please enter password for the new account" << endl;
			cin >> password;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');

			Admin* admin = new Admin();
			admin->Username = username;
			admin->SetPassword(password);
			accounts.push_back(admin);
			cout << "account created" << endl;
		}
		else if(choice == "2")
		{
			string username;
			string password;
			cout << CLEAR;
			cout << "-- Librarian account Creation" << endl;
			cout << "please enter username for the new account"; 
			cin >> username;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "please enter password for the new account" << endl;
			cin >> password;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');

			Librarian* librarian = new Librarian();
			librarian->Username = username;
			librarian->SetPassword(password); 
			accounts.push_back(librarian);
			cout << "accout created" << endl;
		}

	}
	void GenerateReports() 
	{
		bool NoBooks = false;
		cout << "--Book borrow report--" << endl;

		for (int i = 0; i < books.size(); i++)
		{
			Books* Books = books[i];

			if (Books->borrowed == true)
			{
				NoBooks = true;
				Books->PrintReportInfo();

				
			}


		}
		if (NoBooks == false) 
		{
			string choice;
			cout << CLEAR;
			cout << "There are no books currently being borrowed" << endl;
			cout << "press any key and enter to return to Librarian menu" << endl;
			cin >> choice;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');



		}
		else 
		{
			string choice;
			cout << "this is all currently borrowed books right now" << endl;
			cout << "press any key and enter to return to Librarian menu" << endl;
			cin >> choice;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
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
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
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
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			if (choice == "1") 
			{
				cout << CLEAR;
				CreateBook();
				MainSystem(user);


			}
			else if (choice == "2") 
			{
				cout << CLEAR;
				RemoveBooks();
				MainSystem(user);
			}
			else if (choice == "3") 
			{
				cout << CLEAR;
				GenerateReports();
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
			cout << "1. Create accounts " << endl;
			cout << "2. Remove accounts " << endl;
			cout << "3. Log out" << endl;
			cin >> choice;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');

			if (choice == "1") 
			{
				cout << CLEAR;
				CreateAccount(user);
				MainSystem(user);

				
			}
			else if (choice == "2") 
			{
				
				cout << CLEAR;
				RemoveAccounts(user);
				MainSystem(user);

			}
			else if (choice == "3") 
			{
				cout << CLEAR;
				AdminAccount = false;
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
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	cout << "please enter password "; cin >> Password;
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	
	Customer* customer = new Customer();
	customer->Username = Username;
	customer -> SetPassword(Password);
	accounts.push_back(customer);

	cout << "user created" << endl;
	cout << "1. Log in" << endl;
	cout << "2. Create another account" << endl;
	cin >> choice;
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
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

User* getUser(string LoginUsername, string LoginPassword) 
{
	
	for (int i = 0; i < accounts.size(); i++) {
		User* account = (User*)accounts[i];

		if (account->Username == LoginUsername and account->GetPassword()== LoginPassword)
		{
			return account;
		}
	}
	return nullptr;
}




void UserLogin()
{
	cout << CLEAR;
	string LoginUsername;
	string LoginPassword;
	cout << "--User Login--" << endl;
	cout << "please enter username "; cin >> LoginUsername;
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	cout << "please enter password "; cin >> LoginPassword;
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');

	

	User* account = getUser(LoginUsername, LoginPassword);

	if (account == nullptr) 
	{
		cout << CLEAR;
		cout << "Invalid username or password please try again" << endl;
		//return;

	}
	else  
	{
		cout << CLEAR;
		MainSystem(account);
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
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	cout << "please enter password "; cin >> Password;
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	
	Librarian* librarian = new Librarian();
	librarian->Username = Username;
	librarian -> SetPassword(Password);
	accounts.push_back(librarian);

	cout << "user created" << endl;
	cin >> choice;
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');

}


//========================================================================================


int main() 

{   
	//============================      PRE MADE ACCOUNTS FOR TESTING PURPOSES      ============================ 


	Customer* customer = new Customer();
	customer -> Username = "seanItaly";
	customer -> SetPassword("pastasanwich");
	accounts.push_back(customer);

	Librarian* librarian = new Librarian();
	librarian-> Username = "harryknowls";
	librarian-> SetPassword("pinkballthing"); //idk how tf to spell it
	accounts.push_back(librarian);

	Admin* admin = new Admin();
	admin->Username = "elliot";
	admin->SetPassword("pocketband");
	accounts.push_back(admin);

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
		cout << "2.create customer account" << endl;
		cout << "which option would you like to choose? "<< endl; 
		cout << "(type the number corosponding to the option)";
		cin >> LoginOrCreateAccount;
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
			if (LoginOrCreateAccount == "1")
		{
				UserLogin();
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


