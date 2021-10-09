#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

//#define DEBUG
//#define USE_MAGIC_IO

#define ll long long
#define pii pair<int,int>
#define pdd pair<double,double>
#define ldouble long double
#define nl '\n'
const ll MOD = 1e9+7;
const int INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;

// MODINT
template<int MOD> struct ModInt {
  ll x;
  ModInt(ll n=0) { n %= MOD; if (n < 0) n += MOD; x = n; }
  int get() const { return (int) x; }
  ModInt operator + (const ModInt& other) { return ModInt(x + other.x); }
  ModInt operator - (const ModInt& other) { return ModInt(x + MOD - other.x); }
  ModInt operator * (const ModInt& other) { return ModInt(x * other.x); } 
  ModInt& operator += (const ModInt& other) { x = (x + other.x) % MOD; return *this; }
  ModInt& operator -= (const ModInt& other) { x = (x + MOD - other.x) % MOD; return *this; }
  ModInt& operator *= (const ModInt& other) { x = (x * other.x) % MOD; return *this; }
};

int main() {
  ios::sync_with_stdio(0); 
  cin.tie(0); cout.tie(0);

  int ppl, vaults, cap, tleft, temp;
  vector<int> people, coffin;
  cin >> ppl >> vaults >> cap >> tleft;
  for (int i = 0; i < ppl; i++) {
    cin >> temp;
    people.push_back(temp);
  }
  for (int i = 0; i < vaults; i++) {
    cin >> temp;
    coffin.push_back(temp);
  }
  sort(people.begin(), people.end());
  sort(coffin.begin(), coffin.end());

  int full[vaults];
  memset(full, 0, sizeof(full));
  int ans = 0;
  for (int cpos = 0, ppos = 0; ppos < ppl && cpos < vaults; ppos++) {
    redo:
    if (coffin[cpos] - people[ppos] > tleft)
      continue;
    if (coffin[cpos] >= people[ppos]) {
      full[cpos]++;
      ans++;
    }
    else if (people[ppos] - coffin[cpos] > tleft) {
      ++cpos;
      while (cpos < vaults && people[ppos] - coffin[cpos] > tleft)
        cpos++;
      if (cpos == vaults)
        break;
      else
        goto redo;
    }
    else {
      full[cpos]++;
      ans++;
    }
    if (full[cpos] == cap)
      cpos++;
  }
  cout << ans << nl;

  return 0;
}
