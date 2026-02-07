#include <iostream>
#include <vector>
#include <string>
#include <limits>

using namespace std;

struct User {
    string name;
    string pass;
    double money;
    bool isAdmin;
};

vector<User> allUsers;


void clearInput() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

string getStringInput(const string& prompt) {
    string input;
    cout << prompt;
    cin >> ws; 
    getline(cin, input);
    return input;
}

int main() {

    User admin;
    admin.name = "admin";
    admin.pass = "admin";
    admin.money = 0;
    admin.isAdmin = true;
    allUsers.push_back(admin);

    while (true) {

    cout << "\n1. signup\n2. login\n3. quit\n";
    int choice;
    cin >> choice;

        if (cin.fail()) {
            clearInput();
            cout << "Invalid input! Please enter a number.\n";
            continue;
        }
        clearInput(); 

        if (choice == 1) {

        User newUser;
        newUser.name = getStringInput("enter username: ");

        if (newUser.name.empty()) {
                cout << "invalid username!\n";
                continue;
        }

        bool userExists = false;

        for (size_t i = 0; i < allUsers.size(); i++) {
            if (allUsers[i].name == newUser.name) {
                    userExists = true;
                    break;
                }
            }

            if (userExists) {
                cout << "username already exists!\n";
            }
            else {
                newUser.pass = getStringInput("enter password: ");

                if (newUser.pass.empty()) {
                    cout << "invalid password!\n";
                }
                else {
                    newUser.money = 0;
                    newUser.isAdmin = false;
                    allUsers.push_back(newUser);
                    cout << "account created!\n";
                }
            }
        }

        else if (choice == 2) {

            string user = getStringInput("username: ");
            string password = getStringInput("password: ");

            int idx = -1;

            for (size_t i = 0; i < allUsers.size(); i++) {
                if (allUsers[i].name == user && allUsers[i].pass == password) {
                    idx = i;
                    break;
                }
            }

            if (idx == -1) {
                cout << "wrong username or password!\n";
            }
            else {

                cout << "logged in!\n";

                while (true) {

                    cout << "\n1. check balance\n2. deposit\n3. send money\n4. logout\n";
                    int opt;
                    cin >> opt;

                    if (cin.fail()) {
                        clearInput();
                        cout << "Invalid input! Please enter a number.\n";
                        continue;
                    }
                    clearInput(); 

                    if (opt == 1) {
                        cout << "your balance: $" << allUsers[idx].money << "\n";
                    }

                    else if (opt == 2) {

                        double amount;
                        cout << "how much: ";
                        cin >> amount;

                        if (cin.fail()) {
                            clearInput();
                            cout << "invalid input!\n";
                            continue;
                        }
                        clearInput(); 

                        if (amount > 0) {
                            allUsers[idx].money += amount;
                            cout << "deposited!\n";
                        }
                        else {
                            cout << "invalid amount!\n";
                        }
                    }

                    else if (opt == 3) {

                        string sendTo = getStringInput("send to who: ");

                        if (sendTo == allUsers[idx].name) {
                            cout << "you cant send money to yourself!\n";
                            continue;
                        }

                        double amount;
                        cout << "how much: ";
                        cin >> amount;

                        if (cin.fail()) {
                            clearInput();
                            cout << "invalid input!\n";
                            continue;
                        }
                        clearInput(); 

                        if (amount <= 0) {
                            cout << "invalid amount!\n";
                        }
                        else if (allUsers[idx].money < amount) {
                            cout << "not enough money!\n";
                        }
                        else {

                            bool found = false;

                            for (size_t i = 0; i < allUsers.size(); i++) {
                                if (allUsers[i].name == sendTo) {
                                    allUsers[idx].money -= amount;
                                    allUsers[i].money += amount;
                                    cout << "sent!\n";
                                    found = true;
                                    break;
                                }
                            }

                            if (!found) {
                                cout << "user not found!\n";
                            }
                        }
                    }

                    else if (opt == 4) {
                        cout << "logged out\n";
                        break;
                    }
                    else {
                        cout << "invalid option!\n";
                    }

                    if (allUsers[idx].isAdmin) {
                        cout << "\n--- ADMIN VIEW ---\n";
                        for (size_t i = 0; i < allUsers.size(); i++) {
                            cout << allUsers[i].name << " has $" << allUsers[i].money << "\n";
                        }
                    }
                }
            }
        }

        else if (choice == 3) {
            cout << "bye!\n";
            break;
        }
        else {
            cout << "invalid choice!\n";
        }
    }

    return 0;
}