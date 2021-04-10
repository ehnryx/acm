#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
constexpr char nl = '\n';

#define FNAME "joke"

const int N = 55;

string s;
ll mask;
int ans[N];

bool dfs(int idx, int j, int cnt) {
  if (idx == s.size()) {
    return true;
  }

  int cur = 0;
  do {
    cur = cur*10 + s[idx] - '0';
    if (cur > cnt || cur < 1) {
      break;
    }
    ans[j] = cur;
    ++idx;
    if (((1LL<<cur)&(mask)) == 0) {
      mask ^= (1LL<<cur);
      if (dfs(idx, j+1, cnt)) {
        return true;
      }
      mask ^= (1LL<<cur);
    }
  } while (idx < s.size() && cur < 100);
  /*
  for (int q=0; q<j; ++q) {
    cerr << ans[q] << " ";
  }
  cerr << endl;
  */
  return false;
}

int len[N];
int rev[N*2];
void setup() {
  string t;
  for (int i=1; i<N; ++i) {
    t += to_string(i);
    len[i] = t.size();
    rev[t.size()] = i;
  }
}

int main() {
  string __fname = FNAME;
#ifdef ONLINE_JUDGE
  freopen(FNAME ".in", "r", stdin);
  freopen(FNAME ".out", "w", stdout);
#endif
  ios_base::sync_with_stdio(0), cin.tie(0);
  setup();
  cin >> s;
  assert(rev[s.size()]);
  bool res = dfs(0, 0, rev[s.size()]);
  assert(res);
  for (int i=0; i<rev[s.size()]; ++i) {
    cout << ans[i];
    if (i+1 != rev[s.size()]) {
      cout << " ";
    }
  }
  cout << "\n";


  return 0;
}
