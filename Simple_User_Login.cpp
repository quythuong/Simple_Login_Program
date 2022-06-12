#include<iostream>
#include<fstream>
#include<string>
#include<conio.h>
#include<cstdio>
using namespace std;


class User
{
	string User_Name;
	string Password;
public:
	User();
	User(const User &existingUser);
	bool isLogged;
	bool isExist();
	void type_HidePassword();
	void registerr();
	void login();
	void logout();
	void take_Note();
	void view_Note();
};

void Start_Menu();
void start_Using_Menu(User &Usr);

int main() {
	Start_Menu();
	return 0;
}

User::User()
{
	this->User_Name = "";
	isLogged = false;
}
User::User(const User& existingUser){}
bool User::isExist()
{
	ifstream UserFile;
	string UserFileName = "data//" + this->User_Name + ".txt";
	UserFile.open(UserFileName, ios_base::in);
	if(UserFile.fail())
		return false;
	UserFile.close();
	return true;
}
void User::type_HidePassword()
{
	char c;
	string Temp_Str;
	while(c != char(13))
	{
		c = _getch();
		Temp_Str.push_back(c);
	}
	this->Password = Temp_Str;
}
void User::registerr()
{
	string Tmp;
	string UserFileName;

	system("cls");
	cout << "REGISTER";
	cout << "\n\n\tType user name(no space): "; fflush(stdin); getline(cin, this->User_Name);
	UserFileName = "data//" + this->User_Name + ".txt";
	if(isExist())
	{
		cout << "\nUser name exist.\n";
		system("pause");
		return;
	}
	cout << "\n\tType Password(at least 8 charaters): "; fflush(stdin); this->type_HidePassword();

	if(this->User_Name.find(" ") != -1 && this->Password.length() < 8)
		return;
	cout << "\nRegister successfully!\n";

	//save to file
	ofstream UserFile;
	UserFileName = "data//" + this->User_Name + ".txt";
	UserFile.open(UserFileName, ios_base::out);
	UserFile << this->Password << "\n";
	UserFile.close();
	system("pause");
}
void User::login()
{
	string UserFileName;


	system("cls");
	cout << "LOG-IN";
	cout << "\n\n\tUser name: "; fflush(stdin); getline(cin, this->User_Name);
	UserFileName = "data//" + this->User_Name + ".txt";
	if(!isExist())	
	{
		cout << "User name doesn't exist.\n";
		system("pause");
		return;
	}
	cout << "\n\tPassword: "; fflush(stdin); this->type_HidePassword();


	// open file to check password
	ifstream UserFile;
	UserFileName = "data//" + this->User_Name + ".txt";
	string Correct_PW;
	UserFile.open(UserFileName, ios_base::in);
	getline(UserFile, Correct_PW);

	if(Correct_PW != this->Password)
	{
		cout << "\nWrong password!\n";
		system("pause");
		return;
	}
	UserFile.close();
	isLogged = true;
	cout << "\nYou logged in\n";
	system("pause");
}
void User::take_Note()
{
	cout << "\nTake your note below " << char(25) << " (Type back-- to save note go back)\n";
	
	string UserFileName = "data//" + this->User_Name + ".txt";
	string Line;
	ifstream UserFile;
	ofstream Temp;
	// open file to write
	UserFile.open(UserFileName, ios_base::in);
	Temp.open("data//tmp.txt", ios_base::out);
	while(getline(UserFile, Line))
		Temp << Line << "\n";
	while(true)
	{
		getline(cin, Line);
		if(Line == "back--")
			break;
		Temp << Line;
	}
	
	// convert UserFileName to char *
	int Len = UserFileName.length();
	char* UFN = new char[Len];
	for(int i = 0; i < Len; i++)
		UFN[i] = UserFileName[i];
	UFN[Len] = '\0';

	UserFile.close();
	Temp.close();
	remove(UFN);
	rename("data//tmp.txt", UFN);
	delete[] UFN;
}
void User::view_Note()
{
	string Line, UserFileName = "data//" + this->User_Name + ".txt";
	ifstream UserFile;
	// open file to read
	UserFile.open(UserFileName, ios_base::in);

	//fflush(stdin);
	getline(UserFile, Line);
	while(getline(UserFile, Line))
		cout << Line << "\n";

	UserFile.close();
}
void start_Using_Menu(User &Usr)
{
	int Choice;
	while(true)
	{
		system("cls");
		cout << "\t\tWELCOME NOTE TAKING PROGRAM";
		cout << "\n\n\t1. View your notes";
		cout << "\n\t2. Take note";
		cout << "\n\t3. Log out";
		cout << "\n\nYou choose: "; cin >> Choice;
		if(Choice == 1)
		{
			cout << "_____________________________\n";
			Usr.view_Note();
			cout << "_____________________________\n";
			system("pause");
		}
		else if(Choice == 2)
			Usr.take_Note();
		else
		{
			Usr.isLogged = false;
			return;
		}
	}
}
void Start_Menu()
{
	User Usr;
	int Choice;
	while(true)
	{
		system("cls");
		cout << "\t\tWELCOME NOTE TAKING PROGRAM";
		cout << "\n\n\t1. Log in";
		cout << "\n\t2. Register";
		cout << "\n\t3. Exit";
		cout << "\n\nYou choose: "; cin >> Choice;
		if(Choice == 1)
		{
			Usr.login();
			if(Usr.isLogged)
				start_Using_Menu(Usr);
		}
		else if(Choice == 2)
			Usr.registerr();
		else
			break;
	}
}

