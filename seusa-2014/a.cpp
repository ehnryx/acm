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

struct Circle {
  int x, y, r, a, b;
  bool contains(const Circle& c) const {
    ld dx = x-c.x;
    ld dy = y-c.y;
    return sqrt(dx*dx+dy*dy)+c.r < r;
  }
};
vector<Circle> circ;

const int N = 2e3+1;
vector<int> adj[N];
int par[N];
bool vis[N];

bool valid(bool& skip, int a, int b, int anc, int num) {
  if (num==0) {
    return true;
  }
  if (a==0 && b==0) {
    return true;
  }
  if (a==0 && b>0) {
    if (abs(anc-num)<=1) {
      skip = (num%2==0);
      return true;
    } else {
      return false;
    }
  }
  if (a==0 && b<0) {
    return num<=1;
  }
  if (a>0 && b==0) {
    if (abs(anc-num)<=1) {
      skip = (num%2==1);
      return true;
    } else {
      return false;
    }
  }
  if (a<0 && b==0) {
    return num<=0;
  }
  if (a>0 && b>0) {
    skip = (anc==num);
    return anc==num;
  }
  if (a<0 && b<0) {
    return num<=0;
  }
  if (a>0 && b<0) {
    if (abs(a)<abs(b)) {
      skip = (num==1);
      return num==1;
    } else if (abs(a)>abs(b)) {
      if (anc%2==1) {
        skip = (anc==num);
        return anc==num;
      } else {
        skip = (anc==num+1);
        return anc==num+1;
      }
    } else {
      skip = (num==1);
      return num%2==1;
    }
  }
  if (a<0 && b>0) {
    if (abs(a)>abs(b)) {
      return num<=0;
    } else if (abs(a)<abs(b)) {
      if (anc%2==0) {
        skip = (anc==num);
        return anc==num;
      } else {
        skip = (anc==num+1);
        return anc==num+1;
      }
    } else {
      return num%2==0;
    }
  }
  assert(false);
}

int value(int a, int b, int x) {
  if (x==0) return 0;
  if (a>=0 && b>=0) return a*(x%2) + (a+b)*(x/2);
  if (a<0 && b>=0) return max(0, (a+b)*(x/2));
  if (a>=0 && b<0) return a + max(0, (a+b)*((x-1)/2));
  if (a<0 && b<0) return 0;
  assert(false);
}

int answer(int cur, int anc=0) {
  int res = value(circ[cur].a, circ[cur].b, anc);
  for (int x : adj[cur]) {
    res += answer(x, anc+1);
  }
  return res;
}

bool solve(int& res, int cur, int anc=0, int take=0) {
  bool skip = false;
  for (int x : adj[cur]) {
    skip |= solve(res, x, anc+1, take+!vis[cur]);
  }
  if (!skip && !vis[cur]) {
    if (valid(skip, circ[cur].a, circ[cur].b, anc, take)) {
      res = min(res, cur);
    }
  }
  return skip;
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

  memset(par, -1, sizeof par);

  int n;
  cin >> n;

  int x, y, r, a, b;
  for (int i=0; i<n; i++) {
    cin >> x >> y >> r >> a >> b;
    circ.push_back({x,y,r,a,b});
  }

  for (int i=0; i<n; i++) {
    int minr = INF;
    for (int j=0; j<n; j++) {
      if (circ[j].contains(circ[i])) {
        if (circ[j].r < minr) {
          par[i] = j;
          minr = circ[j].r;
        }
      }
    }
    if (par[i] != -1) {
      adj[par[i]].push_back(i);
    }
  }

  int ans=0;
  for (int r=0; r<n; r++) {
    if (par[r] == -1) {
      ans += answer(r);
    }
  }
  cout << ans << nl;

  for (int i=0; i<n; i++) {
    int cur = INF;
    for (int r=0; r<n; r++) {
      if (par[r]==-1) {
        solve(cur, r);
      }
    }
    vis[cur] = true;
    cout << cur+1 << " ";
  }
  cout << nl;

  return 0;
}
