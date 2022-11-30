#include <bits/stdc++.h>
using namespace std;

//%:include "utility/fast_input.h"
//%:include "utility/output.h"

using ll = long long;
using ld = long double;

constexpr char nl = '\n';
constexpr int MOD = 998244353;
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());

const int N = 1 << 18;
int st[2 * N];

void insert(int i, int v) {
  st[i += N] = v;
  for(i /= 2; i > 0; i /= 2) {
    st[i] = min(st[2*i], st[2*i + 1]);
  }
}

int query(int l, int r) {
  int res = numeric_limits<int>::max();
  for(l += N, r += N + 1; l < r; l /= 2, r /= 2) {
    if(l & 1) res = min(res, st[l++]);
    if(r & 1) res = min(res, st[--r]);
  }
  return res;
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cout << fixed << setprecision(10);
#ifdef USING_FAST_INPUT
  fast_input cin;
#endif

  int n, k;
  cin >> n >> k;
  vector<int> a(n + 1);
  vector<queue<int>> ids(k + 1);
  vector<int> last(k + 1);
  set<int> lasts;
  for(int i=1; i<=n; i++) {
    cin >> a[i];
    last[a[i]] = i;
    ids[a[i]].push(i);
  }

  for(int i=1; i<=k; i++) {
    lasts.insert(last[i]);
    insert(i, ids[i].front());
  }

  vector<int> ans;
  for(int i=1, done=0; i<=k; i++) {
    int rb = *lasts.begin();
    int l = 1;
    int r = k;
    while(l < r) {
      int m = (l + r) / 2;
      if(query(1, m) <= rb) {
        r = m;
      } else {
        l = m + 1;
      }
    }
    int to = query(1, r);
    ans.push_back(r);
    lasts.erase(last[r]);
    insert(r, numeric_limits<int>::max());

    while(done < to) {
      ++done;
      ids[a[done]].pop();
      if(lasts.count(last[a[done]])) {
        insert(a[done], ids[a[done]].front());
      }
    }
  }

  for(int i : ans) {
    cout << i << " ";
  }
  cout << nl;

  return 0;
}
