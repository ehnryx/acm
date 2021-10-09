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

const int N = 1<<19;
ll st[2*N], za[2*N], zm[2*N];

void fix(int i) {
  if(st[i] > MOD) st[i] %= MOD;
  if(za[i] > MOD) za[i] %= MOD;
  if(zm[i] > MOD) zm[i] %= MOD;
}

void push(int i) {
  if(zm[i] != 1) {
    for(int t=0; t<2; t++) {
      zm[2*i+t] *= zm[i];
      za[2*i+t] *= zm[i];
      st[2*i+t] *= zm[i];
    }
    zm[i] = 1;
  }
  if(za[i] != 0) {
    for(int t=0; t<2; t++) {
      za[2*i+t] += za[i];
      st[2*i+t] += za[i];
    }
    za[i] = 0;
  }
  fix(2*i);
  fix(2*i+1);
}

void update_add(int l, int r, int v, int i=1, int s=0, int e=N-1) {
  if(r<s || e<l) return;
  if(l<=s && e<=r) {
    za[i] += v;
    st[i] += v;
    fix(i);
    return;
  }
  push(i);
  int m = (s+e)/2;
  update_add(l,r,v,2*i,s,m);
  update_add(l,r,v,2*i+1,m+1,e);
}

void update_mul(int l, int r, int v, int i=1, int s=0, int e=N-1) {
  if(r<s || e<l) return;
  if(l<=s && e<=r) {
    zm[i] *= v;
    za[i] *= v;
    st[i] *= v;
    fix(i);
    return;
  }
  push(i);
  int m = (s+e)/2;
  update_mul(l,r,v,2*i,s,m);
  update_mul(l,r,v,2*i+1,m+1,e);
}

void insert_am(int x, int a, int v, int i=1, int s=0, int e=N-1) {
  if(s==e) {
    assert(zm[i] == 1 && st[i] == 0);
    zm[i] = v;
    st[i] = a;
    return;
  }
  push(i);
  int m = (s+e)/2;
  if(x<=m) insert_am(x,a,v,2*i,s,m);
  else insert_am(x,a,v,2*i+1,m+1,e);
}

pair<ll,ll> query_pl(int x, int i=1, int s=0, int e=N-1) {
  if(s==e) {
    return make_pair(st[i], zm[i]);
  }
  push(i);
  int m = (s+e)/2;
  if(x<=m) return query_pl(x,2*i,s,m);
  else return query_pl(x,2*i+1,m+1,e);
}

const int L = 31;
ll offset[L], offhalf[L];
vector<ll> start[L];
vector<int> idx[L];
int other[L];
int firstv;

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(10);

  fill(zm, zm+2*N, 1);
  fill(other, other+L, -1);

  int T;
  cin >> T;

  start[0].push_back(0);
  idx[0].push_back(0);
  firstv = 0;

  int gid = 0;
  while (T--) {
    int t;
    cin >> t;

    if(t == 1) {
      int k;
      cin >> k;
      if(k > 0) {
        update_add(0, gid++, k);
        for(int j=0; j<L; j++) {
          offset[j] += k;
          offhalf[j] += k;
        }
        start[0].push_back(-offset[0]);
        idx[0].push_back(gid);
        firstv = gid;
      }

      else {
        update_mul(0, gid++, 2);
        insert_am(gid, 1, 2);
        for(int j=L-1; j>0; j--) {
          offset[j] = 0;
          start[j].clear();
          idx[j].clear();
          for(int i=0; i<start[j-1].size(); i++) {
            ll actual = 2 * (start[j-1][i] + offset[j-1]);
            if(actual < INF) {
              start[j].push_back(actual);
              idx[j].push_back(idx[j-1][i]);
            }
          }
          other[j] = other[j-1];
          offhalf[j] = offhalf[j-1] * 2;
          if(offhalf[j] >= INF) {
            offhalf[j] = INF;
            other[j] = -1;
          }
        }
        offset[0] = 0;
        start[0].clear();
        idx[0].clear();
        other[1] = gid;
        offhalf[1] = 1;
      }

      //cerr<<"after update "<<t<<" "<<k<<nl; for(int j=0; j<5; j++) {
      //cerr<<j<<": offset "<<offset[j]; assert(start[j].size() == idx[j].size());
      //cerr<<nl; for(int i=0; i<start[j].size(); i++) {
      //cerr<<idx[j][i]<<" w/ s = "<<start[j][i] + offset[j]<<nl; }
      //cerr<<"got other idx = "<<other[j]<<" at "<<offhalf[j]<<nl;
      //cerr<<nl; }
      //cerr<<nl;
    }

    else if(t == 2) {
      int g, x;
      cin >> g >> x;
      ll s, len;
      tie(s,len) = query_pl(g);
      ////cerr<<"s,len = "<<s<<" "<<len<<nl;
      cout << (s + len*(x-1)) % MOD << nl;
    }

    else {
      int x;
      cin >> x;
      int res = firstv;
      for(int j=L-1; j>=0; j--) {
        assert(start[j].size() == idx[j].size());
        if(!start[j].empty()) {
          ll first = start[j].back() + offset[j];
          ll mod = (x-first) % (1LL<<j);
          if(first <= x && mod == 0) {
            ////cerr<<"mod = 0"<<nl;
            auto it = lower_bound(start[j].begin(), start[j].end(), x-offset[j], greater<ll>());
            assert(it != start[j].end());
            res = idx[j][it-start[j].begin()];
            break;
          }
        }
        if(other[j] != -1) {
          ll first = offhalf[j];
          ll mod = (x-first) % (1LL<<j);
          if(first <= x && mod == 0) {
            ////cerr<<"other"<<nl;
            res = other[j];
            break;
          }
        }
      }
      assert(res != -1);
      cout << res << nl;
      cerr<<endl;
    }
  }

  return 0;
}
