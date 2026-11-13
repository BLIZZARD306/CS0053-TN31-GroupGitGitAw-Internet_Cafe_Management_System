#include <iostream>
#include <string>
#include <stdexcept>
#include "extend.h"

using namespace std;

void extendTime(vector<pcStation>& pcs) {
    int pcId;
    string pcIdStr;

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

        return; // NOTE: TEMPORARY ONLY! Will be removed in the next commit :)
    }
}