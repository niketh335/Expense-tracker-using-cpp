#include <iostream>
#include <iomanip>
#include <vector>
#include <map>

#ifdef _WIN32
#include <conio.h>
#endif

using namespace std;

string getMaskedPassword() {
    string password = "";
#ifdef _WIN32
    char ch;
    while ((ch = _getch()) != 13) { 
        if (ch == 8) { 
            if (!password.empty()) {
                cout << "\b \b"; 
                password.pop_back();
            }
        } else {
            cout << '*';
            password.push_back(ch);
        }
    }
    cout << endl;
#else
    cout << "Password: ";
    cin >> password;
#endif
    return password;
}
using namespace std;

// Expense class to represent an individual expense
class Expense {
private:
    string moneySpentOn;
    double amountInRupees;
    string dueDate;
    string descriptionIfAny;
    bool isPaid;

public:
    // Constructor
    Expense(const string& spentOn, double amount, const string& dueDt, const string& descIfAny, bool paid)
        : moneySpentOn(spentOn), amountInRupees(amount), dueDate(dueDt), descriptionIfAny(descIfAny), isPaid(paid) {}

    // Getter methods
    string getMoneySpentOn() const { return moneySpentOn; }
    double getAmountInRupees() const { return amountInRupees; }
    string getDueDate() const { return dueDate; }
    string getDescriptionIfAny() const { return descriptionIfAny; }
    bool getIsPaid() const { return isPaid; }
};

// ExpenseTracker class to manage expenses and generate summaries
class ExpenseTracker {
private:
    string userID;
    map<string, double> categories;
    vector<Expense> expenses;

public:
    // Constructor
    ExpenseTracker(const string& userID) : userID(userID) {}

    // Method to add an expense
    void addExpense() {
        string spentOn;
        double amount;
        string dueDate;
        string descIfAny;
        char paidChoice;

        cout << "Money spent on (name of your item): ";
        getline(cin, spentOn);

        cout << "Enter amount in rs: ";
        cin >> amount;

        cout << "Is the expense paid? (y/n): ";
        cin >> paidChoice;
        cin.ignore(); // Clear newline character

        bool isPaid = (paidChoice == 'y' || paidChoice == 'Y');

        if (!isPaid) {
            cout << "Enter due date (DD-MM-YYYY): ";
            getline(cin, dueDate);
        } else {
            dueDate = "";
        }

        cout << "Enter description if any: ";
        getline(cin, descIfAny);

        Expense expense(spentOn, amount, dueDate, descIfAny, isPaid);
        expenses.push_back(expense);
        categories[spentOn] += amount;
        cout << "Expense added successfully!\n";
    }

    // Method to generate and display the expense summary
    void generateSummary() const {
        if (expenses.empty()) {
            cout << "No expenses to show.\n";
            return;
        }

        // Display header
        cout << setw(15) << "Money Spent On" << setw(20) << "Amount (rs)" << setw(20) << "Due Date"
             << setw(25) << "Description if any" << setw(15) << "Paid/Unpaid" << endl;
        cout << setfill('-') << setw(95) << "" << setfill(' ') << endl;

        // Display each expense
        for (const Expense& expense : expenses) {
            string paidStatus = (expense.getIsPaid() ? "Paid" : "Unpaid");
            cout << setw(15) << expense.getMoneySpentOn() << setw(20) << expense.getAmountInRupees()
                 << setw(20) << expense.getDueDate() << setw(25) << expense.getDescriptionIfAny()
                 << setw(15) << paidStatus << endl;
        }

        // Display footer with total
        double total = 0;
        for (const auto& category : categories) {
            total += category.second;
        }

        cout << setfill('-') << setw(95) << "" << setfill(' ') << endl;
        cout << setw(15) << "Total" << setw(20) << total << endl;
    }

     bool login() {
        cout << "Enter password: ";
        string enteredPassword = getMaskedPassword();
        const string correctPassword = "password123";

        return (enteredPassword == correctPassword);
    }
};

// Main function to run the Expense Tracker program
int main() {
    
    string userID = "user123";
    ExpenseTracker tracker(userID);

    cout << "                (: EXPENSE TRACKER :)\n                  ";
    int count = 0;
    while(!tracker.login() && count < 5) {
        cout << "Login failed.You have tries left:  " << (4 - count) << endl;
        count++;
        if(count == 5)
        {
            cout << "EXITING..... " << endl;
            return 1;
        }
    }

    char choice;
    do {
        cout << "1. Add Expense\n";
        cout << "2. Generate Summary\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore(); 

        switch (choice) {
            case '1':
                tracker.addExpense();
                break;
            case '2':
                tracker.generateSummary();
                break;
            case '3':
                cout << "Exited\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }

    } while (choice != '3');

    return 0;
}
