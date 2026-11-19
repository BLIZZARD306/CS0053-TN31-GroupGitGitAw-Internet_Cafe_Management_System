# Internet Cafe Management System

**Course:** CS0053 – Programming Tools and Techniques
**Group:** GitGitAw  
**Members:**
* Austria, Brianne Paolo M.
* Cuarentas, Justin Kurt S.
* Fojas, Franz Erich S.
* Francisco, Hans Eleazar C.

---

## Project Purpose & Overview

The **Internet Cafe Management System** is a C++ console application designed to help internet cafe administrators manage client accounts, monitor PC station availability, and control active PC sessions in a structured and reliable manner. 

The system uses a modular multi-file architecture (`.h` headers and `.cpp` implementations) and persists registered user records locally via `accounts.csv` so account data remains intact across program restarts.

> **Known Limitation:** Session durations are tracked as integer minute values (`minutesLeft`) rather than real-time system clock countdowns (`<ctime>`). Administrators manually close sessions using the **End PC Session** option.

---

## Features

1. **PC Stations Dashboard:** Displays the real-time status (`Available` or `In Use`), active user, and remaining minutes for all 4 PC stations upon loading the main menu.
2. **Open PC Session (`[1]`):** Assigns an available registered user account and session duration (in minutes) to an available PC station, preventing duplicate simultaneous logins and handling full-cafe states gracefully.
3. **Extend PC Time (`[2]`):** Lists active (`In Use`) PCs and allows admins to add extra minutes to a selected station with input validation, confirmation prompts, and a `0` cancel option.
4. **End PC Session (`[3]`):** Closes an active session on a selected PC station and resets it back to `Available`.
5. **Register New Account (`[4]`):** Creates a new member account with duplicate-username checks, comma-filtering (to protect CSV delimiters), and strict 4-digit numeric PIN validation, automatically saving the record to `accounts.csv`.
6. **View All Accounts (`[5]`):** Loads and displays all registered accounts from `accounts.csv` in a formatted table with masked PINs (`****`).

---

## Project Structure

```text
CS0053-TN31-GroupGitGitAw-Internet_Cafe_Management_System/
├── .vscode/
│   └── tasks.json          # Multi-file g++ build task configuration
├── main.cpp                # Main menu loop, dashboard display, and startup CSV loader
├── account.h               # Account struct definition and account management declarations
├── account.cpp             # Account registration, validation, display, and CSV persistence
├── session.h               # pcStation struct definition and session function declarations
├── session.cpp             # Open and end PC session logic and state validations
├── extend.h                # Extend PC time function declaration
├── extend.cpp              # Extend PC time logic and input validation
├── accounts.csv            # Local CSV storage for registered accounts (auto-generated)
└── README.md               # Project documentation
```

---

## Required Compiler & Standard

* **Compiler:** GNU C++ Compiler (`g++` via MSYS2 UCRT64 / MinGW-w64, GCC 11.0 or newer recommended)
* **C++ Standard:** **C++17** (`-std=c++17`) or **C++11** minimum
  * All standard libraries used in the codebase (`<iostream>`, `<iomanip>`, `<vector>`, `<string>`, `<fstream>`, `<sstream>`, `<cctype>`, `<stdexcept>`) and language features (`constexpr`, range-based `for` loops, `std::stoi`) are fully compatible with **C++11 through C++17+**.

---

## Compilation & Run Instructions

### Option 1: Using the Terminal (PowerShell / Command Prompt)

1. Open a terminal inside the root project directory (`CS0053-TN31-GroupGitGitAw-Internet_Cafe_Management_System`).
2. Compile all `.cpp` source files together:
   ```powershell
   g++ -std=c++17 -static -g main.cpp session.cpp extend.cpp account.cpp -o cafe_manager.exe
   ```
   *(Note: If `g++` is not in your system `PATH` on Windows, specify the full MSYS2 compiler path: `C:\msys64\ucrt64\bin\g++.exe -std=c++17 -static -g main.cpp session.cpp extend.cpp account.cpp -o cafe_manager.exe`)*
3. Run the executable:
   ```powershell
   .\cafe_manager.exe
   ```

### Option 2: Using VS Code Build Task

1. Open the repository folder in **Visual Studio Code**.
2. Open any `.cpp` file and press **`Ctrl + Shift + B`** (or navigate to **Terminal → Run Build Task...** and select **`C/C++: g++.exe build active file`**).
3. Open the integrated terminal (**`Ctrl + ` `**) and run `.\cafe_manager.exe`.

---

## Sample Input & Output

### 1. Main Menu & PC Dashboard
```text
========================================
INTERNET CAFE MANAGEMENT SYSTEM
========================================

--- PC STATIONS STATUS ---
PC ID   Status        Current User      Time Left
--------------------------------------------------
PC 1    Available     None              -
PC 2    Available     None              -
PC 3    Available     None              -
PC 4    Available     None              -
--------------------------------------------------
[1] Open PC Session
[2] Extend PC Time
[3] End PC Session
[4] Register New Account
[5] View All Accounts
[0] Exit
Enter your choice: 4
```

### 2. Registering & Viewing Accounts (`[4]` & `[5]`)
```text
+====== Register New Account ======+
Enter new username (no spaces or commas, or '0' to cancel): franz
Enter 4-digit numeric PIN: 1234
Account franz registered and saved successfully!

Enter your choice: 5

+====== Registered Accounts ======+
No.   Username            PIN
---------------------------------
1     franz               ****
---------------------------------
Total Registered Accounts: 1
```

### 3. Opening & Extending a PC Session (`[1]` & `[2]`)
```text
Enter your choice: 1

+====== Open PC Session ======+
Enter PC ID to open session (1-4 or exit): 1
Existing Accounts:
1. Franz

Choose an account (Enter number or exit): 1
Enter session time in minutes: 60

+====== Detail Confirmation ======+
PC ID: 1
User: franz
Session Time: 60 minutes
+=================================+

Confirm details? (Yes/No): yes
Session opened successfully for PC 1 with user franz

--- PC STATIONS STATUS ---
PC ID   Status        Current User      Time Left
--------------------------------------------------
PC 1    In Use        franz             60 mins
PC 2    Available     None              -
PC 3    Available     None              -
PC 4    Available     None              -
--------------------------------------------------
```
