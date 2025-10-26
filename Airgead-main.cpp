// CS 210 Project Two ? Airgead Banking
// Name: Shaveze Mcdonald
// Date: 10/05/2025
// Purpose: show year-end balance and interest with and without monthly deposits

#include <iostream>
#include <iomanip>
#include <limits>
#include <string>
#include <cmath>
#include "Investment.h"

#ifdef _WIN32
#include <conio.h>
#endif

using namespace std;

void pressAnyKey() {
#ifdef _WIN32
    cout << "Press any key to continue...";
    _getch();
    cout << "\n";
#else
    cout << "Press Enter to continue...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
#endif
}

void clearCin() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

double getDouble(string prompt, bool allowZero = true) {
    while (true) {
        cout << prompt;
        double val;
        if (cin >> val) {
            if ((allowZero && val >= 0) || (!allowZero && val > 0))
                return val;
            cout << "Enter a positive number.\n";
        }
        else {
            cout << "Invalid entry.\n";
            clearCin();
        }
    }
}

unsigned getYears(string prompt) {
    while (true) {
        cout << prompt;
        double val;
        if (cin >> val && val >= 1 && floor(val) == val)
            return (unsigned)val;
        cout << "Enter a whole number (>=1).\n";
        clearCin();
    }
}

bool askYesNo(string prompt) {
    cout << prompt;
    string ans;
    cin >> ans;
    return (ans == "y" || ans == "Y");
}

void printReport(string title, const vector<AnnualSummary>& data) {
    cout << "\n" << title << "\n";
    cout << "---------------------------------------------\n";
    cout << left << setw(6) << "Year"
        << right << setw(20) << "Year End Balance"
        << setw(25) << "Year End Earned Interest" << endl;
    cout << string(51, '-') << endl;

    cout << fixed << setprecision(2);
    for (auto& r : data) {
        cout << left << setw(6) << r.year
            << right << setw(10) << "$" << setw(10) << r.yearEndBalance
            << setw(10) << "$" << setw(13) << r.yearEndEarnedInterest << endl;
    }
}

int main() {
    cout << "**********************************\n";
    cout << "*  Airgead Banking Investment    *\n";
    cout << "**********************************\n";

    do {
        double initial = getDouble("Initial Investment Amount: ", false);
        double monthly = getDouble("Monthly Deposit: ");
        double rate = getDouble("Annual Interest (percent): ");
        unsigned years = getYears("Number of years: ");
        pressAnyKey();

        InvestmentScenario scenario(initial, monthly, rate, years);

        auto reportA = InvestmentCalculator::simulate(scenario, false);
        printReport("Balance and Interest Without Additional Monthly Deposits", reportA);

        auto reportB = InvestmentCalculator::simulate(scenario, true);
        printReport("Balance and Interest With Additional Monthly Deposits", reportB);

    } while (askYesNo("\nRun another scenario? (Y/N): "));

    cout << "Goodbye\n";
    return 0;
}
