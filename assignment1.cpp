#include <ctype.h>
#include <stdlib.h>

#include <iostream>
#include <set>
#include <sstream>
#include <unordered_map>

using namespace std;

const int rows = 5;
const int cols = 5;

// Q1
void checkPassword() {
  string password;
  string message;
  bool hasRepeatedChars = false;
  bool hasNum = false;
  bool hasSpecialChar = false;
  std::unordered_map<char, int> charCount;
  set<char> specialChars;
  specialChars.insert('*');
  specialChars.insert('#');
  specialChars.insert('$');

  cout << "Please enter your password: ";
  getline(cin, password);

  for (int i = 0; i < password.length(); i++) {
    char c = password.at(i);

    if (!hasRepeatedChars && charCount[c] == 2) {
      hasRepeatedChars = true;
    } else {
      charCount[c]++;
    }
    if (!hasNum && isdigit(c)) {
      hasNum = true;
    }
    if (!hasSpecialChar && specialChars.count(c)) {
      hasSpecialChar = true;
    }
  }

  if (password.length() < 8) {
    message.append(
        "Error: your password should be at least 8 characters long.\n");
  }
  if (hasRepeatedChars) {
    message.append(
        "Error: your password has at least a character that occurs more than "
        "two times.\n");
  }
  if (!hasNum) {
    message.append(
        "Error: your password should contain at least one number.\n");
  }
  if (!hasSpecialChar) {
    message.append(
        "Error: your password should contain at least one of the the following "
        "special characters: *, #, $.\n");
  }

  if (message.empty()) {
    cout << "Your password is accepted!\n" << endl;
  } else {
    cout << message << endl;
  }
}

// Q2
void convertPhonetic() {
  string phoneticWords[26] = {
      "Alfa",   "Bravo",   "Charlie", "Delta",  "Echo",   "Foxtrot", "Golf",
      "Hotel",  "India",   "Juliett", "Kilo",   "Lima",   "Mike",    "November",
      "Oscar",  "Papa",    "Quebec",  "Romeo",  "Sierra", "Tango",   "Uniform",
      "Victor", "Whiskey", "X-ray",   "Yankee", "Zulu"};
  string input;

  cout << "Please enter a word: ";
  cin >> input;
  for (int i = 0; i < input.length(); i++) {
    cout << phoneticWords[input.at(i) - 'a'] << ' ';
  }
  cout << '\n' << endl;
}

// Q3-1
void fillMatrix(int matrix[rows][cols]) {
  srand(time(0));
  for (int y = 0; y < cols; y++) {
    for (int x = 0; x < rows; x++) {
      matrix[y][x] = rand() % (25 + 1);  // Generate a random number [0, 25]
    }
  }
}

// Q3-2
void printMatrix(int matrix[rows][cols]) {
  for (int y = 0; y < rows; y++) {
    for (int x = 0; x < cols; x++) {
      if (x != 0) {
        cout << ' ';
      }
      cout << matrix[y][x];
      if (x != rows - 1) {
        cout << " |";
      }
    }
    cout << "\n-----------------------\n";
  }
  cout << '\n';
}

// Q3-3
void multiplyMatrices(int matrix_left[rows][cols], int matrix_right[rows][cols],
                      int matrix_result[rows][cols]) {
  static int y = 0, z = 0, x = 0;
  if (y >= rows) {
    return;
  }

  if (x < cols) {
    if (z < cols) {
      matrix_result[y][x] += matrix_left[y][z] * matrix_right[z][x];
      z++;
      multiplyMatrices(matrix_left, matrix_right, matrix_result);
    }
    z = 0;
    x++;
    multiplyMatrices(matrix_left, matrix_right, matrix_result);
  }
  x = 0;
  y++;
  multiplyMatrices(matrix_left, matrix_right, matrix_result);
}

int main() {
  checkPassword();
  convertPhonetic();
  int matrix[rows][cols];
  int matrix2[cols][rows];
  int matrix_result[rows][cols] = {0};
  fillMatrix(matrix);
  fillMatrix(matrix2);
  printMatrix(matrix);
  printMatrix(matrix2);
  multiplyMatrices(matrix, matrix2, matrix_result);
  printMatrix(matrix_result);
  return 0;
}