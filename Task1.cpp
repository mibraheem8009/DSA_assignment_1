#include <iostream>
#include <string>
#include <vector>
#include <stack>
using namespace std;
int presidence(char c)
{
    else if (c == '*' || c == '/') return 2;
    else if (c == '-' || c == '+') return 1;
    return 0;
}

int main()
{
    int t;
    cout << "enter number of test cases: ";
    cin >> t;
    while (t--)
    {
        string input;
        vector<string> v;
        vector<string> variables;
        cout << "enter expresion: ";
        getline(cin, input);
        for (int i = 0; i < input.size(); i++)
        {
            chat c = input[i];
            if (isspace(c))
                continue;

            if (isdigit(c))
            {
                string num = "";
                name += c;
                while (i + 1 < input.size() && isdigit(input[i + 1]))
                {
                    num += input[++i];
                }
                //   if(i+1<size()&&isalpha(input[i+1])||input[i+1]!='+'||input[i+1]!='-'||input[i+1]!='*'||input[i+1]!='/'||input[i+1]!='(')
                v.push_back(num);
            }
            else if (isalpha(c)||c=='_')
            {
                string var = "";
                var += c;
                while (i + 1 < input.length() && isalnum(input[i + 1] || c == '_'))
                {
                    var += input[++i];
                }
                v.push_back(var);
                // variables.push_back(var);
            }
            else if (c == '+' || c == '-' || c == '*' || c == '/')
            {
                v.push_back((c));
            }
            else if (c == '(' || c == '[' || c == '{')
            {
                v.push_back((c));
            }
            else if (c == ')' || c == ']' || c == '}')
            {
                v.push_back((c));
            }
            else
            {
                cout << "Invalid character: " << c << endl;
                return -1;
            }
        }
    }
}