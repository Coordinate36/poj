#include <iostream>
#include <string>

using namespace std;

int match(string s1, string s2) {
    int len1 = s1.size();
    int len2 = s2.size();
    for (int i = 0; i <= len1; ++i) {
        bool isMatch = true;
        int maxj = min(len2, len1 - i);
        for (int j = 0; j < maxj; ++j) {
            if (s1[i + j] == '2' && s2[j] == '2') {
                isMatch = false;
                break;
            }
        }
        if (isMatch) {
            return max(len1, i + len2);
        }
    }
}

int main() {
    string s1, s2;
    cin >> s1 >> s2;
    cout << min(match(s1, s2), match(s2, s1)) << endl;
    return 0;
}