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

bool dfs(int start, int end, const vector<set<int>>& graph) {
  bitset<200000> visited;
  stack<int> next;
  int curr;
  next.push(start);
  while (!next.empty()) {
    curr = next.top();
    next.pop();
    if (curr == end) return true;
    if (!visited[curr]) {
      visited[curr] = true;
      for (int neighbour: graph[curr]) {
        if (!visited[neighbour])
          next.push(neighbour);
      }
    }
  }
  return false;
}

int main() {
  ios::sync_with_stdio(0); 
  cin.tie(0); cout.tie(0);

  int n, k, x;
  cin >> n;
  int arr[n];
  for (int i = 0; i < n; i++)
    cin >> arr[i];
  vector<set<int>> graph(n);
  cin >> k;
  while (k--) {
    for (int i = 0; i < n; i++) {
      cin >> x;
      graph[x-1].insert(i);
    }
  }
  cin >> x;
  for (int i = 0; i < n; i++) {
    if (arr[i] == x) {
      x = i;
      break;
    }
  }
  if (dfs(x, 0, graph)) cout << "YES" << nl;
  else cout << "NO" << nl;

  return 0;
}
