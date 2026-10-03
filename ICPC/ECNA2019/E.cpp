#include <bits/stdc++.h>
using namespace std;
using ld = long double;
using ll = long long;

#define BIG_NUM 1000000000

ll cache[500][500][12];

int main() {
    ll r,c,n;
    cin >> r>> c>>n;
    ll elevation_map[500][500];
    ll is_pass[500][500];
    for (int i =0;i < r;i++){
        for (int j = 0; j < c; j++) {
            cin >> elevation_map[i][j];
            is_pass[i][j] = 0;
            if(elevation_map[i][j]==-1){
                elevation_map[i][j]=BIG_NUM;
            }
        }
    }
    
    for (int i = 1; i < r-1;i++){
        for(int j=1;j<c-1;j++){
            if(elevation_map[i][j]<elevation_map[i-1][j] &&elevation_map[i][j]<elevation_map[i+1][j]&&elevation_map[i][j]>elevation_map[i][j-1]&&elevation_map[i][j]>elevation_map[i][j+1]&&elevation_map[i+1][j] != BIG_NUM&&elevation_map[i-1][j]!=BIG_NUM&&elevation_map[i][j+1]!=BIG_NUM&&elevation_map[i][j-1]!=BIG_NUM) {
                is_pass[i][j]=1;
            }
        }
    }

    for (int i = 0; i < r; i++) {
        for (int j =0;j < c;j++){
            for (int k=0;k<n+1;k++){
                cache[i][j][k]=BIG_NUM;
            }
        }
    }

    for (int i = 0; i < r; i++){
        cache[i][0][0] = elevation_map[i][0];
    }

    for (int j = 0; j < c - 1; j++) {
        for (int i =0;i < r; i++) {
            for (int k = 0;k < n+1; k++) {
                int out_pass = k;
                if (is_pass[i][j]) {
                    out_pass++;
                }
                if (i > 0) {
                    cache[i-1][j+1][out_pass] = min(cache[i-1][j+1][out_pass], cache[i][j][k] + elevation_map[i-1][j+1]);
                }
                if (i < r - 1) {
                    cache[i+1][j+1][out_pass] = min(cache[i+1][j+1][out_pass], cache[i][j][k] + elevation_map[i+1][j+1]);
                }
                cache[i][j+1][out_pass] = min(cache[i][j+1][out_pass], cache[i][j][k] + elevation_map[i][j+1]);
            }
        }
    }


    ll mini = BIG_NUM;
    for (int i = 0; i < r; i++) {
        mini = min(mini, cache[i][c-1][n]);
    }

    if (mini < BIG_NUM) {
        cout << mini <<endl;
    } else{
        cout<<"impossible"<<endl;
    }
}
