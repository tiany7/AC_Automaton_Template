#include <bits/stdc++.h>
using namespace std;
#define limit (500000 + 5)//防止溢出
#define INF 0x3f3f3f3f
#define inf 0x3f3f3f3f3f
#define lowbit(i) i&(-i)//一步两步
#define EPS 1e-6
#define FASTIO  ios::sync_with_stdio(false);cin.tie(0);
#define ff(a) printf("%d\n",a );
#define pi(a,b) pair<a,b>
#define rep(i, a, b) for(int i = a; i <= b ; ++i)
#define per(i, a, b) for(int i = b ; i >= a ; --i)
#define mint(a,b,c) min(min(a,b), c)
#define MOD 998244353
#define FOPEN freopen("C:\\Users\\tiany\\CLionProjects\\acm_01\\data.txt", "rt", stdin)
typedef long long ll;
typedef unsigned long long ull;
ll read(){
    ll sign = 1, x = 0;char s = getchar();
    while(s > '9' || s < '0' ){if(s == '-')sign = -1;s = getchar();}
    while(s >= '0' && s <= '9'){x = x * 10 + s - '0';s = getchar();}
    return x * sign;
}//快读
void write(ll x){
    if(x < 0) putchar('-'),x = -x;
    if(x / 10) write(x / 10);
    putchar(x % 10 + '0');
}
int n;
int trie[limit][26], fail[limit],cnt[limit],tot = 0;
struct node{
    #define ALPHA 25

    void insert(char *s){
        int root = 0;
        int len = strlen(s);
        rep(i , 0 ,len - 1){
            int val = s[i] - 'a';
            if(!trie[root][val])trie[root][val] = ++tot;
            root = trie[root][val];
        }
        ++cnt[root];
    }
    void build(){
        queue<int>q;
        rep(i ,0 , ALPHA){
            if(trie[0][i])fail[trie[0][i]] = 0, q.push(trie[0][i]);
        }
        while (q.size()){
            int u = q.front();
            q.pop();
            rep(i , 0 ,ALPHA){
                if(trie[u][i]){
                    fail[trie[u][i]] = trie[fail[u]][i];
                    q.push(trie[u][i]);
                }else{
                    trie[u][i] = trie[fail[u]][i];
                }
            }
        }
    }
    int operator[](char * s){
        int len = strlen(s);
        int root = 0 , ans = 0;
        rep(i, 0 , len - 1){
            root = trie[root][s[i] - 'a'];
            for(int t = root; t && cnt[t] != -1; t = fail[t]){
                ans += cnt[t];
                cnt[t] = -1;
            }
        }
        return ans;
    }
};
char str[limit];
node AC_Automaton;
int main() {
#ifdef LOCAL
    FOPEN;
#endif
    n = read();
    rep(i ,1, n){
        scanf("%s", str);
        AC_Automaton.insert(str);
    }
    AC_Automaton.build();
    scanf("%s", str);
    write(AC_Automaton[str]);
    return 0;
}