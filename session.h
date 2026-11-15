#ifndef SESSION_H
#define SESSION_H

#include <iostream>
#include <vector>
#include <string>
#include "account.h"

struct pcStation
{
    int id;
    std::string status;
    std::string currentUser;
    int minutesLeft;
};

void openPCSession(std::vector<pcStation>& pcs, const std::vector<account>& accounts);
void endSession(std::vector<pcStation>& pcs);

#endif