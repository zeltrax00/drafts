#include <bits/stdc++.h>
using namespace std;

const uint64_t MOD = 1e9 + 7;
uint64_t N = 0, M = 0;
uint64_t s = 0;
uint64_t prevN = 0;
uint64_t currentNumber = 0;
uint64_t add = 0;

int t = 0;

unordered_map<uint64_t, uint64_t> nextMonoMap;


uint64_t generateNextMonotone(uint64_t num) {
    int count = 0;
    while (true) {
        uint64_t digit = num % 10;
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

void init()
{
    uint64_t cu = 0, pr = 0;
    while (cu < 1e19)
    {
        pr = cu;
        cu = generateNextMonotone(cu);
        nextMonoMap[pr] = cu;
    }

}

static int dummy = (init(), 0);


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    //freopen("input.txt", "r", stdin);

    cin >> t;

    while (t--)
    {
//        auto start = chrono::steady_clock::now();
        s = 0;
        cin >> N >> M;

        currentNumber = monotoneIncreasingDigits(N);
        if (N == M)
            s = currentNumber % MOD;
        prevN = currentNumber;

        while (N < M)
        {
            //currentNumber = generateNextMonotone(currentNumber);
            currentNumber = nextMonoMap[currentNumber];
            if (currentNumber <= M)
            {
                add = ((prevN % MOD) * ((currentNumber - N) % MOD)) % MOD;
                s = (s + add) % MOD;

                if (currentNumber == M)
                    s = (s + (currentNumber % MOD)) % MOD;

                prevN = N = currentNumber;
            }
            else
            {
                add = ((prevN % MOD) * ((M - N + 1) % MOD)) % MOD;
                s = (s + add) % MOD;
                prevN = N = currentNumber;
            }
        }
        cout << s;
        if (t > 0) cout << "\n";

    }

    return 0;
}
