/* main.c — ULDA Test Suite */
#include "ulda.h"
#include <stdio.h>
#include <string.h>

static int check(const char *name, const char *got, const char *expected) {
    int ok = (strcmp(got, expected) == 0);
    printf("%-28s got=%-18s expected=%-18s  %s\n",
           name, got, expected, ok ? "PASS" : "FAIL");
    return ok;
}

int main(void) {
    printf("ULDA-X28 — Base-60 Coordinate Engine (Hand Grid)\n");
    printf("================================================\n\n");

    int all_ok = 1;
    char buf[128];

    /* Bereken */
    coordinaat c1860 = bereken(1860);
    write_coordinaat(&c1860, buf, sizeof(buf));
    all_ok &= check("bereken(1860)", buf, "(31, 0, 0)");

    coordinaat c3600 = bereken(3600);
    write_coordinaat(&c3600, buf, sizeof(buf));
    all_ok &= check("bereken(3600)", buf, "(60, 0, 0)");

    coordinaat c4320 = bereken(4320);
    write_coordinaat(&c4320, buf, sizeof(buf));
    all_ok &= check("bereken(4320)", buf, "(72, 0, 0)");

    coordinaat c1878 = bereken(1878);
    write_coordinaat(&c1878, buf, sizeof(buf));
    all_ok &= check("bereken(1878)", buf, "(31, 1, 6)");

    /* Add */
    coordinaat som = add(c1860, c3600);
    write_coordinaat(&som, buf, sizeof(buf));
    all_ok &= check("add(1860, 3600)", buf, "(91, 0, 0)");

    /* Sub */
    coordinaat verschil;
    int ok = sub(c3600, c1860, &verschil);
    write_coordinaat(&verschil, buf, sizeof(buf));
    all_ok &= check("sub(3600, 1860)", buf, "(29, 0, 0)");
    all_ok &= (ok == 1);

    ok = sub(c1860, c3600, &verschil);
    all_ok &= (ok == 0);

    /* Mul */
    coordinaat product = mul(c1860, 2);
    write_coordinaat(&product, buf, sizeof(buf));
    all_ok &= check("mul(1860, 2)", buf, "(62, 0, 0)");

    /* Mul with carry roll */
    coordinaat product5 = mul(c1878, 5);
    write_coordinaat(&product5, buf, sizeof(buf));
    all_ok &= check("mul(1878, 5)", buf, "(156, 2, 6)");

    /* Div */
    coordinaat quotient;
    ok = div_op(c3600, 2, &quotient);
    write_coordinaat(&quotient, buf, sizeof(buf));
    all_ok &= check("div(3600, 2)", buf, "(30, 0, 0)");
    all_ok &= (ok == 1);

    ok = div_op(c3600, 0, &quotient);
    all_ok &= (ok == 0);

    printf("\n%s\n", all_ok ? "ALL TESTS PASSED" : "SOME TESTS FAILED");
    return all_ok ? 0 : 1;
}
