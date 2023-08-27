#include <bits/stdc++.h>

using namespace std;

const uint64_t MOD = 1e9 + 7;
const uint64_t CHUNK = 100000000000;
uint64_t N = 0, M = 0;
uint64_t s = 0;
uint64_t prevN = 0;
uint64_t currentNumber = 0;
uint64_t add = 0;
uint64_t digit = 0;
int t = 0;

unordered_map<uint64_t, uint64_t> nextMonoMap;


uint64_t generateNextMonotone(uint64_t num) {
    int count = 0;
    while (true) {
        digit = num % 10;
        if (digit == 9) {
            num /= 10;
            ++count;
        }
        else {
            num += 1;
            digit = num % 10;
            for (int i = 0; i < count; ++i)
                num = num * 10 + digit;

            return num;
        }
    }
}

uint64_t monotoneIncreasingDigits(uint64_t num) {
    uint64_t tmp = num, nineSum = 9, base = 10;
    uint64_t pre = tmp % 10;
    uint64_t sum = pre;
    uint64_t cur = 0;
    uint64_t add2 = 0;
    tmp /= 10;
    while (tmp)
    {
        cur = tmp % 10;
        sum += base * cur;

        if (cur > pre)
        {
            add2 = base * (cur - 1);
            num = num - sum + base * (cur - 1) + nineSum;
            sum = base * (cur - 1) + nineSum;
            pre = cur - 1;
        }
        else
        {
            pre = cur;
        }

        tmp /= 10;
        base *= 10;
        nineSum = nineSum * 10 + 9;
    }

    return num;
}



void input()
{
    cin >> N >> M;
}

uint64_t solve(uint64_t a, uint64_t b)
{
    uint64_t res = 0;
    currentNumber = monotoneIncreasingDigits(a);
    if (a == b)
        res = currentNumber % MOD;
    prevN = currentNumber;

    while (a < b)
    {
        currentNumber = generateNextMonotone(currentNumber);
        //currentNumber = nextMonoMap[currentNumber];
        if (currentNumber <= b)
        {
            add = ((prevN % MOD) * ((currentNumber - a) % MOD)) % MOD;
            res = (res + add) % MOD;

            if (currentNumber == b)
                res = (res + (currentNumber % MOD)) % MOD;

            prevN = a = currentNumber;
        }
        else
        {
            add = ((prevN % MOD) * ((b - a + 1) % MOD)) % MOD;
            res = (res + add) % MOD;
            prevN = a = currentNumber;
        }
    }

    return res;
}

void solve2()
{
    s = 0;

    if (N == M)
    {
        s = monotoneIncreasingDigits(N) % MOD;
    }
    else if (M - N <= CHUNK)
    {
        s = solve(N, M);
    }
    else
    {
        if (M % CHUNK == 0)
        {
            if (N % CHUNK == 0)
            {
                s = monotoneIncreasingDigits(N) % MOD;
                for (auto i = N + CHUNK; i <= M; i += CHUNK)
                {
                    s = (s + nextMonoMap[i]) % MOD;
                }
            }
            else
            {
                uint64_t upper_N = N + (CHUNK - (N % CHUNK));

                s = solve(N, upper_N);
                for (auto i = upper_N + CHUNK; i <= M; i += CHUNK)
                {
                    s = (s + nextMonoMap[i]) % MOD;
                }
            }
        }
        else
        {
            if (N % CHUNK == 0)
            {
                uint64_t lower_M = M - (M % CHUNK);

                s = solve(lower_M + 1, M);

                s = (s + (monotoneIncreasingDigits(N) % MOD)) % MOD;
                for (auto i = N + CHUNK; i <= lower_M; i += CHUNK)
                {
                    s = (s + nextMonoMap[i]) % MOD;
                }
            }
            else
            {
                uint64_t upper_N = N + (CHUNK - (N % CHUNK));
                uint64_t lower_M = M - (M % CHUNK);

                s = solve(N, upper_N);
                s = (s + solve(lower_M + 1, M))%MOD;

                for (auto i = upper_N + CHUNK; i <= lower_M; i += CHUNK)
                {
                    s = (s + nextMonoMap[i]) % MOD;
                }
            }
        }
    }
}

void print()
{
    cout << s;
    if (t > 0) cout << "\n";

}
void init()
{
    N = 1; M = CHUNK;
    while (M <= 1e18)
    {
        nextMonoMap[M] = solve(N, M);
        N = M + 1;
        M += CHUNK;
    }
}

static int dummy = (init(), 0);
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    system("pause");
    cin >> t;

    while (t--)
    {
        input();
        solve2();
        print();
    }



    return 0;
}
