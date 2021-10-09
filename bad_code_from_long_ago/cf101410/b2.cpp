#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef complex<ld> pt;
typedef vector<pt> pol;
#define nl '\n'

///* advent of code
typedef istringstream iss;
#define pb push_back
#define ins insert
#define multiset mset
#define getl(A) getline(cin, A)
//*/

const ll INF = 0x3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-9;

struct Move {
  int p, q;
  Move() {}
  Move(int p, int q): p(p), q(q) {}
};
ostream& operator << (ostream& os, const Move& mov) {
  os << mov.p << " " << mov.q; return os;
}

struct Cup {
  int id, v;
  Cup() {}
  Cup(int i, int v): id(i), v(v) {}
  operator int&() { return v; }
  void operator = (int x) { v = x; }
  bool operator < (const Cup other) const {
    return v < other.v;
  }
};
ostream& operator << (ostream& os, const Cup& cup) {
  os << "(" << cup.id << "," << cup.v << ")"; return os;
}

template<class T>
ostream& operator << (ostream& os, const vector<T>& v) {
  for (const T& it : v) os << it << " "; return os;
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  freopen("barrels.in", "r", stdin);
  freopen("barrels.out", "w", stdout);

  int n;
  cin >> n;

  int best = 0;
  vector<Move> ans;
  int rlim = n*n*n;
  srand(clock()+time(nullptr));

  while (clock() < 0.9*CLOCKS_PER_SEC) {
    vector<Move> random;
    vector<Cup> a;
    for (int i = 1; i <= n; i++) {
      a.push_back(Cup(i,i));
    }

    int zero = 0;
    if (n % 4 == 3 || n % 4 == 0) 
      zero = 1;
    for (int round = 0; round < rlim && zero + 2 < n; round++) {
      int i = zero + rand()%(n-zero);
      int j = zero + rand()%(n-zero);
      if (i == j)
        continue;
      if (a[i] > a[j])
        swap(i,j);
      random.push_back(Move(a[i].id, a[j].id));
      a[j] -= a[i];
      a[i] *= 2;
      if (a[j] == 0) {
        swap(a[j], a[zero++]);
      }
    }

    if (min(a[n-1].v, a[n-2].v) > __gcd(a[n-1].v, a[n-2].v)) {
      int high = 0;
      unordered_set<int> seen;
      while (!seen.count(a[n-1])) {
        high = max(high, a[n-1].v);
        high = max(high, a[n-2].v);
        seen.insert(a[n-1]);
        if (a[n-1] < a[n-2]) {
          random.push_back(Move(a[n-1].id, a[n-2].id));
          a[n-2] -= a[n-1];
          a[n-1] *= 2;
        } else {
          random.push_back(Move(a[n-2].id, a[n-1].id));
          a[n-1] -= a[n-2];
          a[n-2] *= 2;
        }
      }

      for (int ii = 0; ii < 100; ii++) {
        if (a[n-1] == high || a[n-2] == high)
          break;
        if (a[n-1] < a[n-2]) {
          random.push_back(Move(a[n-1].id, a[n-2].id));
          a[n-2] -= a[n-1];
          a[n-1] *= 2;
        } else {
          random.push_back(Move(a[n-2].id, a[n-1].id));
          a[n-1] -= a[n-2];
          a[n-2] *= 2;
        }
      }
    }

    int cur = max(a[n-1].v, a[n-2].v);
    if (cur > best) {
      ans = random;
      best = cur;
    }
  }
  //cout << best << nl;

  //cerr << "best: " << best << nl;
  //cerr << "remainder: " << n*(n+1)/2 - best << nl;
  //cerr << "ans size: " << ans.size() << nl;

  vector<int> simulate(n+1);
  for (int i = 1; i <= n; i++) {
    simulate[i] = i;
  }

  int sz = -1;
  for (int i = 0; i < ans.size(); i++) {
    simulate[ans[i].q] -= simulate[ans[i].p];
    simulate[ans[i].p] *= 2;
    if (simulate[ans[i].p] == best) {
      sz = i;
      break;
    }
  }
  //cerr << "sz: " << sz << nl;
  //cerr << "final: " << simulate << nl;

  cout << sz+1 << nl;
  for (int i = 0; i <= sz; i++) {
    cout << ans[i] << nl;
  }

  return 0;
}
