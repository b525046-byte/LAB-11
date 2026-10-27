#include <stdio.h>
#include <string.h>

#define MAXN 100005
#define TABLE 262144
#define INF 1000000000

char words[MAXN][12];
int table[TABLE];
int distF[MAXN], distB[MAXN];
int frontF[MAXN], frontB[MAXN], nextFront[MAXN];
int count = 0, L;

int hash(char *s) {
    unsigned long h = 5381;
    for (int i = 0; s[i] != '\0'; i++)
        h = h * 33 + s[i];
    return h & (TABLE - 1);
}

int find(char *s) {
    int h = hash(s);
    while (table[h] != -1) {
        if (strcmp(words[table[h]], s) == 0)
            return table[h];
        h = (h + 1) & (TABLE - 1);
    }
    return -1;
}

int insert(char *s) {
    int idx = find(s);
    if (idx != -1) return idx;
    int h = hash(s);
    while (table[h] != -1)
        h = (h + 1) & (TABLE - 1);
    strcpy(words[count], s);
    table[h] = count;
    count++;
    return count - 1;
}

int expand(int *front, int *size, int *mine, int *other) {
    int best = INF, newSize = 0;
    for (int i = 0; i < *size; i++) {
        int cur = front[i];
        char tmp[12];
        strcpy(tmp, words[cur]);
        for (int pos = 0; pos < L; pos++) {
            char orig = tmp[pos];
            for (char c = 'a'; c <= 'z'; c++) {
                if (c == orig) continue;
                tmp[pos] = c;
                int idx = find(tmp);
                if (idx == -1) continue;
                if (other[idx] != -1 && mine[cur] + 1 + other[idx] < best)
                    best = mine[cur] + 1 + other[idx];
                if (mine[idx] == -1) {
                    mine[idx] = mine[cur] + 1;
                    nextFront[newSize++] = idx;
                }
            }
            tmp[pos] = orig;
        }
    }
    for (int i = 0; i < newSize; i++)
        front[i] = nextFront[i];
    *size = newSize;
    return best;
}

int main() {
    int N, i;
    char w[12], A[12], B[12];

    for (i = 0; i < TABLE; i++)
        table[i] = -1;

    printf("Enter number of dictionary words: ");
    scanf("%d", &N);
    printf("Enter dictionary words:\n");
    for (i = 0; i < N; i++) {
        scanf("%11s", w);
        insert(w);
    }
    printf("Enter start word A and target word B: ");
    scanf("%11s %11s", A, B);
    L = strlen(A);

    int dictCount = count;
    int b = find(B);
    if (b == -1 || b >= dictCount) {
        printf("-1\n");
        return 0;
    }
    int a = insert(A);
    if (a == b) {
        printf("Minimum mutations: 0\n");
        return 0;
    }

    for (i = 0; i < count; i++) {
        distF[i] = -1;
        distB[i] = -1;
    }
    distF[a] = 0;
    distB[b] = 0;
    frontF[0] = a;
    frontB[0] = b;
    int sizeF = 1, sizeB = 1;
    int answer = INF;

    while (sizeF > 0 && sizeB > 0 && answer == INF) {
        if (sizeF <= sizeB)
            answer = expand(frontF, &sizeF, distF, distB);
        else
            answer = expand(frontB, &sizeB, distB, distF);
    }

    if (answer == INF)
        printf("-1\n");
    else
        printf("Minimum mutations: %d\n", answer);
    return 0;
}
