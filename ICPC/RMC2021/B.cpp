#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;

int main() {
    int N, Q;
    cin >> N >> Q;
    vector<pair<int, int>> points;
    int xsum;
    int ysum;
    for (int i = 0; i < N; ++i)
    {
        int x, y;
        cin >> x >> y;
        points.push_back({x, y});
        xsum += x;
        ysum += y;
    }

    // get the above and below for all the possible lines, where line i corresponds to points i and i + 1
    ld xav = xsum / N;
    ld yav = ysum / N;
    vector<int> above_below(points.size(), 0); // 0 is on, 1 is below, 2 is above
    for (int i = 0; i < N; ++i)
    {
        pair<int, int> point1 = points[i];
        pair<int, int> point2 = points[((i + 1) % N)];
        if ((yav - point1.second) * (xav - point2.first) > (yav - point2.second) * (xav - point1.first))
        {
            above_below[i] = 2;
        }
        else if ((yav - point1.second) * (xav - point2.first) < (yav - point2.second) * (xav - point1.first))
        {
            above_below[i] = 1;
        }
    }

    // for each query
    for (int i = 0; i < Q; ++i)
    {
        cin >> x >> y;
        bool didBreak = false;

        // for each line
        for (int i = 0; i < N; ++i)
        {
            pair<int, int> point1 = points[i];
            pair<int, int> point2 = points[((i + 1) % N)];
            int a = point2.first - point1.first;
            int b = point2.second - point1.second;
            int c = -(point1.first) * (point2.first - point1.first) + (point1.second) * (point2.second - point1.second);
            
            // calculate the projection
            dl projection = (a * x + b * y + c) / (sqrt(a * a + b * b));
            bool currPointStatus;

            // above line
            if (projection > 0)
            {
                currPointStatus = true;
            }
            // below line
            else
            {
                currPointStatus = false;
            }

            // check if we are on inside or outside
            if (abs(projection <= 1 / (sqrt(2))))
            {
                // calculate the fraction below the line
                int numerator = (point2.second - point1.second) * x + point2.first * point1.second - point1.first * point2.second;
                int denominator = point2.first - point1.first;
                int g = gcd(numerator, denominator);
                numerator /= g;
                denominator /= g;
                if (!currPointStatus && above_below[i])
                {
                    cout << numerator << "/" << denominator << endl;
                }
                else if (currPointStatus )
            }
            else
            {
                if (currPointStatus && !above_below[i])
                {
                    cout << "0/1" << endl;
                    didBreak = true;
                    break;
                }
                else if (!currPointStatus && above_below[i])
                {
                    cout << "0/1" << endl;
                    didBreak = true;
                    break;
                }
            }
        }

        if (!didBreak)
        {
            cout << "1/1" << endl;
        }
    }
}