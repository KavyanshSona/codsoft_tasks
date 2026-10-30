#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <limits>
using namespace std;

class Calculator {
private:
    vector<string> history;
    const string historyFile = "calc_history.txt";

    void saveHistoryToFile() {
        ofstream file(historyFile, ios::app);
        if(file.is_open() && !history.empty()){
            file << history.back() << endl;
            file.close();
        }
    }

    double getNumber(string prompt) {
        double num;
        while(true) {
            cout << prompt;
            cin >> num;
            if(cin.fail()){
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input! Please enter a number.\n";
            } else {
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                return num;
            }
        }
    }

public:
    Calculator() {
        cout << "\n==========================================\n";
        cout << "  ADVANCED SCIENTIFIC CALCULATOR v2.0\n";
        cout << "  Developed for CODSOFT INTERNSHIP\n";
        cout << "==========================================\n";
    }

    void add(double a, double b) {
        string res = to_string(a) + " + " + to_string(b) + " = " + to_string(a+b);
        cout << "Result: " << a+b << endl;
        history.push_back(res); saveHistoryToFile();
    }
    void subtract(double a, double b) {
        string res = to_string(a) + " - " + to_string(b) + " = " + to_string(a-b);
        cout << "Result: " << a-b << endl;
        history.push_back(res); saveHistoryToFile();
    }
    void multiply(double a, double b) {
        string res = to_string(a) + " * " + to_string(b) + " = " + to_string(a*b);
        cout << "Result: " << a*b << endl;
        history.push_back(res); saveHistoryToFile();
    }
    void divide(double a, double b) {
        if(b==0){ cout << "Error: Division by zero not allowed!\n"; return; }
        string res = to_string(a) + " / " + to_string(b) + " = " + to_string(a/b);
        cout << "Result: " << fixed << setprecision(4) << a/b << endl;
        history.push_back(res); saveHistoryToFile();
    }
    void power(double a, double b) {
        cout << "Result: " << pow(a,b) << endl;
        history.push_back(to_string(a)+" ^ "+to_string(b)+" = "+to_string(pow(a,b)));
        saveHistoryToFile();
    }
    void squareRoot(double a) {
        if(a<0){ cout << "Error: Negative number!\n"; return; }
        cout << "Result: " << sqrt(a) << endl;
        history.push_back("sqrt("+to_string(a)+") = "+to_string(sqrt(a)));
        saveHistoryToFile();
    }
    void logarithm(double a) {
        if(a<=0){ cout << "Error: Log of non-positive!\n"; return; }
        cout << "Log: " << log10(a) << endl;
        history.push_back("log("+to_string(a)+") = "+to_string(log10(a)));
        saveHistoryToFile();
    }

    void showHistory() {
        cout << "\n--- CALCULATION HISTORY ---\n";
        ifstream file(historyFile);
        string line;
        int i=1;
        if(!file.is_open()){ cout << "No history found.\n"; return; }
        while(getline(file, line)){
            cout << i++ << ". " << line << endl;
        }
        file.close();
    }
    void clearHistory() {
        ofstream file(historyFile, ios::trunc);
        file.close();
        history.clear();
        cout << "History cleared successfully!\n";
    }

    void run() {
        int choice;
        do {
            cout << "\n--- MAIN MENU ---\n";
            cout << "1. Addition (+)\n2. Subtraction (-)\n3. Multiplication (*)\n4. Division (/)\n";
            cout << "5. Power (x^y)\n6. Square Root\n7. Logarithm (log10)\n";
            cout << "8. View History\n9. Clear History\n10. Exit\n";
            cout << "Enter choice: ";
            cin >> choice;

            if(choice>=1 && choice<=5){
                double a = getNumber("Enter first number: ");
                double b = getNumber("Enter second number: ");
                if(choice==1) add(a,b);
                if(choice==2) subtract(a,b);
                if(choice==3) multiply(a,b);
                if(choice==4) divide(a,b);
                if(choice==5) power(a,b);
            } else if(choice==6 || choice==7){
                double a = getNumber("Enter number: ");
                if(choice==6) squareRoot(a);
                if(choice==7) logarithm(a);
            } else if(choice==8) showHistory();
            else if(choice==9) clearHistory();
            else if(choice==10) cout << "Thank you! Exiting calculator.\n";
            else cout << "Invalid choice!\n";

        } while(choice!=10);
    }
};

int main() {
    Calculator calc;
    calc.run();
    return 0;
}
