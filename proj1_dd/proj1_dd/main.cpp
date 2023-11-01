#include <iostream>
#include <vector>
#include "../Printing.h"
#include "../Validation.h"
#include "../PrimeImplicants.h"
using namespace std;

int main()
{

    //---------------------------Intro----------------------------------------
    cout << "🅀 🅄 🄸 🄽 🄴  🄼 🄲 🄲 🄻 🅄 🅂 🄺 🄴 🅈\n";
    cout << "Welcome to the Logic Minimization Tool!\n";
    cout << "\nPlease enter a Boolean expression in SOP or POS form: \n";
    cout << " Example (SOP): ab + bc + ca \n";
    cout << " Example (POS): (a + b + c)(a + b + c') \n";
    cout << "\nYour expression: ";

    //-----------------------User Input and Validation-----------------------

    string expression;
    getline(cin, expression);
    cout << endl;

    if (validation(expression))
    {
        cout << endl
             << "Valid Expression: ";
    }
    else
    {
        cout << endl
             << "Invalid Expression! \n";
    }
    if (isSOP(expression))
    {
        cout << "SOP\n";
    }
    else
    {
        cout << "POS\n";
    }

    if (validation(expression))
    {
        string bool_exp = transform(expression);
        // cout << " \t" << bool_exp << "\n"; // for testing the transform function

        //---------------------------------------Printing the TRUTH TABLE---------------------------------------------
        cout << "\n\n";
        vector<string> minterms = printTruthTable(bool_exp);
        cout << "\n\n";
        vector<string> Minterms = PrintBinaryMinterms(minterms); // binary
        //        vector<int> decimalMinterms = PrintDecimalMinterms(Minterms);//decimal

        //---------------------------------------Printing the PI------------------------------------------------------
        //        vector<string> primeImplicants = generatePrimeImplicants(Minterms);
        //        printPrimeImplicant_1(primeImplicants, Minterms);

        map<string, string> PI = generatePrimeImplicants(Minterms);
        for (const auto &pair : PI)
        {
            cout << "Prime Implicant: " << pair.first << ", Minterms Covered: " << pair.second << endl;
        }

        //-----------------------------------------Printing the EPI-------------------------------------------------
        vector<string> EPI = generateEssentialPrimeImplicants(PI);
        // print EPI
        cout << "\n\nEssential Prime Implicants: ";
        for (int i = 0; i < EPI.size(); i++)
        {
            cout << EPI[i] << " ";
        }

        //--------------------------------------Printing the K-MAP----------------------------------------------------
        cout << "\n\n\t\t\tK-MAP\t\t\n\n";
        vector<char> variables = extractVar(bool_exp);
        vector<string> Kminterms = PrintBinaryMinterms(minterms); // removed the "Minterms in sorted binary form:" from printbinary func
        print_KMap(Kminterms, variables);
        cout << "\n";
    }

    else
    {
        cout << "cant process the truth table ... Expression INVALID" << endl;
    }

    return 0;
}
