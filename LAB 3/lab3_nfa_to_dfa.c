#include <stdio.h>

int nfa[10][10][10];     // NFA[state][symbol][next states]
int dfa[10][10];        // DFA table
int nfa_states, symbols;
int dfa_states = 0;

/* Check if state exists in DFA */
int stateExists(int state) {
    return state < dfa_states;
}

/* Main */
int main() {
    printf("Enter number of NFA states: ");
    scanf("%d", &nfa_states);

    printf("Enter number of input symbols: ");
    scanf("%d", &symbols);

    printf("\nNOTE: Enter transitions as 0 or 1\n");
    printf("If transition exists from qi to qj on symbol k, enter 1\n\n");

    for (int i = 0; i < nfa_states; i++) {
        for (int k = 0; k < symbols; k++) {
            printf("From state q%d on symbol %d:\n", i, k);
            for (int j = 0; j < nfa_states; j++) {
                printf("  To q%d? ", j);
                scanf("%d", &nfa[i][k][j]);
            }
        }
    }

    // Initial DFA state = NFA start state
    dfa_states = 1;
    for (int k = 0; k < symbols; k++) {
        for (int j = 0; j < nfa_states; j++) {
            dfa[0][k] |= nfa[0][k][j];
        }
    }

    printf("\nDFA TRANSITION TABLE\n");
    printf("---------------------\n");

    printf("State\t");
    for (int k = 0; k < symbols; k++)
        printf("%d\t", k);
    printf("\n");

    for (int i = 0; i < dfa_states; i++) {
        printf("q%d\t", i);
        for (int k = 0; k < symbols; k++) {
            printf("q%d\t", dfa[i][k]);
        }
        printf("\n");
    }

    return 0;
}
