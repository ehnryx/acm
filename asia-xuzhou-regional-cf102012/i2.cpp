#pragma GCC optimize("O3")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,avx,mmx,tune=native")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef complex<ld> pt;

const char nl = '\n';
const int INF = 0x3f3f3f3f;

const ll MOD[2] = {1234567891, (ll)1e9+7};
const ll MLT[2] = {(ll)1e9+9, 101};

int n, m, shit;

ll hashv(const vector<char>& v) {
  ll ha[2];
  for (int i=0; i<2; i++) {
    ha[i] = 0;
    for (int j=0; j<n; j++) {
      ha[i] = ha[i]*MLT[i]%MOD[i] + v[j];
    }
  }
  return ha[0]|ha[1]<<31;
}

vector<pii> cmp;
unordered_set<ll> vis;
vector<vector<char>> cur;
vector<char> init;



int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);

  int T;
  cin >> T;
  while (T--) {
    cin >> n >> m >> shit;

    cmp.clear();
    vis.clear();
    cur.clear();
    init.clear();

    for (int i=0; i<m; i++) {
      int a, b;
      cin >> a >> b;
      cmp.emplace_back(a-1,b-1);
    }

    for (int i=1; i<=n; i++) {
      init.push_back(i);
    }
    vis.insert(hashv(init));
    cur.push_back(init);

    for (int i=0; i<n; i++) {
      for (int j=0; j<i; j++) {
        {
          vector<char> it = init;
          for (int k=j; k<i; k++) {
            swap(it[k], it[k+1]);
          }
          ll ha = hashv(it);
          if (!vis.count(ha)) {
            vis.insert(ha);
            cur.push_back(it);
          }
        }
        {
          vector<char> it = init;
          for (int k=i; k>j; k--) {
            swap(it[k], it[k-1]);
          }
          ll ha = hashv(it);
          if (!vis.count(ha)) {
            vis.insert(ha);
            cur.push_back(it);
          }
        }
      }
    }

    //cerr << "init: " << cur.size() << nl; for (int i=0; i<cur.size(); i++) {
      //cerr << i << ": "; for (int j : cur[i]) {
        //cerr << j << ' '; }
      //cerr << nl; }

    for (const pii& idx : cmp) {
      int len = cur.size();
      for (int j=0; j<len; j++) {
        swap(cur[j][idx.first], cur[j][idx.second]);
        ll ha = hashv(cur[j]);
        if (!vis.count(ha)) {
          vis.insert(ha);
          cur.push_back(cur[j]);
        }
        swap(cur[j][idx.first], cur[j][idx.second]);
      }
    }

    cout << cur.size() << nl;
  }

  return 0;
}
