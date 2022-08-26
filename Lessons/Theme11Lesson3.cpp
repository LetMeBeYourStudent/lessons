#include <iostream>
#include <string>

using namespace std;

// Определяет, будет ли слово палиндромом
// text может быть строкой, содержащей строчные символы английского алфавита и пробелы
// Пустые строки и строки, состоящие только из пробелов, — это не палиндромы
bool IsPalindrome(const string& text) {
    string new_text_no_space;

    for (const char c : text)
        if (c != ' ') new_text_no_space += c;

    if (new_text_no_space.empty() || text.empty()) return false;

    int half_word_size = static_cast<int>(new_text_no_space.size()) / 2;

    for (int i = 0; i < half_word_size; ++i)
        if (new_text_no_space[i] != new_text_no_space[new_text_no_space.size() - 1 - i]) return false;

    // Напишите недостающий код
    return true;
}

int main() {
    string text;
    getline(cin, text);

    if (IsPalindrome(text)) {
        cout << "palindrome"s << endl;
    } else {
        cout << "not a palindrome"s << endl;
    }
}