#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <bits/stdc++.h>
#include <iterator>
#ifdef _WIN32
#include <io.h>
#define access _access
#else
#include <unistd.h>
#endif
using namespace std;
class Core
{
public:
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
    int template_counter = 0;
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
    ofstream outf(outfile.c_str());
    line = "";
    ifstream file_2(filename.c_str());
    string codeline;
    outf << "#include<iostream>" << endl;
    outf << "#include<string>" << endl;
    outf << "#include<vector>" << endl;
    outf << "#include<fstream>" << endl;
    outf << "#include<sstream>" << endl;
    outf << "#include<iterator>" << endl;
    outf << "#include<chrono>" << endl;
    outf << "#include<bits/stdc++.h>" << endl;
    outf << "#include<thread>" << endl;
    outf << "#include \"hanalibs.h\"" << endl;
    outf << "using namespace std;" << endl;
    while (getline(file_2, codeline))
    {
        codeline = obj.trim(codeline, WHITESPACE);
        if (codeline.substr(0, codeline.find(" ")) == "print")
        {
            if (codeline[codeline.length() - 1] == '"')
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
        codeline = obj1.replaceAll(codeline, "write", "wread");
        codeline = obj1.replaceAll(codeline, "start new thread", "thread");
        codeline = obj1.replaceAll(codeline, "sleep for", "sleepfor");
        codeline = obj1.replaceAll(codeline, "variables", "variable");
        codeline = obj1.replaceAll(codeline, "lists", "list");
        codeline = obj1.replaceAll(codeline, "text function", "function string");
        codeline = obj1.replaceAll(codeline, "number function", "function int");
        codeline = obj1.replaceAll(codeline, "instances", "instance");
        codeline = obj1.replaceAll(codeline, "number list", "vector<int>");
        codeline = obj1.replaceAll(codeline, "text list", "vector<string>");
        codeline = obj1.replaceAll(codeline, "text variable", "string");
        codeline = obj1.replaceAll(codeline, "number variable", "int");
        codeline = obj1.replaceAll(codeline, "else if", "elif");
        codeline = obj1.replaceAll(codeline, "and assign to", "to");
        codeline = obj1.replaceAll(codeline, "'s length", ".length()");
        if (codeline.substr(0, codeline.find(" ")) == "thread")
        {
            string arg_vars = codeline.substr(codeline.find("(") + 1, codeline.find(")"));
            string func_name = codeline.substr(codeline.find("with") + 4, codeline.find("("));
            func_name = func_name.substr(0, func_name.find("("));
            if (arg_vars == ")")
            {
                codeline = "thread " + codeline.substr(7, codeline.find("with") - 8) + "(" + func_name + ");";
            }
            else
            {
                codeline = "thread " + codeline.substr(7, codeline.find("with") - 8) + "(" + func_name + "," + arg_vars + ";";
            }

            outf << codeline << endl;
        }
        if (codeline.substr(0, codeline.find(" ")) == "function")
        {
            string arg_vars = codeline.substr(codeline.find("(") + 1, codeline.find(")"));
            if (arg_vars != ")")
            {
                string ending = codeline.substr(codeline.find(")") + 1, codeline.length());
                codeline = codeline.substr(codeline.find(" "), codeline.find(")"));

                outf << "template <";
                vector<string> tokens;
                stringstream check1(arg_vars);
                string intermediate;
                while (getline(check1, intermediate, ','))
                {
                    tokens.push_back(intermediate);
                }
                for (int ij = 0; ij < tokens.size() - 1; ij++)
                {
                    outf << "typename T" << obj1.convertIntToString(template_counter) << ",";
                    tokens[ij] = "T" + obj1.convertIntToString(template_counter) + " " + tokens[ij];
                    template_counter++;
                }
                outf << "typename T" << obj1.convertIntToString(template_counter) << ">" << endl;
                tokens[tokens.size() - 1] = "T" + obj1.convertIntToString(template_counter) + " " + tokens[tokens.size() - 1];
                arg_vars = "";
                for (int ij = 0; ij < tokens.size() - 1; ij++)
                {
                    arg_vars += tokens[ij] + ",";
                }
                arg_vars += tokens[tokens.size() - 1];
                outf << "inline " << codeline.substr(codeline.find(" ") + 1, codeline.find("(") + 1) << arg_vars << ending << endl;
            }
            else
            {
                outf << "inline" << codeline.substr(codeline.find("function") + 8, codeline.length()) << endl;
            }
        }
        if (codeline.find("change") != string::npos && codeline.find("to upper case") != string::npos)
        {
            codeline = obj1.replaceAll(codeline, "change", "changetoupper");
        }
        if (codeline.find("change") != string::npos && codeline.find("to lower case") != string::npos)
        {
            codeline = obj1.replaceAll(codeline, "change", "changetolower");
        }
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
            //cout << codeline << endl;
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
            else if (v != "function" && v != "thread")
            {
                //cout << codeline << endl;
                //const int sizeofverblist = sizeof(verbs) / sizeof(verbs[0]);
                //const bool isVerbValid = obj.search(verb_pointer, 0, sizeofverblist, v);
                //if (isVerbValid == true)
                //{
                vector<string> tokens;
                stringstream check1(codeline);
                string intermediate;
                while (getline(check1, intermediate, ' '))
                {
                    tokens.push_back(intermediate);
                }
                //cout << v << endl;4
                string ffn="lib/"+v + ".gen";
                ifstream gen_file(ffn.c_str());
                string l, tok1, code123 = "";
                int counter_tok = 1;
                while (getline(gen_file, l))
                {
                    code123 += l + "\n";
                }
                for (int ik = 0; ik < tokens.size(); ik++)
                {
                    //cout << tokens[ik] << "-->";
                    tok1 = "v" + obj1.convertIntToString(ik + 1);
                    //cout << tok1 << endl;
                    code123 = obj1.replaceAll(code123, tok1, tokens[ik]);
                }
                for (int k = 0; k < literal_reference_token.size(); k++)
                {
                    code123 = obj1.replaceAll(code123, obj1.convertIntToString(literal_reference_token[k]), literal_token[k]);
                }
                outf << code123;
                //}
                gen_file.close();
            }
        }
    }
    outf.close();
    file_2.close();
}
