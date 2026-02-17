#include <stdio.h>
#include <string.h>
#include <ctype.h>

int n;
char prod[20][20];
char first[20][20];
char follow[20][20];
char nt[20];

/* ---------- FIRST ---------- */
void addToSet(char set[], char c) {
    if (!strchr(set, c)) {
        int len = strlen(set);
        set[len] = c;
        set[len + 1] = '\0';
    }
}

void findFirst(char c, int idx) {
    if (!isupper(c)) {
        addToSet(first[idx], c);
        return;
    }

    for (int i = 0; i < n; i++) {
        if (prod[i][0] == c) {
            int j = 2;
            while (prod[i][j] != '\0') {
                if (!isupper(prod[i][j])) {
                    addToSet(first[idx], prod[i][j]);
                    break;
                } else {
                    findFirst(prod[i][j], idx);
                    if (!strchr(first[prod[i][j] - 'A'], '#'))
                        break;
                }
                j++;
            }
        }
    }
}

/* ---------- FOLLOW ---------- */
void findFollow(char c, int idx) {
    if (c == nt[0])
        addToSet(follow[idx], '$');

    for (int i = 0; i < n; i++) {
        for (int j = 2; j < strlen(prod[i]); j++) {
            if (prod[i][j] == c) {
                if (prod[i][j + 1] != '\0') {
                    if (!isupper(prod[i][j + 1])) {
                        addToSet(follow[idx], prod[i][j + 1]);
                    } else {
                        strcat(follow[idx], first[prod[i][j + 1] - 'A']);
                    }
                }
                if (prod[i][j + 1] == '\0' && prod[i][0] != c) {
                    findFollow(prod[i][0], idx);
                }
            }
        }
    }
}

int main() {
    printf("Enter number of productions: ");
    scanf("%d", &n);

    printf("Enter productions (use # for epsilon):\n");
    for (int i = 0; i < n; i++) {
        scanf("%s", prod[i]);
        nt[i] = prod[i][0];
        first[i][0] = '\0';
        follow[i][0] = '\0';
    }

    printf("\nFIRST SETS\n");
    for (int i = 0; i < n; i++) {
        findFirst(nt[i], i);
        printf("FIRST(%c) = { %s }\n", nt[i], first[i]);
    }

    printf("\nFOLLOW SETS\n");
    for (int i = 0; i < n; i++) {
        findFollow(nt[i], i);
        printf("FOLLOW(%c) = { %s }\n", nt[i], follow[i]);
    }

    return 0;
}
