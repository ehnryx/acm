#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
constexpr char nl = '\n';

#define FNAME "filter"

const int N = 1010;
typedef bitset<N> bs;
int z[256];

void setup() {
  for (int i=0; i<=9; ++i) {
    z[i+'0'] = i;
  }
  for (int i=0; i<6; ++i) {
    z['a'+i] = i+10;
  }
}

bs load(string s, int m) {
  int i=0;
  bs ans;
  for (auto& c : s) {
    int q = z[c];
    for (int j=0; j<4 && i<m; ++j, ++i) {
      if (q&(1<<j)) {
        ans.set(i);
      }
    }
  }
  return ans;
}

int a[110];
bs file[N];
int used[N];
int m, f, n;

int main() {
  string __fname = FNAME;
#ifdef ONLINE_JUDGE
  freopen(FNAME ".in", "r", stdin);
  freopen(FNAME ".out", "w", stdout);
#endif
  ios_base::sync_with_stdio(0), cin.tie(0);
  setup();

  cin >> m >> f;
  for (int i=1; i<=f; ++i) {
    cin >> a[i];
  }
  cin >> n;
  for (int i=1; i<=n; ++i) {
    string s;
    cin >> s;
    file[i] = load(s, m);
  }
  int q;
  cin >> q;
  for (int _i=1; _i<=q; ++_i) {
    int uk;
    cin >> uk;
    bs me;
    for (int j=1; j<=f; ++j) {
      me.set(((ll) uk*a[j])%m);
    }
    for (int j=1; j<=n; ++j) {
      if ((me&file[j]) == me) {
        used[j] = 1;
      }
    }
  }
  set<int> ans;
  for (int i=1; i<=n; ++i) {
    if (used[i]) {
      ans.insert(i-1);
    }
  }
  cout << ans.size();
  for (auto& x : ans) {
    cout << " " << x;
  }
  cout << "\n";


  return 0;
}
