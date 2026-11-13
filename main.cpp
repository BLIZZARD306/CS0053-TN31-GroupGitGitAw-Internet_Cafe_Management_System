#include <iostream>
#include <iomanip>
#include <vector>
#include "session.h"
#include "account.h"

using namespace std;

void displayDashboard(const vector<pcStation>& pcs);
//void extendTime(vector<pcStation>& pcs);

int main()
{
    vector<pcStation> pcs = {
        {1, "Available", "None", 0},
        {2, "Available", "None", 0},
        {3, "Available", "None", 0},
        {4, "Available", "None", 0}};

    vector<account> accounts;
    loadAccounts(accounts);
    
    int choice = 0;
    do{

        cout << left << setfill('=') << setw(40) << "" << endl;
        cout << left << "INTERNET CAFE MANAGEMENT SYSTEM" << endl;
        cout << setw(40) << "" << endl;
        
        displayDashboard(pcs);
        
        cout << "[1] Open PC Session\n";
        cout << "[2] Extend PC Time\n";
        cout << "[3] End PC Session\n";
        cout << "[4] Register New Account\n";
        cout << "[5] View All Accounts\n";
        cout << "[0] Exit\n";
        cout << "Enter your choice: ";

        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid choice. Please enter a number.\n";
            choice = -1;
            continue;
        }

        switch (choice) {
            case 1:
                openPCSession(pcs, accounts);
                break;
            case 2:
                //extendTime(pcs);
                break;
            case 3:
                endSession(pcs);
                break;
            case 4:
                registerAccount(accounts);
                break;
            case 5:
                displayAccounts(accounts);
                break;
            case 0:
                cout << "Exiting Cafe Manager. Goodbye!\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }

    }while(choice != 0);

    return 0;
}

void displayDashboard(const vector<pcStation>& pcs){
    cout << "\n--- PC STATIONS STATUS ---\n";
    cout << left << setw(8) << setfill(' ')<< "PC ID" << setw(14) << "Status" << setw(18) << "Current User" << "Time Left\n";
    cout << "-------------------------------------------------\n";
    for (const auto& pc : pcs) {
        cout << "PC " << left << setw(5) << pc.id 
             << setw(14) << pc.status 
             << setw(18) << pc.currentUser;
        if (pc.status == "In Use") {
            cout << pc.minutesLeft << " mins\n";
        } else {
            cout << "-\n";
        }
    }
     cout << "-------------------------------------------------\n";
}