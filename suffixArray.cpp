 
 
struct suffixArray{
    int n; string s;
    vector <int > lcp , suf , ord;
    vector<vector<int> > table;
    void init() {
        table = vector < vector<int > > (n , vector<int > (LOG+1));
        for (int i = 0; i < n; ++i) table[i][0] = lcp[i];
        for (int j = 1; j < LOG; ++j) {
            for (int i = 0; i + (1 << j) <= n ; ++i){
                table[i][j] = min(table[i][j-1]  , table[i + (1 << (j-1))][j-1]);
            }
        }
    }
 
    int query(int L , int R){ // query by position on array c .. takecare of the data you send
        assert(L <= R);
        int d = 31-clz(R-L+1);
        return min(table[L][d]  , table[R-(1 << d)+1][d]);
    }
    void read(string & _s){ // empty suffix contains # or " or [
        s = _s; s+='[';
        n = (int)s.size();
        lcp = vector <int > (n);
        build();
    }
 
    void countSort(vector<int > & p , vector <int > & c){
        vector <int > cnt(n);
        for (auto &i : c) cnt[i]++;
        vector <int >pos(n);
        for (int i = 1; i < n; ++i) pos[i] = pos[i-1] + cnt[i-1];
        vector <int > newP(n);
        for (auto &i : p){
            newP[pos[c[i]]++] = i;
 
        }
        p = newP;
    }
 
    void build(){
        vector < pair <char , int > > a(n);
        for (int i = 0; i < n; ++ i) a[i] = {s[i] , i};
        sort(all(a));
        vector <int > p(n) , c(n);
        for (int i = 0; i < n; ++i) p[i] = a[i].second;
        for (int i = 1; i < n; ++i) c[p[i]] = c[p[i-1]] + (a[i].first != a[i-1].first);
 
        for (int k = 0; (1 << k) < n; ++k){ // k - > k+1
            int bit = (1 << k);
            vector <int > newC(n);
            for (int i = 0; i < n; ++i) p[i] = (p[i] - bit + n) % n;
            countSort(p , c);
            for (int i = 1; i < n; ++i){
                pair<int , int > cur {c[p[i]] , c[(p[i] + bit)% n]};
                pair<int , int > prev = {c[p[i-1]] , c[(p[i-1] + bit ) %n]};
                newC[p[i]] = newC[p[i-1]] + (cur != prev);
            }
            c = newC;
 
        }
        ord = c;
 
        for (int i = 0 , k =0 ; i +1< n; ++i , k = max(0 , k-1)){
            int pi = c[i];
            int j = p[pi-1];
            while(s[i+k] == s[j+k]) ++k;
            lcp[pi] = k;
        }
        suf = p;
        init();
    }
    int lcpAt(int i){
        return lcp[i];
    }
    int orderOf(int i){
        return ord[i];
    }
    int suffixAt(int i){
        return suf[i];
    }
    }
 
 
 
};
 
