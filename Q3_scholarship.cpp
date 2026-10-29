/*
 * Name       : MUHAMMAD YAHYA ASHFAQ
 * Reg No     : L1S26BSCS0041
 * Assignment : ASSIGNMENT 2
 * Question   : Q3 - Scholarship List
 */

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

int main() {
    char path[100];
    cout << "Enter the file name: ";
    cin.getline(path, 100);

    ifstream inFile(path);
    if (!inFile.is_open()) {
        cout << "Could not open " << path << "!" << endl;
        return 1;
    }

    int n;
    inFile >> n;
    inFile.ignore(100, '\n'); // skip rest of line after n

    if (n > 30) {
        cout << "Too many students!" << endl;
        inFile.close();
        return 0;
    }

    ofstream scholarship("scholarship.txt");

    char name[30];
    double cgpa;
    int studentsRead = 0;
    double totalCgpa = 0.0;
    int eligibleCount = 0;

    double maxCgpa = -1.0;
    char topStudentName[30] = "";

    for (int i = 0; i < n; i++) {
        if (!inFile.getline(name, 30, ',')) {
            break;
        }
        if (!(inFile >> cgpa)) {
            break;
        }
        inFile.ignore(100, '\n'); // skip rest of line

        studentsRead++;
        totalCgpa += cgpa;

        cout << "[" << name << "] CGPA: " << cgpa << endl;

        if (cgpa >= 3.50) {
            scholarship << name << "," << cgpa << endl;
            eligibleCount++;
        }

        if (cgpa > maxCgpa) {
            maxCgpa = cgpa;
            strcpy(topStudentName, name);
        }
    }

    inFile.close();
    scholarship.close();

    if (studentsRead < n) {
        cout << "Warning: only " << studentsRead << " of " << n << " records found." << endl;
    }

    if (studentsRead == 0) {
        cout << "No students found!" << endl;
        return 0;
    }

    double averageCgpa = totalCgpa / studentsRead;

    cout << "Students: " << studentsRead << endl;
    cout << "Average CGPA: " << averageCgpa << endl;
    cout << "Eligible for scholarship: " << eligibleCount << endl;
    cout << "Top student: " << topStudentName << " (" << maxCgpa << ")" << endl;

    return 0;
}
