#include <iostream>
#include <iomanip>
#include <string>
#include <stdexcept>
#include<bits/stdc++.h>
using namespace std;

class BankAccount {
private:
    // Add private fields: accountNumber (string), ownerName (string), balance (double)
    string accountNumber;
    string ownerName;
    double balance;

public:
    BankAccount(const string& accountNumber, const string& ownerName):
    accountNumber(accountNumber), ownerName(ownerName), balance(0.0) {
        /* Initialize fields. Balance should start at 0.
        We cannot handle object creations/constructor calls like BankAccount("12") or BankAccount("Haseeb") using try-catch as these are compile-time errors and not run-time errors! */
        // Don't handle this by defining variable in initializer list - BankAccount(const string& accountNumber="Invalid", const string& ownerName="Guest") - this is wrong! If accountNumber and ownerName are compulsory - leave it as it is.
        if(accountNumber.empty())
            throw std::invalid_argument("Account Number cannot be empty!");
        if(ownerName.empty())
            throw std::invalid_argument("Owner Name cannot be empty!");
    }

    void deposit(double amount) {
        if (amount > 0) balance += amount;
        else throw invalid_argument("Deposit amount must be positive!");
    }

    bool withdraw(double amount) {
        // Remove amount from balance if sufficient funds exist
        // Return true if successful, false otherwise
        if(amount>0 && amount <= balance){
            balance -= amount;
            return true;
        }   
        return false;
    }

    double getBalance() const {
        // Return the current balance
        return balance;
    }
};

int main() {
    BankAccount account("123456", "John Doe");
    account.deposit(1000);
    cout << fixed << setprecision(1) << account.getBalance() << endl;  // Should print 1000.0

    bool success = account.withdraw(500);
    cout << boolalpha << success << endl;  // Should print true
    cout << fixed << setprecision(1) << account.getBalance() << endl;  // Should print 500.0

    success = account.withdraw(1000);
    cout << boolalpha << success << endl;  // Should print false

    return 0;
}