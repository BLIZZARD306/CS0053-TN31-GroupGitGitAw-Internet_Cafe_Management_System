#ifndef SESSION_H
#define SESSION_H

#include <iostream>
#include <vector>
#include <string>

struct pcStation
{
    int id;
    string status;
    string currentUser;
    int minutesLeft;
};

void openPCSession(vector<pcStation>& pcs, const vector<account>& accounts);
void endSession(vector<pcStation>& pcs);

#endif