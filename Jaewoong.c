#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

// 다항식 항 구조
typedef struct ListNode {
    int coef;
    int expon;
    struct ListNode* link;
} ListNode;

// 다항식 시작과 끝
typedef struct ListHeader {
    ListNode* head;
    ListNode* tail;
} ListHeader;

// 다항식 초기화
void init(ListHeader* plist) {
    plist->head = plist->tail = NULL;
}
// 항 삽입
void insert_node(ListHeader* plist, int coef, int expon) {
    ListNode* p = (ListNode*)malloc(sizeof(ListNode));
    p->coef = coef;
    p->expon = expon;
    p->link = NULL;
    if (plist->tail == NULL) {
        plist->head = plist->tail = p;
    }
    else {
        plist->tail->link = p;
        plist->tail = p;
    }
}

void poly_add(ListHeader* plist1, ListHeader* plist2, ListHeader* plist3) {
    ListNode* a = plist1->head;
    ListNode* b = plist2->head;
    int sum;
    while (a && b) {
        if (a->expon == b->expon) {
            sum = a->coef + b->coef;
            if (sum != 0)insert_node(plist3, sum, a->expon);
            a = a->link;
            b = b->link;
        }
        else if (a->expon > b->expon) {
            insert_node(plist3, a->coef, a->expon);
            a = a->link;
        }
        else {
            insert_node(plist3, b->coef, b->expon);
            b = b->link;
        }
        for (; a != NULL; a = a->link)
            insert_node(plist3, a->coef, a->expon);
        for (; b != NULL; b = b->link)
            insert_node(plist3, b->coef, b->expon);
    }
}

void poly_print(ListHeader* plist,FILE *output) {
    for (ListNode* p = plist->head; p;p = p->link)
        printf("%d %d\n", p->coef, p->expon);
}

int main() {
    int n, a, b;
    ListHeader plist1, plist2, plist3, plist4;
    init(&plist1);
    init(&plist2);
    init(&plist3);
    init(&plist4);

    FILE* input = fopen("input.txt", "r");
    FILE* output = fopen("output.txt", "w");

    fscanf_s(input, "%d",&n);
    while (n--) {
        fscanf_s(input, "%d%d", &a, &b);
        insert_node(&plist1, a, b);
    }
    fscanf_s(input, "%d", &n);
    while (n--) {
        fscanf_s(input, "%d%d", &a, &b);
        insert_node(&plist2, a, b);
    }

    poly_add(&plist1, &plist2, &plist3);

    fprintf(output, "Addition\n");
    poly_print(&plist3, output);

    fclose(input);
    fclose(output);
}