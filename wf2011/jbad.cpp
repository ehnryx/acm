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

const int K = 8;
bool dp[N][K];
pyr par[N][K];

void solve() {
  dp[0][0] = 1;
  for (const pyr& p : pyrs) {
    for (int i = N-1; i >= p.sz; i--) {
      for (int j = K-1; j >= 1; j--) {
      //for (int j = 1; j < K; j++) {
        //if (dp[i][j]) continue;
        if (dp[i-p.sz][j-1]) {
          dp[i][j] = 1;
          par[i][j] = p;
        }
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
    int best = INF;
    for (int i = 0; i < K; i++) {
      if (dp[c][i]) {
        best = i;
        break;
      }
    }
    if (best == INF) {
      cout << "impossible\n";
      continue;
    }
    int ci = c, cj = best;
    //cerr << c << " " << ci << " " << cj << endl;
    vector<pyr> sol;
//    set<string> anses;
    while (ci > 0) {
      sol.push_back(par[ci][cj]);
//      if (anses.count(par[ci][cj].to_string())) assert(0);
//      anses.insert(par[ci][cj].to_string());
      ci -= par[ci][cj].sz;
      cj--;
    }
    sort(sol.begin(), sol.end(), [](const pyr& a, const pyr& b) {
      return a.sz == b.sz ? a.type < b.type : a.sz > b.sz;
    });
    for (const pyr& p : sol) {
      cout << p.hgt << p.type << " ";
    }
    cout << nl;
  }

  return 0;
}
