    #include <iostream>
    #include <string>
    
    using namespace std;
    
    std::string removeString(string s, string rmStr) {
        int i = s.find(rmStr);
        // cout << rmStr << endl;
        // cout << "i:" << i << endl;
        return s.substr(0, i) + s.substr(i + rmStr.size());
    }
    
    bool isMatch(string s, string p) {
        string rmStr;
        for (size_t i = 0; i < p.size(); ++i) {
            if (p[i] == '*' || p[i] == '.') {
                continue;
            }
            rmStr = p[i];
            for (size_t j = i + 1; j < p.size(); ++j) {
                if (p[j] != '*' && p[j] != '.') {
                    rmStr = p.substr(i, j + 1);
                }
                else {
                    break;
                }
            }
            s = removeString(s, rmStr);
            p = removeString(p, rmStr);
            cout << s << endl;
            cout << p << endl;
            rmStr = "";
        }

        int quantutyOfPpoint = 0;
        bool flagOfStar = false;
        for (size_t i = 0; i < s.size(); ++i) {
            if (p[i] == '.') {
                ++quantutyOfPpoint;
            }
            if (p[i] == '*') {
                flagOfStar = true;
            }
        }

        if (flagOfStar && quantutyOfPpoint <= s.size()) {
            return true;
        }
        else if (!flagOfStar && flagOfStar == s.size()) {
            return true;
        }
        else {
            return false;
        }

    }

    int main() {
        cout << isMatch("mississippi", "mis*is*p*.") << endl;

        return 0;
    }