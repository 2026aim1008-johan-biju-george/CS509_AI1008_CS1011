#include "../headers/algorithms.hpp"
#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>

using namespace std;

int main() {
    srand(time(0));
    int choice;
    string filename;

    do {
        cout << "Assignment 2 (Buddy)\n";
        cout << "1. Run Triangle Counting\n";
        cout << "2. Run Betweenness Centrality\n";
        cout << "3. Run Connected Components\n";
        cout << "0. Exit\n";
        
        cout << "Enter choice: ";
        cin >> choice;

        switch(choice) {
            case 1:
                cout << "Enter input file path: ";
                cin >> filename;
                runTriangleCounting(filename);
                break;

            case 2:
                cout << "Enter input file path: ";
                cin >> filename;
                runBetweennessCentrality(filename);
                break;

            case 3:
                cout << "Enter input file path: ";
                cin >> filename;
                runConnectedComponents(filename);
                break;

            case 0:
                cout << "Exiting...\n";
                break;

            default:
                cout << "Invalid choice.\n";
        }
        cout << "\n";
    } while (choice != 0);

    return 0;
}