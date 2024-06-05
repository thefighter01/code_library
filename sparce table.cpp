struct sp {
    vector<vector<int> > table;
    int n , mood;
    int merge(int u, int v) {
        return mood ? max(u , v) : min(u , v);
    }
    void init(vector<int> & a , int m) {
        n = (int)a.size();mood = m;
        table = vector < vector<int > > (n , vector<int > (LOG+1));
        for (int i = 0; i < n; ++i) table[i][0] = a[i];
        for (int j = 1; j < LOG; ++j) {
            for (int i = 0; i + (1 << j) <= n ; ++i){
                table[i][j] = merge(table[i][j-1]  , table[i + (1 << (j-1))][j-1]);
            }
        }
    }

    int query(int L , int R){
        int d = 31-clz(R-L+1);
     //   cout << "uuu " << L <<" " << R << " " << d << " " << mood <<" "<< table[L][d] << endl;
        return merge(table[L][d]  , table[R-(1 << d)+1][d]);
    }

};
