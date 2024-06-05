ll p1[N], p2[N] , inv[N] , inv2[N]; 
vector <ll > primes = {999999937 ,999999929 ,999999893 ,999999883, 999999797 ,999999761 ,999999757 ,999999751, 999999739 ,999999733 ,999999677 ,999999667 ,999999613, 999999607 ,999999599, 999999587, 999999541 ,999999527 ,999999503 ,999999491 ,999999487, 999999433, 999999391 ,999999353 ,999999337, 999999323 ,999999229, 999999223, 999999197, 999999193 ,999999191 ,999999181 ,999999163 ,999999151 ,999999137 ,999999131 ,999999113 ,999999107 ,999999103 ,999999067 ,999999059 ,999999043, 999999029 ,999999017 ,999999001, 999998981 ,999998971 ,999998959, 999998957 ,999998929 ,999998921  };
void init(){
    // create 1e5 primes and choose 4 random values from them 
    p2[0] = inv2[0] = p1[0] = inv[0] = 1;
    B1 = primes[rand(0 , 49)];
    B2 = primes[rand(0 , 49)];
    ll Inv = modInv(B1 , mod);
    ll Inv2 = modInv(B2 , mod2);
    for (ll i = 1; i < N ; ++i){
        p1[i] = mul(p1[i-1] , B1 , mod);
        inv[i] = mul(inv[i-1] , Inv , mod);
        p2[i] = mul(p2[i-1] , B2 , mod2);
        inv2[i] = mul(inv2[i-1] , Inv2 , mod2);
    }
}
struct Hash{
    int n;
    vector <array<ll,2 > > pre;
    void build(string & s){
        n = (int)s.size();
        pre = vector <array<ll,2 > > (n+5);
        pre[0][0] = pre[0][1]= s[0] - 'a'+1;
        for (int i = 1; i < n; ++i){
            pre[i][0] = add(pre[i-1][0] , mul(s[i]-'a'+1 , p1[i] , mod) , mod);
            pre[i][1] = add(pre[i-1][1] , mul(s[i]-'a'+1 , p2[i] , mod2) , mod2);
        }
    }
    array<ll , 2 > query(ll l , ll r){ // zero based inclusive
        array<ll,2 > ans;
        ans[0] = add(pre[r][0] , (l ? -pre[l-1][0] : 0) , mod);
        ans[1] = add(pre[r][1] , (l ? - pre[l-1][1] : 0) , mod2);
        ans[0] = mul(ans[0] , inv[l] , mod);
        ans[1] = mul(ans[1] , inv2[l] , mod2);
        return ans;
    }
 
};
 
