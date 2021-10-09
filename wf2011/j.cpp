#include <bits/stdc++.h>
using namespace std;

#define nl '\n'

typedef long long ll;
typedef long double ld;
typedef complex<ld> pt;
typedef pair<int,int> pii;
const int N = 1e6+1;
const int INF = 0x3f3f3f3f;

struct pyr {
  int sz;
  int hgt;
  char type;
  string to_string() const {
    return std::to_string(hgt) + type;
  }
  bool operator<(const pyr& o) const {
    //if (sz == o.sz) cerr << to_string() << " " << o.to_string() << nl;
    return sz == o.sz ? type > o.type : sz < o.sz;
  }
};

vector<pyr> pyrs;
void pre() {
  // high
  int cur = 1;
  for (int i = 2; cur < N; i++) {
    cur += i*i;
    if (cur >= N) break;
    pyrs.push_back(pyr{cur, i, 'H'});
  }
  // odd lo
  cur = 1;
  for (int i = 3; cur < N; i += 2) {
    cur += i*i;
    if (cur >= N) break;
    pyrs.push_back(pyr{cur, i, 'L'});
  }
  // even lo
  cur = 2*2;
  for (int i = 4; cur < N; i += 2) {
    cur += i*i;
    if (cur >= N) break;
    pyrs.push_back(pyr{cur, i, 'L'});
  }
  sort(pyrs.begin(), pyrs.end());
}

int dp[N];
vector<int> sol[N];

void solve() {
  memset(dp, INF, sizeof dp);
  dp[0] = 0;
  for (int k = 0; k < pyrs.size(); k++) {
    const pyr& p = pyrs[k];
    for (int i = N-1; i >= p.sz; i--) {
      if (dp[i] >= dp[i-p.sz] + 1) {
        //dp[i][j] = 1;
        sol[i] = sol[i-p.sz];
        sol[i].push_back(k);
        dp[i] = dp[i-p.sz] + 1;
      }
    }
  }
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);

  int c;
  pre();
  solve();
  int tt = 1;
  while (cin >> c) {
    if (!c) break;
    cout << "Case " << tt++ << ": ";
    if (dp[c] == INF) {
      cout << "impossible\n";
      continue;
    }
    sort(sol[c].begin(), sol[c].end(), [](const int& a, const int& b) {
      return pyrs[a].sz > pyrs[b].sz;
    });
    for (int i : sol[c]) {
      const pyr& p = pyrs[i];
      cout << p.hgt << p.type << " ";
    }
    cout << nl;
  }

  return 0;
}
