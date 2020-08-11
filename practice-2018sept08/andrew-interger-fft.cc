#include <bits/stdc++.h>
using namespace std;
typedef long double ld;
typedef long long ll;
typedef complex<ld> Complex;

typedef vector<ll> poly;

const ll mod=(15<<27)+1;
const ll N=1<<27;
const ll wF=440564289,wB=1713844692;
ll power(ll b, ll e){
    if (e==0) return 1;
    if (e==1) return b;
    ll ans=power(b,e/2);
    ans=(ans*ans)%mod;
    if (e%2) ans=(ans*b)%mod;
    return ans;
}
poly eval(poly &v, ll w){ //returns the evaluation of v[i]x^i at the n roots of unity w^i for i = 0, ..., n-1
    int n=v.size();
    if (n==1) return v;
    ll curr=1;
    poly p1,p2;
    for (int i=0;i<n;i++){
        if (i%2==0) p1.push_back(v[i]);
        else p2.push_back(v[i]);
    }
    ll nw=(w*w)%mod;
    poly v1=eval(p1,nw),v2=eval(p2,nw);
    poly res(n,0);
    for (int i=0;i<n/2;i++){
        res[i]=(v1[i]+(curr*v2[i])%mod)%mod;
        res[i+(n/2)]=(v1[i]-(curr*v2[i])%mod+mod)%mod;
        curr=(curr*w)%mod;
    }
    return res;
}
poly mult(poly p1, poly p2){
    int sz = p1.size()+p2.size()-1;
    int n  = 1<<int(ceil(log2(sz)));
    while (p1.size()<n) p1.push_back(0);
    while (p2.size()<n) p2.push_back(0);
    ll f=wF,b=wB;
    for (ll k=n;k!=N;k=k<<1) f=(f*f)%mod,b=(b*b)%mod;
    
    poly e1=eval(p1,f),e2=eval(p2,f);
    poly e3;
    for (int i=0;i<e1.size();i++) e3.push_back((e1[i]*e2[i])%mod);
    poly res=eval(e3,b);
    ll inv=power(n,mod-2);
    for (int i=0;i<res.size();i++) res[i]=(res[i]*inv)%mod;
    return res;
}
poly a,b,ans; 
int main(){
    ios::sync_with_stdio(0);
    int t; cin>>t;
    while (t--){
        a.clear(); b.clear(); ans.clear();
        string s;
        cin>>s;
        for (int i=s.size()-1;i>=0;i--) a.push_back(s[i]-'0');
        cin>>s;
        for (int i=s.size()-1;i>=0;i--) b.push_back(s[i]-'0');
        ans=mult(a,b);
        for (int i=0;i+1<ans.size();i++){
            ans[i+1]+=int(ans[i]/10);
            ans[i]%=10;
        }
        while ((ans[ans.size()-1]==0)&&(ans.size()>1)) ans.pop_back();
        for (int i=ans.size()-1;i>=0;i--) cout<<ans[i];
        cout<<endl;
    }
    return 0;
}