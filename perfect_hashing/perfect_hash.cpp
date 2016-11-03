#include <cstdio>
#include <iostream>
#include <vector>
#include <list>
#include <ctime>

#define N 1000000
#define P 10000099999

using namespace std;

struct sec_hash_table {
    long long int a, b;
    vector<long long int> table;
    long long int l;

    void init()
    {
        a = rand() % P + 1;
        b = rand() % P + 1;
    }

    sec_hash_table(long long int len, list<long long int> slot) : table(len, -1)
    {

        l = len;
        if (len == 0)
            return;
        else if (len == 1) {
            a = b = 0;
            for (long long int i : slot)
                hash(i);
        }
        else {
            bool collision = false;
            while (1) {
                fill(table.begin(), table.end(), -1);
                init();
                for (long long int i : slot) {
                    if (hash(i) == -1) {
                        collision = true;
                        break;
                    }
                }
                if (!collision) {
                    break;
                }
                collision = false;
            }
        }
    }

    long long int hash(long long int e)
    {
        long long int pos = (((a * e + b) % P) % l);
        if (table[pos] == -1) {
            table[pos] = e;
            return pos;
        }
        else {
            return -1;
        }
    }

    long long int lookup(long long int e)
    {
        long long int pos = (((a * e + b) % P) % l);
        if (table[pos] == e)
            return pos;
        else
            return -1;
    }

};


struct hash_table {
    long long a, b;
    vector< list<long long int> > slot;
    long long len[N];
    vector<sec_hash_table> sec;
    long long count;

    hash_table()
    {
        a = rand() % N + 1;
        b = rand() % N + 1;
        fill(len, len+N, 0);
        count = 0;
        sec.reserve(N);
        slot = vector< list<long long int> > (N);
    }

    long long int hash(long long x)
    {
        long long pos = (((a * x + b) % P) % N);
        slot[pos].push_back(x);
        len[pos]++;
        count++;
        return pos;
    }

    void convert()
    {
        for (long long int i = 0; i < N; ++i) {
            sec.push_back(sec_hash_table(len[i]*len[i], slot[i]));
            slot[i].clear();
        }
        cout << "Op complete" << endl;
    }

    long long int lookup(long long int e)
    {
        long long pos = (((a * e + b) % P) % N);
        return sec[pos].lookup(e);
    }
};



int main()
{
    srand(time(NULL));

    hash_table ht;
    long long n;
    for (long long i = 0; i < N; ++i) {
        scanf("%lld", &n);
        ht.hash(n);
    }
    cout << "Number of elements hashed :" << ht.count << endl;
    cout << "Converting\n";
    ht.convert();


    /*
    * Modify as required
    long long int y;
    printf("Lookup:\n");
    cin >> y;
    printf("Pos: %lld %lld\n", y, ht.lookup(y));
    */

    return 0;
}
