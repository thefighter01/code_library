ll ecuild(ll a , ll b , ll &x0 , ll & y0){
    auto nxt =[&](ll &x , ll &y , ll q){
        ll next = x - q * y;
        x = y;
        y = next;
    };
    ll r0 , r1 , x1 , y1;
    r0 = a , r1 = b , x0 = y1 = 1 , y0 = x1 = 0;
    while (r1){
        ll q = r0 / r1;
        nxt(r0 , r1 , q);
        nxt(x0 , x1 , q);
        nxt(y0 , y1 , q);
    }
    return r0;
}
 
 
ll de(ll a , ll b , ll c , ll &x0 , ll &y0){
    ll g = ecuild(abs(a) , abs(b) , x0 , y0);
    if (c % g) return -1;
    x0*= c/g;
    y0*= c/g;
    a >= 0 ? x0*=1 : x0*=-1;
    b >= 0 ? y0*=1 : y0*=-1;
    return g;
}
// solve ax is congruent to n in space mod
// a x + b mod is congruent to n in space mod
// a ( x0 + k * b/g ) + b (y0 - k * a/g ) = n
pair<int , array<ll, 2 > > get_range(ll a , ll b , ll n ){ 
    ll x0 , y0;
    ll g = de(a , b , n, x0 , y0);
    if (g == -1) return {0 , {-1 , -1}};
    // mn 0 , mx = n
    a/=g , b/=g;
    // mnx - x0 <= k * b <= mxx-x0
    ll lx = ceil(-x0/1.0 / b);
    ll rx = floor((n-x0) *1.0 / b);
    // -mny +y0 >=  k * a >= -mxy +y0
    ll ly = ceil((y0 -n) *1.0 / a);
    ll ry = floor(y0 *1.0/a);
    ll L = max(lx , ly);
    ll R = min(rx , ry);
    if (L > R) return {0 , {-1 , -1}};
    return {1 , {L , R}};
}
ll modInv(ll n , ll m){ ll c , no;
    ll g = ecuild(n , m , c , no);
    if (g != 1) return -1;
    /* 11 -- > mod //  -4 %11 = -4 but it mst be 7
   n = bq +r // -4 = 0 *11 -4
   but another solution is // -4 = -1*11 +7
    */
    return (c  % m + m ) % m;
}
/*  the system is solvable if and only if
 *  case 1) all mods are pairwise gcd
 *  case 2) every ai is congruent to aj mod gcd(ni , nj)
 */
ll solve_relative_primes(vector <ll > & mods , vector <ll > & rems){ // if and only if all mods are pairwise gcd
    ll lc = 1;
    for (auto &c : mods) lc*= c;
    ll x = 0;
    for (int i = 0; i < (int)mods.size(); ++i) x+= lc/ mods[i] * rems[i] * modInv(lc/ mods[i] , mods[i]);
    return x % lc;
}
 
ll solve(vector <ll > & mods , vector <ll > & rems){ // every ai is congruent to aj mod gcd(ai , agj) // nasted
    ll rem = rems[0]; ll Mod = mods[0];
    // T is congruent to x Mod n which means T % n is equal to x % n
    // T is congruent to y mod m
    // T = k * n + x // T = p * m + y
    // k * n + x = p * m + y
    // k * n - p * m = y - x
    for (int i = 1; i < (int)mods.size(); ++i){
        ll x , y , a  = Mod , b = -mods[i] , c = rems[i] - rem;
        ll g = de(a , b , c , x , y); if (g == -1 || rem % g != rems[i] % g) return -1;
        assert(x * a + b * y == c);
        rem+= x * Mod;
        Mod = Mod / g * mods[i];  // new mod is the lcm
        rem = (rem % Mod + Mod) % Mod;
    }
    return rem;
 
}
