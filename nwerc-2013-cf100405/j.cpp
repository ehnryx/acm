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

const int N = 2420;
vector<int> child[N];
int parent[N], ball[N], all[N];
int memo[N][N];

void init() {
  fill(child, child+N, vector<int>());
  memset(parent, -1, sizeof parent);
  memset(ball, 0, sizeof ball);
  memset(all, 0, sizeof all);
  memset(memo, -1, sizeof memo);
}

void treedp(int x) {
  all[x] = 1;
  for (int y : child[x]) {
    treedp(y);
    all[x] += all[y];
  }
}

int dfs(int x, int num) {
  if (memo[x][num] != -1) {
    return memo[x][num];
  }
  if (num > all[x]) {
    return memo[x][num] = INF;
  }
  if (child[x].empty()) {
    return memo[x][num] = (ball[x] != num);
  }

  if (num%2 == 0) {
    return memo[x][num] = min(INF, dfs(child[x][0], num/2) + dfs(child[x][1], num/2));
  }
  else {
    int first = dfs(child[x][0], num/2) + dfs(child[x][1], num/2+1);
    int second = dfs(child[x][0], num/2+1) + dfs(child[x][1], num/2);
    return memo[x][num] = min(INF, min(first, second));
  }
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  cout << fixed << setprecision(10);

  string s;
  while (cin >> s) {
    init();

    int total = 0;
    int id = 0;
    int cur = -1;
    for (char c : s) {
      if (c == '(') {
        parent[id] = cur;
        if (cur != -1) child[cur].push_back(id);
        cur = id++;
      }
      else if (c == ')') {
        cur = parent[cur];
      }
      else {
        ball[cur] = true;
        total++;
      }
    }

    treedp(0);

    int ans = dfs(0, total);

    if (ans == INF) cout << "impossible" << nl;
    else cout << ans/2 << nl;
  }

  return 0;
}
