#pragma warning(disable:4996)
#include<stdio.h>
#include<cstring>
#include<ctype.h>

const int MAXlen = 1000;

char stack1[MAXlen], stack2[MAXlen], stack3[MAXlen]; 
int  s_top1 = 0, s_top2 = 0, s_top3 = 0;

// implements of stack
void s_push(char v, int f) {
    if (f == 1) stack1[s_top1++] = v;
    else if (f == 2) stack2[s_top2++] = v;
    else if (f == 3) stack3[s_top3++] = v;
}
void s_pop(int f) {
    if (f == 1) { stack1[--s_top1] = ' '; }
    else if (f == 2) { stack2[--s_top2] = ' '; }
    else if (f == 3) { stack3[--s_top3] = ' '; }
}
bool s_is_empty(int f) {
    if (f == 1) return s_top1 == 0;
    else if (f == 2) return s_top2 == 0;
    else if (f == 3) return s_top3 == 0;
}
char s_top(int f) {
    if (f == 1) return stack1[s_top1 - 1];
    else if (f == 2) return stack2[s_top2 - 1];
    else if (f == 3) return stack3[s_top3 - 1];
}

char rules[26][MAXlen];
bool is_decoded[26];
char devil_words[MAXlen];

void rule_decode(char* str, int k) {
    char res[MAXlen];
    int p = 0;
    memset(res, 0, sizeof res);
    for (int i = 0; i < (int)strlen(str); i++) {
        if (!isupper(str[i])) {
            res[p++] = str[i];
        }
        else {
            if (!is_decoded[str[i] - 'A']) {
                rule_decode(rules[str[i] - 'A'], str[i] - 'A');
                is_decoded[str[i] - 'A'] = 1;
            }
            strcat(res, rules[str[i] - 'A']);
            p = strlen(res);
        }
    }
    if (strlen(str) == 0) {
        res[0] = k + 'A';
        res[1] = '\0';
    }
    strcpy(str, res);
}//decoder

int main() {
    printf("-----请输入你想要指定多少规则-----\n");
    int R_cnt;
    scanf("%d", &R_cnt);
    printf("\n-----------输入你的规则-----------");
    printf("\n-----------样例 A>aTdT -----------\n");
    for (int i = 1; i <= R_cnt; i++) {
        char buff[MAXlen];
        printf("%d:", i);
        scanf("%s", buff);
        memcpy(rules[buff[0] - 'A'], buff + 2, strlen(buff) - 2);
    }

    printf("\n-----------说出你的鸟语-----------\n");
    scanf("%s", devil_words);

    //decode the rules
    for (int i = 0; i < 26; i++) {
        if (strlen(rules[i]) > 0) {
            rule_decode(rules[i], i);
        }
    }

    for (int i = 0; i < strlen(devil_words); i++) {
        s_push(devil_words[i], 1);
    }// push the words to Stack1

    while(!s_is_empty(1)) {
        if (s_top(1) != '(') {
            s_push(s_top(1), 2);
            s_pop(1);
        }// Push stack1 to stack2 in normal state
        else { 
            s_pop(1); // pop stack1 top '('
            s_push(s_top(2), 3);
            char theta = s_top(2);
            s_pop(2); // pop theta
            while(s_top(2) != ')') {
                s_push(s_top(2), 3);
                s_push(theta, 3);
                s_pop(2);
            }
            while(!s_is_empty(3)) {
                s_push(s_top(3), 1);
                s_pop(3);
            }
        s_pop(2); // pop stack2 top ')'
        }
    }

    while (!s_is_empty(2)) {
        s_push(s_top(2), 1);
        s_pop(2);
    }

    for (int i = s_top1 - 1; i >= 0; i--) {
        devil_words[i] = s_top(1);
        s_pop(1);
    }

    rule_decode(devil_words, -1);

    printf("\n-----------byd.鸟语翻译-----------\n");

    for (int i = 0; i < strlen(devil_words); i++) {
        putchar(devil_words[i]);
    }
    printf("\n");

    return 0;

}
