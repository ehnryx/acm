#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef complex<ld> pt;
typedef vector<pt> pol;

const char nl = '\n';
const ll INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-10;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());



int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  cout << fixed << setprecision(10);

  string s;
  getline(cin, s);

  vector<int> line;
  int minlen = 0;
  while (getline(cin, s)) {
    istringstream ss(s);
    while (ss >> s) {
      line.push_back(s.size());
      minlen = max(minlen, (int)s.size());
    }
  }
  int n = line.size();

  int river[2][2500*81+7];

  int length = -1;
  int ans = 0;
  for (int len = minlen; len < n * 81; len++) {
    int id = 0;
    int res = 0;
    int lines = 1;

    int curlen = line[0];
    for (int i = 0; i < 2; i++) {
      memset(river[i], 0, (len+2)*sizeof(river[i][0]));
    }
    for (int i = 1; i < n; i++) {
      if (curlen + 1 + line[i] <= len) {
        int maxlen = 0;
        for (int i = curlen-1; i <= curlen+1; i++) {
          maxlen = max(maxlen, river[id][i]);
        }
        river[id^1][curlen] = maxlen + 1;
        res = max(res, maxlen + 1);
        curlen += 1 + line[i];
      } else {
        memset(river[id], 0, (len+2)*sizeof(river[id][0]));
        id ^= 1;

        curlen = line[i];
        lines++;
      }
    }
    if (lines <= ans) break;

    if (res > ans) {
      ans = res;
      length = len;
    }
  }

  cout << length << " " << ans << nl;

  return 0;
}
