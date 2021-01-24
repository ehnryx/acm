#include <bits/stdc++.h>
using namespace std;

constexpr char nl = '\n';

using ll = long long;

void FST(vector<ll>& a, bool inv = false) {
  for (int n = a.size(), step = 1; step < n; step *= 2) {
    for (int i=0; i<n; i += 2 * step) for (int j=i; j<i+step; j++) {
      ll &u = a[j], &v = a[j + step]; tie(u, v) =
        // inv ? pair(v-u, u) : pair(v, u+v); // AND /// include-line
        // inv ? pair(v, u-v) : pair(u+v, u); // OR /// include-line
        pair(u + v, u - v);                // XOR /// include-line
    }
  }
  if (inv) for (auto& x : a) x /= a.size(); // XOR only /// include-line
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);

  int n, m;
  cin >> n >> m;
  vector<int> v;
  for(int i=0; i<n; i++) {
    string s;
    cin >> s;
    v.push_back(stoi(s, 0, 2));
  }
  sort(v.begin(), v.end());
  v.resize(unique(v.begin(), v.end()) - v.begin());
  n = v.size();

  vector<vector<int>> other(m+1);
  for(int bm=0; bm<1<<m; bm++) {
    for(int j=0; j<=__builtin_popcount(bm); j++) {
      other[j].push_back(bm);
    }
  }

  vector<ll> orig(1<<m);
  for(int it : v) {
    orig[it] = 1;
  }
  FST(orig);

  for(int k=m; k>=0; k--) {
    vector<ll> goal(1<<m);
    for(int it : other[k]) {
      goal[it] = 1;
    }
    FST(goal);
    vector<ll> res(1<<m);
    transform(orig.begin(), orig.end(), goal.begin(), res.begin(), multiplies<ll>());
    FST(res, true);
    for(int i=0; i<1<<m; i++) {
      if(res[i] < n) continue;
      string ans;
      for(int j=0; j<m; j++) {
        ans.push_back((i>>j & 1) + '0');
      }
      reverse(ans.begin(), ans.end());
      cout << ans << nl;
      return 0;
    }
  }
  assert(false);

  return 0;
}
