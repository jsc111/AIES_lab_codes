#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
using namespace std;

bool isValid(unordered_map<char, int> &letterToDigit, string &word1, string &word2, string &result) {
    int num1 = 0, num2 = 0, numResult = 0;

    for (char ch : word1) num1 = num1 * 10 + letterToDigit[ch];
    for (char ch : word2) num2 = num2 * 10 + letterToDigit[ch];
    for (char ch : result) numResult = numResult * 10 + letterToDigit[ch];

    return num1 + num2 == numResult;
}

bool solveCryptarithmetic(vector<char> &letters, unordered_map<char, int> &letterToDigit, vector<bool> &usedDigits, int idx, string &word1, string &word2, string &result) {
    if (idx == letters.size()) {
        return isValid(letterToDigit, word1, word2, result);
    }

    for (int digit = 0; digit <= 9; digit++) {
        if (!usedDigits[digit]) {
            usedDigits[digit] = true;
            letterToDigit[letters[idx]] = digit;
            if (solveCryptarithmetic(letters, letterToDigit, usedDigits, idx + 1, word1, word2, result)) {
                return true;
            }
            usedDigits[digit] = false;
        }
    }

    return false;
}

int main() {
    string word1 = "SEND", word2 = "MORE", result = "MONEY";
    vector<char> letters = {'S', 'E', 'N', 'D', 'M', 'O', 'R', 'Y'};
    unordered_map<char, int> letterToDigit;
    vector<bool> usedDigits(10, false);

    if (solveCryptarithmetic(letters, letterToDigit, usedDigits, 0, word1, word2, result)) {
        cout << "Solution found:\n";
        for (auto &pair : letterToDigit) {
            cout << pair.first << " = " << pair.second << endl;
        }
    } else {
        cout << "No solution exists.\n";
    }

    return 0;
}
