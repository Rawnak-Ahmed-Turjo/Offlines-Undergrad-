#include <iostream>
#include <string>
using namespace std;
int dp[100][100];

int isExpression(string s, string p)
{
    int i, j;
    s = " " + s;
    p = " " + p;
    for (i = 0; i < p.length(); i++)
    {
        for (j = 0; j < s.length(); j++)
        {
            if (p[i] == s[j])
            {
                if ((i == 0 && j == 0) || s[j] == p[0])
                {
                    dp[i][j] = 1;
                }
                else
                {
                    dp[i][j] = dp[i - 1][j - 1];
                }
            }
            else if (p[i] == '.')
            {
                if (i > 0 && j > 0)
                    dp[i][j] = dp[i - 1][j - 1];
            }
            else if (p[i] == '*')
            {

                if (dp[i - 2][j])
                    dp[i][j] = dp[i - 2][j];
                else if (j > 0)
                {
                    if ((p[i - 1] == '.' || p[i - 1] == s[j]) && dp[i][j - 1])
                        dp[i][j] = dp[i][j - 1];
                }
            }
            else if (p[i] == '+')
            {
                if (dp[i - 1][j])
                    dp[i][j] = dp[i - 1][j];
                else if (j > 0)
                {
                    if ((p[i - 1] == '.' || p[i - 1] == s[j]) && dp[i][j - 1])
                        dp[i][j] = dp[i][j - 1];
                }
            }
        }
    }
    return dp[i - 1][j - 1];
}
int main()
{
    string s, p;

    getline(cin, s);
    getline(cin, p);
    int x = isExpression(s, p);
    if (x)
        cout << "true\n";
    else
        cout << "false\n";

    return 0;
}
