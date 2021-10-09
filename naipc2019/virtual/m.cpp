#include <bits/stdc++.h>
using namespace std;

#define nl '\n'
typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
const int INF = 0x3f3f3f3f;
const int N = (1 << 16), K = 16, MOD = 1e9+7;

int n, m;
int p[N];
bool same[2*N];
bool allsame[2*N];
ll dp[2*N][K];

ll solve(int i, int bit) {
  if (bit < 0) return allsame[i];
  if (dp[i][bit] != -1) return dp[i][bit];
  if (same[i]) {
    //puts("!");
    //cerr << i << " " << bit << " -> " << 2*solve(i, bit-1) << nl;
    //assert(solve(2*i, bit-1) == solve(2*i+1, bit-1));
    return dp[i][bit] = (2*solve(2*i, bit-1)) % MOD;
  }
  return dp[i][bit] = (solve(2*i, bit-1) * solve(2*i+1, bit-1) % MOD) % MOD;
}

void pre(int i, int l, int r) {
  if (l == r) {
    same[i] = allsame[i] = 1;
    return;
  }
  allsame[i] = 1;
  for (int j = l; j <= r; j++) {
    if (p[j] != p[l]) {
      allsame[i] = 0;
      break;
    }
  }
  int mid = (l+r)/2;
  bool alleq = 1;
  unordered_set<int> s;
  for (int j = l; j <= mid; j++) {
    if (p[j] != p[mid+1+(j-l)]) {
      alleq = 0;
    }
    s.insert(p[j]);
  }
  if (!alleq) {
    for (int j = mid+1; j <= r; j++) {
      if (s.count(p[j])) {
        //cerr << "!!! " << i << " " << l << " " << r << nl;
        puts("0");
        exit(0);
      }
    }
  }
  same[i] = alleq;
  pre(2*i, l, mid);
  pre(2*i+1, mid+1, r);
}

void out(int i, int l, int r) {
  cerr << "[" << l << ", " << r << "]\n";
  cerr << same[i] << " " << allsame[i] << nl;
  for (int j = 0; j < m; j++) {
    cerr << dp[i][j] << " ";
  }
  cerr << nl;
  if (l == r) return;
  int mid = (l+r)/2;
  out(2*i, l, mid);
  out(2*i+1, mid+1, r);
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);

  cin >> m >> n;
  for (int i = 0; i < (1 << m); i++) {
    cin >> p[i];
  }
  pre(1, 0, (1 << m) - 1);
  memset(dp, -1, sizeof dp);
  cout << solve(1, m-1) << nl;
  //out(1, 0, (1 << m) - 1);

  return 0;
}
