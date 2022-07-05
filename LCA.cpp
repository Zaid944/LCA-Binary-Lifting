#include <bits/stdc++.h>
using namespace std;
#define int long long
#define mod 1000000007
vector<vector<int>> tim;
int cntr = 0;
vector<vector<int>> dp;
vector<int> height;
void dfs(vector<vector<int>> &tree, int src, int par, int h)
{
    cntr++;
    tim[src][0] = cntr;
    dp[src][0] = par;
    height[src] = (int)log2(h);
    for (int i = 1; i <= (int)log2(h); i++)
    {
        dp[src][i] = dp[dp[src][i - 1]][i - 1];
    }
    for (int i = 0; i < tree[src].size(); i++)
    {
        if (tree[src][i] != par)
        {
            dfs(tree, tree[src][i], src, h + 1);
        }
    }
    cntr++;
    tim[src][1] = cntr;
}
bool is_ancestor(int u, int v)
{
    // u is ancestor of v
    return tim[u][0] <= tim[v][0] and tim[u][1] >= tim[v][1];
}
int query(int u, int v)
{
    if (is_ancestor(u, v))
        return u;
    else if (is_ancestor(v, u))
        return v;
    else
    {
        for (int i = height[u]; i >= 0; i--)
        {
            if (!is_ancestor(dp[u][i], v))
            {
                return query(dp[u][i], v);
            }
        }
        return dp[u][0];
    }
}
void Solve()
{
    int n;
    cin >> n;
    int x = (int)log2(n) + 1;
    dp.resize(n, vector<int>(x));
    height.resize(n, 0);
    tim.resize(n, vector<int>(2));
    vector<vector<int>> tree(n);
    for (int i = 0; i < n; i++)
    {
        int sz;
        cin >> sz;
        for (int j = 0; j < sz; j++)
        {
            int v;
            cin >> v;
            v--;
            tree[i].push_back(v);
            tree[v].push_back(i);
        }
    }
    dfs(tree, 0, -1, 0);
    int q;
    cin >> q;
    while (q--)
    {
        int u, v;
        cin >> u >> v;
        u--, v--;
        cout << query(u, v) + 1 << endl;
    }
}
int inc = 1;
void google()
{
    cout << "Case " << inc << ":" << endl;
    inc++;
}
int32_t main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t = 1;
    cin >> t;
    while (t--)
    {
        google();
        Solve();
    }
}