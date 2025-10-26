#pragma once
#ifndef INVESTMENT_H_
#define INVESTMENT_H_

#include <vector>

struct AnnualSummary {
    int year;
    double yearEndBalance;
    double yearEndEarnedInterest;
};

class InvestmentScenario {
public:
    InvestmentScenario(double initial, double monthly, double rate, unsigned years);
    double getInitial() const;
    double getMonthly() const;
    double getRate() const;
    unsigned getYears() const;
private:
    double m_initial;
    double m_monthly;
    double m_rate;
    unsigned m_years;
};

class InvestmentCalculator {
public:
    static std::vector<AnnualSummary> simulate(const InvestmentScenario& s, bool withDeposits);
};

#endif
