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


bool solvable(ll a, ll b) {
  //ll g = gcd(a, b);
  return __builtin_popcountll((a + b)/* / g*/) == 1;
}

//#define MULTI_TEST
void solve_main([[maybe_unused]] int testnum, [[maybe_unused]] auto& cin) {
  vector<ll> orig(3);
  for(int i=0; i<3; i++) {
    cin >> orig[i];
  }

  ll sum = orig[0] + orig[1] + orig[2];
  const int len = 64 - __builtin_clzll(sum);
  const ll ub = 5 * (ll)sqrt(sum) - len;
  cerr << "want R <= " << ub << nl;

  //uniform_int_distribution<int> d(0, 2);

  vector<tuple<ll, ll, ll>> ans;
  ans.reserve(ub);
  for(int tt=1; clock() < 0.9*CLOCKS_PER_SEC; tt++) {
    cerr << "iteration " << tt << nl;
    ans.clear();
    auto v = orig;
    while(size(ans) < ub &&
        !solvable(v[0], v[1]) && !solvable(v[1], v[2]) && !solvable(v[2], v[0])) {
      bool done = false;
      {
        const vector<int> c = {
          __builtin_popcountll(v[0]),
          __builtin_popcountll(v[1]),
          __builtin_popcountll(v[2]),
        };
        for(int i=0; i<3; i++) {
          int j = (i+1 == 3 ? 0 : i+1);
          if(v[i] < v[j]) {
            if(__builtin_popcountll(v[j] - v[i]) + __builtin_popcountll(v[i] + v[i]) < c[i] + c[j]) {
              v[j] -= v[i];
              v[i] += v[i];
              done = true;
              break;
            }
          } else {
            if(__builtin_popcountll(v[i] - v[j]) + __builtin_popcountll(v[j] + v[j]) < c[i] + c[j]) {
              v[i] -= v[j];
              v[j] += v[j];
              done = true;
              break;
            }
          }
        }
      }
      if(!done) {
        int i = t % 3;
        int j = (i+1 == 3 ? 0 : i+1);
        if(v[i] < v[j]) {
          v[j] -= v[i];
          v[i] += v[i];
        } else {
          v[i] -= v[j];
          v[j] += v[j];
        }
      }
      ans.emplace_back(v[0], v[1], v[2]);
    }

    if(solvable(v[0], v[1])) {
      while(v[0] && v[1]) {
        if(v[0] < v[1]) {
          v[1] -= v[0];
          v[0] += v[0];
        } else {
          v[0] -= v[1];
          v[1] += v[1];
        }
        ans.emplace_back(v[0], v[1], v[2]);
      }
    } else if(solvable(v[1], v[2])) {
      while(v[1] && v[2]) {
        if(v[1] < v[2]) {
          v[2] -= v[1];
          v[1] += v[1];
        } else {
          v[1] -= v[2];
          v[2] += v[2];
        }
        ans.emplace_back(v[0], v[1], v[2]);
      }
    } else if(solvable(v[2], v[0])) {
      while(v[0] && v[2]) {
        if(v[0] < v[2]) {
          v[2] -= v[0];
          v[0] += v[0];
        } else {
          v[0] -= v[2];
          v[2] += v[2];
        }
        ans.emplace_back(v[0], v[1], v[2]);
      }
    } else {
      continue;
    }

    cout << size(ans) << nl;
    for(auto [a, b, c] : ans) {
      cout << a << " " << b << " " << c << nl;
    }
    return;
  }

  assert(false);
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cout << fixed << setprecision(10);
#ifdef USING_FAST_INPUT
  fast_input cin;
#endif

  int T = 1;
#ifdef MULTI_TEST
  cin >> T;
#endif
  for(int testnum=1; testnum<=T; testnum++) {
    solve_main(testnum, cin);
  }

  return 0;
}
