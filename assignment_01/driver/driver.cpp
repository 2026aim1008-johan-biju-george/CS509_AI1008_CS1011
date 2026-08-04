#include "../headers/graph_generator.h"
#include "../headers/bfs_dfs.h"
#include "../headers/sssp.h"
#include <iostream>

using namespace std;

int main(){
    srand(time(0));
    int choice;
    do{
        cout << "Assignment 1 (Buddy):\n";
        cout << "1. Generate Graph Test Files\n";
        cout << "2. Run BFS and DFS Algorithms\n";
        cout << "3. Run SSSP Algorithm\n";
        cout << "0. Exit\n";

        cout << "Enter choice: ";
        cin >> choice;

        switch(choice){
            case 1:
                generate_unweighted_tests();
                generate_weighted_tests();
                break;

            case 2:
                run_BFS_DFS();
                break;

            case 3:
                run_SSSP_test();
                break;

            case 0:
                cout << "Exiting...\n";
                break;

            default:
                cout << "Invalid choice.\n";
        }
    }while(choice != 0);
    return 0;
}