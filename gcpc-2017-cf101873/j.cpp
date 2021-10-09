#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef complex<ld> pt;
typedef vector<pt> pol;

const char nl = '\n';
const int INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-10;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

const int N = 18;
string s[N];

vector<int> id;
int rows[N][1<<N], pos[N][1<<N];
int h, w, n;
vector<int> order;

bool solve(int cur, int bm) {
  if (bm == 0) {
    order.push_back(cur);
    return true;
  }

  int len = s[id[cur]].size();
  for (int j = 0; j < n; j++) {
    if (bm & 1<<j) {
      for (int k = 1; k < len; k++) {
        if (s[id[cur]].substr(k, len-k) == s[id[j]].substr(0, len-k)) {
          cerr << "...." << endl;
          if (pos[j][bm] - len + k + s[id[j]].size() <= w) {
            pos[j][bm | 1<<j] = pos[cur][bm] - len + k + s[id[j]].size();
            rows[j][bm | 1<<j] = rows[cur][bm];
            if (solve(j, bm | 1<<j)) {
              order.push_back(cur);
              return true;
            }
          }
          else if (rows[j][bm] < h) {
            pos[j][bm | 1<<j] = s[id[j]].size();
            rows[j][bm | 1<<j] = rows[cur][bm] + 1;
            if (solve(j, bm | 1<<j)) {
              order.push_back(cur);
              return true;
            }
          }
        }
      }
    }
  }
  return false;
}

//#define FILEIO
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  cout << fixed << setprecision(10);
#ifdef FILEIO
  freopen("test.in", "r", stdin);
  freopen("test.out", "w", stdout);
#endif

  cin >> h >> w >> n;

  bitset<N> bad;
  for (int i = 0; i < n; i++) {
    cin >> s[i];
    if (s[i].size() > w) {
      cout << "impossible" << nl;
      return 0;
    }
  }

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (i != j && s[j].find(s[i]) != -1) {
        bad[i] = true;
      }
    }
    if (!bad[i]) id.push_back(i);
  }

  n = id.size();
  for (int i = 0; i < n; i++) {
    int bm = ((1<<n)-1) ^ 1<<i;
    rows[i][bm] = 1;
    pos[i][bm] = s[id[i]].size();
    if (solve(i, bm)) {
      reverse(order.begin(), order.end());

      int r = 0;
      string ans[N];
      for (int i : order) {
        int len = ans[r].size();
        for (int k = 0; k < len; k++) {
          if (ans[r].substr(k, len-k) == s[id[i]].substr(0, len-k)) {
            for (int j = len-k; j < s[id[i]].size(); j++) {
              ans[r].push_back(s[id[i]][j]);
            }
          }
          else {
            while (ans[r].size() < w) {
              ans[r].push_back('X');
            }
            ans[++r] = s[id[i]];
          }
        }
      }
      while (ans[h-1].size() < w) {
        ans[h-1].push_back('X');
      }

      for (int i = 0; i < h; i++) {
        cout << ans[i] << nl;
      }

      return 0;
    }
  }

  cout << "impossible" << nl;

  return 0;
}
