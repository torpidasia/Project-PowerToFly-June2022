#include <iostream>
#include <string.h>
#include <string>
#include <iomanip>
#include <Windows.h>
#include <fstream>

using namespace std;

class Car {
private:
	string name;
	int rate;
	string specs;
public:
	Car() {
		name = "";
		rate = 0;
		specs = "";
	}
	Car(string a, int b,string c):name(a),rate(b),specs(c) {
		
	}
	void set_car(string a,int b, string c) {
		name = a;
		rate = b;
		specs = c;
	}
	string getspecs()const {
		return specs;
	}
	virtual void displayC(int a) {
		cout << "Car's name: " << name<<endl;
		cout << "Total amount:" << a * rate << endl;
		cout << "Rate per day: " << rate << endl;
		cout << "Specs: \n" << specs << endl;
	}
};

class Luxury :public Car {
public:
	Luxury() {
		set_car("Audi E tron 2022", 20000, "Color: Black\nEngine: 475 kW(Electric)\nType: Sedan.\n");
	}
};

class Road :public Car {
private:
public:
	Road() {
		set_car("Honta Civic 2020", 10000, "Color: White\nEngine: 1500 cc\nBody Type: Sedan.\n");
	}
};

class Truck :public Car {
public:
	Truck() {
		set_car("Ford F 150 Raptor 5.0L", 15000, "Color: Red\nEngine: 5000cc\nBody Type: Double Cabin Truck.\n");
	}
};

class Buyer {
private:
	string name;
	string user;
	string pass;
public:
	Buyer(){}
	Buyer(string a, string b, string c) :name(a), user(b), pass(c) {}
};

class Rent:public Car {
private:
	Buyer* buyers[20];
public:
	Rent() {
	}
	static int count;
	void addBuyer(Buyer* p)
	{
		buyers[count] = p;
		count++;
	}
	void menu() {
		int menu;

		do {
			system("cls");
			cout << "To Rent a car, Press 1,\nTo view admin logs, Press 2,\nTo Exit the program, Press 3.";
			cout << "\nEnter the Option: ";
			cin >> menu;
			if (menu > 0 || menu < 4) {	//To be enable to enter switch statements
				switch (menu) {
				case 1:	//For the main vehicle renting
				{
					rentcar();
					break;
				}
				case 2:	//For the admin logs
				{
					admin_logs();
					break;
				}
				case 3:	//To exit
					exit(0);
					break;
				}
			}
		} while (menu < 1 || menu > 3);
	}

	void rentcar()
	{
		system("CLS");
		int ch;
		cout << "To register a new ID, Press 1,\nTo login, Press 2,\nTo return to main menu, Press 3.\nYour choice: ";
		do {
			cin >> ch;
			if (ch == 1) {
				system("CLS");
				registration();
			}
			else if (ch == 2) {
				system("CLS");
				login();
			}
			else if (ch == 3) {
				system("CLS");
				menu();
			}
		} while (ch < 1 || ch>3);
	}

	void admin_logs()
	{
		system("cls");
		int pass;
		cout << "Enter password: ";
		cin >> pass;
		if (pass == 1234)
		{
			system("cls");
			char ch;
			takeinfo();//Function call to the file reading function
			cout << "Enter Y to return to main menu or N to exit: ";
			cin >> ch;
			if (ch == 'y' || ch == 'Y') {
				menu();
			}
			else
				exit(0);

		}
		else if (pass != 1234)
		{
			system("cls");
			cout << "Wrong password!";
			Sleep(500);
			menu();
		}
	}

