#include <iostream>
#include <string>
#include <stdexcept>
#include <cctype>
#include "extend.h"

using namespace std;

void extendTime(vector<pcStation>& pcs) {
    int pcId, extraMins;
    string pcIdStr, minsStr, confirmExtend, contSession;

    while (true) {
        cout << "+===== Extend PC Time =====+" << endl;
        
        // Only shows what PCs can be extended
        bool anyInUse = false;
        for (int i = 0; i < pcs.size(); i++) {
            if (pcs[i].status == "In Use") {
                anyInUse = true;
                cout << "PC " << pcs[i].id << " (User: " << pcs[i].currentUser
                     << ", Time Left: " << pcs[i].minutesLeft << " mins)" << endl;
            }
        }
        if (!anyInUse) {
            cout << "No PCs are in use currently" << endl;
            return;
        }

        // Validates the PC ID
        cout << "Enter PC ID to extend (1-4): ";
        cin >> pcIdStr;

        try {
            pcId = stoi(pcIdStr);

            if (pcId < 1 || pcId > pcs.size()) {
                cout << "The PC ID is invalid" << endl;
                continue;
            }
        } catch (const exception&) {
            cout << "Please enter a valid PC ID." << endl;
            continue;
        }

        if (pcs[pcId - 1].status != "In Use") {
            cout << "This PC is not in use. Kindly choose another PC." << endl;
            continue;
        }

        // Validates the extra minutes
        cout << "Enter minutes to add: ";
        cin >> minsStr;

        try {
            extraMins = stoi(minsStr);

            if (extraMins <= 0) {
                cout << "Minutes must be greater than 0." << endl;
                continue;
            }
        } catch (const exception&) {
            cout << "Please enter a valid number of minutes." << endl;
            continue;
        }

        // Confirms the time added, then the time gets extended
        while (true) {
            cout << "Add " << extraMins << " minutes to PC " << pcId << "? (Yes/No): ";
            cin >> confirmExtend;
            for (int i = 0; i < confirmExtend.length(); i++) {
                confirmExtend[i] = tolower(confirmExtend[i]);
            }

            if (confirmExtend == "yes") {
                pcs[pcId - 1].minutesLeft += extraMins;
                cout << "PC " << pcId << " now has " << pcs[pcId - 1].minutesLeft << " mins left.\n" << endl;
                break;
            } else if (confirmExtend == "no") {
                cout << "Cancelled extending time." << endl;
                break;
            } else {
                cout << "Please type Yes or No only." << endl;
            }
        }

        // Extends another PC or goes back to the menu
        cout << "Extend another PC? (Yes/Exit): ";
        cin >> contSession;

        while (true) {
            for (int i = 0; i < contSession.length(); i++) {
                contSession[i] = tolower(contSession[i]);
            }

            if (contSession == "yes") {
                break;
            } else if (contSession == "exit") {
                return;
            } else {
                cout << "Invalid input. Please type Yes to continue or Exit to return to the main menu: ";
                cin >> contSession;
            }
        }
    }
}