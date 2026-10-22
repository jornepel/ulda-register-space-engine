/* ulda.c — ULDA Topological Decoder Engine */
#include "ulda.h"
#include <stdlib.h>
#include <stdio.h>

void reg_init(ulda_register *r, u64 capacity) {
    r->steps = (u64 *)malloc(capacity * sizeof(u64));
    r->ranks = 0;
    r->capacity = capacity;
}

void reg_free(ulda_register *r) {
    free(r->steps);
    r->steps = NULL;
    r->ranks = 0;
    r->capacity = 0;
}

static void reg_ensure(ulda_register *r, u64 needed) {
    if (needed <= r->capacity) return;
    u64 new_cap = r->capacity ? r->capacity * 2 : 8;
    while (new_cap < needed) new_cap *= 2;
    r->steps = (u64 *)realloc(r->steps, new_cap * sizeof(u64));
    r->capacity = new_cap;
}

void peel(ulda_register *r, u64 n) {
    r->ranks = 0;
    u64 value = n;
    u64 odd = 1;
    u64 steps = 0;

    while (value > 0) {
        if (value < odd) {
            reg_ensure(r, r->ranks + 1);
            r->steps[r->ranks++] = steps;
            steps = 0;
            odd = 1;
            continue;
        }
        value -= odd;
        steps++;
        odd += 2;
    }

    if (steps > 0) {
        reg_ensure(r, r->ranks + 1);
        r->steps[r->ranks++] = steps;
    }
}

int reken(ulda_register *out, u64 a, u64 b, char op) {
    u64 result;
    switch (op) {
        case '+': result = a + b; break;
        case '-': if (a < b) return 0; result = a - b; break;
        case '*': result = a * b; break;
        case '/': if (b == 0) return 0; result = a / b; break;
        default:  return 0;
    }
    peel(out, result);
    return 1;
}

coord compass(u64 angle) {
    coord c = {0, 0, 0};
    u64 a = angle;
    while (a >= 72) { a -= 72; c.x++; }
    c.y = c.x * 2;
    c.z = 0;
    return c;
}

void write_register(const ulda_register *r, char *buf, size_t size) {
    size_t pos = 0;
    pos += snprintf(buf + pos, size - pos, "[");
    for (u64 i = 0; i < r->ranks; i++) {
        pos += snprintf(buf + pos, size - pos, "%llu%s",
                        r->steps[i],
                        (i + 1 < r->ranks) ? ", " : "");
    }
    snprintf(buf + pos, size - pos, "]");
}
