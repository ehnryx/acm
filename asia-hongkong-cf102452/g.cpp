#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;
#define nl '\n'

int cbrt(int x) {
  int rt = 0;
  while (rt*rt*rt <= x) rt++;
  return rt-1;
}

void solve(int a, int b, int c) {
  vector<int> p, w = {10};
  int cur = 1; //previous parent
  for (int i = 0; i < c; ++i) {
    p.push_back(cur++);
    w.push_back(3);
  }
  p.push_back(cur++);
  w.push_back(10);
  const int fork1 = cur;
  //chain 2s
  for (int i = 0; i < b; ++i) {
    if (i == 0) {
      p.push_back(fork1);
    } else {
      p.push_back(cur);
    }
    cur++;
    w.push_back(2);
  }
  p.push_back(cur++);
  w.push_back(10);
  const int fork2 = cur;
  //chain 1s
  for (int i = 0; i < a; ++i) {
    if (i == 0) {
      p.push_back(fork1);
    } else {
      p.push_back(cur);
    }
    cur++;
    w.push_back(1);
  }
  for (int x = 0; x < 2; ++x) {
    for (int i = 0; i < a; ++i) {
      if (i == 0) {
        p.push_back(fork2);
      } else {
        p.push_back(cur);
      }
      cur++;
      w.push_back(1);
    }
  }
  assert(p.size() +1 == w.size());
  assert(w.size() >= 2);
  assert(w.size() <= (int)1e5);
  cout << w.size() << nl;
  for (int v : p) {
    cout << v << " ";
  } cout << nl;
  for (int v : w) {
    cout << v << " ";
  } cout << nl;
}

int main() {
  ios::sync_with_stdio(0); cin.tie(0);

  int k; cin >> k;
  int a = cbrt(k);
  int sub = k-a*a*a;
  assert(sub >= 0);
  int b = 0;
  while (b*a <= sub) b++;
  b--;
  int c = sub - b*a;
  //fprintf(stderr, "%d %d %d\n", a, b, c);
  solve(a,b,c);

  return 0;
}

