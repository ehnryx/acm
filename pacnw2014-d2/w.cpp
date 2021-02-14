#include <bits/stdc++.h>
using namespace std;

constexpr char nl = '\n';

double sqr(double x) {
  return x * x;
}

int main() {
  ios::sync_with_stdio(0); cin.tie(0);

  int T;
  cin >> T;
  for(int tt=1; tt<=T; tt++) {
    cout << "Case " << tt << ":" << nl;

    int n;
    cin >> n;
    unordered_map<string,int> remap;
    vector<int> x(n), y(n), z(n);
    vector dist(n, vector<double>(n));
    for(int i=0; i<n; i++) {
      string s;
      cin >> s >> x[i] >> y[i] >> z[i];
      remap[s] = i;
      for(int j=0; j<i; j++) {
        double d = sqrt(sqr(x[i]-x[j]) + sqr(y[i]-y[j]) + sqr(z[i]-z[j]));
        dist[i][j] = dist[j][i] = d;
      }
    }

    int m;
    cin >> m;
    for(int i=0; i<m; i++) {
      string a, b;
      cin >> a >> b;
      dist[remap[a]][remap[b]] = 0;
    }

    for(int k=0; k<n; k++) {
      for(int i=0; i<n; i++) {
        for(int j=0; j<n; j++) {
          dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
        }
      }
    }

    int q;
    cin >> q;
    while(q--) {
      string a, b;
      cin >> a >> b;
      int ans = round(dist[remap[a]][remap[b]]);
      cout << "The distance from " << a << " to " << b << " is " << ans << " parsecs." << nl;
    }
  }

  return 0;
}
