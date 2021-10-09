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

  vector<int> left, right;
  int n, a, b;
  cin >> n;
  for (int i = 0; i < n; i++) {
    cin >> a >> b;
    if (a > 0)
      right.push_back(b);
    else
      left.push_back(-b);
  }
  sort(left.begin(), left.end());
  sort(right.begin(), right.end());
  
  int m, q;
  cin >> m;
  for (int i = 0; i < m; i++) {
    cin >> q;
    int ans = 0;
    int lx, rx, mid;
    if (left.size() > 0) {
      lx = 0; rx = left.size()-1;
      while (lx <= rx) {
        mid = (lx+rx)/2;
        if (left[mid] >= q)
          rx = mid-1;
        else
          lx = mid+1;
      }
      if (left[mid] < q)
        mid++;
      ans += left.size() - mid;
    }
    if (right.size() > 0) {
      lx = 0; rx = right.size()-1;
      while (lx <= rx) {
        mid = (lx+rx)/2;
        if (right[mid] > q) 
          rx = mid-1;
        else 
          lx = mid+1;
      }
      if (right[mid] <= q)
        mid++;
      ans += mid;
    }
    cout << ans << nl;
  }

  return 0;
}
