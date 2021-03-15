#include <bits/stdc++.h>

using namespace std;

#define FILENAME "jumping"

#define nl '\n'
typedef long long ll;
typedef long double ld;

const int N = 5000*3+5;
int a,b,c;
bool vis[N];
int pos = 0;

vector<int> ans;

void jump(int j) {
  switch (abs(j)) {
    case 1: assert(a); a--;
    break;
    case 2: assert(b); b--;
    break;
    case 3: assert(c); c--;
    break;
    default:
    break;
  }
  pos += j;
  assert(vis[pos] == 0);
  //vis[pos] = 1;
  ans.push_back(pos);
}

#define rep(n) for(int i=0;i<(n);++i)

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
#ifdef ONLINE_JUDGE
  freopen(FILENAME ".in", "r", stdin);
  freopen(FILENAME ".out", "w", stdout);
#endif
  int T; cin >> T;
  while(T--) {
    pos = 0;
    //memset(vis,0,sizeof vis);
    ans.clear();
    cin >> a >> b >> c;
    jump(0);
    if (c % 3 == 0) {
      const int j = c/3;
      rep(j) jump(+3);
      jump(+1);
      rep(j) jump(-3);
      jump(+1);
      rep(j) jump(+3);
    } else if (c % 3 == 1) {
      const int j = c/3;
      rep(j+1) jump(+3);
      jump(-2);
      rep(j) jump(-3);
      jump(+1);
      rep(j) jump(+3);
      jump(+2);
    } else {
      const int j = c/3;
      rep(j+1) jump(+3);
      jump(-1);
      rep(j) jump(-3);
      jump(-1);
      rep(j+1) jump(+3);
    }
    while(a > 1) {
      jump(+1);
    }
    if (b % 2 == 0) {
      const int j = b/2;
      rep(j) jump(+2);
      jump(+1);
      rep(j) jump(-2);
    } else {
      const int j = b/2;
      rep(j+1) jump(+2);
      jump(-1);
      rep(j) jump(-2);
    }
    assert((a | b | c) == 0);
    for (int v:ans) {
      cout << v << " ";
    }
    cout << nl;
  }
  return 0;
}

