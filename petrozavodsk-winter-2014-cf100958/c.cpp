#include <bits/stdc++.h>
using namespace std;

#define nl '\n'
typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
const int INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3fLL;
const int N = 6;

int n;
int fre[N];
vector<int> interesting;
ll ans = INFLL;
ll cur = 0;

void dfs(int i) {
  if (i >= n) {
    ans = min(ans, cur);
    return;
  }
  int unfre = 0, sub = 0;
  function<void(int)> dfs2 = [&i, &unfre, &sub, &dfs2](int j) {
    if (j >= interesting.size()) {
      cur += fre[i];
      dfs(i+1);
      cur -= fre[i];
      return;
    }
    if (interesting[j] & (~unfre)) return dfs2(j+1);
    // try using
    if (fre[i]) {
      sub++;
      unfre ^= interesting[j];
      interesting[j] += (1 << i);
      fre[i]--;
      dfs2(j+1);
      fre[i]++;
      interesting[j] -= (1 << i);
      unfre ^= interesting[j];
      sub--;
    }
    // don't use
    dfs2(j+1);
  };
  function<void(int)> dfs3 = [&](int j) {
    if (j >= i) return dfs2(0);
    if (fre[j]) {
      if (fre[i]) {
        fre[j]--;
        fre[i]--;
        sub++;
        interesting.push_back((1 << i) | (1 << j));
        dfs3(j+1);
        interesting.pop_back();
        sub--;
        fre[i]++;
        fre[j]++;
      }
      dfs3(j+1);
    } else {
      unfre ^= (1 << j);
      dfs3(j+1);
      unfre ^= (1 << j);
    }
  };
  dfs3(0);
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);

  cin >> n;
  for (int i = 0; i < n; i++) {
    cin >> fre[i];
  }
  sort(fre, fre + n);
  do {
    assert(interesting.empty());
    assert(cur == 0);
    dfs(0);
  } while (next_permutation(fre, fre + n));
  cout << ans << nl;

  return 0;
}
