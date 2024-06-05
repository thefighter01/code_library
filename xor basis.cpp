

struct basis{ // take care of the size of the basis and the data type // can u use timer idea to solve subarray queries
    int sz;
    array < int , LOG+1 > d;//T
    basis(){
        sz  = 0; for (int b = 0 ; b <= LOG; ++b) d[b] = 0;
    }
    bool bit(int mask, int i){
        return (mask >> i) & 1;
    }
    void push(int mask){
        for (int b = LOG ; b >= 0 ; -- b){
            if (!bit(mask, b)) continue;
            if (!d[b]){
                d[b] = mask; ++sz;
                return;
            }
            mask ^= d[b];
        }
    }
    ll max_xor(){
        ll ans = 0;
        for (int b = LOG; b >= 0 ; --b){
            if (!bit(ans , b) && d[b]) ans^= d[b];
        }
        return ans;
    }
    bool check (int mask){
        for (int b = LOG; b >= 0 ; --b){
            if (!bit(mask , b)) continue;
            if (!d[b]) return false;
            mask^= d[b];
        }
        assert(!mask);
        return true;
    }
    ll kth(int k){ // k th in sorted array , k <= 2 ^ sz
        ll mask = 0;
        ll tot = (1 << sz); assert(k <= tot);
        for (int b = LOG; b >= 0 ; --b){
            if (d[b]) {
                ll low = tot >> 1;
                if ((bit(mask, b) && k <= low) || (!bit(mask, b) && k > low)) mask ^= d[b];
                if (k > low) k -= low;
                tot = low;
            }
        }
        return mask;
    }
    bool empty() {return !sz;}
};
