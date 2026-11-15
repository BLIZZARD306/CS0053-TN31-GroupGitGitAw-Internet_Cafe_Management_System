#include "account.h"
#include <cctype>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>

using namespace std;

namespace {
constexpr size_t PIN_LENGTH = 4;
}

bool isValidPin(const string& pin) {
    if (pin.length() != PIN_LENGTH) {
        return false;
    }
    // Cast to unsigned char to prevent undefined behavior with negative char values in std::isdigit
    for (char c : pin) {
        if (!isdigit(static_cast<unsigned char>(c))) {
            return false;
        }
    }
    return true;
}

bool isValidUsername(const string& username) {
    // Disallow commas so CSV delimiter parsing remains unambiguous
    return !username.empty() && username.find(',') == string::npos;
}

bool isUsernameTaken(const vector<account>& accounts, const string& username) {
    for (const auto& acc : accounts) {
        if (acc.username == username) {
            return true;
        }
    }
    return false;
}

void loadAccounts(vector<account>& accounts, const string& filename) {
    accounts.clear();
    ifstream inFile(filename);
    if (!inFile.is_open()) {
        // Missing file is expected on first launch; saveAccounts() will initialize it
        return;
    }

    string line;
    while (getline(inFile, line)) {
        if (line.empty()) {
            continue;
        }

        stringstream ss(line);
        string username, pin;
        if (getline(ss, username, ',') && getline(ss, pin)) {
            if (isValidUsername(username) && isValidPin(pin)) {
                accounts.push_back({username, pin});
            }
        }
    }
}

void saveAccounts(const vector<account>& accounts, const string& filename) {
    ofstream outFile(filename);
    if (!outFile.is_open()) {
        cout << "Error: Unable to write account records to " << filename << ".\n";
        return;
    }

    for (const auto& acc : accounts) {
        outFile << acc.username << "," << acc.pin << "\n";
    }
}

void registerAccount(vector<account>& accounts) {
    string username;
    string pin;

    cout << "\n+====== Register New Account ======+\n";

    while (true) {
        cout << "Enter new username (no spaces or commas, or '0' to cancel): ";
        cin >> username;

        if (username == "0") {
            cout << "Account registration cancelled.\n\n";
            return;
        }

        if (!isValidUsername(username)) {
            cout << "Invalid username. Commas are not allowed.\n";
            continue;
        }

        if (isUsernameTaken(accounts, username)) {
            cout << "Username '" << username << "' is already taken. Try another.\n";
            continue;
        }
        break;
    }

    while (true) {
        cout << "Enter 4-digit numeric PIN: ";
        cin >> pin;

        if (!isValidPin(pin)) {
            cout << "Invalid PIN. Please enter exactly 4 digits (e.g., 1234).\n";
            continue;
        }
        break;
    }

    accounts.push_back({username, pin});
    saveAccounts(accounts);
    cout << "Account '" << username << "' registered and saved successfully!\n\n";
}

void displayAccounts(const vector<account>& accounts) {
    cout << "\n+====== Registered Accounts ======+\n";
    if (accounts.empty()) {
        cout << "No registered accounts found.\n";
        cout << "+=================================+\n\n";
        return;
    }

    cout << left << setw(6) << "No." << setw(20) << "Username" << "PIN\n";
    cout << "-----------------------------------\n";
    for (size_t i = 0; i < accounts.size(); i++) {
        cout << left << setw(6) << (i + 1)
             << setw(20) << accounts[i].username
             << "****\n";
    }
    cout << "-----------------------------------\n";
    cout << "Total Registered Accounts: " << accounts.size() << "\n\n";
}