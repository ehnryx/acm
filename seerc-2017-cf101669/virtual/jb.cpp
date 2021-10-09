#include <bits/stdc++.h>
using namespace std;

#define nl '\n'
typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;

const int INF = 0x3f3f3f3f;

const int N = 7, K = 6;

bool inc(vector<int>& v) {
  for (int i = 0; i < N; i++) {
    if (++v[i] == K) {
      v[i] = 0;
    } else return 1;
  }
  return 0;
}

map<pair<vector<int>, bool>, bool> dp;

int solve(vector<int> v, bool turn) {
  sort(v.begin(), v.end());
  if (dp.count({v, turn})) return dp[{v, turn}];
  bool lose = 1;
  for (int i : v) {
    if (i) {
      lose = 0;
      break;
    }
  }
  if (lose) return dp[{v, turn}] = 0;
  if (turn) {
    // 2 moves
    for (int i = 0; i < N; i++) {
      for (int j = i+1; j < N; j++) {
        for (int k = 1; k <= v[i]; k++) {
          for (int l = 1; l <= v[j]; l++) {
            vector<int> nex = v;
            nex[i] -= k;
            nex[j] -= l;
            if (!solve(nex, !turn)) return dp[{v, turn}] = 1;
          }
        }
      }
    }
    for (int i = 0; i < N; i++) {
      for (int k = 2; k <= v[i]; k++) {
        vector<int> nex = v;
        nex[i] -= k;
        if (!solve(nex, !turn)) return dp[{v, turn}] = 1;
      }
    }
    return dp[{v, turn}] = 0;
  } else {
    for (int i = 0; i < N; i++) {
      for (int k = 1; k <= v[i]; k++) {
        vector<int> nex = v;
        nex[i] -= k;
        if (!solve(nex, !turn)) return dp[{v, turn}] = 1;
      }
    }
    return dp[{v, turn}] = 0;
  }
}

bool solve2(vector<int> a) {
  sort(a.rbegin(), a.rend());
  int n = 0;
  while (n < a.size() && a[n]) n++;
  if (n == 1) return 1;
  if (n == 2) {
    return (a[1] == 1 ? 1 : 0);
  }
  if (a[2] > 1) {
    return 0;
  }
  if (a[0] == 1) {
    return (n % 3 ? 1 : 0);
  }
  if (a[1] == 2) {
    return (n % 3 == 2 ? 0 : 1);
  }
  if (a[1] == 1) {
    return 1;
  }
  return 0;
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);

  vector<int> v(N);
  do {
    //dp.clear();
    for (int i : v) cout << i << " ";
    cout << " -> " << solve(v, 0) << endl;
    /*
    bool full = 1; int ocnt = 0;
    for (int i : v) {
      if (!i) full = 0;
      ocnt += (i == 1);
    }
    */
    assert(solve(v, 0) == solve2(v));
  } while (inc(v));
  /*
  vector<int> v(N, 1);
  for (; v[0] < K; v[0]++) {
    for (; v[1] < K; v[1]++) {
      for (int i : v) cout << i << " ";
      cout << "-> " << solve(v, 0) << nl;
    }
    v[1] = 1;
  }
  */

  return 0;
}
