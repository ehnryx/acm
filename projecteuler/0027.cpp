#pragma GCC optimize("O3")

#include <bits/stdc++.h>
using namespace std;

#include "../../lca/number/int_base10.h"
#include "../../lca/math/linear_sieve.h"

constexpr char nl = '\n';
using ll = long long;
using Int = int_base10;

const int N = 1'000'000;
vector<bool> prime(N);

pair<int, int> solve(int a, int n) {
  pair<int, int> ans(0, 0);
  for (int b = -n + 1; b < n; b++) {
    int i = 0;
    int num = i*i + a*i + b;
    while (0 < num && prime[num]) {
      i++;
      num = i*i + a*i + b;
      assert(num < N);
    }
    ans = max(ans, pair(i, a * b));
  }
  return ans;
}

int main(int argc, char** argv) {
  cin.tie(0)->sync_with_stdio(0);

  linear_sieve sieve(N);
  for (int i : sieve.prime) {
    prime[i] = true;
  }

  ll n = 1'000;
  if (argc > 1) n = atoll(argv[1]);

  //vector<future<pair<int,int>>> handles;
  pair<int, int> ans(0, 0);
  for (int a = -n + 1; a < n; a++) {
    //handles.push_back(async(launch::async, solve, a, n));
    ans = max(ans, solve(a, n));
  }
  /*
  for(auto& it : handles) {
    ans = max(ans, it.get());
  }*/
  cout << ans.second << ": primes " << ans.first << nl;

  return 0;
}
