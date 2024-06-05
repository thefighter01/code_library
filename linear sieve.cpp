int lp[N], f[N], p[N], id[N] , ids;
vector <int > primes;
void init(){
    for (int i = 2 ; i <= 70; ++i){
        if (!lp[i]) lp[i] = i, primes.push_back(i), id[i] = ids++;
        for (auto &pr : primes){
            if (pr > lp[i] || i * pr > 70) break;
            lp[i * pr] = pr;
        }
    }
    p[0] = 1;
    for (int i = 1; i < N; ++i) p[i] = mul(2 , p[i-1] , mod);
}

vector < array < int , 2 > > fa(int n){
    vector < array < int , 2 > > ans;
    while(n > 1){
        if (ans.empty() || ans.back()[0] ^ lp[n]) ans.push_back({lp[n] , 1});
        else ans.back()[1]++;
        n/=lp[n];
    }
    return ans;
}

int turn (vector < array < int ,2  >> d){
    int mask = 0;
    for(auto [a , b] : d) if (b & 1) mask |= (1 << id[a]);
    return mask;
}