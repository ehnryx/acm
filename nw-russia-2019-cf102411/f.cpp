#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
typedef pair<ld,ld> pdd;
typedef complex<ld> pt;

const char nl = '\n';
const ll INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-13;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

enum {
  VALUE,
  REF,
};

const int N = 50+1;
const int M = 100+1;
int a[N], b[N], done[N];
int acnt[M], bcnt[M];
int last = -1;

int n;

vector<string> ans;
void foreach(int v, bool ref) {
  if(ref) ans.push_back("foreach ($a as &$x) if ($x == " + to_string(v) + ") break;");
  else    ans.push_back("foreach ($a as  $x) if ($x == " + to_string(v) + ") break;");
}

void update(int v, int x) {
  assert(acnt[v]);
  acnt[a[x]]--;
  a[x] = v;
  acnt[a[x]]++;
}

void copy_value_to(int,int);
void copy_to_last(int);
void save_last_value();

void copy_value_to(int v, int x) {
  //cerr<<"copy "<<v<<" to "<<x<<nl;
  for(int i=1;i<=x;i++) {
    if(a[i] == a[x]) {
      if(acnt[a[i]] == 1 && bcnt[a[i]]) {
        copy_to_last(a[i]);
      }
      //cerr<<"do copy @ "<<i<<" w/ value "<<a[i]<<nl;
      foreach(a[i], REF);
      foreach(v, VALUE);
      update(v, i);
    }
  }
  //cerr<<nl;
}

void copy_to_last(int v) {
  if(acnt[a[n]] == 1 && bcnt[a[n]]) {
    save_last_value();
  }
  //cerr<<"copy "<<v<<" to last"<<nl<<nl;
  foreach(last, REF);
  foreach(v, VALUE);
  update(v, n);
}

void save_last_value() {
  for(int i=1;i<=n;i++) {
    if(acnt[a[i]] > 1 || !bcnt[a[i]]) {
      copy_value_to(a[n], i);
      return;
    }
  }
  assert(false);
}

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(10);

  cin>>n;

  for(int i=1;i<=n;i++) {
    cin>>a[i];
    acnt[a[i]]++;
  }
  for(int i=1;i<=n;i++) {
    cin>>b[i];
    bcnt[b[i]]++;
  }

  int maxcnt = 0;
  for(int i=1;i<M;i++) {
    if(bcnt[i] && !acnt[i]) {
      cout<<-1<<nl;
      return 0;
    }
    maxcnt = max(maxcnt, bcnt[i]);
    if(bcnt[i] == 0) {
      last = i;
    }
  }

  if(maxcnt==1) {
    bool ok = true;
    for(int i=1;i<=n;i++) {
      ok &= (a[i] == b[i]);
    }
    if(ok) {
      cout<<0<<nl;
    } else {
      cout<<-1<<nl;
    }
    return 0;
  }
  assert(last != -1);

  int unique_first = (bcnt[b[1]] == 1);
  int orig_first = 0;
  if(unique_first) {
    for(int i=1;i<=n;i++) {
      if(bcnt[b[i]] > 1) {
        orig_first = b[i];
        bcnt[b[i]]--;
        b[i] = b[1];
        bcnt[b[i]]++;
        unique_first = i;
        break;
      }
    }
  }

  for(int i=n-1;i>0;i--) {
    if(a[i] == b[i]) continue;
    copy_value_to(b[i], i);
  }
  if(a[n] != b[n]) {
    copy_to_last(b[n]);
  }

  //cerr<<"prelim: "<<nl;
  for(int i=1;i<=n;i++) {
    //cerr<<i<<": "<<a[i]<<nl;
    assert(a[i] == b[i]);
  }

  if(int i = unique_first) {
    copy_value_to(a[n], 1);
    copy_to_last(a[i]);
    copy_value_to(a[1], i);
    copy_value_to(a[n], 1);
    copy_to_last(a[i]);
    copy_value_to(orig_first, i);
  }

  //cerr<<"result: "<<nl; for(int i=1;i<=n;i++) {
    //cerr<<i<<": "<<a[i]<<nl; }

  cout<<ans.size()<<nl;
  for(const string& s:ans) {
    cout<<s<<nl;
  }

  return 0;
}
