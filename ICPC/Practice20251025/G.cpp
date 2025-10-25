#include <bits/stdc++.h>
using namespace std;

long long op(long long a, long long b, string op_letter) {
    if (op_letter == "+")
    {
        return a + b;
    }
    else
    {
        return a * b;
    }
}

void solve() {
    string x;
    string y;
    string z;
    string symbol;
    string trash;

    cin >> x >> symbol >> y >> trash >> z;

    long long back_index = 1;
    long long xlen = x.length();
    long long ylen = y.length();
    long long zlen = z.length();
    long long min_length = min(min(xlen, ylen), zlen);
    long long max_length = max(max(xlen, ylen), zlen);

    // while (back_index <= max_length)
    // {
    //     if (back_index > xlen && back_index > ylen)
    //     {
    //         break;
    //     }
    //     else if (back_index > xlen)
    //     {
    //         break;
    //     }
    //     else if (back_index > ylen)
    //     {
    //         break;
    //     }
    //     else
    //     {
    //         if ((op(stoll(x.substr(xlen - back_index, back_index)), stoll(y.substr(ylen - back_index, back_index)), symbol) - stoll(z))
    //         % (long long) pow(10.0, (double) back_index) != 0)
    //         {
    //             break;
    //         }
    //     }
    //     ++back_index;
    // }

    // --back_index;
    // string xend = x.substr(xlen - back_index, back_index);
    // string yend = y.substr(ylen - back_index, back_index);
    // string zend = z.substr(zlen - back_index, back_index);

    // // for x, y
    // for (int i = 0; i <= xlen - back_index; ++i)
    // {
    //     for (int j = 0; j <= ylen - back_index; ++j)
    //     {
    //         string xtemp = y.substr(0, j) + x.substr(i, xlen - back_index - i) + xend;
    //         string ytemp = x.substr(0, i) + y.substr(j, ylen - back_index - j) + yend;
    //         if (op(stoll(xtemp), stoll(ytemp), symbol) == stoll(z))
    //         {
    //             cout << xtemp << " " << symbol << " " << ytemp << " = " << z;
    //             return;
    //         }
    //     }
    // }

    // // for x, z
    // for (int i = 0; i <= xlen - back_index; ++i)
    // {
    //     for (int j = 0; j <= zlen - back_index; ++j)
    //     {
    //         string xtemp = z.substr(0, j) + x.substr(i, xlen - back_index - i) + xend;
    //         string ztemp = x.substr(0, i) + z.substr(j, zlen - back_index - j) + zend;
    //         if (op(stoll(xtemp), stoll(y), symbol) == stoll(ztemp))
    //         {
    //             cout << xtemp << " " << symbol << " " << y << " = " << ztemp;
    //             return;
    //         }
    //     }
    // }

    // // for y, z
    // for (int i = 0; i <= ylen - back_index; ++i)
    // {
    //     for (int j = 0; j <= zlen - back_index; ++j)
    //     {
    //         string ytemp = z.substr(0, j) + y.substr(i, ylen - back_index - i) + yend;
    //         string ztemp = y.substr(0, i) + z.substr(j, zlen - back_index - j) + zend;
    //         if (op(stoll(x), stoll(ytemp), symbol) == stoll(ztemp))
    //         {
    //             cout << x << " " << symbol << " " << ytemp << " = " << ztemp;
    //             return;
    //         }
    //     }
    // }



    // for x, y
    for (int i = 0; i <= xlen; ++i)
    {
        for (int j = 0; j <= ylen; ++j)
        {
            string xtemp = y.substr(0, j) + x.substr(i, xlen - i);
            string ytemp = x.substr(0, i) + y.substr(j, ylen - j);
            if (op(stoll(xtemp), stoll(ytemp), symbol) == stoll(z))
            {
                cout << xtemp << " " << symbol << " " << ytemp << " = " << z;
                return;
            }
        }
    }

    // for x, z
    for (int i = 0; i <= xlen; ++i)
    {
        for (int j = 0; j <= zlen; ++j)
        {
            string xtemp = z.substr(0, j) + x.substr(i, xlen - i);
            string ztemp = x.substr(0, i) + z.substr(j, zlen - j);
            if (op(stoll(xtemp), stoll(y), symbol) == stoll(ztemp))
            {
                cout << xtemp << " " << symbol << " " << y << " = " << ztemp;
                return;
            }
        }
    }

    // for y, z
    for (int i = 0; i <= ylen; ++i)
    {
        for (int j = 0; j <= zlen; ++j)
        {
            string ytemp = z.substr(0, j) + y.substr(i, ylen - i);
            string ztemp = y.substr(0, i) + z.substr(j, zlen - j);
            if (op(stoll(x), stoll(ytemp), symbol) == stoll(ztemp))
            {
                cout << x << " " << symbol << " " << ytemp << " = " << ztemp;
                return;
            }
        }
    }
}

int main() {
    solve();
    return 0;
}