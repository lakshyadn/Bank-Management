#include <fstream>
#include <iomanip>
#include <iostream>
#include <map>
#include <string>
#include <vector>

struct Transaction {
  std::string description;
  double amount;
  std::string category;
};

class PersonalFinanceTracker {
private:
  std::vector<Transaction> transactions;
  double balance;
  std::map<std::string, double> categoryTotals;

public:
  PersonalFinanceTracker() : balance(0.0) { loadTransactions(); }

  ~PersonalFinanceTracker() { saveTransactions(); }

  void addTransaction(const std::string &description, double amount,
                      const std::string &category) {
    Transaction transaction{description, amount, category};
    transactions.push_back(transaction);
    balance += amount;

    // Update category totals
    categoryTotals[category] += amount;
  }

  void showTransactions() {
    std::cout << "Transaction History:\n";
    for (const Transaction &transaction : transactions) {
      std::cout << "Description: " << transaction.description << "\n";
      std::cout << "Category: " << transaction.category << "\n";
      std::cout << "Amount: " << transaction.amount << "\n";
      std::cout << "-------------------------\n";
    }
    std::cout << "Current Balance: " << balance << "\n";
  }

  void showCategoryTotals() {
    std::cout << "Category Totals:\n";
    for (const auto &categoryTotal : categoryTotals) {
      std::cout << "Category: " << categoryTotal.first << "\n";
      std::cout << "Total Expense: " << categoryTotal.second << "\n";
      std::cout << "-------------------------\n";
    }
  }

  void generateReport() {
    std::ofstream report("finance_report.txt");
    if (report.is_open()) {
      report << "Finance Report\n";
      report << "-------------------------\n";
      report << "Transaction History:\n";
      for (const Transaction &transaction : transactions) {
        report << "Description: " << transaction.description << "\n";
        report << "Category: " << transaction.category << "\n";
        report << "Amount: " << transaction.amount << "\n";
        report << "-------------------------\n";
      }
      report << "Category Totals:\n";
      for (const auto &categoryTotal : categoryTotals) {
        report << "Category: " << categoryTotal.first << "\n";
        report << "Total Expense: " << categoryTotal.second << "\n";
        report << "-------------------------\n";
      }
      report << "Current Balance: " << balance << "\n";
      report.close();
      std::cout << "Report generated in finance_report.txt\n";
    } else {
      std::cout << "Unable to generate report.\n";
    }
  }

  void loadTransactions() {
    std::ifstream file("transactions.txt");
    if (file.is_open()) {
      while (!file.eof()) {
        Transaction transaction;
        file >> transaction.description >> transaction.amount >>
            transaction.category;
        transactions.push_back(transaction);
        balance += transaction.amount;
        categoryTotals[transaction.category] += transaction.amount;
      }
      file.close();
    }
  }

  void saveTransactions() {
    std::ofstream file("transactions.txt");
    if (file.is_open()) {
      for (const Transaction &transaction : transactions) {
        file << transaction.description << " " << transaction.amount << " "
             << transaction.category << "\n";
      }
      file.close();
    }
  }
};

int main() {
  PersonalFinanceTracker tracker;
  char choice;
  std::string incomeDescription, expenseDescription, incomeCategory,
      expenseCategory;
  double income, expense;

  do {
    std::cout << "Personal Finance Tracker Menu:\n";
    std::cout << "1. Add Income\n";
    std::cout << "2. Add Expense\n";
    std::cout << "3. Show Transactions\n";
    std::cout << "4. Show Category Totals\n";
    std::cout << "5. Generate Report\n";
    std::cout << "6. Exit\n";
    std::cout << "Enter your choice: ";
    std::cin >> choice;

    switch (choice) {
    case '1':
      std::cout << "Enter income description: ";
      std::cin.ignore();
      getline(std::cin, incomeDescription);
      std::cout << "Enter income amount: ";
      std::cin >> income;
      std::cout << "Enter income category: ";
      std::cin.ignore();
      getline(std::cin, incomeCategory);
      tracker.addTransaction(incomeDescription, income, incomeCategory);
      break;
    case '2':
      std::cout << "Enter expense description: ";
      std::cin.ignore();
      getline(std::cin, expenseDescription);
      std::cout << "Enter expense amount: ";
      std::cin >> expense;
      std::cout << "Enter expense category: ";
      std::cin.ignore();
      getline(std::cin, expenseCategory);
      tracker.addTransaction(expenseDescription, -expense, expenseCategory);
      break;
    case '3':
      tracker.showTransactions();
      break;
    case '4':
      tracker.showCategoryTotals();
      break;
    case '5':
      tracker.generateReport();
      break;
    case '6':
      std::cout << "Exiting the Personal Finance Tracker. Goodbye!\n";
      break;
    default:
      std::cout << "Invalid choice. Please try again.\n";
    }
  } while (choice != '6');

  return 0;
}