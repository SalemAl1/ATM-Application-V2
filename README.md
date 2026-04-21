# 🏦 ATM-APPLICATION-V2

A robust, object-oriented console application simulating a fully functional banking ATM. Built with a heavy emphasis on defensive programming, memory safety, and persistent state management.

## 🚀 Overview

This project goes beyond basic `cin`/`cout` interactions. It was designed from the ground up to expect the worst from users—handling catastrophic typos, preventing duplicate card numbers, and ensuring that unexpected app closures never result in lost or duplicated funds. 

### Core Design Philosophies
* **Defensive Input Handling:** The system strictly catches `std::cin.fail()`, safely flushes garbage characters from the buffer, and utilizes a universal `-1` escape hatch across almost all menus.
* **Atomic State Management:** Memory changes and hard drive commits happen simultaneously. After every successful transaction, the `BankDatabase` auto-saves to prevent exploits.
* **Memory Efficiency:** Features an Admin Dashboard that manipulates the master user vector via direct memory references (`&`), avoiding costly runtime clones.

## ✨ Key Features

* **Secure Account Creation:** Generates collision-resistant card numbers and strictly enforces password matching and formatting rules.
* **Financial Transactions:** Supports deposits, withdrawals (with strict bounds checking for insufficient funds/negative amounts), and real-time EGP to USD currency conversion.
* **Persistent Data Storage:** Reads and writes user states to a lightweight, CSV-style local `.txt` database.
* **Dynamic UI Pacing:** Utilizes custom `Utils` namespaces for ANSI-colored terminal outputs, strict two-decimal `std::fixed` financial formatting, and paginated screen clearing for a seamless UX.

## 📁 Repository Structure

```text
ATM-APPLICATION-V2/
├── .gitignore
├── README.md
├── ATM-APPLICATION-V2.slnx
│
├── data/
│   └── database.txt
│
└── src/
    ├── main.cpp
    ├── ATM_UI.h / .cpp
    ├── BankDatabase.h / .cpp
    ├── User.h / .cpp
    └── Utils.h / .cpp
