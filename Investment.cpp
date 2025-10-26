#include "Investment.h"

InvestmentScenario::InvestmentScenario(double initial, double monthly, double rate, unsigned years)
    : m_initial(initial), m_monthly(monthly), m_rate(rate), m_years(years) {
}

double InvestmentScenario::getInitial() const { return m_initial; }
double InvestmentScenario::getMonthly() const { return m_monthly; }
double InvestmentScenario::getRate() const { return m_rate; }
unsigned InvestmentScenario::getYears() const { return m_years; }

std::vector<AnnualSummary> InvestmentCalculator::simulate(const InvestmentScenario& s, bool withDeposits) {
    unsigned months = s.getYears() * 12;
    double monthlyRate = (s.getRate() / 100.0) / 12.0;
    double opening = s.getInitial();
    double yearInterest = 0.0;
    std::vector<AnnualSummary> result;

    for (unsigned m = 1; m <= months; ++m) {
        double deposit = withDeposits ? s.getMonthly() : 0.0;
        double total = opening + deposit;
        double interest = total * monthlyRate;
        double closing = total + interest;
        yearInterest += interest;

        if (m % 12 == 0) {
            result.push_back({ (int)(m / 12), closing, yearInterest });
            yearInterest = 0.0;
        }
        opening = closing;
    }
    return result;
}
