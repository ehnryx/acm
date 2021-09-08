#include<bits/stdc++.h>
using namespace std;

int grid[1024][1024];

typedef pair<int,int> pii;

bool solve(int n) {
    map<int,vector<pii>> m;

    int zc = 0;
    for (int i = 0; i < (1<<n); i++) {
        for (int j = 0; j < (1<<n); j++) {
            cin >> grid[i][j];
            if (!grid[i][j]) {
                zc++;
            } else {
                m[grid[i][j]].push_back({i,j});
            }
        }
    }

    bool ok = true;

    if (ok) {
        for (auto& p : m) {
            if (p.second.size() != 3) {
                ok = false;
                goto VELOCIRAPTOR;
            }
            sort(p.second.begin(), p.second.end());
            // xx
            // x.
            bool t1 = (p.second[1].first == p.second[0].first && p.second[1].second == p.second[0].second+1 &&
                       p.second[2].first == p.second[0].first+1 && p.second[2].second == p.second[0].second);
            // xx
            // .x
            bool t2 = (p.second[1].first == p.second[0].first && p.second[1].second == p.second[0].second+1 &&
                       p.second[2].first == p.second[0].first+1 && p.second[2].second == p.second[0].second+1);
            // x.
            // xx
            bool t3 = (p.second[1].first == p.second[0].first+1 && p.second[1].second == p.second[0].second &&
                       p.second[2].first == p.second[0].first+1 && p.second[2].second == p.second[0].second+1);
            // .x
            // xx
            bool t4 = (p.second[1].first == p.second[0].first+1 && p.second[1].second == p.second[0].second-1 &&
                       p.second[2].first == p.second[0].first+1 && p.second[2].second == p.second[0].second);
            if (!(t1 || t2 || t3 || t4)) {
                ok = false;
                goto VELOCIRAPTOR;
            }
        }
    }

VELOCIRAPTOR:
    return (zc == 1) && (m.size() == ((1<<(2*n))-1)/3) && ok;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n;
    while (cin >> n) {
        cout << solve(n) << "\n";
    }

    return 0;
}