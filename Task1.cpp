#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <cctype>
#include <map>
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
    // int val;
    // Token(string variable, int val = 0) : variable(variable), val(val) {}
    Token(string variable) : variable(variable) {}
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
void Tokenization(vector<string> &v, vector<Token> &variables)
{
    string input;
    // cerr << "enter expresion: ";
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
                    exit(1);
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
            exit(1);
        }
    }
    // return true;
}
int presidence(string c)
{
    if (c == "*" || c == "/")
        return 2;
    else if (c == "-" || c == "+")
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
void inToPost(vector<string> infix, vector<string> &post)
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
            while (!opStack.empty() && Operator(opStack.top()))
            {
                if (presidence(opStack.top()) >= presidence(token))
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
                    cerr << "Mismatched parentheses: expected " << expected << " but found " << opStack.top() << endl;
                    exit(1);
                }
            }
            else
            {
                cerr << "Unmatched right bracket: " << token << endl;
                exit(1);
            }
        }
        else
        {
            cerr << "Unknown token: " << token << endl;
            exit(1);
        }
    }
    while (!opStack.empty())
    {
        if (leftbracket(opStack.top()))
        {
            cerr << "Unmatched left bracket: " << opStack.top() << endl;
            exit(1);
        }
        post.push_back(opStack.top());
        opStack.pop();
    }

    // return true;
}
void variableInput(vector<Token> input, map<string, int> &varMap)
{
    for (int i = 0; i < input.size(); i++)
    {
        int val;
        cerr << "Enter val for " << input[i].variable << ": ";
        while (!(cin >> val))
        {
            cerr << "Error non integer input expected integer ";
            exit(2);
        }
        varMap[input[i].variable] = val;
    }
}
int postToEval(vector<string> post, map<string, int> varmap)
{
    stack<int> st;
    for (int i = 0; i < post.size(); i++)
    {
        string token = post[i];

        if (isdigit(token[0]))
        {
            st.push(stoi(token));
        }
        else if (isalpha(token[0]) || token[0] == '_')
        {
            st.push(varmap[token]);
        }
        else if (Operator(token))
        {
            if (st.size() < 2)
            {
                cerr << "insufficient operands" << endl;
                exit(3);
            }
            int b = st.top();
            st.pop();
            int a = st.top();
            st.pop();
            int result;
            if (token == "+")
                result = a + b;
            else if (token == "-")
                result = a - b;
            else if (token == "*")
                result = a * b;
            else if (token == "/")
            {
                if (b == 0)
                {
                    cerr << "error division by zero" << endl;
                    exit(2);
                }
                result = a / b;
            }
            else
            {
                cerr << " unknown operator" << endl;
                exit(3);
            }
            st.push(result);
        }
        else
        {
            cerr << "invalid token in postfix" << endl;
            exit(3);
        }
    }

    if (st.size() != 1)
    {
        cerr << "invalid expression" << endl;
        exit(3);
    }
    return st.top();
}
int main()
{

    vector<string> v;
    vector<Token> variables;
    vector<string> post;
    map<string, int> varmap;
    Tokenization(v, variables);

    inToPost(v, post);
    variableInput(variables, varmap);
    for (int i = 0; i < post.size(); i++)
    {
        if (i != 0)
            cout << " ";
        cout << post[i];
    }
    cout << endl;
    cout << postToEval(post, varmap) << endl;

    exit(0);
}