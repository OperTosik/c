#include <iostream>
#include <ctime>

using namespace std;

string longestPalindrome(string s) {
    if (s == "") return "";
    int size = 1;
    string temp;
    string res = s.substr(0, 1);
    for (int i = 0; i < s.size(); ++i) {
        if (i + 1 < s.size() && s[i] == s[i + 1]) {
            temp = s.substr(i, 2);
            for (int j = i + 1; j < s.size(); ++j) {

            }
        }
    }
    return res;
}

int main(void) {
    clock_t start = clock();
    string s = "";
    string t = "fsghj";
    // cout << string(t[1] + t[2]) << endl;
    // cout << longestPalindrome(s) << endl;
    clock_t end = clock();
    cout << ((double) (end - start)) * 1000 / CLOCKS_PER_SEC << endl;
    return 0;
}