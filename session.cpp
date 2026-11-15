#include <iostream>
#include <cctype>
#include <string>
#include <stdexcept>
#include "session.h"
#include "account.h"

using namespace std;

bool accInUseCheck(const vector<pcStation>& pcs, const string& username) {
    for (const auto& pc : pcs) {
        if (pc.status == "In Use" && pc.currentUser == username) {
            return true;
        }
    }

    return false;
}

bool endSessionCheck(const vector<pcStation>& pcs) {
    for (const auto& pc : pcs) {
        if (pc.status == "In Use") {
            return true;
        }
    }
    return false;
}

bool openPCSessionCheck(const vector<pcStation>& pcs) {
    for (const auto& pc : pcs) {
        if (pc.status == "Available") {
            return true;
        }
    }
    return false;
}

bool availableAccountCheck(const vector<pcStation>& pcs, const vector<account>& accounts) {
    for (const auto& acc : accounts) {
        if (!accInUseCheck(pcs, acc.username)) {
            return true;
        }
    }

    return false;
}


void openPCSession(vector<pcStation>& pcs, const vector<account>& accounts) {
    int pcId, mins = 0, accountChoice;
    string pcIdStr, userName, aChoiceStr, minsStr, contSession, finalConfirm;

    while (true) {
        // ID handling and validation
        cout << "\n+====== Open PC Session ======+" << endl;
        
        if (!openPCSessionCheck(pcs)) {
            cout << "No available PCs to open a session.\n" << endl;
            return;
        }

        if (accounts.empty()) {
            cout << "No accounts found, please register an account first.\n" << endl;
            return;
        }

        if (!availableAccountCheck(pcs, accounts)) {
            cout << "All registered accounts are currently in use. Please end a session first.\n" << endl;
            return;
        }

        
        cout << "Enter PC ID to open session (1-4 or exit): ";
        cin >> pcIdStr;

        try {
            if (pcIdStr == "exit" || pcIdStr == "Exit") {
                return;
            }

            pcId = stoi(pcIdStr);

            if (pcId < 1 || pcId > pcs.size()) {
                cout << "Invalid PC ID. Please choose between 1 and 4." << endl;
                continue;
            }

        } catch (const invalid_argument&) {
            cout << "Please Enter a Valid PC ID." << endl;
            continue;
        }

        if (pcs[pcId - 1].status == "In Use") {
            cout << "PC is already in use, please choose another PC." << endl;
            continue;
        }


        // Username handling and validation
        if (accounts.empty()) {
            cout << "No accounts found, please register an account first.\n" << endl;
            return;
        }

        cout << "Existing Accounts:" << endl;
        for (int i = 0; i < accounts.size(); i++) {
            cout << i + 1 << ". " << accounts[i].username << endl;
        }

        cout << "\nChoose an account (Enter number or exit): ";
        cin >> aChoiceStr;

        try {
            if (aChoiceStr == "exit" || aChoiceStr == "Exit") {
                return;
            }

            accountChoice = stoi(aChoiceStr);
            if (accountChoice < 1 || accountChoice > accounts.size()) {
                cout << "Please Choose a Valid Account." << endl;
                continue;
            }

            if (accounts[accountChoice - 1].username.empty()) {
                cout << "Selected account is invalid. Please choose a valid account." << endl;
                continue; 
            }
            
        } catch (const invalid_argument&) {
            cout << "Please Enter a Valid Account Choice." << endl;
            continue;
        }

        userName = accounts[accountChoice - 1].username;
        
        if (accInUseCheck(pcs, userName)) {
            cout << "Please choose another account." << endl;
            continue;
        }

        // Session time handling and validation
        cout << "Enter session time in minutes: ";
        cin >> minsStr;

        try {
            mins = stoi(minsStr);
            if (mins <= 0) {
                cout << "Session time must be greater than 0 minutes." << endl;
                continue;
            }
        } catch (const invalid_argument&) {
            cout << "Please Enter a Valid Session Time." << endl;
            continue;
        }

        
        cout << "\n+====== Detail Confirmation ======+" << endl;
        cout << "PC ID: " << pcId << endl;
        cout << "User: " << userName << endl;
        cout << "Session Time: " << mins << " minutes" << endl;
        cout << "+=============================+\n\n";

        while (true) {
            cout << "Confirm details? (Yes/No): ";
            cin >> finalConfirm;
            for (int i = 0; i < finalConfirm.length(); i++) {
                finalConfirm[i] = tolower(finalConfirm[i]);
            }

            if (finalConfirm == "yes") {
                pcs[pcId - 1].status = "In Use";
                pcs[pcId - 1].currentUser = userName;
                pcs[pcId - 1].minutesLeft = mins;
                cout << "Session opened successfully for PC " << pcId << " with user " << userName << "\n" << endl;
                break;
            } else if (finalConfirm == "no") {
                cout << "Cancelled Session." << endl;
                break;
            } else {
                cout << "Please type Yes or No." << endl;
                continue;
            }
        }

        // Continue or Exitting of Adding a Session
        cout << "Add more or Retry Session? (Yes/Exit): ";
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

void endSession(vector<pcStation>& pcs) {
    int pcId;
    string pcIdStr, contSession, confirmEnd;

    while(true) {
        cout << "\n+====== End PC Session ======+" << endl;
        
        if (!endSessionCheck(pcs)) {
            cout << "No active sessions to end.\n" << endl;
            return;
        }

        // PC list display
        for(int i = 0; i < pcs.size(); i++) {
            cout << "PC " << pcs[i].id << ": " << pcs[i].status;
            if (pcs[i].status == "In Use") {
                cout << " (User: " << pcs[i].currentUser << ", Time Left: " << pcs[i].minutesLeft << " mins)";
            }
            cout << endl;
        }

        // Session ending process
        cout << "Enter PC ID to end session (1-4 or exit): ";
        cin >> pcIdStr;

        try {
            if (pcIdStr == "exit" || pcIdStr == "Exit") {
                return;
            }

            pcId = stoi(pcIdStr);

            if (pcId < 1 || pcId > pcs.size()) {
                cout << "Invalid PC ID. Please choose between 1 and 4." << endl;
                continue;
            }

        } catch (const invalid_argument&) {
            cout << "Please Enter a Valid PC ID." << endl;
            continue;
        }

        if (pcs[pcId - 1].status == "Available") {
            cout << "PC is not in use, please choose another PC." << endl;
            continue;
        }

        // Confirming the end of session
        cout << "Are you sure you want to end the session for PC " << pcId << "? (Yes/No): ";
        cin >> confirmEnd;
        for (int i = 0; i < confirmEnd.length(); i++) {
            confirmEnd[i] = tolower(confirmEnd[i]);
        }
        
        if (confirmEnd == "yes") {
            pcs[pcId - 1].status = "Available";
            pcs[pcId - 1].currentUser = "";
            pcs[pcId - 1].minutesLeft = 0;
        } else if (confirmEnd == "no") {
            cout << "Cancelled Ending Session." << endl;
            continue;
        } else {
            cout << "Please type Yes or No." << endl;
            continue;
        }

        cout << "Session ended successfully for PC " << pcId << ".\n" << endl;

        cout << "End another session? (Yes/Exit): ";
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