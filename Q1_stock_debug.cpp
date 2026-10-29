/*
 * Name       : Muhammad Yahya Ashfaq
 * Reg No     : L1S26BSCS0041
 * Assignment : ASSIGNMENT 2
 * Question   : Q1 - Stock Report (Debugging)
 */

 // FIX 1: <fstream> was missing, so ifstream and ofstream were unknown
#include <fstream>
#include <iostream>
using namespace std;

int main() {
    ifstream inFile("stock.txt");
    // FIX 2: Check condition was wrong (!inFile should be checked to detect if file failed to open)
    if (!inFile) {
        cout << "stock.txt not found!" << endl;
        return 1;
    }

    // FIX 3: ios::app flag was missing, so a plain ofstream would overwrite the old lines in reorder.txt
    ofstream reorder("reorder.txt", ios::app);

    char code[10];
    int qty, count = 0, low = 0;
    double price;
    // FIX 4: total must be a double because price has decimals, initializing it as int caused loss of decimal precision
    double total = 0.0;

    while (count < 50 && inFile >> code >> qty >> price) {
        count++;
        // FIX 5: Fixed calculation logic (total = total + (qty * price)); previously it was storing wrong integer multiplication
        total = total + (qty * price);
        if (qty < 10) {
            // FIX 6: Added endl to write each low stock item on a new line in reorder.txt
            reorder << code << " " << qty << endl;
            low++;
        }
    }
    inFile.close();
    reorder.close();

    cout << "Items: " << count << endl;
    cout << "Total stock value: " << total << endl;
    cout << "Low stock items: " << low << endl;
    return 0;
}
