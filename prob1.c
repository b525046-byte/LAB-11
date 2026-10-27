#include <stdio.h>
#define INF 1000000000
int head[1000], nxt[10000], to[10000], wt[10000], ec = 0;
int dist[1000][2];
int dq[60000];
void addEdge(int u, int v, int w) {
    to[ec] = v;
    wt[ec] = w;
    nxt[ec] = head[u];
    head[u] = ec;
    ec++;
}
int main() {
    int V, E, S, C, i, e;
    printf("Enter V, E, source S and penalty C: ");
    scanf("%d %d %d %d", &V, &E, &S, &C);
    for (i = 0; i < V; i++) {
        head[i] = -1;
        dist[i][0] = INF;
        dist[i][1] = INF;
    }
    printf("Enter directed edges (u v w), vertices 0 to %d, w is 0 or 1:\n", V - 1);
    for (i = 0; i < E; i++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        addEdge(u, v, w);
    }
    int front = 30000, back = 30000;
    dist[S][0] = 0;
    dq[back++] = S * 2;
    while (front < back) {
        int state = dq[front++];
        int u = state / 2;
        int p = state % 2;
        for (e = head[u]; e != -1; e = nxt[e]) {
            int v = to[e];
            int np = p ^ wt[e];
            int nd = dist[u][p] + wt[e];
            if (nd < dist[v][np]) {
                dist[v][np] = nd;
                if (wt[e] == 0)
                    dq[--front] = v * 2 + np;
                else
                    dq[back++] = v * 2 + np;
            }
        }
    }
    printf("\nMinimum cost from source %d:\n", S);
    for (i = 0; i < V; i++) {
        int best = dist[i][0];
        if (dist[i][1] != INF && dist[i][1] + C < best)
            best = dist[i][1] + C;
        if (best == INF)
            printf("Vertex %d: unreachable\n", i);
        else
            printf("Vertex %d: %d\n", i, best);
    }
    return 0;
}
