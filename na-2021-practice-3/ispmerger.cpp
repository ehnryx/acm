#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;
using pt = complex<ld>;

constexpr char nl = '\n';
constexpr int MOD = 998244353;
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());

const int N = 1e5 + 1;
int slots[N], wires[N], nodes[N];
int dsu[N];

int find(int i) {
  if(dsu[i] == -1) return i;
  return dsu[i] = find(dsu[i]);
}

void link(int i, int j) {
  i = find(i);
  j = find(j);
  if(i != j) {
    dsu[j] = i;
    slots[i] += slots[j];
    wires[i] += wires[j];
    nodes[i] += nodes[j];
  }
  slots[i] -= 2;
  wires[i] += 1;
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cout << fixed << setprecision(10);

  int n, m, k;
  cin >> n >> m >> k;

  // assume we have enough wires

  /*
  if(m < n-1) {
    cout << "no" << nl;
    return 0;
  }
  */

  vector<int> cap(n);
  ll total_slots = 0;
  for(int i=0; i<n; i++) {
    cin >> cap[i];
    dsu[i] = -1;
    nodes[i] = 1;
    slots[i] = cap[i];
    total_slots += slots[i];
  }
  if (total_slots < (n-1)*2) {
    cout << "no" << nl;
    return 0;
  }
  // uhh

  for(int i=0; i<m; i++) {
    int a, b;
    cin >> a >> b;
    link(a, b);
  }

  vector<int> groups;
  for(int i=0; i<n; i++) {
    if(i == find(i)) {
      groups.push_back(i);
    }
  }

  if(size(groups) == 1) {
    cout << "yes" << nl;
    return 0;
  }

  int comps = 0;
  int ones = 0;
  int nt_ones = 0;
  int have = 0;
  int deg = 0;
  for(int g : groups) {
    deg += slots[g];
    if(slots[g] == 0) {
      k -= 1;
      have += 1;
      if(wires[g] == nodes[g] - 1) {
        ones += 2;
      } else {
        comps += 1;
      }
      deg += 2;
    } else if(slots[g] == 1) {
      if (wires[g] == nodes[g] - 1) {
        ones += 1;
      } else {
        nt_ones += 1;
      }
    } else {
      comps += 1;
    }
  }

  /*
  int goal = comps + ones + nt_ones - 1;
  while (have < goal) {
    k -= 1;
    have += 1;
    deg += 2;
    if (nt_ones) {
      nt_ones -= 1;
      comps += 1;
    }
  }

  assert(deg >= 2*ones);
  k -= goal; // reconnect all
  */

  // get more slots
  while (deg < 2*(ones + nt_ones)) {
    k -= 1;
    have += 1;
    deg += 2;
    if (nt_ones) {
      nt_ones -= 1;
      comps += 1;
    }
  }

  // reconnect all
  k -= comps + ones + nt_ones - 1;

  cerr << "k = " << k << nl;
  if(k < 0) {
    cout << "no" << nl;
  } else {
    cout << "yes" << nl;
  }

  return 0;
}
