#include <bits/stdc++.h>
using namespace std;

#define double long double // Offers higher precision for tight LP constraints
const double eps = 1e-9;
typedef vector<double> vd;
typedef vector<vd> vvd;

struct Simplex {
    int rows, cols;
    vvd tableau;
    vector<int> basis;

    // c: objective coefficients, A: constraints matrix, b: RHS values
    Simplex(const vd& c, const vvd& A, const vd& b) {
        int m = b.size();
        int n = c.size();
        rows = m + 1;
        cols = n + m + 1;
        
        tableau.assign(rows, vd(cols, 0.0));
        basis.assign(m, 0);

        // Build standard maximization tableau
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                tableau[i][j] = A[i][j];
            }
            tableau[i][n + i] = 1.0;      // slack variable for constraint i
            tableau[i][cols - 1] = b[i];
            basis[i] = n + i;             // slacks form the initial basis
        }

        // Objective row stores -c so that tableau[rows-1][cols-1] ends up as max Z
        for (int j = 0; j < n; ++j) {
            tableau[rows - 1][j] = -c[j];
        }
    }

    // Performs one pivot; returns false when optimal (or unbounded)
    bool pivot() {
        // Entering variable: most negative coefficient in the objective row
        int pivot_col = -1;
        double most_neg = -eps;
        for (int j = 0; j < cols - 1; ++j) {
            if (tableau[rows - 1][j] < most_neg) {
                most_neg = tableau[rows - 1][j];
                pivot_col = j;
            }
        }
        if (pivot_col == -1) return false; // Optimal: no improving direction

        // Leaving variable: minimum ratio test
        int pivot_row = -1;
        double min_ratio = -1;
        for (int i = 0; i < rows - 1; ++i) {
            if (tableau[i][pivot_col] > eps) {
                double ratio = tableau[i][cols - 1] / tableau[i][pivot_col];
                if (min_ratio < 0 || ratio < min_ratio) {
                    min_ratio = ratio;
                    pivot_row = i;
                }
            }
        }
        if (pivot_row == -1) return false; // Unbounded problem state

        // Gaussian Elimination step
        double pivot_val = tableau[pivot_row][pivot_col];
        for (int j = 0; j < cols; ++j) {
            tableau[pivot_row][j] /= pivot_val;
        }
        for (int i = 0; i < rows; ++i) {
            if (i != pivot_row && abs(tableau[i][pivot_col]) > eps) {
                double factor = tableau[i][pivot_col];
                for (int j = 0; j < cols; ++j) {
                    tableau[i][j] -= factor * tableau[pivot_row][j];
                }
            }
        }

        basis[pivot_row] = pivot_col;
        return true;
    }

    // solution array will store optimal variable coordinates
    double solve(vd& solution) {
        while (pivot());

        solution.assign(cols - rows, 0.0);
        for (int i = 0; i < rows - 1; ++i) {
            if (basis[i] < (int)solution.size()) {
                solution[basis[i]] = tableau[i][cols - 1];
            }
        }
        return tableau[rows - 1][cols - 1];
    }
};

void solve_problem() {
    // // Problem parameters: Z = 3x1 + 5x2
    // vd c = {3.0, 5.0};
    // vvd A = {
    //     {1.0, 0.0},
    //     {0.0, 2.0},
    //     {3.0, 2.0}
    // };
    // vd b = {4.0, 12.0, 18.0};

    // Simplex solver(c, A, b);
    // vd x;
    // double max_z = solver.solve(x);

    // cout << fixed << setprecision(6);
    // cout << "Optimal Decision Variables:\n";
    // for (size_t i = 0; i < x.size(); ++i) {
    //     cout << "x" << i + 1 << " = " << x[i] << "\n";
    // }
    // cout << "Maximum Value (Z): " << max_z << "\n";

    int n, m;
    cin >> n >> m;
    vd b(n);
    for (int i = 0; i < n; ++i) cin >> b[i];
    vd c(m);
    vvd A(n, vd(m));
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> A[j][i];
            A[j][i] /= 100.0;
        }
        cin >> c[i];
    }

    Simplex solver(c, A, b);
    vd x(n);
    double max_z = solver.solve(x);
    cout << fixed << setprecision(2) << max_z << endl;
}

int main() {
    // Fast I/O optimized for competitive programming platforms
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int test_cases = 1;
    // cin >> test_cases; // Uncomment if problem uses multiple query states
    while (test_cases--) {
        solve_problem();
    }
    return 0;
}
