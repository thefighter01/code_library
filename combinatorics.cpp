ll f[N] , fi[N];
void init(){
    f[0] = fi[0] = 1;
    for (int i = 1; i < N; ++i){
        f[i] = mul(f[i-1] , i , mod2);
        fi[i] = modInv(f[i] , mod2);
    }
}
 
ll npr(int n , int r){
    if (r > n || r < 0) return 0;
    return mul(f[n] , fi[n - r] ,mod2);
}
ll ncr (int n , int r){
    if (r > n || r <0 ) return 0;
    return mul(npr(n , r) , fi[r] , mod2);
}