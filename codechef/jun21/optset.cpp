#include <bits/stdc++.h>
using namespace std;

const char nl = '\n';
using ll = long long;

const int L = 3;
const int R = 6;
const int M = 9;

void solve_tiny(int n, int k) {
  //cerr << "SOLVE (tiny) " << n << " " << k << endl;

  int two = 1 << (32 - __builtin_clz(n));
  vector dp(n + 1, vector<int>(two, -1));
  dp[0][0] = 0;
  for (int i = 1; i <= n; i++) {
    for (int j = i - 1; j >= 0; j--) {
      for (int v = 0; v < two; v++) {
        if (dp[j][v] == -1) continue;
        if (dp[j + 1][v ^ i] == -1) {
          dp[j + 1][v ^ i] = i;
        }
      }
    }
  }
  int goal = -1;
  for (int v = 0; v < two; v++) {
    if (dp[k][v] != -1) {
      goal = v;
    }
  }
  assert(goal != -1);

  vector<int> ans;
  for (int i = k; i > 0; i--) {
    ans.push_back(dp[i][goal]);
    goal ^= ans.back();
  }
  assert(goal == 0);

  sort(begin(ans), end(ans));
  for(int it : ans) {
    cout << it << " ";
  }
  cout << nl;
}

void solve_small(int n, int k) {
  //cerr << "SOLVE (small) " << n << " " << k << endl;

  if (k == 1) {
    cout << n << nl;
    return;
  }

  int two = 1 << (32 - __builtin_clz(n));
  int rem = k % 4;
  if (rem <= 1) rem += 4;
  vector<int> ans;
  for (int i = 1; i < rem; i++) {
    ans.push_back(two >> i);
  }
  ans.push_back((two >> (rem - 1)) - 1);

  vector<bool> have(n + 1);
  for (int it : ans) {
    have[it] = true;
  }

  k -= rem;
  for (int i = 2; i < n && k > 0; i += 2) {
    if (!have[i] && !have[i + 1]) {
      ans.push_back(i);
      ans.push_back(i + 1);
      k -= 2;
    }
  }
  assert(k == 0);

  int res = 0;
  sort(begin(ans), end(ans));
  for(int it : ans) {
    cout << it << " ";
    res ^= it;
  }
  cout << nl;
  assert(res == two - 1);
}

// solution broken when n = 2^c - 2, k = n - 2. Can't reach all 1's
void solve_big(int n, int k) {
  //cerr << "SOLVE (big) " << n << " " << k << endl;

  if (k == n) {
    for (int i = 1; i <= n; i++) {
      cout << i << " ";
    }
    cout << nl;
    return;
  }

  int all = 0;
  for (int i = 1; i <= n; i++) {
    all ^= i;
  }

  if (k == n - 1) {
    pair<int, int> best(-1, -1);
    for (int i = 1; i <= n; i++) {
      best = max(best, pair(all ^ i, i));
    }
    for (int i = 1; i <= n; i++) {
      if (i != best.second) {
        cout << i << " ";
      }
    }
    cout << nl;
    return;
  }

  int two = 1 << (32 - __builtin_clz(n));
  int fix = all ^ (two - 1);
  k = n - k;
  int rem = k % 4;
  if (rem == 0 && fix > 0) rem += 4;
  if (rem == 1 && fix > n) rem += 4;
  assert(rem <= k);
  k -= rem;

  //cerr << "rem: " << rem << " to make " << fix << endl;
  vector<int> out;
  if (fix > 0) {
    random_device rd;
    mt19937 rng(rd());
    while (true) {
      out.clear();
      int value = fix;
      for (int i = 1; i < rem; i++) {
        int v = rng() % n + 1;
        while (find(begin(out), end(out), v) != end(out)) {
          v = rng() % n + 1;
        }
        out.push_back(v);
        value ^= v;
      }
      if (0 < value && value <= n && find(begin(out), end(out), value) == end(out)) {
        out.push_back(value);
        break;
      }
    }
  }
  //cerr << "out.size: " << out.size() << nl;

  for (int i = 2; i < n && k > 0; i += 2) {
    if (find(begin(out), end(out), i) == end(out)
        && find(begin(out), end(out), i + 1) == end(out)) {
      out.push_back(i);
      out.push_back(i + 1);
      k -= 2;
    }
  }
  assert(k == 0);

  int res = 0;
  for (int i = 1; i <= n; i++) {
    if (find(begin(out), end(out), i) == out.end()) {
      cout << i << " ";
      res ^= i;
    }
  }
  cout << nl;
  //cerr << "got res = " << res << endl;
  assert(res == two - 1);
}

void solve_middle(int n, int k) {
  return solve_small(n, k); // this is fine
}

void solve() {
  int n, k;
  cin >> n >> k;
  if (n < 2 * M) {
    return solve_tiny(n, k);
  } else if (k < M) {
    return solve_small(n, k);
  } else if (k > n - M) {
    return solve_big(n, k);
  } else {
    return solve_middle(n, k);
  }
}

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int T;
  cin >> T;
  while (T--) {
    solve();
  }

  return 0;
}