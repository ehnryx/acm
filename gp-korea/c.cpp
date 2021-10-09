#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using vi = vector<int>;

const char nl = '\n';

const int N = 1e3+1;
vector<ld> path[N];
int len[N];
ld EF[N], P[N];
ld dp[N];

bool cmp(int i, int j) {
  return P[i]*len[i] + (1-P[i])*P[j]*(EF[i]+len[j])
    < P[j]*len[j] + (1-P[j])*P[i]*(EF[j]+len[i]);
}

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(11);

  int n;
  cin >> n;

  vector<int> order;
  for(int i=0; i<n; i++) {
    int k;
    cin >> k;
    len[i] = k;
    for(int j=0; j<k; j++) {
      ld v;
      cin >> v;
      path[i].push_back((ld)v/1000);
    }
    sort(path[i].begin(), path[i].end());

    ld cond = 0;
    ld pass = 1;
    for(int j=0; j<k; j++) {
      cond += pass * (1-path[i][j]) * (j+1);
      pass *= path[i][j];
    }
    cond /= (1-pass);
    EF[i] = cond;
    P[i] = pass;
    order.push_back(i);
  }
  sort(order.begin(), order.end(), cmp);

  reverse(order.begin(), order.end());
  dp[0] = 0;
  for(int i=1; i<=n; i++) {
    int j = order[i-1];
    dp[i] = P[j]*len[j] + (1-P[j])*(EF[j]+dp[i-1]);
  }
  cout << dp[n] << nl;

  return 0;
}
