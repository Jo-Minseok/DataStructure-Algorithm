#include <iostream>
using namespace std;
#define MAX_SIZE 10

int parent[MAX_SIZE + 1];
int rank_arr[MAX_SIZE + 1];

void Make_set() {
    for (int i = 1; i < MAX_SIZE + 1; i++)
    {
        parent[i] = i;
        rank_arr[i] = 1;
    }
}

// Path Compression 적용
int Find(int x)
{
    if (x == parent[x])
    {
        return x;
    }
    return parent[x] = Find(parent[x]);
}

// Path Compression 미적용
/*
int Find(int x)
{
    if (x == parent[x])
    {
        return x;
    }
    return Find(parent[x]);
}
*/


// Union-by-Rank 적용
void Union(int x, int y)
{
    x = Find(x);
    y = Find(y);

    if (x == y)
    {
        return;
    }
    if (rank_arr[x] > rank_arr[y])
    {
        parent[y] = x;
        rank_arr[x] += rank_arr[y];
    }
    else
    {
        parent[x] = y;
        rank_arr[y] += rank_arr[x];
    }
}

// Union-by-Rank 미적용
/*
void Union(int x, int y)
{
    x = Find(x);
    y = Find(y);

    if (x == y)
    {
        return;
    }
    if (a < b){
	parent[b] = a;
    }
    else{
        parent[a] = b;
    }
}
*/

bool isUnion(int x, int y)
{
    return Find(x) == Find(y);
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    Make_set();
    int pos1, pos2, link_count;
    cout << "연결 시킬 간선의 개수를 입력하세요: ";
    cin >> link_count;
    while (link_count--)
    {
        cout << "연결 시킬 노드 두개를 입력하세요: ";
        cin >> pos1 >> pos2;
        Union(pos1, pos2);
    }
    cout << "확인할 노드 세트 개수를 입력하세요: ";
    cin >> link_count;
    while (link_count--)
    {
        cout << "확인할 노드 두개를 입력하세요: ";
        cin >> pos1 >> pos2;
        cout << pos1 << "과 " << pos2 << "는 " << (isUnion(pos1, pos2) ? "연결되어 있습니다." : "연결되어 있지 않습니다.") << "\n";
    }
}