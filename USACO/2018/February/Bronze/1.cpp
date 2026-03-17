#include <bits/stdc++.h>

int main() {
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);

    std::ifstream fin("teleport.in");
    std::ofstream fout("teleport.out");

    int a, b, x, y;
    fin >> a >> b >> x >> y;
    fout << std::min({
        abs(b-a),
        abs(x-a) + abs(b-y),
        abs(y-a) + abs(b-x)
    }) << std::endl;

    return 0;
}
