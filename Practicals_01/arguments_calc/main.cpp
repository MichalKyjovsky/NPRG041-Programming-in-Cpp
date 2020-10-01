#include <iostream>
#include <string>
#include <stack>
#include <vector>

using namespace std;

const string kNumericCharacters = "0123456789";
const string kBinaryOperators = "+-*/";

bool IsNumber(char& number) {
        if (kNumericCharacters.find(number) != string::npos) {
            return true;
        }
    return false;
}

bool IsOperator(const char& func) {
    if (kBinaryOperators.find(func) != string::npos) {
        return true;
    } else {
        return false;
    }
}

int OperatorPriority(char& func) {
    if (func == '+' || func == '-') {
        return 1;
    } else if (func == '*' || func == '/') {
        return 2;
    } else {
        return 0; // We are on the bottom of the stack, i.e. '#'.
    }
}

vector<string> ConvertToPostfix(string& expression) {
    string out_expression;
    vector<string> out_expression_arr;
    stack<char> operators_stack;
    operators_stack.push('#'); // Boundary

    for (char c : expression) {
        if (IsNumber(c)) {
            out_expression += c;
        } else if (IsOperator(c)) {
            out_expression_arr.push_back(out_expression);
            out_expression = "";
            if (OperatorPriority(c) > OperatorPriority(operators_stack.top())) {
                operators_stack.push(c);
            } else {
                while (operators_stack.top() != '#'
                && OperatorPriority(c) <= OperatorPriority(operators_stack.top())) {
                    out_expression_arr.push_back(string(1, operators_stack.top()));
                    operators_stack.pop();
                }
                operators_stack.push(c);
            }
        } else {
            cerr << "Unrecognized input. Quiting the application!" << endl;
            exit(1);
        }
    }
    out_expression_arr.push_back(out_expression);
    while (operators_stack.top() != '#') {
        out_expression_arr.push_back(string(1, operators_stack.top()));
        operators_stack.pop();
    }

    return out_expression_arr;
}

int EvaluatePostfixExpression(const vector<string> &expression) {
    stack<int> values;

    for (string value: expression) {
        if (!IsOperator(value[0])) {
            values.push(stoi(value));
        } else {
            int arg_1 = values.top();
            values.pop();
            int arg_2 = values.top();
            values.pop();

            switch (value[0]) {
                case '+': values.push(arg_1 + arg_2);
                    break;
                case '-': values.push(arg_2 - arg_1);
                    break;
                case '*': values.push(arg_1 * arg_2);
                    break;
                case '/': values.push(arg_2 / arg_1);
                    break;
            }
        }
    }
    return values.top();
}


int main(int argc, char** argv) {
    vector<string> cmd_line_args(argv, argv + argc);
    cout << EvaluatePostfixExpression(ConvertToPostfix(cmd_line_args[1])) << endl;
    return 0;
}