	void registration()
	{
		int count = 0;
		int specials = 0;
		bool valid_password = true;
		string rname, rid, rpass;
		cin.ignore();
		cout << "To Rent a car, you first have to register yourself in order for future verification.\n";
		cout << "Enter your first name: ";
		getline(cin, rname);
		cout << "Enter a username: ";
		cin >> rid;


		do {
			valid_password = true;
			cout << "- A password must have at least 4 characters. " << endl;
			cout << "- A password must contain at least one digits." << endl;
			cout << "Please enter a password: ";
			cin.ignore();
			cin >> rpass;

			count = 0;
			specials = 0;

			for (int i = 0; i < rpass.length(); i++)
			{
				if (!isalnum(rpass[i]))
				{
					specials++;
					valid_password = false;
				}
				else {
					valid_password = true;
				}
			}
			if ((rpass.length() < 3) || (specials != 0)) {
				cout << "Invalid password" << endl;
				valid_password = false;
			}

			for (int j = 0; j < rpass.length(); j++) {
				if (isdigit(rpass[j]))
				{
					count++;
				}
			}

			if (count < 1 || (rpass.length() < 3)) {
				valid_password = false;
			}

			if (valid_password) {
				cout << "Valid Password" << endl;
				Sleep(500);
			}
		} while (valid_password == false);

		Buyer* ptr=new Buyer(rname,rid,rpass);
		Rent::addBuyer(ptr);
		saveinfo(rname, rid, rpass);
		rentcar();
	}

	void login() {
		int count = 0;
		string id, pass, ID, PASS;
		string name;
		cout << "Enter login information: " << endl;
		cout << "Username: ";
		cin >> id;
		cout << "Password: ";
		cin >> pass;
		ifstream input;

		input.open("Buyer info.txt");
		while (input >> name >> ID >> PASS) {
			if (id == ID && pass == PASS) {
				count = 1;
			}
		}
		input.close();
		if (count == 1) {
			cout << "Successful login.\n";
			cout << "Showing info: \n";
			cout << "User id: " << id << endl;
			int ma;
			cout << "Enter 1 to proceed further.\nEnter 2 to return to rent a car menu\nYour choice: ";
			cin >> ma;
			if (ma == 1) {
				
				daysandcar();
			}
			else if (ma == 2) {
				rentcar();
			}
			else
				menu();
		}
		else {
			cout << "Invalid login info.";
			Sleep(1000);
			rentcar();
		}
	}

	void daysandcar() {
		int carn = 0;
		int days, ch;
		Car* s= nullptr;
		cout << "Car choice: " << endl;
		cout << "For luxury car, Press 1\nFor road car, Press 2\nFor an offroad truck, Press 3.\n";
		cout << "Enter the car you want: ";
		do {
		cin >> ch;
		if (ch == 1) {
			s = new Luxury();
			carn = 1;
		}
		else if (ch == 2) {
			s = new Road();
			carn = 2;
		}
		else if (ch == 3) {
			s = new Truck();
			carn = 3;
		}
		else
			cout << "Wrong car choice, Please enter again:";
		} while (ch > 3 || ch < 1);
		cout << "Enter the ammount of days you want the car for: ";
		cin >> days;
		saveinfo(carn);
		s->displayC(days);
		Sleep(1000);
		rentcar();
	}

	void saveinfo(int a) {
		ofstream savedata;
		savedata.open("CarN.txt", ios::app);
		savedata << a << endl;
		savedata.close();
	}
	void saveinfo(string o, string i, string p) {

		ofstream savedata;
		savedata.open("Buyer info.txt", ios::app);
		savedata << o << " " << i << " " << p << endl;
		savedata.close();
	}

	void takeinfo()
	{
		ifstream readdata;
		int a;
		string p, w, d;
		readdata.open("Buyer info.txt", ios::app);
		int counter = 1;
		while (readdata >> p)
		{
			cout << "Buyer " << counter << "'s Name: " << p << endl;
			readdata >> w;
			cout << "Buyer " << counter << "'s Id: " << w << endl;
			readdata >> d;
			ifstream rd;
			rd.open("CarN.txt", ios::app);
			rd >> a;
				if (a == 1) {
					Luxury a;
					string b;
					b = a.getspecs();
					cout << "Car Info: " << b;
				}
				else if (a == 2) {
					Road a;
					string b;
					b = a.getspecs();
					cout << "Car Info: " << b;
				}
				else if (a == 3) {
					Truck a;
					string b;
					b = a.getspecs();
					cout << "Car Info: " << b;
				}
			cout << endl;
			counter++;
		}
	}
		
};
int Rent::count = 0;
int main()
{
	Rent r1;
	r1.menu();
	return 0;
}