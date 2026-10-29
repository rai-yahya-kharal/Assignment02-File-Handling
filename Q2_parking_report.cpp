/*
 * Name       : MUHAMMAD YAHYA ASHFAQ
 * Reg No     : L1S26BSCS0041
 * Assignment : ASSIGNMWNT 2
 * Question   : Q2 - Parking Report
 */

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

int main() {
    ifstream inFile("parking.txt");
    if (!inFile) {
        cout << "parking.txt not found!" << endl;
        return 1;
    }

    int day, month, year;
    char slash1, slash2;
    inFile >> day >> slash1 >> month >> slash2 >> year;
    inFile.ignore(100, '\n'); // skip rest of line 1

    char header[100];
    inFile.getline(header, 100); // skip header line

    char plate[15];
    char type;
    int inH, inM, outH, outM;
    char colon;

    int vehicleCount = 0;
    int carCount = 0;
    int bikeCount = 0;
    int totalCollected = 0;

    int maxMinutes = -1;
    char longestPlate[15] = "";
    int longestH = 0;
    int longestM = 0;

    ofstream receipts("receipts.txt");
    receipts << "Receipts for " << day << "/" << month << "/" << year << endl;

    cout << "Parking report for " << day << "/" << month << "/" << year << endl;

    while (inFile >> plate >> type >> inH >> colon >> inM >> outH >> colon >> outM) {
        vehicleCount++;

        int inTotalMins = inH * 60 + inM;
        int outTotalMins = outH * 60 + outM;
        int parkedMins = outTotalMins - inTotalMins;

        int hoursCharged = (parkedMins + 59) / 60;
        if (hoursCharged == 0) {
            hoursCharged = 1;
        }

        int fee = 0;
        if (type == 'C') {
            fee = hoursCharged * 100;
            carCount++;
            cout << plate << " Car ";
        }
        else if (type == 'B') {
            fee = hoursCharged * 40;
            bikeCount++;
            cout << plate << " Bike ";
        }

        int hParked = parkedMins / 60;
        int mParked = parkedMins % 60;

        cout << hParked << " h " << mParked << " min Fee: " << fee << endl;

        totalCollected += fee;
        receipts << plate << " " << fee << endl;

        if (parkedMins > maxMinutes) {
            maxMinutes = parkedMins;
            strcpy(longestPlate, plate);
            longestH = hParked;
            longestM = mParked;
        }
    }

    inFile.close();
    receipts.close();

    if (vehicleCount == 0) {
        cout << "No vehicles found!" << endl;
        return 0;
    }

    cout << "Vehicles: " << vehicleCount << endl;
    cout << "Cars: " << carCount << " Bikes: " << bikeCount << endl;
    cout << "Total collected: " << totalCollected << endl;
    cout << "Longest stay: " << longestPlate << " (" << longestH << " h " << longestM << " min)" << endl;

    return 0;
}
