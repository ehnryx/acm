#include <bits/stdc++.h>
using namespace std;

#include "../../lca/number/mod_int.h"

using ll = long long;
using ld = long double;
using pt = complex<ld>;

constexpr char nl = '\n';
constexpr int MOD = 1e9 + 7;
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());

using Int = mod_int<MOD>;

bool isv(char c) {
  c = tolower(c);
  return c == 'a' || c == 'e' || c == 'o' || c == 'i' || c == 'u';
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cout << fixed << setprecision(10);

  string s;
  cin >> s;
  int n = size(s);
  s = '0' + s;

  string vowels = "aeiou";
  string consonants = "qwrtypsdfghjklzxcvbnm";
  vector<char> vowel, consonant;
  for(char c : vowels) {
    vowel.push_back(c);
    vowel.push_back(toupper(c));
  }
  for(char c : consonants) {
    consonant.push_back(c);
    consonant.push_back(toupper(c));
  }

  const int V = size(vowel);
  const int K = size(consonant);

  vector prefo(V, vector<Int>(n+1));
  vector suffo(V, vector<Int>(n+1));
  vector pref(V, vector<Int>(n+1));
  vector suff(V, vector<Int>(n+1));

  vector dp(n+2, vector<Int>(3));
  vector dpo(n+2, vector<Int>(3));
  dp[0][0] = dp[n+1][0] = 1;
  dpo[0][0] = dpo[n+1][0] = 1;

  Int ans = 0;

  for(int c=0; c<K; c++) {
    for(int a=0; a<V; a++) {
      // left to right (not/only a, not c)
      {
        for(int i=1; i<=n; i++) {
          for(int j=0; j<3; j++) {
            dp[i][j] = dp[i-1][j];
            dpo[i][j] = dpo[i-1][j];
          }
          if(isv(s[i])) {
            if(s[i]!=vowel[a]) {
              dp[i][1] += dp[i-1][0];
            } else {
              dpo[i][1] += dpo[i-1][0];
            }
          } else if(s[i]!=consonant[c]) {
            dp[i][2] += dp[i-1][1];
            dpo[i][2] += dpo[i-1][1];
          }
          pref[a][i] = dp[i][2];
          prefo[a][i] = dpo[i][2];
        }
      }

      // right to left (not/only a, only c)
      {
        for(int i=n; i>0; i--) {
          for(int j=0; j<3; j++) {
            dp[i][j] = dp[i+1][j];
            dpo[i][j] = dpo[i+1][j];
          }
          if(isv(s[i])) {
            if(s[i]!=vowel[a]) {
              dp[i][1] += dp[i+1][0];
            } else {
              dpo[i][1] += dpo[i+1][0];
            }
          } else if(s[i]==consonant[c]) {
            dp[i][2] += dp[i+1][1];
            dpo[i][2] += dpo[i+1][1];
          }
          suff[a][i] = dp[i][2];
          suffo[a][i] = dpo[i][2];
        }
      }
    }

    for (int i=1; i<=n; i++) {
      if(!isv(s[i])) continue;
      int a = find(begin(vowel), end(vowel), s[i]) - begin(vowel);
      ans += pref[a][i] * suff[a][i];  // not a
      for(int b=0; b<V; b++) {
        if(a == b) continue;
        ans -= prefo[b][i] * suffo[b][i];  // only b
      }
    }
  }

  cout << ans << nl;

  return 0;
}
