# CPJudge

A tiny local **Competitive Programming Judge** written in **C++**.

CPJudge allows you to run your solution locally against predefined test cases and instantly check whether your output matches the expected output.

This tool is useful for practicing competitive programming problems without needing an online judge.

---

## Features

* Run C++ solutions locally
* Automatically test solutions with multiple input files
* Compare program output with expected output
* Simple **PASS / FAIL** test results
* Lightweight and easy to use

---

## Project Structure

```
cpjudge
│
├── cpjudge.cpp
├── solution.cpp
│
├── tests
│   ├── input1.txt
│   ├── output1.txt
│   ├── input2.txt
│   └── output2.txt
│
└── README.md
```

---
 ## Program Example
<div align="center">

<img src="screenshots/first.jpg" alt="CPJudge Screenshot 1" width="600" height="350">

<br><br>

<img src="screenshots/second.jpg" alt="CPJudge Screenshot 2" width="450" height="400">

</div>

## Example Problem

Example solution (`solution.cpp`):

```
#include <iostream>
using namespace std;

int main() {
    int a, b;
    cin >> a >> b;
    cout << a + b << endl;
}
```

Example test files:

**tests/input1.txt**

```
1 2
```

**tests/output1.txt**

```
3
```

---

## Compile

Compile the solution:

```
g++ solution.cpp -o solution
```

Compile the judge:

```
g++ cpjudge.cpp -o cpjudge
```

---

## Run the Judge

```
./cpjudge
```

Example output:

```
Test 1 PASSED
Test 2 PASSED

Passed 2/2 tests
```

---

## Why CPJudge?

When practicing competitive programming, repeatedly copying input/output can be slow.
CPJudge automates this process by running your program against predefined test cases instantly.

---

## Future Improvements

* Colored PASS / FAIL output
* Support for unlimited test cases
* Time limit enforcement
* Command line arguments
* Automatic compilation
* Support for multiple programming languages

---

## License

MIT License

---

## Author

**Jay Dev**

GitHub: https://github.com/jayDevCodes
