/*
 * Name       : MUHAMMAD YAHYA ASHFAQ
 * Reg No     : L1S26BSCS0041
 * Assignment : ASSIGNMENT 2
 * Question   : Q5 - Expense Tracker
 */

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

void displayMenu() {
    cout << "===== Expense Tracker =====" << endl;
    cout << "1. Add an expense" << endl;
    cout << "2. Show all expenses" << endl;
    cout << "3. Show total of a category" << endl;
    cout << "4. Clear all expenses" << endl;
    cout << "5. Exit" << endl;
    cout << "Enter your choice: ";
}

int main() {
    int choice;

    do {
        displayMenu();
        if (!(cin >> choice)) {
            break;
        }

        if (choice == 1) {
            char category[20];
            int amount;
            cout << "Enter category: ";
            cin >> category;
            cout << "Enter amount: ";
            cin >> amount;

            if (amount <= 0) {
                cout << "Invalid amount!" << endl;
            }
            else {
                ofstream outFile("expenses.txt", ios::app);
                if (outFile) {
                    outFile << category << " " << amount << endl;
                    outFile.close();
                    cout << "Expense saved." << endl;
                }
            }
        }
        else if (choice == 2) {
            ifstream inFile("expenses.txt");
            if (!inFile) {
                cout << "No expenses yet." << endl;
            }
            else {
                char categories[100][20];
                int amounts[100];
                int count = 0;
                int totalSpent = 0;

                while (count < 100 && inFile >> categories[count] >> amounts[count]) {
                    totalSpent += amounts[count];
                    count++;
                }
                inFile.close();

                if (count == 0) {
                    cout << "No expenses yet." << endl;
                }
                else {
                    for (int i = 0; i < count; i++) {
                        cout << i + 1 << ". " << categories[i] << " " << amounts[i] << endl;
                    }
                    cout << "Total spent: " << totalSpent << endl;

                    int maxAmount = amounts[0];
                    int maxIndex = 0;
                    for (int i = 1; i < count; i++) {
                        if (amounts[i] > maxAmount) {
                            maxAmount = amounts[i];
                            maxIndex = i;
                        }
                    }
                    cout << "Largest expense: " << categories[maxIndex] << " (" << maxAmount << ")" << endl;
                }
            }
        }
        else if (choice == 3) {
            char targetCategory[20];
            cout << "Enter category: ";
            cin >> targetCategory;

            ifstream inFile("expenses.txt");
            if (!inFile) {
                cout << "No expenses found for " << targetCategory << endl;
            }
            else {
                char category[20];
                int amount;
                int catCount = 0;
                int catTotal = 0;

                while (inFile >> category >> amount) {
                    if (strcmp(category, targetCategory) == 0) {
                        catCount++;
                        catTotal += amount;
                    }
                }
                inFile.close();

                if (catCount == 0) {
                    cout << "No expenses found for " << targetCategory << endl;
                }
                else {
                    cout << "Expenses in " << targetCategory << ": " << catCount << endl;
                    cout << "Total for " << targetCategory << ": " << catTotal << endl;
                }
            }
        }
        else if (choice == 4) {
            ofstream outFile("expenses.txt"); // opening in plain ofstream clears the file
            outFile.close();
            cout << "All expenses cleared." << endl;
        }
        else if (choice == 5) {
            cout << "Goodbye!" << endl;
            break;
        }
        else {
            cout << "Invalid choice!" << endl;
        }

    } while (choice != 5);

    return 0;
}
