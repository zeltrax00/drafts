#include <bits/stdc++.h>

using namespace std;

const long long bs = 1000000007;

int dummy = []
{
    freopen("input", "r", stdin);
    freopen("output", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    return 0;
}();

const int max_size = 100000 + 10;
long long d[max_size];
long long r[max_size];
long long n;
string s;
long long up, down;

bool process(long long hp)
{
    for (int i = 0; i < n; ++i)
    {
        hp -= d[i];
        if (hp <= 0)
            return false;
        if (s[i] == '*')
            hp *= r[i];
        else
            hp += r[i];
    }

    return true;
}

int main(void)
{
    int t = 0;
    cin >> t;
    while (t--)
    {
        n = up = down = 0;
        memset(d, 0, max_size);
        memset(r, 0, max_size);
        cin >> n;
        for (int i = 0; i < n; ++i)
        {
            cin >> d[i];
            up += d[i];
            if (d[i] > down)
                down = d[i];
        }
        up += 1;
        getline(cin, s);
        s.clear();
        getline(cin, s);
        for (int i = 0; i < n; ++i)
        {
            cin >> r[i];
        }
        long long hp;
        long long finalhp;
        while (down <= up)
        {
            
            hp = down + (up - down) / 2;
            if (process(hp))
            {
                finalhp = hp;
                up = hp - 1;
            }
            else
            {
                down = hp + 1;

            }
        }

        cout << finalhp << '\n';
    }
    return 0;
}
