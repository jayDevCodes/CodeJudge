#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

using namespace std;

string readFile(string path)
{
    ifstream file(path);
    return string((istreambuf_iterator<char>(file)),
                   istreambuf_iterator<char>());
}

int main()
{
    int total = 2;
    int passed = 0;

    for(int i=1;i<=total;i++)
    {
        string input = "tests/input" + to_string(i) + ".txt";
        string expected = "tests/output" + to_string(i) + ".txt";

        string cmd = "./solution < " + input + " > temp.txt";
        system(cmd.c_str());

        string out = readFile("temp.txt");
        string exp = readFile(expected);

        if(out.find(exp) != string::npos)
        {
            cout << "Test " << i << " PASSED\n";
            passed++;
        }
        else
        {
            cout << "Test " << i << " FAILED\n";
        }
    }

    cout << "\nPassed " << passed << "/" << total << " tests\n";
}