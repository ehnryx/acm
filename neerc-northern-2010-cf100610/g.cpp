#include <bits/stdc++.h>
using namespace std;
using vi = vector<int>;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
const char nl = '\n';

#define FILE "gadgets"

const int N = 100100;
const ld EPS = 1e-13L;
vector<int> fac[N];
int cur[N];
int n, m;

struct collection {
  ll sum = 0;
  int amt = 0;
  ll a = 0, b = 0, c = 0;
  void insert(ll p) {
    sum += p;
    amt ++;
    a++;
    b-=2*p;
    c+=p*p;
  }
  void remove(ll p) {
    sum -= p;
    amt --;
    a--;
    b+=2*p;
    c-=p*p;
  }
  ld loc() {
    return (ld) sum/amt;
  }
  ld query() {
    ld x = loc();
    return x*x*a+b*x+c;
  }
};

struct minstore {
  ld val = 1e19;
  vector<ld> pos;
  void insert(ld amt, ld p) {
    if (abs(amt-val) < EPS) {
      pos.push_back(p);
    } else if(amt < val) {
      val = amt;
      pos.clear();
      pos.push_back(p);
    }
  }
};

int main() {
  if (fopen(FILE ".in", "r")) {
    freopen(FILE ".in", "r", stdin);
    freopen(FILE ".out", "w", stdout);
  }

  minstore mst;
  cin >> n >> m;
  for (int i=1; i<=m; ++i) {
    int x, p;
    cin >> x >> p;
    fac[p].push_back(x);
  }

  vector<pii> splits;
  for (int i=1; i<=n; ++i) {
    for (int j=0; j<fac[i].size()-1; ++j) {
      splits.emplace_back(fac[i][j] + fac[i][j+1], i);
    }
  }

  collection coll;
  for (int i=1; i<=n; ++i) {
    coll.insert(fac[i][0]);
  }

  mst.insert(coll.query(), coll.loc());

  sort(splits.begin(), splits.end());
  for (auto& pp : splits) {
    int i = pp.second;
    coll.remove(fac[i][cur[i]]);
    coll.insert(fac[i][++cur[i]]);
    mst.insert(coll.query(), coll.loc());
  }

  cout << mst.pos.size() << "\n";
  cout << fixed << setprecision(10);

  sort(mst.pos.begin(), mst.pos.end());
  Rat pre = new Rat(-999999999);
  for (auto& x : mst.pos) {
    if (x.comareTo(pre) != 0) {
      cout << x << "\n";
    }
    pre = x;
  }

  return 0;
}
