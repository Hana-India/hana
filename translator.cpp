#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <bits/stdc++.h>
#include <iterator>
#ifdef _WIN32
#include <io.h>
#define access _access_s
#else
#include <unistd.h>
#endif
using namespace std;
class Core
{
public:
    string parser(string);
    string convertIntToString(int);
    string replaceAll(string, const string &, const string &);
};
class Translator
{
public:
    bool doesFileExist(string);
    int countVerbs();
    string *sort(string *);
    bool search(string *, int, int, string);
    string parser(string, string);
    int typeOfSentence(string);
    string ltrim(const string &, string);
    string rtrim(const string &, string);
    string trim(const string &, string);
    string printFormatter(string);
    string convertToString(char *, int);
    string printSpaceParser(string);
    vector<string> split(string &, string &);
};
string Translator::ltrim(const string &s, string WHITESPACE)
{
    size_t start = s.find_first_not_of(WHITESPACE);
    return (start == string::npos) ? "" : s.substr(start);
}
string Translator::rtrim(const string &s, string WHITESPACE)
{
    size_t end = s.find_last_not_of(WHITESPACE);
    return (end == string::npos) ? "" : s.substr(0, end + 1);
}
string Translator::trim(const string &s, string WHITESPACE)
{
    return rtrim(ltrim(s, WHITESPACE), WHITESPACE);
}
vector<string> Translator::split(string &text, string &delims)
{
    vector<string> tokens;
    size_t start = text.find_first_not_of(delims), end = 0;

    while ((end = text.find_first_of(delims, start)) != string::npos)
    {
        tokens.push_back(text.substr(start, end - start));
        start = text.find_first_not_of(delims, end);
    }
    if (start != string::npos)
        tokens.push_back(text.substr(start));

    return tokens;
}
string Translator::convertToString(char *a, int size)
{
    int i;
    string s = "";
    for (i = 0; i < size; i++)
    {
        s = s + a[i];
    }
    return s;
}
string Translator::printFormatter(string str)
{
    string oldString = str;
    string finalstring;
    char oldArray[oldString.length()];
    int i;
    for (i = 0; i < oldString.length(); i++)
    {
        oldArray[i] = oldString[i];
    }
    char newString[1000] = {NULL};
    int oldItr = 0;
    bool first = false;
    int arrayLen = oldString.length();
    for (int i = 0; i < arrayLen; i++)
    {
        if (oldArray[i] == '"')
        {
            first = !first;
            if (first)
            {
                newString[oldItr++] = '<';
                newString[oldItr++] = '<';
                newString[oldItr++] = oldArray[i];
            }
            else
            {
                newString[oldItr++] = oldArray[i];
                newString[oldItr++] = '<';
                newString[oldItr++] = '<';
            }
        }
        else
        {
            newString[oldItr++] = oldArray[i];
        }
    }
    for (int i = 0; i < 1000; i++)
    {
        if (newString[i] == NULL)
        {
            finalstring = Translator::convertToString(newString, i);
            break;
        }
    }
    if (finalstring[finalstring.length() - 1] == '<')
    {
        return finalstring.substr(0, finalstring.length() - 2);
    }
    if (finalstring[0] != '<')
    {
        return "<<" + finalstring;
    }
    return finalstring;
}
string Core::replaceAll(string str, const string &from, const string &to)
{
    size_t start_pos = 0;
    while ((start_pos = str.find(from, start_pos)) != string::npos)
    {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length();
    }
    return str;
}
string Core::convertIntToString(int x)
{
    string str;
    stringstream ss;
    ss << x;
    ss >> str;
    return str;
}
string Core::parser(string line)
{
    string gen_command_intent = line.substr(0, line.find("("));
    int i, j;
    line = line.substr(gen_command_intent.length() + 1, line.length() - 1);
    line = line.substr(0, line.length() - 1);
    vector<string> tokens;
    stringstream check1(line);
    string intermediate;
    while (getline(check1, intermediate, '`'))
    {
        tokens.push_back(intermediate);
    }
    ifstream gen_file(gen_command_intent + ".gen");
    string l, code = "";
    while (getline(gen_file, l))
    {
        //l = l.substr(0, l.length() - 1);
        code += l + "\n";
    }
    for (i = 0; i < tokens.size(); i++)
    {
        code = Core::replaceAll(code, "v" + Core::convertIntToString(i + 1), tokens[i]);
    }
    gen_file.close();
    return code;
}
int Translator::typeOfSentence(string str)
{
    size_t found = str.find("from");
    size_t found_2 = str.find("to ");
    size_t found_3 = str.find("with");
    if (found != string::npos)
        return 3;
    else if (found_2 != string::npos && found == string::npos && found_3 == string::npos)
        return 2;
    else if (found_3 != string::npos)
    {
        return 4;
    }
    return 1;
}
string Translator::parser(string verb, string str)
{
    if (typeOfSentence(str) == 1)
        return verb + "(" + str + "`)";
    else if (typeOfSentence(str) == 2)
        return verb + "(" + str.substr(str.find("to") + 3, str.length()) + "`" + str.substr(0, str.find("to") - 1) + "`)";
    else if (typeOfSentence(str) == 3)
    {
        string midval = str.substr(str.find("from") + 5, str.find("to") - 1);
        midval = midval.substr(0, midval.find(" "));
        return verb + "(" + str.substr(0, str.find("from") - 1) + "`" + midval + "`" + str.substr(str.find("to") + 3, str.length()) + "`)";
    }
    else if (typeOfSentence(str) == 4)
    {
        string x = str.substr(str.find("with") + 5, str.find("in") - 1);
        x = x.substr(0, x.find("in") - 1);
        return verb + "(" + str.substr(str.find("in") + 3, str.length()) + "`" + str.substr(0, str.find(" ")) + "`" + x + "`)";
    }
    return "//Error 404!";
}
bool Translator::search(string *arr, int l, int r, string x)
{
    while (l <= r)
    {
        int m = l + (r - l) / 2;
        if (arr[m] == x)
            return true;
        if (arr[m] < x)
            l = m + 1;
        else
            r = m - 1;
    }
    return false;
}
string *Translator::sort(string *arr)
{
    int i, j;
    string temp;
    int arrSize = sizeof(arr) / sizeof(arr[0]);
    for (i = 0; i < arrSize - 1; i++)
    {
        for (j = 0; j < arrSize - 1 - i; j++)
        {
            if (arr[j].length() > arr[j].length())
            {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
    return arr;
}
int Translator::countVerbs()
{
    ifstream file("verbs.log");
    string line = "";
    int count = 0;
    while (getline(file, line))
    {
        count++;
    }
    file.close();
    return count;
}
bool Translator::doesFileExist(string Filename)
{
    return access(Filename.c_str(), 0) == 0;
}
int main(int argc, char *argv[])
{
    Translator obj;
    string WHITESPACE = " \n\r\t\f\v";
    Core obj1;
    vector<string> literal_token;
    vector<int> literal_reference_token;
    int literal_reference_pointer = 0;
    int literal_pointer = 0;
    string q = "\"", temp1;
    int temporary, startpos;
    string verbs[obj.countVerbs()];
    string line = "";
    ifstream file("verbs.log");
    int i = 0;
    while (getline(file, line))
    {
        line = line.substr(0, line.length() - 1);
        verbs[i] = line;
        i++;
    }
    file.close();
    string *verb_pointer = verbs;
    verb_pointer = obj.sort(verb_pointer);
    string filename = argv[1];
    string outfile = "exec.cpp";
    ofstream outf(outfile);
    line = "";
    ifstream file_2(filename);
    string codeline;
    outf << "#include<iostream>" << endl;
    outf << "#include<string>" << endl;
    outf << "#include<vector>" << endl;
    outf << "#include<fstream>" << endl;
    outf << "#include<bits/stdc++.h>" << endl;
    outf << "using namespace std;" << endl;
    string filereadercode = "inline string readFromFile(string filename){\nifstream file(filename);\nstring line,cont=\"\";\nwhile(getline(file,line)){\ncont+=line+\"\\n\";\n}\nfile.close();\nreturn cont.substr(0,cont.length()-1);\n}";
    string filewritercode = "inline void writeToFile(string filename, string contents){\nofstream file(filename);\nfile<<contents;\nfile.close();\n}";
    string replaceallstring = "inline string replaceAll(string str, const string &from, const string &to){\nsize_t start_pos = 0;\nwhile ((start_pos = str.find(from, start_pos)) != string::npos)\n{\nstr.replace(start_pos, from.length(), to);\nstart_pos += to.length();\n}\nreturn str;\n}\n";
    string findinstring = "inline int findStr(string str1, string str){\nreturn str.find(str1);\n}\n";
    string touppercase = "inline string touppercase(string su){\ntransform(su.begin(), su.end(), su.begin(), ::toupper);\nreturn su;\n}\n";
    string tolowercase = "inline string tolowercase(string su){\ntransform(su.begin(), su.end(), su.begin(), ::tolower);\nreturn su;\n}\n";
    string substring = "inline string substrg(int l,int u, string s){\nreturn s.substr(l,u+1);\n}\n";
    outf << filereadercode << endl;
    outf << filewritercode << endl;
    outf << replaceallstring << endl;
    outf << findinstring << endl;
    outf << touppercase << endl;
    outf << tolowercase << endl;
    outf << substring << endl;
    while (getline(file_2, codeline))
    {
        codeline = obj.trim(codeline, WHITESPACE);
        if (codeline.substr(0, codeline.find(" ")) == "print" && codeline[codeline.length() - 1] == '"')
        {
            codeline += " ";
        }
        vector<string> itms = obj.split(codeline, q);
        for (vector<string>::iterator it = itms.begin() + 1; it != itms.end(); it += 2)
        {
            temp1 = *it;
            literal_token.push_back(temp1);
            temporary = rand();
            literal_reference_token.push_back(temporary);
            codeline = obj1.replaceAll(codeline, temp1, obj1.convertIntToString(temporary));
        }
        //cout << codeline << endl;
        if (codeline.find("list") != string::npos)
        {
            codeline += "(1)";
        }
        codeline = obj1.replaceAll(codeline, "variables", "variable");
        codeline = obj1.replaceAll(codeline, "lists", "list");
        codeline = obj1.replaceAll(codeline, "number list", "vector<int>");
        codeline = obj1.replaceAll(codeline, "text list", "vector<string>");
        codeline = obj1.replaceAll(codeline, "text variable", "string");
        codeline = obj1.replaceAll(codeline, "number variable", "int");
        codeline = obj1.replaceAll(codeline, "else if", "elif");
        codeline = obj1.replaceAll(codeline, "read from", "read");
        codeline = obj1.replaceAll(codeline, "write to", "write");
        codeline = obj1.replaceAll(codeline, "and assign to", "to");
        codeline = obj1.replaceAll(codeline, "'s length", ".length()");
        codeline = obj1.replaceAll(codeline, "first occurence of", "findStr(");
        if (codeline.substr(0, codeline.find(" ")) == "extract")
        {

            string temp123 = codeline.substr(codeline.find("in"), codeline.length());
            codeline = obj1.replaceAll(codeline, " text from", " substrg(");
            codeline = obj1.replaceAll(codeline, " to", ",");
            codeline = obj1.replaceAll(codeline, codeline.substr(codeline.find("in"), codeline.length()), "");
            codeline += temp123;
            codeline = obj1.replaceAll(codeline, " in", ",");
        }
        if (codeline.substr(0, codeline.find(" ")) == "change")
        {
            if (codeline.find("to upper case") != string::npos)
            {
                codeline = obj1.replaceAll(codeline, "change", "changetoupper");
            }
            else if (codeline.find("to lower case") != string::npos)
            {
                codeline = obj1.replaceAll(codeline, "change", "changetolower");
            }
            codeline = obj1.replaceAll(codeline, "to upper case", "");
            codeline = obj1.replaceAll(codeline, "to lower case", "");
        }
        if (codeline.substr(0, codeline.find(" ")) == "find")
        {
            codeline = obj1.replaceAll(codeline, " in ", ",");
            //cout << "found" << endl;
        }
        //codeline = obj1.replaceAll(codeline, "in", ",");

        if (codeline.find("main()") != string::npos)
        {
            if (codeline.find("{") != string::npos)
            {
                outf << "int main() {" << endl;
            }
            else if (codeline.find("{") == string::npos)
            {
                outf << "int main()" << endl;
            }
        }
        if (codeline == "{" || codeline == "}")
        {
            outf << codeline << endl;
        }
        if (codeline == "else")
        {
            outf << "else" << endl;
        }
        else
        {
            string v = codeline.substr(0, codeline.find(" "));
            codeline = codeline.substr(codeline.find(" ") + 1, codeline.length());
            if (v == "print")
            {
                string printcode = obj.printFormatter(codeline);
                for (int k = 0; k < literal_reference_token.size(); k++)
                {
                    printcode = obj1.replaceAll(printcode, obj1.convertIntToString(literal_reference_token[k]), literal_token[k]);
                }
                if (printcode[0] == '<')
                {
                    if (printcode[printcode.length() - 1] != ' ')
                        outf << "cout" << printcode << "<<\"\";" << endl;
                    else
                        outf << "cout" << printcode << "\"\";" << endl;
                }
                else
                {
                    if (printcode[printcode.length() - 1] != ' ')
                        outf << "cout" << printcode << "<<\"\";" << endl;
                    else
                        outf << "cout" << printcode << "\"\";" << endl;
                }
            }
            //const int sizeofverblist = sizeof(verbs) / sizeof(verbs[0]);
            //const bool isVerbValid = obj.search(verb_pointer, 0, sizeofverblist, v);
            //if (isVerbValid == true)
            //{
            string gen_code = obj.parser(v, codeline);
            for (int k = 0; k < literal_reference_token.size(); k++)
            {
                gen_code = obj1.replaceAll(gen_code, obj1.convertIntToString(literal_reference_token[k]), literal_token[k]);
            }
            outf << obj1.parser(gen_code);
            //}
        }
    }
    outf.close();
    file_2.close();
}