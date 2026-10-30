#include <iostream>
#include <fstream>
#include <string>
#include <limits>
using namespace std;
class Contact {
public:
    string name, phone, email;
    void input() {
        cout << "Enter Name: ";
        getline(cin, name);
        cout << "Enter Phone Number: ";
        getline(cin, phone);
        cout << "Enter Email: ";
        getline(cin, email);
    }
    void display() {
        cout << "\nName  : " << name;
        cout << "\nPhone : " << phone;
        cout << "\nEmail : " << email << endl;
    }
};
class ContactManager : public Contact {
private:
    Contact c;
    string filename = "contacts.txt";
public:
    void addContact() {
        ofstream file(filename, ios::app);
        if (!file) {
            cout << "Error opening file!\n";
            return;
        }
        cout << "\n--- Add New Contact ---\n";
        c.input();
        file << c.name << "\n";
        file << c.phone << "\n";
        file << c.email << "\n";
        file.close();
        cout << "\nContact added successfully!\n";
    }
    void displayContacts() {
        ifstream file(filename);
        if (!file) {
            cout << "\nNo contacts found!\n";
            return;
        }
        string name, phone, email;
        int count = 0;
        cout << "\n--- All Contacts ---\n";
        while (getline(file, name) &&
               getline(file, phone) &&
               getline(file, email)) {
            cout << "\nContact " << ++count;
            cout << "\nName  : " << name;
            cout << "\nPhone : " << phone;
            cout << "\nEmail : " << email << endl;
        }
        if (count == 0)
            cout << "No contacts available.\n";
        file.close();
    }
    void searchContact() {
        ifstream file(filename);
        if (!file) {
            cout << "\nNo contacts found!\n";
            return;
        }
        string searchName, name, phone, email;
        bool found = false;
        cout << "\nEnter name to search: ";
        getline(cin, searchName);
        while (getline(file, name) &&
               getline(file, phone) &&
               getline(file, email)) {
            if (name == searchName) {
                c.name = name;
                c.phone = phone;
                c.email = email;
                cout << "\nContact Found!\n";
                c.display();
                found = true;
            }
        }
        if (!found)
            cout << "\nContact not found!\n";
        file.close();
    }
    void deleteContact() {
        ifstream file(filename);
        ofstream temp("temp.txt");
        if (!file || !temp) {
            cout << "\nUnable to open file!\n";
            return;
        }
        string deleteName, name, phone, email;
        bool found = false;
        cout << "\nEnter name to delete: ";
        getline(cin, deleteName);
        while (getline(file, name) &&
               getline(file, phone) &&
               getline(file, email)) {
            if (name == deleteName) {
                found = true;
            } else {
                temp << name << "\n";
                temp << phone << "\n";
                temp << email << "\n";
            }
        }
        file.close();
        temp.close();
        remove(filename.c_str());
        rename("temp.txt", filename.c_str());
        if (found)
            cout << "\nContact deleted successfully!\n";
        else
            cout << "\nContact not found!\n";
    }
};
int main() {
    ContactManager manager;
    int choice;
    do {
        cout << "\n==============================";
        cout << "\n    CONTACT MANAGEMENT SYSTEM";
        cout << "\n==============================";
        cout << "\n1. Add Contact";
        cout << "\n2. Display All Contacts";
        cout << "\n3. Search Contact";
        cout << "\n4. Delete Contact";
        cout << "\n5. Exit";
        cout << "\nEnter your choice: ";
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\nInvalid input! Enter a number.\n";
            continue;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        switch (choice) {
            case 1:
                manager.addContact();
                break;
            case 2:
                manager.displayContacts();
                break;
            case 3:
                manager.searchContact();
                break;
            case 4:
                manager.deleteContact();
                break;
            case 5:
                cout << "\nThank you for using the system!\n";
                break;
            default:
                cout << "\nInvalid choice! Try again.\n";
        }
    } while (choice != 5);
    return 0;
}