// Online Banking System in C++
// Features: Create Account, Deposit, Withdraw, Transfer
#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Account {
    static int nextId;
    int id;
    string name;
    double balance;
public:
    Account(const string& name, double initialDeposit) : name(name), balance(initialDeposit) {
        id = ++nextId;
    }
    int getId() const { return id; }
    string getName() const { return name; }
    double getBalance() const { return balance; }
    void deposit(double amount) { balance += amount; }
    bool withdraw(double amount) {
        if (amount > balance) return false;
        balance -= amount;
        return true;
    }
    bool transfer(Account& to, double amount) {
        if (withdraw(amount)) {
            to.deposit(amount);
            return true;
        }
        return false;
    }
};
int Account::nextId = 0;

class BankSystem {
    vector<Account> accounts;
public:
    void createAccount() {
        string name;
        double deposit;
        cout << "Enter name: ";
        cin >> name;
        cout << "Initial deposit: ";
        cin >> deposit;
        accounts.emplace_back(name, deposit);
        cout << "Account created. ID: " << accounts.back().getId() << endl;
    }
    Account* findAccount(int id) {
        for (auto& acc : accounts) {
            if (acc.getId() == id) return &acc;
        }
        return nullptr;
    }
    void deposit() {
        int id; double amount;
        cout << "Enter account ID: ";
        cin >> id;
        Account* acc = findAccount(id);
        if (!acc) { cout << "Account not found.\n"; return; }
        cout << "Enter amount to deposit: ";
        cin >> amount;
        acc->deposit(amount);
        cout << "Deposit successful. New balance: " << acc->getBalance() << endl;
    }
    void withdraw() {
        int id; double amount;
        cout << "Enter account ID: ";
        cin >> id;
        Account* acc = findAccount(id);
        if (!acc) { cout << "Account not found.\n"; return; }
        cout << "Enter amount to withdraw: ";
        cin >> amount;
        if (acc->withdraw(amount))
            cout << "Withdrawal successful. New balance: " << acc->getBalance() << endl;
        else
            cout << "Insufficient funds.\n";
    }
    void transfer() {
        int fromId, toId; double amount;
        cout << "Enter your account ID: ";
        cin >> fromId;
        cout << "Enter recipient account ID: ";
        cin >> toId;
        cout << "Enter amount to transfer: ";
        cin >> amount;
        Account* from = findAccount(fromId);
        Account* to = findAccount(toId);
        if (!from || !to) { cout << "Account not found.\n"; return; }
        if (from->transfer(*to, amount))
            cout << "Transfer successful. Your new balance: " << from->getBalance() << endl;
        else
            cout << "Insufficient funds.\n";
    }
    void showAccounts() {
        cout << "\n--- All Accounts ---\n";
        for (const auto& acc : accounts) {
            cout << "ID: " << acc.getId() << ", Name: " << acc.getName() << ", Balance: " << acc.getBalance() << endl;
        }
    }
};

int main() {
    BankSystem bank;
    int choice;
    do {
        cout << "\n1. Create Account\n2. Deposit\n3. Withdraw\n4. Transfer\n5. Show Accounts\n0. Exit\nChoice: ";
        cin >> choice;
        switch (choice) {
            case 1: bank.createAccount(); break;
            case 2: bank.deposit(); break;
            case 3: bank.withdraw(); break;
            case 4: bank.transfer(); break;
            case 5: bank.showAccounts(); break;
            case 0: cout << "Goodbye!\n"; break;
            default: cout << "Invalid choice.\n";
        }
    } while (choice != 0);
    return 0;
}
