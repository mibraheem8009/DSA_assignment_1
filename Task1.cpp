#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <cctype>
using namespace std;
int presidence(char c)
{
    if (c == '*' || c == '/')
        return 2;
    else if (c == '-' || c == '+')
        return 1;
    return 0;
}
struct token
{
    string variable;
    int val;
    token(string variable, int val = 0) : variable(variable), val(val) {}
};

bool exists(string var, vector<token> vars)
{
    for (auto &t : vars)
    {
        if (t.variable == var)
            return true;
    }
    return false;
}
bool Tokenization(vector<string>&v,vector <token>&variables)
{
    string input;
    cout << "enter expresion: ";
        getline(cin, input);
        for (int i = 0; i < input.size(); i++)
        {
            char c = input[i];
            if (isspace(c))
                continue;

            if (isdigit(c))
            {
                string num = "";
                num += c;
                while (i + 1 < input.size() && isdigit(input[i + 1]))
                {
                    num += input[++i];
                }
                if (i + 1 < input.size())
                {
                    char next = input[i + 1];
                    if (!(next == '+' || next == '-' || next == '*' || next == '/' ||
                          next == '(' || next == ')' || next == '[' || next == ']' ||
                          next == '{' || next == '}' || isspace(next)))
                    {
                        cout << "invalid input expression\n";
                        return false;
                    }
                }
                v.push_back(num);
            }
            else if (isalpha(c) || c == '_')
            {
                string var = "";
                var += c;
                while (i + 1 < input.length() && (isalnum(input[i + 1]) || input[i + 1] == '_'))
                {
                    var += input[++i];
                }
                v.push_back(var);
                if (!exists(var, variables))
                {
                    variables.push_back(token(var));
                }
            }
            else if (c == '+' || c == '-' || c == '*' || c == '/')
            {
                v.push_back(string(1, c));
            }
            else if (c == '(' || c == '[' || c == '{')
            {
                v.push_back(string(1, c));
            }
            else if (c == ')' || c == ']' || c == '}')
            {
                v.push_back(string(1, c));
            }
            else
            {
                cout << "Invalid character: " << c << endl;
                return false;
            }
        }
       return true;
}
vector<string> inToPost(vector <string>tok)
{
    vector <string > post;
    
}
int main()
{
    int t;
    cout << "enter number of test cases: ";
    cin >> t;
    cin.ignore();
    while (t--)
    {
        vector<string> v;
        vector<token> variables;
     if(Tokenization(v,variables))  
     {

     } 
    }
}