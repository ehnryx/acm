#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;
#define nl '\n'

struct Stack : stack<int> {
  int first() {
    return (empty() ? 0 : top());
  }
  int second() {
    if(empty()) return 0;
    int tmp = top(); pop();
    int res = first(); push(tmp);
    return res;
  }
};

const int N = 5e3 + 1;
int a[N], ans[N];

bool solve(int l, int r, int v, int g) {
  int diff = 0;
  for(int i=l; i<r; i++) {
    diff += (a[i] < v ? -1 : 1);
  }

  Stack stk;
  for(int i=l; i<r; i++) {
    int cur = (a[i] < v ? -1 : 1);
    if((diff < g && stk.second() < 0 && stk.first() < 0)
        || (diff > g && stk.second() > 0 && stk.first() > 0)) {
      diff -= stk.first();
      diff -= cur;
      stk.pop();
    } else {
      stk.push(cur);
    }
  }

  return diff == g;
}

int main() {
  ios::sync_with_stdio(0); cin.tie(0);

  int T;
  cin >> T;
  while(T--) {
    int n;
    cin >> n;
    for(int i=0; i<n; i++) {
      cin >> a[i];
      ans[i] = false;
    }

    for(int i=0; i<n; i++) {
      if(i%2 == 1) {
        if(solve(0, i, a[i], 1) && solve(i+1, n, a[i], -1)) {
          ans[i] = true;
        } else if(solve(0, i, a[i], -1) && solve(i+1, n, a[i], 1)) {
          ans[i] = true;
        }
      } else {
        if(solve(0, i, a[i], 2) && solve(i+1, n, a[i], -2)) {
          ans[i] = true;
        } else if(solve(0, i, a[i], -2) && solve(i+1, n, a[i], 2)) {
          ans[i] = true;
        } else if(solve(0, i, a[i], 0) && solve(i+1, n, a[i], 0)) {
          ans[i] = true;
        }
      }
    }

    for(int i=0; i<n; i++) {
      cout << ans[i];
    }
    cout << nl;
  }

  return 0;
}
