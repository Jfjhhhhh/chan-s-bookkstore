#ifndef SRC_TOKEN_SCANNER_H
#define SRC_TOKEN_SCANNER_H

#include <cstring>
#include <iostream>

using std::string;

class Tokenscanner {
private:
    std::string str;
    int pos;
public:
    Tokenscanner() { pos = 0; }

    ~Tokenscanner() = default;

    void read(const string &s) {
        str = s;
        pos = 0;
    }

    string nextToken() {
        int i = pos;
        if (str[pos] == '\0')return "";
        while (str[pos] == ' ') {
            i++;
            pos++;
        }
        while (str[pos] != ' ' && str[pos] != '\0') { pos++; }
        return str.substr(i, pos - i);
    }

    bool haveMoreTokens() {
        while (str[pos] == ' ')pos++;
        if (str[pos] == '\0')return false;
        else return true;
    }

    bool check_ID(const string &s) {
        if (s.size() > 30) return false;
        for (int i = 0; i < s.size(); i++)
            if (!(s[i] >= '0' && s[i] <= '9' ||
                  s[i] >= 'A' && s[i] <= 'Z' ||
                  s[i] >= 'a' && s[i] <= 'z' ||
                  s[i] == '_'))
                return false;
        return true;
    }

    bool check_Passwd(const string &s) {
        if (s.size() > 30) return false;
        for (int i = 0; i < s.size(); i++)
            if (!(s[i] >= '0' && s[i] <= '9' ||
                  s[i] >= 'A' && s[i] <= 'Z' ||
                  s[i] >= 'a' && s[i] <= 'z' ||
                  s[i] == '_'))
                return false;
        return true;
    }

    bool check_Username(const string &s) {
        if (s.size() > 30) return false;
        for (int i = 0; i < s.size(); i++)
            if (!(s[i] >= 33 && s[i] <= 126))return false;
        return true;
    }

    bool check_Privilege(const string &s) {
        if (s.size() != 1) return false;
        if (s == "0" || s == "1" || s == "3" || s == "7") {
            return true;
        }
        return false;
    }

    bool check_ISBN(const string &s) {
        if (s.size() > 20) return false;
        for (int i = 0; i < s.size(); i++)
            if (!(s[i] >= 33 && s[i] <= 126))return false;
        return true;
    }

    bool check_BookName(const string &s) {
        if (s.size() > 60) return false;
        for (int i = 0; i < s.size(); i++)
            if (!(s[i] >= 33 && s[i] <= 126) || s[i] == '"')return false;
        return true;
    }

    bool check_Author(const string &s) {
        if (s.size() > 60) return false;
        for (int i = 0; i < s.size(); i++)
            if (!(s[i] >= 33 && s[i] <= 126) || s[i] == '"')return false;
        return true;
    }

    bool check_Keyword(const string &s) {
        if (s.size() > 60) return false;
        if (s[0] == '|') return false;
        if (s[s.size() - 1] == '|') return false;
        for (int i = 0; i < s.size(); i++) {
            if (!(s[i] >= 33 && s[i] <= 126))return false;
            if (s[i] == '|') {
                if (s[i + 1] == '|') return false;
            }
        }
        return true;
    }

    bool check_Quantity(const string &s) {
        if (s.size() > 10) return false;
        long long k = 0;
        for (int i = 0; i < s.size(); i++) {
            if (!(s[i] >= '0' && s[i] <= '9'))
                return false;
            k += s[i];
            if (k > 2147483647) return false;
            k *= 10;
        }
        return true;
    }

    bool check_Price(const string &s) {
        if (s.size() > 13) return false;
        for (int i = 0; i < s.size(); i++) {
            if (i == s.size() - 3) {
                if (s[i] != '.') return false;
            } else {
                if (!(s[i] >= '0' && s[i] <= '9'))
                    return false;
            }
        }
        return true;
    }

    bool check_TotalCost(const string &s) {
        if (s.size() > 13) return false;
        for (int i = 0; i < s.size(); i++) {
            if (i == s.size() - 3) {
                if (s[i] != '.') return false;
            } else {
                if (s[i] == '-' && i == 0) continue;
                if (!(s[i] >= '0' && s[i] <= '9'))
                    return false;
            }
        }
        return true;
    }

    double StringtoDouble(const string &s) {
        double flag = 1.00;
        int i = 0;
        if (s[0] == '-')flag = -1.00;
        i = 1;
        double tot = 0;
        for (; i < s.size() - 3; i++) {
            tot += s[i] - '0';
            tot *= 10.00;
        }
        tot /= 10.00;
        tot += 0.1 * (s[s.size() - 2] - '0') + 0.2 * (s[s.size()-1] - '0');
        return tot;
    }
};

#endif //SRC_TOKEN_SCANNER_H
