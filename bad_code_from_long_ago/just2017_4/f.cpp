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

struct RMQ {
  struct Node {
    int index;
    int value;
    Node(int i=-1, int v=-1) {
      index = i;
      value = v;
    }
    bool operator > (const Node& other) const {
      if (value == other.value) return index < other.index;
      else return value > other.value;
    }
    Node max(Node other) {
      if ((*this) > other) return (*this);
      else return other;
    }
  };
  Node prev[10001][20];
  int bestjump[10001];
  void insert(int id, int value) {
    prev[id][0] = Node(id, value);
  }
  void build(int n) {
    // do next
    for (int i = 1; i <= n; i++) {
      for (int jump = 1; (1<<jump) <= i; jump++) {
        prev[i][jump] = prev[i-(1<<(jump-1))][jump-1].max(prev[i][jump-1]);
      }
    }
    for (int jump = 0; (1<<jump) <= n; jump++) {
      for (int r = (1<<jump); r < min(1<<(jump+1), n+1); r++)
        bestjump[r] = jump;
    }
  }
  int query(int a, int b) {
    if (a > b) swap(a,b);
    int jump = bestjump[b-a+1];
    if (prev[b][jump] > prev[a+(1<<jump)-1][jump])
      return prev[b][jump].index;
    else
      return prev[a+(1<<jump)-1][jump].index;
  }
};

// palindrome substrings
int palindromes(const string& s) {
  int cnt = 0;
  for (int mid = 0; mid < s.size(); mid++) {
    int r;
    for (r = 0; mid-r >= 0 && mid+r < s.size(); r++) 
      if (s[mid-r] != s[mid+r]) 
        break;
    cnt += r;
    if (mid>0) {
      for (r = 0; mid-1-r >= 0 && mid+r < s.size(); r++) 
        if (s[mid-1-r] != s[mid+r]) 
          break;
      cnt += r;
    }
  }
  return cnt;
}

int main() {
  ios::sync_with_stdio(0); 
  cin.tie(0); cout.tie(0);

  int n, q;
  string a, b;
  RMQ rmq;
  unordered_map<string, int> index_of;

  int T;
  cin >> T;
  while (T--) {
    cin >> n >> q;
    for (int i = 1; i <= n; i++) {
      cin >> a;
      index_of[a] = i;
      rmq.insert(i, palindromes(a));
    }
    rmq.build(n);
    while (q--) {
      cin >> a >> b;
      cout << rmq.query(index_of[a], index_of[b]) << nl;
    }
  }

  return 0;
}
