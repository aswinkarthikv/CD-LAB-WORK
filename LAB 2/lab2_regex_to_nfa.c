#include <stdio.h>
#include <stdlib.h>

int state = 0;

struct NFA {
    int start;
    int end;
};

struct NFA stack[100];
int top = -1;

void push(struct NFA n) {
    stack[++top] = n;
}

struct NFA pop() {
    return stack[top--];
}

void add_transition(int from, char symbol, int to) {
    if (symbol == 'e')
        printf("q%d -- ε --> q%d\n", from, to);
    else
        printf("q%d -- %c --> q%d\n", from, symbol, to);
}

int main() {
    char postfix[50];
    printf("Enter Regular Expression (postfix): ");
    scanf("%s", postfix);

    printf("\nNFA Transitions:\n");

    for (int i = 0; postfix[i] != '\0'; i++) {
        char ch = postfix[i];

        if (ch >= 'a' && ch <= 'z') {
            struct NFA n;
            n.start = state++;
            n.end = state++;
            add_transition(n.start, ch, n.end);
            push(n);
        }

        else if (ch == '*') {
            struct NFA n1 = pop();
            struct NFA n;
            n.start = state++;
            n.end = state++;

            add_transition(n.start, 'e', n1.start);
            add_transition(n.start, 'e', n.end);
            add_transition(n1.end, 'e', n1.start);
            add_transition(n1.end, 'e', n.end);

            push(n);
        }

        else if (ch == '.') {
            struct NFA n2 = pop();
            struct NFA n1 = pop();

            add_transition(n1.end, 'e', n2.start);

            struct NFA n;
            n.start = n1.start;
            n.end = n2.end;
            push(n);
        }
    }

    struct NFA result = pop();

    printf("\nStart State: q%d\n", result.start);
    printf("Final State: q%d\n", result.end);

    return 0;
}
