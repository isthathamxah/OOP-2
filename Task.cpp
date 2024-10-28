#include <iostream>
#include <string>

using namespace std;

class BankAccount {
private:
    int account_number;                
    string* account_holder_name;        
    double balance;                     
    static int number_of_accounts;      

public:
    
    BankAccount(int acc_no, string acc_h, double b) {
        this->account_number = acc_no;
        this->account_holder_name = new string(acc_h);  
        this->balance = b;
        number_of_accounts++;
    }

    ~BankAccount() {
        delete account_holder_name;  
        number_of_accounts--;
    }

    void deposit(double amount) {
        if (amount > 0) {
            balance += amount;
            cout << "Deposited Amount: $" << amount << endl
                << "Current Balance: $" << balance << endl;
        }
        else {
            cout << "Deposit amount must be positive." << endl;
        }
    }

    void withdraw(double amount) {
        if (amount > balance) {
            cout << "Insufficient funds. Current Balance: $" << balance << endl;
        }
        else {
            balance -= amount;
            cout << "Withdrawn Amount: $" << amount << endl
                << "Remaining Balance: $" << balance << endl;
        }
    }

    bool operator==(BankAccount& b) {
        return balance == b.balance;
    }

    void operator+(BankAccount& target) {
        double transferAmount;
        cout << "Enter amount to transfer from Account " << account_number
            << " to Account " << target.account_number << ": $";
        cin >> transferAmount;

        if (transferAmount > balance) {
            cout << "Insufficient balance to transfer." << endl;
        }
        else if (transferAmount <= 0) {
            cout << "Transfer amount must be positive." << endl;
        }
        else {
            balance -= transferAmount;          
            target.balance += transferAmount;   
            cout << "Transferred $" << transferAmount << " from Account "
                << account_number << " to Account " << target.account_number << endl;
        }
    }

    static int display_num_of_accounts() {
        return number_of_accounts;
    }

    friend void display_info(const BankAccount& b);
};
int BankAccount::number_of_accounts = 0;

void display_info(const BankAccount& b) {
    cout << "Account Number: " << b.account_number << endl
        << "Account Holder: " << *b.account_holder_name << endl
        << "Balance: $" << b.balance << endl;
    cout << "\n";
}

int main() {
   
    BankAccount A(1122, "Hamza", 50000);
    BankAccount B(1010, "Jibran", 20000);

    cout << "Initial Account Details:\n";
    display_info(A);
    display_info(B);

    A.withdraw(7500);
    cout << "\n";
    B.deposit(5000);

    cout << "\nComparing account1 and account2: ";
    if (A==B) {
        cout << "Accounts have the same balance.\n";
    }
    else {
        cout << "Accounts do not have the same balance.\n";
    }
    cout << "\n";
   
    A + B;

    cout << "\nAccount Details After Transfer:\n";
    display_info(A);
    display_info(B);

   
    cout << "\nTotal Number of Accounts: " << BankAccount::display_num_of_accounts() << endl;

    return 0;
}
