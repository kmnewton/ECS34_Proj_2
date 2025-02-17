#include "StringUtils.h"

namespace StringUtils{

std::string Slice(const std::string &str, ssize_t start, ssize_t end) noexcept{
    if (start < 0) {
        start = str.size() + start;
    }
    if (end < 0) {
        end = str.size() + end;
    }
    auto len = (end - start);
    return str.substr(start, len);
}

std::string Capitalize(const std::string &str) noexcept{
    std::string res = str;
    res[0] = toupper(res[0]);
    for (size_t i = 1; i < res.size(); i++) {
        res[i] = tolower(res[i]);
    }
    return res;
}

std::string Upper(const std::string &str) noexcept{
    std::string res = str;
    for (size_t i = 0; i < res.size(); i++) {
        res[i] = toupper(res[i]);
    }
    return res;
}

std::string Lower(const std::string &str) noexcept{
    std::string res = str;
    for (size_t i = 0; i < str.size(); i++) {
        res[i] = tolower(res[i]);
    }
    return res;
}

std::string LStrip(const std::string &str) noexcept{
    auto i = 0;
    while (str[i] == ' ') {
        i++;
    }
    return str.substr(i);
}

std::string RStrip(const std::string &str) noexcept{
    auto i = str.length() - 1;
    while (i >= 0 && str[i] == ' ') {
        i--;
    }
    int len = i + 1;
    return str.substr(0, len);
}

std::string Strip(const std::string &str) noexcept{
    auto i = 0;
    while (str[i] == ' ') {
        i++;
    }
    auto c = str.length() - 1;
    while (c >= 0 && str[c] == ' ') {
        c--;
    }
    int len = c - i + 1;
    return str.substr(i, len);
}

std::string Center(const std::string &str, int width, char fill) noexcept{
    std::string res = str;
    int leftspace = (width - str.length())/2; // had to add this first part b/c of failed tests
    int rightspace = (width - str.length())/2; 
    if ((width - str.length()) % 2 != 0) {
        rightspace = rightspace + 1;
    }

    for (int i = 0; i < leftspace; i++) {
        res = fill + res;
    }
    for (int i = 0; i < rightspace; i++) {
        res = res + fill;
    }
    return res;
}

std::string LJust(const std::string &str, int width, char fill) noexcept{
    std::string res = str;
    int ind = width - str.length();
    for (int i = 0; i < ind; i++) {
        res = res + fill;
    }
    return res;
}

std::string RJust(const std::string &str, int width, char fill) noexcept{
    std::string res = str;
    int ind = width - str.length();
    for (int i = 0; i < ind; i++) {
        res = fill + res;
    }
    return res;
}

std::string Replace(const std::string &str, const std::string &old, const std::string &rep) noexcept{
    std::string res = str;
    auto ind = str.find(old);
    while (ind != std::string::npos) {
        res = res.replace(ind, old.length(), rep);
        ind = res.find(old);
    }
    return res;
}

std::vector< std::string > Split(const std::string &str, const std::string &splt) noexcept{
    std::vector<std::string> v;
    std::string res = str;
    auto ind = str.find(splt);
    while (ind != std::string::npos) {
        v.push_back(res.substr(0, ind));
        res = res.substr(ind + 1);
        ind = res.find(splt);
    }
    v.push_back(res);
    return v;
}

std::string Join(const std::string &str, const std::vector< std::string > &vect) noexcept{ 
    std::string res = vect[0];
    for (size_t i = 1; i < vect.size(); i++) {
        res += str + vect[i];
    }
    return res;
}

std::string ExpandTabs(const std::string &str, int tabsize) noexcept{
    std::string res;
    for (size_t i = 0; i < res.length(); i++) {
        if (str[i] == '\t'){
            res.replace(i, 1, tabsize, ' ');
        }
    }
    return res;
}

int EditDistance(const std::string &left, const std::string &right, bool ignorecase) noexcept{
    // Replace code here
    return 0;
}

};