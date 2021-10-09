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

const int N = 2e5+1;
vector<int> adj[N];
int allowed[N];
int bad[N];

vector<int> ans;

void down(int cur, int val = false) {
  if (allowed[cur] == -1) {
    allowed[cur] = val;
  }
  if (adj[cur].empty()) {
    bad[cur] = !allowed[cur];
  } else {
    for (int x : adj[cur]) {
      down(x, allowed[cur]);
      bad[cur] += bad[x];
    }
  }
}

void up(int cur) {
  if (bad[cur] == 0) {
    ans.push_back(cur);
  } else {
    for (int x : adj[cur]) {
      up(x);
    }
  }
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  cout << fixed << setprecision(10);

  int n;
  cin >> n;

  char c;
  for (int i=1; i<=n; i++) {
    cin >> c;
    if (c == '+') allowed[i] = true;
    else if (c == '-') allowed[i] = false;
    else allowed[i] = -1;
  }

  int a, b;
  for (int i=1; i<n; i++) {
    cin >> a >> b;
    adj[a].push_back(b);
  }

  down(1);
  up(1);

  sort(ans.begin(), ans.end());
  cout << ans.size() << nl;
  for (int it : ans) {
    cout << it << " ";
  }
  cout << nl;

  return 0;
}
