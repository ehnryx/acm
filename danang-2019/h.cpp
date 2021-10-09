#include <bits/stdc++.h>
using namespace std;

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

typedef long long ll;
typedef long double ld;
#define nl '\n'

const int N = 6;
int kn[N], km[N];
vector<int> an[N], am[N];
vector<int> bn[N];

vector<int> blocks(int b) {
  vector<int> out;
  int cnt = 0;
  for(int j=0; j<N+1; j++) {
    if(b & 1<<j) {
      cnt++;
    } else if(cnt > 0) {
      out.push_back(cnt);
      cnt = 0;
    }
  }
  return out;
}

int main() {
  ios::sync_with_stdio(0); cin.tie(0);

  int n, m;
  cin >> n >> m;
  for(int i=0; i<n; i++) {
    cin >> kn[i];
    an[i].resize(kn[i]);
    for(int j=0; j<kn[i]; j++) {
      cin >> an[i][j];
    }
  }
  for(int i=0; i<m; i++) {
    cin >> km[i];
    am[i].resize(km[i]);
    for(int j=0; j<km[i]; j++) {
      cin >> am[i][j];
    }
  }

  for(int i=0; i<n; i++) {
    for(int b=0; b<1<<m; b++) {
      if(an[i] == blocks(b)) {
        bn[i].push_back(b);
      }
    }
  }
  for(int i=n; i<N; i++) {
    bn[i].push_back(0);
  }

  int ans = 0;
  for(int a : bn[0])
  for(int b : bn[1])
  for(int c : bn[2])
  for(int d : bn[3])
  for(int e : bn[4])
  for(int f : bn[5]) {
    bool ok = true;
    for(int j=0; j<m; j++) {
      int col = (a>>j & 1)
        | (b>>j & 1) << 1
        | (c>>j & 1) << 2
        | (d>>j & 1) << 3
        | (e>>j & 1) << 4
        | (f>>j & 1) << 5;
      if(am[j] != blocks(col)) {
        ok = false;
        break;
      }
    }
    ans += ok;
  }
  cout << ans << nl;

  return 0;
}
