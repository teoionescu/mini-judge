#include <iostream>
#include <fstream>
#include <vector>
#include <cassert>
 
using namespace std;
 
struct bigint {
    bigint(int x = 0) {
        while (x > 0) {
            digits.push_back(x % 2);
            x /= 2;
        }
    }
 
    bigint& operator*=(int x) {
        int rest = 0;
        for (int i = 0; i < int(digits.size()); ++i) {
            rest += digits[i] * x;
            digits[i] = rest % 2;
            rest /= 2;
        }
        while (rest > 0) {
            digits.push_back(rest % 2);
            rest /= 2;
        }
        return *this;
    }
 
    bigint& operator/=(int x) {
        int rest = 0;
        for (int i = digits.size() - 1; i >= 0; --i) {
            rest = rest * 2 + digits[i];
            digits[i] = rest / x;
            rest %= x;
        }
        while (!digits.empty() && digits.back() == 0)
            digits.pop_back();
        return *this;
    }
 
    bigint& operator+=(const bigint& that) {
        int rest = 0;
        for (int i = 0; i < int(digits.size()) || i < int(that.digits.size()) || rest; ++i) {
            if (i < int(digits.size()))
                rest += digits[i];
            if (i < int(that.digits.size()))
                rest += that.digits[i];
            if (i < int(digits.size()))
                digits[i] = rest % 2;
            else
                digits.push_back(rest % 2);
            rest /= 2;
        }
        return *this;
    }
 
    bool operator<=(const bigint& that) const {
        if (digits.size() != that.digits.size())
            return digits.size() < that.digits.size();
        for (int i = digits.size() - 1; i >= 0; --i)
            if (digits[i] != that.digits[i])
                return digits[i] < that.digits[i];
        return true;
    }
 
    bigint& operator-=(const bigint& that) {
        int rest = 0;
        for (int i = 0; i < int(digits.size()); ++i) {
            digits[i] = digits[i] + rest;
            if (i < int(that.digits.size()))
                digits[i] -= that.digits[i];
            if (digits[i] < 0) {
                digits[i] += 2;
                rest = -1;
            } else
                rest = 0;
        }
        while (!digits.empty() && digits.back() == 0)
            digits.pop_back();
        return *this;
    }
 
    vector<int> digits;
};
 
string encode(vector<int> freq, int N) {
    bigint comb(1); // we start from the total anwer which is Comb(N + K - 1, K - 1)
    int K = freq.size();
    for (int i = N + 1; i <= N + K - 1; ++i)
        comb *= i;
    for (int i = 1; i <= K - 1; ++i)
        comb /= i;
 
    bigint answer = 0;
    int A = N + K - 1;
    int B = K - 1;
    auto decrease = [&](int newA, int newB) {
        while (B > newB) {
            comb *= B;
            --B;
            comb /= (A - B);
        }
 
        while (A > newA) {
            comb *= (A - B);
            if (A > 0)
                comb /= A;
            --A;
        }
    };
 
    for (int i = 0; i < K - 1; ++i) {
        decrease(A - 1, B - 1);
        for (int j = 0; j < freq[i]; ++j) {
            // we count with this here, second part decreases, and so does first
            answer += comb;
            decrease(A - 1, B);
        }
    }
    string binary;
    for (int i = 0; i < int(answer.digits.size()); ++i)
        if (answer.digits[i] == 1)
            binary += '1';
        else
            binary += '0';
    return binary;
}
 
vector<int> decode(string binary, int K, int N) {
    bigint answer;
    for (auto &c : binary)
        answer.digits.push_back(c - '0');
    while (!answer.digits.empty() && answer.digits.back() == 0)
        answer.digits.pop_back();
 
    bigint comb(1);
    for (int i = N + 1; i <= N + K - 1; ++i)
        comb *= i;
    for (int i = 1; i <= K - 1; ++i)
        comb /= i;
 
    int A = N + K - 1;
    int B = K - 1;
    auto decrease = [&](int newA, int newB) {
        while (B > newB) {
            comb *= B;
            --B;
            comb /= (A - B);
        }
 
        while (A > newA) {
            comb *= (A - B);
            if (A > 0)
                comb /= A;
            --A;
        }
    };
 
    vector<int> freq(K, 0);
    for (int i = 0; i < K - 1; ++i) {
        decrease(A - 1, B - 1);
        for (int j = 0; j < N; ++j) {
            if (comb <= answer)
                answer -= comb;
            else
                break;
            // we count with this here, second part decreases, and so does first
            ++freq[i];
            decrease(A - 1, B);
        }
    }
 
    for (int i = 0; i < K - 1; ++i)
        N -= freq[i];
    freq[K - 1] = N;
    return freq;
}
 
int main() {
    ifstream cin("op.in");
    ofstream cout("op.out");
 
    int tip; assert(cin >> tip);
    assert(1 <= tip && tip <= 2);
    if (tip == 1) {
        int K, N; assert(cin >> K >> N);
        assert(1 <= K && K <= 1500);
        assert(1 <= N && N <= 5000);
        vector<int> frequencies(K, 0);
        for (int i = 0; i < N; ++i) {
            int x; cin >> x;
            --x;
            frequencies[x]++;
        }
        cout << encode(frequencies, N) << "\n";
    } else {
        int K, N, M; assert(cin >> K >> N >> M);
        assert(1 <= K && K <= 1500);
        assert(1 <= N && N <= 5000);
        assert(N < M && M <= 1000000);
        string binary; assert(cin >> binary);
        for (auto &c : binary)
            assert(c == '0' || c == '1');
        vector<int> frequencies = decode(binary, K, N);
        int best = 0;
        for (int i = 0; i < K; ++i)
            if (frequencies[i] > frequencies[best])
                best = i;
        for (int i = 0; i < M; ++i) {
            int x; cin >> x;
            --x;
            frequencies[x]++;
            if (frequencies[x] >= frequencies[best])
                best = x;
            cout << best + 1 << "\n";
        }
    }
}