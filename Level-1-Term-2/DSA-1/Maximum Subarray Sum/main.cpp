#include <iostream>
#include <vector>
#include <cstdio>
#include <utility>
using namespace std;
int highrange, lowrange;
pair<int, pair<int, int>> maxsum_subarray_mid(vector<int> &v, int low, int high)
{
    int sum = 0, variableSum = 0, i, j, k;
    int mid = (high + low) / 2;
    variableSum = 0;
    sum = v[mid];
    highrange = mid;
    lowrange = mid;

    for (i = mid; i >= low; i--)
    {
        variableSum += v[i];
        if (variableSum > sum)
        {
            lowrange = i;
            sum = variableSum;
        }
    }
    variableSum = sum;

    for (i = mid + 1; i <= high; i++)
    {
        variableSum += v[i];
        if (variableSum > sum)
        {
            highrange = i;
            sum = variableSum;
        }
    }
    pair<int, pair<int, int>> p(sum, make_pair(lowrange, highrange));
    return p;
}

pair<int, pair<int, int>> maxsum_subarray(vector<int> &v, int low, int high)
{
    if (high <= low)
    {
        pair<int, pair<int, int>> p(v[low], make_pair(low, low));
        return p;
    }
    int mid = (high + low) / 2;
    pair<int, pair<int, int>> p1 = maxsum_subarray(v, low, mid);
    pair<int, pair<int, int>> p2 = maxsum_subarray(v, mid + 1, high);
    pair<int, pair<int, int>> p3 = maxsum_subarray_mid(v, low, high);
    int rangegap1 = p1.second.second - p1.second.first;
    int rangegap2 = p2.second.second - p2.second.first;
    int rangegap3 = p3.second.second - p3.second.first;

    if (p1.first == p2.first && p2.first == p3.first)
    {
        if (rangegap1 < rangegap2 && rangegap1 < rangegap3)
            return p1;
        else if (rangegap2 < rangegap3 && rangegap2 < rangegap1)
            return p2;
        return p3;
    }
    else if (p1.first >= p2.first && p1.first >= p3.first)
    {
        if (p1.first == p2.first)
        {
            if (rangegap1 < rangegap2)
                return p1;
            return p2;
        }
        else if (p1.first == p3.first)
        {
            if (rangegap1 < rangegap3)
                return p1;
            return p3;
        }
        return p1;
    }
    else if (p2.first >= p1.first && p2.first >= p3.first)
    {

        if (p2.first == p3.first)
        {
            if (rangegap2 < rangegap3)
                return p2;
            return p3;
        }
        return p2;
    }
    return p3;
}

int main()
{
    vector<int> v;
    int lowrange, highrange, i, l;
    freopen("input.txt", "r", stdin);
    while (scanf("%d", &l) != EOF)
    {
        v.push_back(l);
    }
    pair<int, pair<int, int>> solution = maxsum_subarray(v, 0, v.size() - 1);
    if(solution.first < 0)
    {
        cout << "[ ] with a sum of 0";
        return 0;
    }
    lowrange = solution.second.first;
    highrange = solution.second.second;
    cout << "[";
    for (i = lowrange; i <= highrange; i++)
    {
        cout << v[i];
        if (i != highrange)
            cout << ",";
    }
    cout << "] with a sum of " << solution.first;
    fclose(stdin);
    return 0;
}