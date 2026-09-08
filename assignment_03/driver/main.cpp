#include "../headers/gradient_descent.hpp"
#include "../headers/csr_graph_creation.h"
#include "../headers/maxflow.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <ctime>
#include <cstdlib>

using namespace std;

int main(){
    srand(time(0));
    int choice;

    do{
        cout << "Assignment 3 (Buddy)\n";
        cout << "1. Run Gradient Descent\n";
        cout << "2. Run Maxflow Mincut\n";
        cout << "0. Exit\n";
        
        cout << "Enter choice: ";
        cin >> choice;

        switch(choice){
            case 1:{
                run_gradient_descent_test();
                break;
            }

            case 2:
                run_maxflow_test();
                break;

            case 0:
                cout << "Exiting...\n";
                break;

            default:
                cout << "Invalid choice.\n";
        }
        cout << endl;
    } while (choice != 0);

    return 0;
}