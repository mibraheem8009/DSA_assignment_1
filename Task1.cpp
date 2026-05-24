#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <cctype>
using namespace std;
bool Operator(string token)
{
    return token == "+" || token == "-" || token == "*" || token == "/";
}

bool leftbracket(string token)
{
    return token == "(" || token == "[" || token == "{";
}

bool rightbracket(string token)
{
    return token == ")" || token == "]" || token == "}";
}
struct Token
{
    string variable;
    int val;
    Token(string variable, int val = 0) : variable(variable), val(val) {}
};

bool exists(string var, vector<Token> vars)
{
    for (auto &t : vars)
    {
        if (t.variable == var)
            return true;
    }
    return false;
}
bool Tokenization(vector<string> &v, vector<Token> &variables)
{
    string input;
    cerr << "enter expresion: ";
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
                if (!(Operator(string(1, next)) || leftbracket(string(1, next)) || rightbracket(string(1, next)) || isspace(next)))
                {
                    cerr << "invalid input expression\n";
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
                variables.push_back(Token(var));
            }
        }
        else if (Operator(string(1, c)))
        {
            v.push_back(string(1, c));
        }
        else if (leftbracket(string(1, c)))
        {
            v.push_back(string(1, c));
        }
        else if (rightbracket(string(1, c)))
        {
            v.push_back(string(1, c));
        }
        else
        {
            cerr << "Invalid character: " << c << endl;
            return false;
        }
    }
    return true;
}
int presidence(char c)
{
    if (c == '*' || c == '/')
        return 2;
    else if (c == '-' || c == '+')
        return 1;
    return 0;
}

string bracketmatch(string right)
{
    if (right == ")")
        return "(";
    if (right == "]")
        return "[";
    if (right == "}")
        return "{";
    return "";
}
bool inToPost(vector<string> infix, vector<string> &post)
{
    stack<string> opStack;

    for (int i = 0; i < infix.size(); i++)
    {
        string token = infix[i];

        if (isdigit(token[0]) || isalpha(token[0]) || token[0] == '_')
        {
            post.push_back(token);
        }
        else if (Operator(token))
        {
            char currentOp = token[0];
            while (!opStack.empty() && Operator(opStack.top()))
            {
                char topOp = opStack.top()[0];
                if (presidence(topOp) >= presidence(currentOp))
                {
                    post.push_back(opStack.top());
                    opStack.pop();
                }
                else
                {
                    break;
                }
            }
            opStack.push(token);
        }
        else if (leftbracket(token))
        {
            opStack.push(token);
        }
        else if (rightbracket(token))
        {
            string expected = bracketmatch(token);
            while (!opStack.empty() && !leftbracket(opStack.top()))
            {
                post.push_back(opStack.top());
                opStack.pop();
            }
            if (!opStack.empty() && leftbracket(opStack.top()))
            {
                if (opStack.top() == expected)
                {
                    opStack.pop();
                }
                else
                {
                    cerr<< "Mismatched parentheses: expected " << expected<< " but found " << opStack.top() << endl;
                    return false;
                }
            }
            else
            {
                cerr << "Unmatched right bracket: " << token << endl;
                return false;
            }
        }
        else
        {
            cerr << "Unknown token: " << token << endl;
            return false;
        }
    }
    while (!opStack.empty())
    {
        if (leftbracket(opStack.top()))
        {
            cerr << "Unmatched left bracket: " << opStack.top() << endl;
            return false;
        }
        post.push_back(opStack.top());
        opStack.pop();
    }

    return true;
}
int main()
{
    int t;
    cerr << "enter number of test cases: ";
    cin >> t;
    cin.ignore();
    while (t--)
    {
        vector<string> v;
        vector<Token> variables;
        vector<string> post;
        if (Tokenization(v, variables))
        {
            if (inToPost(v, post))
            {
            }
        }
    }
}