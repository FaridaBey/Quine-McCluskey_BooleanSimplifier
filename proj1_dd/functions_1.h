#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wconversion"

#ifndef functions_1_h
#define functions_1_h
#include <iostream>
#include <vector>
#include <cctype>
#include <algorithm>
#include <stack>
#include <set>
using namespace std;

//---------------Helper functions for validation------------------
// checks if there is a bracket that doesnt have a sibling
bool balancedParentheses(const string &expression)
{
    stack<char> s;
    for (char c : expression)
    {
        if (c == '(')
        {
            s.push(c);
        }
        else if (c == ')')
        {
            if (s.empty())
            {
                return false;
            }
            else
            {
                s.pop();
            }
        }
    }
    return s.empty();
}

// checks if the expression is in SOP form
bool isSOP(string &expression)
{
    for(int i=0; i<expression.length(); i++)
    {
        if(expression[i]==')'&&expression[i+1]=='(')
        {
            return false;
        }
        

    }
    //remove all brackets from expression
    expression.erase(remove(expression.begin(), expression.end(), '('), expression.end()); // Remove ( from the expression
    expression.erase(remove(expression.begin(), expression.end(), ')'), expression.end()); // Remove ) from the expression



    return true;
}



//--------------------------------Input Validation-------------------------------------------------

// function checks whether a given Boolean expression is a valid POS or SOP.
bool validation (string& boolean_exp)
{
      if(empty(boolean_exp)){
            cout << "Empty Expression\n"; // The expression can't be empty
            return false;
        }

         boolean_exp.erase(remove(boolean_exp.begin(), boolean_exp.end(), ' '), boolean_exp.end()); // Remove spaces from the expression
         
//    Define valid operators and count of variables
    vector<char> Val_operands = {'+', '(', ')', '\''} ;
    int var_count = 0;
    
    //check if more than 10 variables in expression by making a set of variables and counting the size of the set
    set<char> variables;
    for (int i=0; i < boolean_exp.length(); i++) {
        if(isalpha(boolean_exp[i]))
        {
        boolean_exp[i] = tolower(boolean_exp[i]); // Convert all variables to lowercase
       
        if(variables.find(boolean_exp[i]) == variables.end()) //if not in set, add to set
        {
            variables.insert(boolean_exp[i]);
            var_count++;
        }
        }
    }

if(var_count > 10){
            cout << "too many variables\n"; // No more than 10 variables
            return false;
        }

    for (int i=0; i < boolean_exp.length(); i++) {
        if(boolean_exp[i]=='\''&&boolean_exp[i+1]=='\'')
        {
            boolean_exp.erase(i,2);
            i--;
        }
    }

    for (int i=0; i < boolean_exp.length(); i++) {   
        
        //Alphabet characters or vallid operators check
        
        if (!(isalpha(boolean_exp[i]) || any_of(Val_operands.begin(), Val_operands.end(), [&boolean_exp, i](char v) {
            return v == boolean_exp[i];
        }))) {
            cout << "function invalid1" << endl; // Check if the character at index 'i' is an alphabetic character (letter) OR if it matches any character in the 'Val_operands' vector
            return false;
        }
        if(boolean_exp[i] == '+' && boolean_exp[i+1] == '+'){
            cout << "function invalid2.1" << endl; // Check if there are two '+' operators after each other
            return false;
        }
        else if(boolean_exp[i] == '+' && boolean_exp[i+1] == '\''){
            cout << "function invalid2.2" << endl; // Check if there is an apostraphe after a '+' operator
            return false;
        }
        else if((boolean_exp[i]=='('||boolean_exp[i]==')')&&boolean_exp[i+1]=='\'')
        {
            cout << "function invalid2.4" << endl; // Check if there is an apostraphe after a bracket
            return false;
        }
        else if(boolean_exp[i]=='('&&boolean_exp[i+1]=='+')
        {
            cout << "function invalid2.5" << endl; // Check if there is a '+' operator after a bracket
            return false;
        }
       
    }
    
    for(char oper : Val_operands){
        if((boolean_exp[0] == oper && boolean_exp[0] != '(' ) || ((boolean_exp[boolean_exp.length()-1] == oper && boolean_exp[boolean_exp.length()-1] != ')') && boolean_exp[boolean_exp.length()-1] != '\''))
        {
            cout << "function invalid4 \n"; // if expression starts with an operator other than '(' or ends with an operator other than ')' or ' it is invalid
            return false;
                
        }
        else if((boolean_exp[0] == '(' && boolean_exp[1] == oper) || (boolean_exp[boolean_exp.length()-1] == ')' && (boolean_exp[boolean_exp.length()-2] == oper && boolean_exp[boolean_exp.length()-2] != '\'')) || (boolean_exp[boolean_exp.length()-1] == '\'' && (boolean_exp[boolean_exp.length()-2] == oper && boolean_exp[boolean_exp.length()-2] != '\''))){
            cout << "function invalid5 \n"; // if expression starts with '(' or ends with [ ')' or '] and the second term is an operator it is invalid or second to last term is operator other than ' it is invalid
            return false;
        }
    }
    cout << boolean_exp << endl;
    if (!balancedParentheses(boolean_exp)){
        cout<<"function invalid6\n";
        return false;
    }
    

    if (!isSOP(boolean_exp)){
        //check valid POS structure with + in between terms in their brackets
       for(int i=0; i<boolean_exp.length()-1; i++)
       {
            if(isalpha(boolean_exp[i]) && isalpha(boolean_exp[i+1]))
            {
                cout<<"function invalid7\n";
                return false;
                
            }
            
       }
      
    }

    cout<<"Valid Function: " << boolean_exp <<"\n";
    return true;
};

