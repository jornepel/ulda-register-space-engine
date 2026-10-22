/* main.c — ULDA Test Suite */
#include "ulda.h"
#include <stdio.h>
#include <string.h>

static int check(const char *name, const char *got, const char *expected) {
    int ok = (strcmp(got, expected) == 0);
    printf("%-26s got=%-18s expected=%-18s  %s\n",
           name, got, expected, ok ? "PASS" : "FAIL");
    return ok;
}

int main(void) {
    printf("ULDA — Topological Decoder Engine\n");
    printf("==================================\n\n");

    int all_ok = 1;
    char buf[256];

    ulda_register r;
    reg_init(&r, 8);

    peel(&r, 7);   write_register(&r, buf, sizeof(buf));
    all_ok &= check("peel(7)", buf, "[2, 1, 1, 1]");

    peel(&r, 57);  write_register(&r, buf, sizeof(buf));
    all_ok &= check("peel(57)", buf, "[7, 2, 2]");

    reken(&r, 7, 50, '+'); write_register(&r, buf, sizeof(buf));
    all_ok &= check("reken(7, 50, +)", buf, "[7, 2, 2]");

    reken(&r, 57, 7, '/'); write_register(&r, buf, sizeof(buf));
    all_ok &= check("reken(57, 7, /)", buf, "[2, 2]");

    reg_free(&r);

    printf("\n%s\n", all_ok ? "ALL TESTS PASSED" : "SOME TESTS FAILED");
    return all_ok ? 0 : 1;
}
