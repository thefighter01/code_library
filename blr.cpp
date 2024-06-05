struct blr{
    vector <ll > B1 , B2; int n;
    void init(int _n){
        n = _n+10;
        B1 = B2 = vector <ll > (n+50);
    }
    ll qu(ll b){
        ll ans = 0;
        for (int i = b ; i; i-= i & -i) ans+= B1[i];
        ans = ans * b;
        for (int i = b; i; i-= i & -i) ans-=B2[i];
        return ans;
    }
    void upd(ll l , ll r , ll v){
        ++l; ++r;
        for (int i = l ; i <= n; i+= i & -i) B1[i]+=v;
        for (int i = l; i <= n; i+= i & -i) B2[i]+=(l-1) *v;
        for (int i = r+1; i <= n; i+= i & -i) B1[i]-=v;
        for (int i = r+1; i <= n; i+= i & -i) B2[i]-= v *r;
    }

    ll query(int l , int r) {
        ++l , ++r;
        return qu(r) - qu(l-1);
    }
};
