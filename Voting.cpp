#include<iostream>
#include<vector>
#include<algorithm>
#include<cmath>

using namespace std;

struct party{
    long long votes;
    long long num;
    long long bribe;
};

bool operator<(const party & p1, const party & p2)
{
	if (p1.votes < p2.votes)
		return true;
	else if (p1.votes == p2.votes && p1. num < p2.num)
		return true;
	return false;
}

int main()
{
    int n = 0;
    cin >> n;
    vector <party> Parties(n);
    for (int i = 0; i < n; ++i)
    {
        cin >> Parties[i].votes >> Parties[i].bribe;
        Parties[i].num = i;
    }
    sort(Parties.begin(), Parties.end());
    vector <long long> S(n);
    vector <long long> Price(n);
    long long count = 0;
    for (int i = n - 1; i >= 0; --i)
    {
        S[i] = count;
        count += Parties[i].votes;
    }
    long long l1, r1, mid1, l2, r2, mid2;
    for (int i = 0; i < n; ++i)
    {
        l1 = Parties[i].votes;
        r1 = Parties[n - 1].votes;
        if (n > 1 && Parties[n - 1].votes == Parties[n - 2].votes)
            r1++;
        while (l1 + 1 < r1)
        {
            mid1 = (l1 + r1) / 2;
            l2 = -1;
            r2 = n;
            while (l2 + 1 < r2)
            {
                mid2 = (l2 + r2) / 2;
                if (Parties[mid2].votes >= mid1)
                    r2 = mid2;
                else
                    l2 = mid2;
            }
            if (S[r2 - 1] - (n - r2) * (mid1 - 1) + Parties[i].votes <= mid1)
                r1 = mid1;
            else
                l1 = mid1;
        }
        Price[i] = r1;
    }
    int min_ind = 0;
    const int INF = 2e9;
    for (int i = 0; i < n; ++i)
        if (Parties[i].bribe == -1)
            Price[i] = INF;
        else
            Price[i] += Parties[i].bribe - Parties[i].votes;
    for (int i = 0; i < n; ++i)
        if (Price[min_ind] > Price[i])
            min_ind = i;
    cout << Price[min_ind] << endl;
    cout << Parties[min_ind].num + 1 << endl;
    int best_deal = Price[min_ind] - Parties[min_ind].bribe;
    int max_res = best_deal + Parties[min_ind].votes;
    for (int i = 0; i < n; ++i)
    {
        if (Parties[i].votes >= max_res && i != min_ind)
        {
            best_deal = best_deal - (Parties[i].votes - max_res + 1);
            Parties[i].votes = max_res - 1;
        }
    }
    for (int i = 0; best_deal > 0; ++i)
    {
        if (i != min_ind)
        {
            if (best_deal >= Parties[i].votes)
            {
                best_deal -= Parties[i].votes;
                Parties[i].votes = 0;
            }
            else
            {
                Parties[i].votes -= best_deal;
                best_deal = 0;
            }
        }
    }
    Parties[min_ind].votes += Price[min_ind] - Parties[min_ind].bribe;
    for (int i = 0; i < n; ++i)
        swap(Parties[i].votes, Parties[i].num);
    sort(Parties.begin(), Parties.end());
    for (int i = 0; i < n; ++i)
        cout << Parties[i].num << " ";
    return 0;
}
