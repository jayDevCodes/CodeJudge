#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <string>

#include "color.h"

using namespace std;

string readFile(const string &filename) {
    ifstream file(filename);
    stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

bool compareOutput(const string &file1, const string &file2) {
    string out1 = readFile(file1);
    string out2 = readFile(file2);

    return out1 == out2;
}

void runTest(int testNum, int &passed) {

    string inputFile = "tests/input" + to_string(testNum) + ".txt";
    string expectedFile = "tests/output" + to_string(testNum) + ".txt";
    string outputFile = "temp_output.txt";

    string runCmd = "./solution < " + inputFile + " > " + outputFile;
    system(runCmd.c_str());

    if (compareOutput(outputFile, expectedFile)) {
        cout << "Test " << testNum << " "
             << GREEN << "PASSED" << RESET << endl;
        passed++;
    } 
    else {
        cout << "Test " << testNum << " "
             << RED << "FAILED" << RESET << endl;
    }
}

int main() {

    enableColors();

    cout << YELLOW << "===== CodeJudge =====" << RESET << endl;

    string sourceFile = "solution.cpp";

    cout << "Compiling solution..." << endl;

    string compileCmd = "g++ " + sourceFile + " -o solution";

    if (system(compileCmd.c_str()) != 0) {
        cout << RED << "Compilation Failed" << RESET << endl;
        return 1;
    }

    cout << GREEN << "Compilation Successful" << RESET << endl;

    int totalTests = 3;
    int passed = 0;

    cout << "\nRunning Tests...\n" << endl;

    for (int i = 1; i <= totalTests; i++) {
        runTest(i, passed);
    }

    cout << "\n========================\n";

    if (passed == totalTests) {
        cout << GREEN << "All Tests Passed "
             << "(" << passed << "/" << totalTests << ")"
             << RESET << endl;
    } 
    else {
        cout << RED << "Tests Passed "
             << "(" << passed << "/" << totalTests << ")"
             << RESET << endl;
    }

    cout << "========================\n";

    return 0;
}
