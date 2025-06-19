#include <iostream>
#include <string>
using namespace std;

// ---------- STRUCTURE ----------
struct Date {
    int day, month, year;
};

// ---------- BASE CLASS ----------
class Transaction {
protected:
    double amount;
    string description;
    Date date;

public:
    Transaction(double amt, string desc, Date d)
        : amount(amt), description(desc), date(d) {}

    virtual void display() {
        cout << "PKR " << amount << " - " << description
             << " (" << date.day << "/" << date.month << "/" << date.year << ")\n";
    }

    virtual double getAmount() = 0;
    virtual ~Transaction() {}
};

// ---------- INCOME CLASS ----------
class Income : public Transaction {
public:
    Income(double amt, string desc, Date d)
        : Transaction(amt, desc, d) {}

  double getAmount() override {
        return amount;
    }

    void display() override {
        cout << "[INCOME] ";
        Transaction::display();
    }
};

// ---------- EXPENSE CLASS ----------
class Expense : public Transaction {
public:
    Expense(double amt, string desc, Date d)
        : Transaction(amt, desc, d) {}

    double getAmount() override {
        return amount;
    }

    void display() override {
        cout << "[EXPENSE] ";
        Transaction::display();
    }
};

// ---------- TRACKER CLASS ----------
class FinanceTracker {
private:
    double incomeAmount = 0;
    double totalExpenses = 0;

public:
    void addIncome(double amt, const string& desc, const Date& d) {
        Income income(amt, desc, d);
        income.display();
        incomeAmount = income.getAmount();
    }

    void addExpense(double amt, const string& desc, const Date& d) {
        Expense exp(amt, desc, d);
        exp.display();
        totalExpenses += exp.getAmount();
    }

    void showBalance() const {
        double balance = incomeAmount - totalExpenses;
        cout << "\nTotal Income: PKR " << incomeAmount;
        cout << "\nTotal Expenses: PKR " << totalExpenses;
        cout << "\nRemaining Balance: PKR " << balance << endl;
    }

    friend void showFriendView(const FinanceTracker& f);
};

// ---------- FRIEND FUNCTION ----------
void showFriendView(const FinanceTracker& f) {
    cout << "\n[Friend View] Income: PKR " << f.incomeAmount
         << ", Expenses: PKR " << f.totalExpenses << endl;
}

// ---------- MAIN FUNCTION ----------
int main() {
    FinanceTracker tracker;
    Date date = {11, 5, 2025};
    double income;
	cout << "*******FINANCE TRACKING SYSTEM ******* "<<endl<<endl;
    cout << "Enter your monthly salary (in PKR): ";
    cin >> income;
    cin.ignore(); // to handle newline character
    tracker.addIncome(income, "Salary", date);

    int n;
    cout << "\nHow many expenses do you want to enter? ";
    cin >> n;
    cin.ignore();

    for (int i = 0; i < n; ++i) {
        double amt;
        string desc;
        cout << "\nEnter expense description: ";
        getline(cin, desc);
        cout << "Enter amount for " << desc << " (in PKR): ";
        cin >> amt;
        cin.ignore(); // clear newline after number input

        tracker.addExpense(amt, desc, date);
    }

    tracker.showBalance();
    showFriendView(tracker); // demo of friend function

    return 0;
}
