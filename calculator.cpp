#include <iostream>

using namespace std;

double add(double x, double y) {
    return x + y;
}

double subtract(double x, double y) {
    return x - y;
}

double multiply(double x, double y) {
    return x * y;
}

double divide(double x, double y) {
    if (y == 0) {
        cout << "Error! Incorrect format for division." << endl;
        return -1;
    } else {
        return x / y;
    }
}

int main() {
    int choice;
    double num1, num2;
    
    while (true) {
        cout << "Select operation:" << endl;
        cout << "1. Add" << endl;
        cout << "2. Subtract" << endl;
        cout << "3. Multiply" << endl;
        cout << "4. Divide" << endl;
        cout << "5. Exit" << endl;
        cout << "Choose the operation number you wants to perform: ";
        cin >> choice;
        
        if (choice == 5) {
            cout << "Exiting the calculator." << endl;
            break;
        }
        
        if (choice >= 1 && choice <= 4) {
            cout << "Enter first number: ";
            cin >> num1;
            cout << "Enter second number: ";
            cin >> num2;

            switch (choice) {
                case 1:
                    cout << "The result is: " << add(num1, num2) << endl;
                    break;
                case 2:
                    cout << "The result is: " << subtract(num1, num2) << endl;
                    break;
                case 3:
                    cout << "The result is: " << multiply(num1, num2) << endl;
                    break;
                case 4:
                    cout << "The result is: " << divide(num1, num2) << endl;
                    break;
            }
        } else {
            cout << "Invalid choice. Please try again." << endl;
        }
    }

    return 0;
}


                                   // THANKYOU ALL //
 