//--------------- Helper functions for Print ------------------

// Function to extract variable names from the Boolean expression
set<char> extractVar(const string& boolean_exp) {
    set<char> variableNames;
    
    for (char character : boolean_exp) {
        if (isalpha(character)) {
            variableNames.insert(character);
        }
    }
    
    return variableNames;
}

// Function to assign values to variables in the Boolean expression
void assignValue(string& expression, char variable, bool value) {
    for (char& character : expression) {
        if (character == variable) {
            character = value ? '1' : '0';
        }
    }
}

// Function to evaluate the Boolean expression
bool EvaluateExpression(const string& boolean_exp) {
    //    evaluate the expression ??
    //    return to test the rest
    return false;
}
//----------------------------------------------------------------------------------------------------

// Function to generate canonical SoP expression (minterms)
string GenerateCanonicalSoP(const vector<vector<bool>>& truthTable, const set<char>& variableNames) {
    string canonical_SoP = "";

    int numRows = truthTable.size();
    int numVariables = variableNames.size();

    for (int i = 0; i < numRows; ++i) {
        bool output = truthTable[i][numVariables];
        if (output) {
            string minterm = "(";
            for (int j = 0; j < numVariables; ++j) {
                char variable = *next(variableNames.begin(), j);
                if (truthTable[i][j]) {
                    minterm += variable;  // Include the variable if it's true (minterm)
                } else {
                    minterm += "!" + string(1, variable);  // Include the negated variable if it's false (!minterm)
                }
                if (j < numVariables - 1) {
                    minterm += " * ";  // Separate variables with "AND" in the minterm
                }
            }
            minterm += ")";
            canonical_SoP += minterm;  // Add the minterm to the SoP expression
            if (i < numRows - 1) {
                canonical_SoP += " + ";  // Separate minterms with "OR" in the SoP expression
            }
        }
    }

    return canonical_SoP;
}

// Function to generate canonical PoS expression (maxterms)
string GenerateCanonicalPoS(const vector<vector<bool>>& truthTable, const set<char>& variableNames) {
    string canonical_PoS = "";

    int numRows = truthTable.size();
    int numVariables = variableNames.size();

    for (int i = 0; i < numRows; ++i) {
        bool output = truthTable[i][numVariables];
        if (!output) {
            string maxterm = "(";
            for (int j = 0; j < numVariables; ++j) {
                char variable = *next(variableNames.begin(), j);
                if (!truthTable[i][j]) {
                    maxterm += variable;  // Include the variable if it's false (maxterm)
                } else {
                    maxterm += "!" + string(1, variable);  // Include the negated variable if it's true (!maxterm)
                }
                if (j < numVariables - 1) {
                    maxterm += " + ";  // Separate variables with "OR" in the maxterm
                }
            }
            maxterm += ")";
            canonical_PoS += maxterm;  // Add the maxterm to the PoS expression
            if (i < numRows - 1) {
                canonical_PoS += " * ";  // Separate maxterms with "AND" in the PoS expression
            }
        }
    }

    return canonical_PoS;
}
//----------------------------------------------------------------------------------------------------

// Function to print the truth table and canonical SoP/PoS
void PrintTruthTable(const string& boolean_exp) {
    // Extract variable names from the Boolean expression
    set<char> variableNames = extractVar(boolean_exp);
    int numberOfVar = variableNames.size();
    string truthTableHeader = "";

    // Create the header row for the truth table
    for (char variable : variableNames) {
        truthTableHeader += variable;
        truthTableHeader += " | ";
    }

    truthTableHeader += "Output";
    cout << truthTableHeader << endl;

    // Calculate the number of rows for the truth table
    int rows = 1 << numberOfVar;

    // Initialize the truth table
    vector<vector<bool>> truthTable(rows, vector<bool>(numberOfVar, false));

    // Generate and print the truth table
    for (int i = 0; i < rows; ++i) {
        string current_exp = boolean_exp;

        // Populate the truth table and update the current expression
        for (int j = 0; j < numberOfVar; ++j) {
            bool value = (i >> j) & 1;
            char variable = *next(variableNames.begin(), j);
            assignValue(current_exp, variable, value);
            truthTable[i][j] = value;
        }

        // Evaluate the current expression and print the values in the row
        bool output = EvaluateExpression(current_exp);
        for (int j = 0; j < numberOfVar; ++j) {
            cout << truthTable[i][j] << " | ";
        }
        cout << output << endl;
    }

    // Print the canonical SoP/PoS expressions
    string canonicalSoP = GenerateCanonicalSoP(truthTable, variableNames);
    string canonicalPoS = GenerateCanonicalPoS(truthTable, variableNames);

    cout << "Canonical SoP: " << canonicalSoP << endl;
    cout << "Canonical PoS: " << canonicalPoS << endl;
}

//----------------------------------------------------------------------------------------------------


//---------------To be used for QM------------------
bool compareByOnes(int &a, int &b)
{
    int aOnes = __builtin_popcount(a);
    int bOnes = __builtin_popcount(b);
    return aOnes < bOnes;
}

void sortbyones(vector<int> &x)
{
    sort(x.begin(), x.end(), compareByOnes);

}
#endif /* functions_1_h */

#pragma clang diagnostic pop
