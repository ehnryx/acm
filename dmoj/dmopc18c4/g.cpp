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

const int N = 1e5+1;
int vals[N];
int ans[3][N];
vector<int> idx[N];

//#define FILEIO
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  cout << fixed << setprecision(10);
#ifdef FILEIO
  freopen("test.in", "r", stdin);
  freopen("test.out", "w", stdout);
#endif

  int n, m;
  cin >> n >> m;

  ll sum = 0;
  for (int i=0; i<m; i++) {
    cin >> vals[i];
    sum += vals[i];
  }

  if (sum != 3*n || m < n) {
    cout << "no" << nl;
    return 0;
  }

  cout << "yes" << nl;
  
  for (int i=0; i<n; i++) {
    for (int j=0; j<vals[i]; j++) {
      idx[i].push_back(i+1);
    }
  }
  for (int i=n; i<m; i++) {
    vals[n-1] += vals[i];
    for (int j=0; j<vals[i]; j++) {
      idx[n-1].push_back(i+1);
    }
  }
  m = n;

  vector<int> one, two, three;
  vector<pii> stuff;
  for (int i=0; i<m; i++) {
    if (vals[i]==1) one.push_back(i);
    else if (vals[i]==2) two.push_back(i);
    else if (vals[i]==3) three.push_back(i);
    else stuff.push_back(pii(vals[i], i));
  }

  // remove threes
  for (int it : three) {
    --m;
    for (int j=0; j<3; j++) {
      ans[j][m] = idx[it][j];
    }
  }

  int ts = two.size();
  int ss = stuff.size();

  int rounds;
  bool bad = false;
  for (rounds = 1; ; ++rounds) {
    memset(ans[1], 0, m*sizeof(ans[1][0]));
    memset(ans[2], 0, m*sizeof(ans[2][0]));
    memset(ans[3], 0, m*sizeof(ans[3][0]));

    // place twos
    for (int i=0; i<ts; i++) {
      for (int j=0; j<2; j++) {
        ans[j+1][m-1-i] = idx[two[i]][j];
      }
    }

    // place other
    shuffle(stuff.begin(), stuff.end(), rng);

    bool rev = false;
    int cur = m;
    int tpos = m-ts;
    int spos = 0;

    bad = false;

    // top edge
    for (; spos < ss && cur-(stuff[spos].first-1) >= 0; spos++) {
      // overwrites a two
      int ipos = 0;
      if (ans[1][cur-(stuff[spos].first-2)]) {
        for (int i=0; i<stuff[spos].first-2; i++) {
          ans[0][--cur] = idx[stuff[spos].second][ipos++];
        }
        --tpos;
        ans[1][tpos] = ans[1][cur];
        ans[2][tpos] = ans[2][cur];
        ans[1][cur] = idx[stuff[spos].second][ipos++];
        ans[2][cur] = idx[stuff[spos].second][ipos++];
      }
      // turn down, no overwrite
      else {
        for (int i=0; i<stuff[spos].first-1; i++) {
          ans[0][--cur] = idx[stuff[spos].second][ipos++];
        }
        ans[1][cur] = idx[stuff[spos].second][ipos++];
        if (cur == 0) { bad = true; break; }
      }
    }
    if (spos == ss) break;
    if (bad) continue;

    // can't place left end
    if (cur - (stuff[spos].first-1) == 0) {
      bad = true;
    }
    // reverse at left end
    else if (cur - (stuff[spos].first-2) == 0) {
      int ipos = 0;
      for (int i=cur-1; i>=0; i--) {
        ans[0][i] = idx[stuff[spos].second][ipos++];
      }
      ans[1][0] = idx[stuff[spos].second][ipos++];
      ans[2][0] = idx[stuff[spos].second][ipos++];
      cur = 1;
      rev = true;
    }
    // place left end normally
    else {
      int ipos = 0;
      for (int i=cur-1; i>=0; i--) {
        ans[0][i] = idx[stuff[spos].second][ipos++];
      }
      ans[1][0] = idx[stuff[spos].second][ipos++];
      cur = stuff[spos].first - (cur+2);
      for (int i=0; i<cur; i++) {
        if (ans[2][i]) { bad = true; break; }
        ans[2][i] = idx[stuff[spos].second][ipos++];
      }
      if (!ans[1][cur]) {
        ans[1][cur] = idx[stuff[spos].second][ipos++];
      } else if (!ans[2][cur]) {
        ans[2][cur++] = idx[stuff[spos].second][ipos++];
        rev = true;
      } else {
        bad = true;
      }
    }
    ++spos;
    if (bad) continue;

    // bottom layer
    for (; spos < ss; spos++) {
      // non-reversed
      int ipos = 0;
      if (!rev) {
        for (int i=0; i<stuff[spos].first-1; i++) {
          if (ans[2][cur]) { bad = true; break; }
          ans[2][cur++] = idx[stuff[spos].second][ipos++];
        }
        if (bad) break;
        if (!ans[1][cur]) {
          ans[1][cur] = idx[stuff[spos].second][ipos++];
          rev = false;
        } else if (ans[2][cur]) {
          bad = true; break;
        } else {
          ans[2][cur++] = idx[stuff[spos].second][ipos++];
          rev = true;
        }
      }

      // reversed
      else {
        int nxt = cur + stuff[spos].first-2;
        if (ans[1][cur]) {
          nxt++;
        } else {
          ans[1][cur] = idx[stuff[spos].second][ipos++];
        }
        while (cur < nxt) {
          if (ans[2][cur]) { bad = true; break; }
          ans[2][cur++] = idx[stuff[spos].second][ipos++];
        }
        if (bad) break;
        if (!ans[1][cur]) {
          ans[1][cur] = idx[stuff[spos].second][ipos++];
          rev = false;
        } else if (ans[2][cur]) {
          bad = true; break;
        } else {
          ans[2][cur++] = idx[stuff[spos].second][ipos++];
          rev = true;
        }
      }
    }

    if (bad) continue;

    break;
  }

  //cerr << rounds << " rounds" << nl;

  int opos = 0;
  for (int i=0; i<3; i++) {
    for (int j=0; j<n; j++) {
      if (ans[i][j]) cout << ans[i][j] << ' ';
      else cout << idx[one[opos++]][0] << ' ';
    }
    cout << nl;
  }

  assert(!bad);

  return 0;
}
