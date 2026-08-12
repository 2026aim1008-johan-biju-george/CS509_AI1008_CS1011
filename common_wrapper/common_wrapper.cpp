#include <iostream>
#include <cstdlib>

using namespace std;

void run_assignment1() {
#ifdef _WIN32
    system("cd assignment_01 && assignment1.exe");
#else
    system("cd assignment_01 && ./assignment1");
#endif
}
void run_assignment2() {
#ifdef _WIN32
    system("cd assignment_02 && assignment2.exe");
#else
    system("cd assignment_02 && ./assignment2");
#endif
}

int main(){
    int choice;
    do
    {
        cout << "CS509 Lab Wrapper\n";
        cout << "1. Assignment 1\n";
        cout << "2. Assignment 2\n";
        cout << "0. Exit\n\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch(choice)
        {
            case 1:
                run_assignment1();
                break;
            case 2:
                run_assignment2();
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