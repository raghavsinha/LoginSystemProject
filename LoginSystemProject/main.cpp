#include <iostream>
#include <string>
#include <fstream>

using namespace std;

int login();
int reg();
int home();
int loginHome(string, string);
void greeting();
int changePassword(string);

int main() {
	greeting();
	home();
}

void greeting() {
	cout << "Hello. Welcome to the program!" << endl;
}

int home() {
	string choice;

	cout << "Enter 1 to login, 2 to register. 3 to quit. Your choice: ";
	cin >> choice;
	cout << endl;
	try {
		if (stoi(choice) == 1) {
			int retval = login();
			greeting();
		}
		else if (stoi(choice) == 2) {
			int retval = reg();
			greeting();
		}
		else if (stoi(choice) == 3) {
			cout << "Goodbye!" << endl;
			return 1;
		}
		else {
			cout << "That was not a valid choice. Please try again." << endl;
		}
	} catch (exception e) {
		cout << "That was not a valid choice. Please try again." << endl;
	}
	return home();
}

int login() {
	int retval = 0;

	ifstream infile;
	string username, password, pw = "";
	cout << "Enter username: ";
	cin >> username;
	cout << "Enter password: ";
	cin >> password;

	infile.open(username + ".txt");
	if (infile.is_open()) {
		getline(infile, pw);
		if (pw.compare(password) == 0) {
			retval = 1;
			cout << "Login successful!" << endl;
			loginHome(username, password);
		}
		else {
			retval = 0;
			cout << "Login Failure. Password is incorrect. Going home...\n";
		}
		infile.close();
	} else {
		cout << "Login Failure. Username \"" + username + "\" does not exist. Going home...\n" << endl;
		retval = 0;
	}
	return retval;
}

int loginHome(string username, string password) {
	int choice = -1, retval = -1;
	cout << "Welcome " + username + "! What would you like to do?" << endl;
	cout << "Enter 1 to logout, 2 to change password, anything else for a secret fact about the universe. Your choice: ";
	cin >> choice;
	cout << endl;
	
	if (choice == 1) {
		cout << "Logging out..." << endl;
		retval = 1;
	} else if (choice == 2) {
		changePassword(username);
		cout << "Password changed successfully." << endl;
		return loginHome(username, password);
	} else {
		cout << "The mitochondria is the powerhouse of the cell.\n" << endl;
		return loginHome(username, password);
	}
}

int changePassword(string username) {
	string password;
	cout << "Enter a new password: ";
	cin >> password;
	ofstream outfile;
	outfile.open(username + ".txt");
	outfile << password;
	cout << "entered password: " << password << endl;
	outfile.close();
	return 1;
}

int reg() {
	int retval = 0;

	ifstream infile;
	ofstream outfile;
	string username, password;
	cout << "Enter username: ";
	cin >> username;
	cout << "Enter password: ";
	cin >> password;

	cout << "entered password: " << password << endl;

	infile.open(username + ".txt");
	if (infile.is_open()) {
		cout << "Registration Failure. Username \"" + username + "\" already exists. Going home...\n";
		retval = 0;
		infile.close();
	} else {
		outfile.open(username + ".txt");
		outfile << password;
		cout << "Registration successful.\n";
		retval = 1;
	}
	outfile.close();
	return retval;
}