#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <chrono>
#include <map>

using namespace std;
using namespace std::chrono;

const string RED = "\033[31m";
const string GREEN = "\033[32m";
const string YELLOW = "\033[33m";
const string RESET = "\033[0m";

string readFile(const string &path) {
    ifstream file(path);
    if (!file) return "";
    return string((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
}

bool fileExists(const string &path) {
    ifstream f(path);
    return f.good();
}

map<string, string> readConfig(const string &path) {
    map<string, string> config;
    ifstream f(path);
    string line;
    while (getline(f, line)) {
        if (line.empty() || line[0] == '#') continue;
        size_t eq = line.find('=');
        if (eq != string::npos) {
            string key = line.substr(0, eq);
            string value = line.substr(eq + 1);
            config[key] = value;
        }
    }
    return config;
}

int main() {
    int total_tests;
    double time_limit_sec = 0;
    string program_name, program_path, input_folder, output_folder;

    string config_file = "./config.txt";
    if (fileExists(config_file)) {
        auto config = readConfig(config_file);
        if (config.count("time_limit")) time_limit_sec = stod(config["time_limit"]);
        if (config.count("program_name")) program_name = config["program_name"];
        if (config.count("program_path")) program_path = config["program_path"];
        if (config.count("input_folder")) input_folder = config["input_folder"];
        if (config.count("output_folder")) output_folder = config["output_folder"];
        if (config.count("total_tests")) total_tests = stoi(config["total_tests"]);
    }

    if (program_name.empty()) { cout << "Program name:\n"; cin >> program_name; }
    if (program_path.empty()) { cout << "Program path:\n"; cin >> program_path; }
    if (input_folder.empty()) { cout << "Input folder:\n"; cin >> input_folder; }
    if (output_folder.empty()) { cout << "Output folder:\n"; cin >> output_folder; }
    if (time_limit_sec == 0) { cout << "Time limit in seconds (0 = no limit):\n"; cin >> time_limit_sec; }
    if (!config.count("total_tests")) {
        cout << "How many tests:\n";
        cin >> total_tests;
    }

    int passed = 0;

    for (int test_num = 1; test_num <= total_tests; ++test_num) {
        string input = input_folder + to_string(test_num) + ".txt";
        string expected = output_folder + to_string(test_num) + ".txt";

        if (!fileExists(input) || !fileExists(expected)) {
            cout << YELLOW << "Test " << test_num << " skipped (file missing)" << RESET << "\n";
            continue;
        }

#ifdef __APPLE__
        string cmd = "./" + program_path + program_name + " < " + input + " > temp.txt";
#elif _WIN32
        string cmd = "cmd /c \"cd /d " + program_path + " && " + program_name + " < " + input + " > temp.txt\"";
#endif

        auto start = high_resolution_clock::now();
        system(cmd.c_str());
        auto end = high_resolution_clock::now();

        double duration = duration_cast<milliseconds>(end - start).count() / 1000.0;
        string out = readFile("temp.txt");
        string exp = readFile(expected);

        if (time_limit_sec != 0 && duration > time_limit_sec) {
            cout << YELLOW << "Test " << test_num << " TIMEOUT (" << duration << "s)" << RESET << "\n";
        } else if (out == exp) {
            cout << GREEN << "Test " << test_num << " PASSED (" << duration << "s)" << RESET << "\n";
            passed++;
        } else {
            cout << RED << "Test " << test_num << " FAILED (" << duration << "s)" << RESET << "\n";
        }
    }

    cout << "\n" << GREEN << "Passed " << passed << RESET << "/" << total_tests << " tests\n";
}
