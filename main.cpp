#include <iostream>
#include <iomanip>
#include <vector>

using namespace std;

struct account
{
    string username;
    string pin;
};

struct pcStation
{
    int id;
    string status;
    string currentUser;
    int minutesLeft;
};


int main()
{
    vector<pcStation> pcs = {
        {1, "Available", "None", 0},
        {2, "Available", "None", 0},
        {3, "Available", "None", 0},
        {4, "Available", "None", 0}};

    vector<account> accounts;
    
    int choice = 0;
    do{

        cout << left << setfill('=') << setw(40) << "" << endl;
        cout << left << "INTERNET CAFE MANAGEMENT SYSTEM" << endl;
        cout << setw(40) << "" << endl;

        //Calling the pcDashboard here later on

        cout << "[1] Open PC Session\n";
        cout << "[2] Extend PC Time\n";
        cout << "[3] End PC Session\n";
        cout << "[4] Register New Account\n";
        cout << "[5] View All Accounts\n";
        cout << "[0] Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        /*
        Switch(){

        }
        */

    }while(choice != 0);

    return 0;
}

