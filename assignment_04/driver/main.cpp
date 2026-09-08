#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include "../headers/kmeans.hpp"


using namespace std;

int main() {
    
    srand(time(0)); 
    
    int choice;
    string filename;

    do {
        cout << "Assignment 4 (Buddy Tasks)\n";
        cout << "1. Run K-Means Clustering\n";
        cout << "0. Exit\n";
        
        cout << "Enter choice: ";
        cin >> choice;

        switch(choice) {
            case 1:
                cout << "Enter input file path (e.g., tests/km_01.txt): ";
                cin >> filename;
                runKMeansTask(filename);
                break;
            case 0:
                cout << "Exiting...\n";
                break;

            default:
                cout << "Invalid choice. Please try again.\n";
        }
        cout << "\n";
    } while (choice != 0);

    return 0;
}