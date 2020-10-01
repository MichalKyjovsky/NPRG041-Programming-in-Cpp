#include <iostream>
#include <vector>
#include <string>

using namespace std;

const string kNumericCharacters = "0123456789";

bool IsNumber(const string& number) {
    for (char letter : number) {
        if (kNumericCharacters.find(letter) == string::npos) {
            return false;
        }
    }
    return true;
}


int main(int argc, char** argv) {
    vector<string> cmd_line_args(argv, argv + argc);

    int out_result = 0;
    for (int i = 1; i < cmd_line_args.size(); i++) {
        if (IsNumber(cmd_line_args[i])) {
            out_result += stoi(cmd_line_args[i]);
        } else {
            cerr << "\'+\' Operation is allowed only over integers, mismatch input error!" << endl;
            exit(1);
        }
    }
    cout << "The result of sum operation over program arguments: " << out_result << endl;
    return 0;
}

