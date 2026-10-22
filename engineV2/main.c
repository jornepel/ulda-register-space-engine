/* main.c — ULDA Test Suite */
#include "ulda.h"
#include <stdio.h>
#include <string.h>

static int check(const char *name, const char *got, const char *expected) {
    int ok = (strcmp(got, expected) == 0);
    printf("%-30s got=%-40s expected=%-40s  %s\n",
           name, got, expected, ok ? "PASS" : "FAIL");
    return ok;
}

int main(void) {
    printf("ULDA-X28 — Base-60 Coordinate Engine (True Ladder)\n");
    printf("===================================================\n\n");

    int all_ok = 1;
    char buf[256];

    /* Calculate */
    coordinate c1860 = calculate(1860);
    write_coordinate(&c1860, buf, sizeof(buf));
    all_ok &= check("calculate(1860)", buf, "(0, 0, 0, 0, 5, 1, 4)");

    coordinate c3600 = calculate(3600);
    write_coordinate(&c3600, buf, sizeof(buf));
    all_ok &= check("calculate(3600)", buf, "(0, 0, 0, 1, 0, 0, 0)");

    coordinate c1878 = calculate(1878);
    write_coordinate(&c1878, buf, sizeof(buf));
    all_ok &= check("calculate(1878)", buf, "(0, 0, 0, 0, 5, 2, 1)");

    coordinate c12960000 = calculate(12960000);
    write_coordinate(&c12960000, buf, sizeof(buf));
    all_ok &= check("calculate(12960000)", buf, "(1, 0, 0, 0, 0, 0, 0)");

    /* Add */
    coordinate sum = add(c1860, c3600);
    write_coordinate(&sum, buf, sizeof(buf));
    all_ok &= check("add(1860, 3600)", buf, "(0, 0, 0, 1, 5, 1, 4)");

    /* Subtract */
    coordinate difference;
    int ok = subtract(c3600, c1860, &difference);
    write_coordinate(&difference, buf, sizeof(buf));
    all_ok &= check("subtract(3600, 1860)", buf, "(0, 0, 0, 0, 4, 4, 2)");
    all_ok &= (ok == 1);

    ok = subtract(c1860, c3600, &difference);
    all_ok &= (ok == 0);

    /* Multiply */
    coordinate product = multiply(c1860, 2);
    write_coordinate(&product, buf, sizeof(buf));
    all_ok &= check("multiply(1860, 2)", buf, "(0, 0, 0, 1, 0, 3, 2)");

    /* Divide */
    coordinate quotient;
    ok = divide(c3600, 2, &quotient);
    write_coordinate(&quotient, buf, sizeof(buf));
    all_ok &= check("divide(3600, 2)", buf, "(0, 0, 0, 0, 5, 0, 0)");
    all_ok &= (ok == 1);

    ok = divide(c3600, 0, &quotient);
    all_ok &= (ok == 0);

    printf("\n%s\n", all_ok ? "ALL TESTS PASSED" : "SOME TESTS FAILED");
    return all_ok ? 0 : 1;
}
