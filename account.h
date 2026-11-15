#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <string>
#include <vector>

// Domain entity representing a registered internet cafe member
struct account
{
    std::string username;
    std::string pin;
};

// Pure validation and domain helpers (isolated from console I/O for testability)
bool isValidPin(const std::string& pin);
bool isValidUsername(const std::string& username);
bool isUsernameTaken(const std::vector<account>& accounts, const std::string& username);

// Infrastructure layer: CSV file persistence
void loadAccounts(std::vector<account>& accounts, const std::string& filename = "accounts.csv");
void saveAccounts(const std::vector<account>& accounts, const std::string& filename = "accounts.csv");

// Application / Presentation handlers
void registerAccount(std::vector<account>& accounts);
void displayAccounts(const std::vector<account>& accounts);

#endif