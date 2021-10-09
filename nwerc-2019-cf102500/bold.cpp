#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
const char nl = '\n';

int n, k;
const int N = 5e5+10;
int l[N];
int r[N];
int root = 0;
bool in[N];

void add(int u, int p) {
  if (p == -1) {
    assert(root == 0);
    root = u;
  } else {
    if (u < p) {
      assert(l[p] == 0);
      l[p] = u;
    } else {
      assert(r[p] == 0);
      r[p] = u;
    }
  }
}

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cin >> n >> k;
  for (int i = 1; i <= n; ++i) {
    int p; cin >> p;
    add(i, p);
  }
  queue<int> ins;
  assert(root);
  ins.push(root);
  while (k--) {
    assert(!ins.empty());
    int cur = ins.front(); ins.pop();
    in[cur] = 1;
    if (l[cur]) ins.push(l[cur]);
    if (r[cur]) ins.push(r[cur]);
  }
  for (int i = 1; i <= n; ++i) {
    cout << in[i];
  } cout << nl;

  return 0;
}

