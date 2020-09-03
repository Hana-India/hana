#include <iostream>
#include <string>
using namespace std;
inline string replaceAll(string str, const string &from, const string &to)
{
    size_t start_pos = 0;
    while ((start_pos = str.find(from, start_pos)) != string::npos)
    {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length();
    }
    return str;
}
inline string replace(int c, string s, string f, string d)
{
    for (int i = 0; i < c; i++)
    {
        s = s.replace(s.find(f), f.length(), d);
    }
    return s;
}
inline bool is_number(const string &s)
{
    std::string::const_iterator it = s.begin();
    while (it != s.end() && std::isdigit(*it))
        ++it;
    return !s.empty() && it == s.end();
}
inline string replace(string c, string s, string f, string d)
{
    if (c == "all")
    {
        return replaceAll(s, f, d);
    }
    else if (is_number(c) == true)
    {
        stringstream gg(c);
        int x = 0;
        gg >> x;
        for (int i = 0; i < x; i++)
        {
            s = s.replace(s.find(f), f.length(), d);
        }
        return s;
    }
}
inline string substrg(int l, int u, string s)
{
    return s.substr(l, u + 1);
}
inline string tolowercase(string su)
{
    transform(su.begin(), su.end(), su.begin(), ::tolower);
    return su;
}
inline string touppercase(string su)
{
    transform(su.begin(), su.end(), su.begin(), ::toupper);
    return su;
}
inline int findStr(string str1, string str)
{
    return str.find(str1);
}
inline void writeToFile(string filename, string contents)
{
    ofstream file(filename);
    file << contents;
    file.close();
}
inline string readFromFile(string filename)
{
    ifstream file(filename);
    string line, cont = "";
    while (getline(file, line))
    {
        cont += line + "\n";
    }
    file.close();
    return cont.substr(0, cont.length() - 1);
}
