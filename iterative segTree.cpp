#include <iostream>
#include <cstdlib>
using namespace std;
const int n = 1<<18;
int t[2*n];
int h = sizeof(int) * 8 - __builtin_clz(n);
int d[n];  
void apply(int p, int value) {
    t[p] += value;
    if (p < n) d[p] += value;
}

void build(int p) {
    while (p > 1) p >>= 1, t[p] = max(t[p<<1], t[p<<1|1]) + d[p];
}

void push(int p) {
    for (int s = h; s > 0; --s) {
        int i = p >> s;
        if (d[i] != 0) {
            apply(i<<1, d[i]);
            apply(i<<1|1, d[i]);
            d[i] = 0;
        }
    }
}

void inc(int l, int r, int value) {
    l += n, r += n;
    int l0 = l, r0 = r;
    for (; l < r; l >>= 1, r >>= 1) {
        if (l&1) apply(l++, value);
        if (r&1) apply(--r, value);
    }
    build(l0);
    build(r0 - 1);
}

int query(int l, int r) {
    l += n, r += n;
    push(l);
    push(r - 1);
    int res = -2e9;
    for (; l < r; l >>= 1, r >>= 1) {
        if (l&1) res = max(res, t[l++]);
        if (r&1) res = max(t[--r], res);
    }
    return res;
}

int main() {
    ios_base::sync_with_stdio(0);
    for(int i = 0; i < 1e7; ++i) {
        if(rand()&1) {
            int q = rand()%n;
            int w = rand()%n;
            if(q > w) swap(q, w);
            int e = rand()%100;
            inc(q, w+1, e);
        }
        else {
            int q = rand()%n;
            int w = rand()%n;
            if(q > w) swap(q, w);
            int ans = query(q, w+1);;
            cout<<ans<<'\n';
        }
    }
}
