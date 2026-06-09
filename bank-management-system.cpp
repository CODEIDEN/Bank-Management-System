#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

class BankAccount
{
private:
    int accountNumber;
    string customerName;
    double balance;

public:
    BankAccount()
    {
        accountNumber = 0;
        customerName = "";
        balance = 0;
    }

    BankAccount(int accNo, string name, double amount)
    {
        accountNumber = accNo;
        customerName = name;
        balance = amount;
    }

    int getAccountNumber() const
    {
        return accountNumber;
    }

    string getCustomerName() const
    {
        return customerName;
    }

    double getBalance() const
    {
        return balance;
    }

    void deposit(double amount)
    {
        if (amount > 0)
        {
            balance += amount;
            cout << "Deposit successful.\n";
        }
        else
        {
            cout << "Invalid amount.\n";
        }
    }

    void withdraw(double amount)
    {
        if (amount <= 0)
        {
            cout << "Invalid amount.\n";
        }
        else if (amount > balance)
        {
            cout << "Insufficient balance.\n";
        }
        else
        {
            balance -= amount;
            cout << "Withdrawal successful.\n";
        }
    }

    void displayDetails() const
    {
        cout << "\nAccount Number : " << accountNumber << endl;
        cout << "Customer Name  : " << customerName << endl;
        cout << "Balance        : Rs. " << balance << endl;
    }

    string toFileString() const
    {
        return to_string(accountNumber) + "|" +
               customerName + "|" +
               to_string(balance);
    }
};

class BankSystem
{
private:
    vector<BankAccount> accounts;
    const string fileName = "accounts.txt";

    void loadAccounts()
    {
        accounts.clear();

        ifstream fin(fileName);

        if (!fin)
            return;

        string line;

        while (getline(fin, line))
        {
            size_t p1 = line.find('|');
            size_t p2 = line.find('|', p1 + 1);

            if (p1 == string::npos || p2 == string::npos)
                continue;

            int accNo = stoi(line.substr(0, p1));
            string name = line.substr(p1 + 1, p2 - p1 - 1);
            double bal = stod(line.substr(p2 + 1));

            accounts.push_back(BankAccount(accNo, name, bal));
        }

        fin.close();
    }

    void saveAccounts()
    {
        ofstream fout(fileName);

        for (const auto &account : accounts)
        {
            fout << account.toFileString() << endl;
        }

        fout.close();
    }

    int findAccountIndex(int accountNumber)
    {
        for (int i = 0; i < accounts.size(); i++)
        {
            if (accounts[i].getAccountNumber() == accountNumber)
            {
                return i;
            }
        }

        return -1;
    }

public:
    BankSystem()
    {
        loadAccounts();
    }

    void createAccount()
    {
        int accNo;
        string name;
        double openingBalance;

        cout << "\nEnter Account Number: ";
        cin >> accNo;

        if (findAccountIndex(accNo) != -1)
        {
            cout << "Account already exists.\n";
            return;
        }

        cin.ignore();

        cout << "Enter Customer Name: ";
        getline(cin, name);

        cout << "Enter Opening Balance: ";
        cin >> openingBalance;

        accounts.push_back(
            BankAccount(accNo, name, openingBalance));

        saveAccounts();

        cout << "Account created successfully.\n";
    }

    void depositMoney()
    {
        int accNo;
        double amount;

        cout << "\nEnter Account Number: ";
        cin >> accNo;

        int index = findAccountIndex(accNo);

        if (index == -1)
        {
            cout << "Account not found.\n";
            return;
        }

        cout << "Enter Amount to Deposit: ";
        cin >> amount;

        accounts[index].deposit(amount);

        saveAccounts();
    }

    void withdrawMoney()
    {
        int accNo;
        double amount;

        cout << "\nEnter Account Number: ";
        cin >> accNo;

        int index = findAccountIndex(accNo);

        if (index == -1)
        {
            cout << "Account not found.\n";
            return;
        }

        cout << "Enter Amount to Withdraw: ";
        cin >> amount;

        accounts[index].withdraw(amount);

        saveAccounts();
    }

    void checkBalance()
    {
        int accNo;

        cout << "\nEnter Account Number: ";
        cin >> accNo;

        int index = findAccountIndex(accNo);

        if (index == -1)
        {
            cout << "Account not found.\n";
            return;
        }

        accounts[index].displayDetails();
    }
};

int main()
{
    BankSystem bank;
    int choice;

    do
    {
        cout << "\n========== BANK MANAGEMENT SYSTEM ==========\n";
        cout << "1. Create Account\n";
        cout << "2. Deposit Money\n";
        cout << "3. Withdraw Money\n";
        cout << "4. Check Balance\n";
        cout << "5. Exit\n";
        cout << "Enter Choice: ";

        cin >> choice;

        switch (choice)
        {
        case 1:
            bank.createAccount();
            break;

        case 2:
            bank.depositMoney();
            break;

        case 3:
            bank.withdrawMoney();
            break;

        case 4:
            bank.checkBalance();
            break;

        case 5:
            cout << "Thank you for using the system.\n";
            break;

        default:
            cout << "Invalid choice.\n";
        }

    } while (choice != 5);

    return 0;
}