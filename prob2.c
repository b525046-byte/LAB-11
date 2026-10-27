#include <stdio.h>

int head[1000], nxt[20000], to[20000], ec = 0;
int owner[1000], dist[1000], queue[1000], hub[1000];

void addEdge(int u, int v) {
    to[ec] = v;
    nxt[ec] = head[u];
    head[u] = ec;
    ec++;
}

int main() {
    int V, E, K, R, i, e;

    printf("Enter number of vertices and edges: ");
    scanf("%d %d", &V, &E);
    for (i = 0; i < V; i++) {
        head[i] = -1;
        owner[i] = -1;
        dist[i] = -1;
    }

    printf("Enter undirected edges (u v), vertices 0 to %d:\n", V - 1);
    for (i = 0; i < E; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        addEdge(u, v);
        addEdge(v, u);
    }

    printf("Enter number of hubs K: ");
    scanf("%d", &K);
    printf("Enter hub vertices in order h1 to hK: ");
    for (i = 0; i < K; i++)
        scanf("%d", &hub[i]);
    printf("Enter radius R: ");
    scanf("%d", &R);

    int qh = 0, qt = 0;
    for (i = 0; i < K; i++) {
        int h = hub[i];
        if (dist[h] == -1) {
            dist[h] = 0;
            owner[h] = i + 1;
            queue[qt++] = h;
        }
    }

    while (qh < qt) {
        int u = queue[qh++];
        if (dist[u] == R) continue;
        for (e = head[u]; e != -1; e = nxt[e]) {
            int v = to[e];
            if (dist[v] == -1) {
                dist[v] = dist[u] + 1;
                owner[v] = owner[u];
                queue[qt++] = v;
            }
        }
    }

    printf("\nVertex  Owner  Distance\n");
    for (i = 0; i < V; i++) {
        if (owner[i] == -1)
            printf("%-7d -1     -\n", i);
        else
            printf("%-7d %-6d %d\n", i, owner[i], dist[i]);
    }
    return 0;
}
