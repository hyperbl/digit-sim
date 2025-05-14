// src/clock.c
#include "clock.h"
#include <stdio.h>

void Clock_init(Clock * clk, Bit current) {
    clk->initialized = true;
    clk->current = current;
    clk->previous = not_gate(current);
}

void Clock_update(Clock * clk) {
    if (!clk->initialized) {
        fprintf(stderr, "Error: Clock not initialized.\n");
        return;
    }

    if (clk->update) {
        clk->update(clk);
    } else {
        clk->previous = clk->current;
        clk->current = not_gate(clk->current);
    }
}
