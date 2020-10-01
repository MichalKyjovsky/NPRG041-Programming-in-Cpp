#include <iostream>
#include <string>
#include <vector>

using namespace std;

void SayHello(const string& name) {
    cout << "Hello " << name << endl;
}

int main(int argc, char** argv) {
    vector<string> cmd_line_args(argv, argv + argc);
    int input_size = cmd_line_args.size();

    if (input_size > 1) {
        for (int i = 1; i < input_size; i++) {
            SayHello(cmd_line_args[i]);
        }
    } else {
        cerr << "NO Data has been provided, exiting the application!" << endl;
    }
    return 0;
}
