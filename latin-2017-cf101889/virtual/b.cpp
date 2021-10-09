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

const set<int> vow = {'a', 'e', 'i', 'o', 'u'};

//#define FILEIO
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  cout << fixed << setprecision(10);
#ifdef FILEIO
  freopen("test.in", "r", stdin);
  freopen("test.out", "w", stdout);
#endif

  string s; cin >> s;
  bool shit = 0;
  for (char c : s) {
    if (vow.count(c)) {
      shit = 1;
      break;
    }
  }
  if (!shit) {
    puts("1");
    return 0;
  }
  if (!vow.count(s[0])) {
    puts("0");
    return 0;
  }
  vector<int> dumb;
  int cur = 0;
  for (int i = 1; i < s.size(); i++) {
    if (vow.count(s[i])) {
      dumb.push_back(cur);
      cur = 0;
    } else {
      cur++;
    }
  }
  dumb.push_back(cur);
  cout << dumb[(dumb.size()-1)/2]+1 << endl;

  return 0;
}
