// filepath: include/clock.h

#ifndef CLOCK_H
#define CLOCK_H

#include "bit.h"

// Abstract clock signal
typedef struct Clock Clock;
struct Clock{
    bool initialized; // Indicates if the clock is initialized
    Bit current;     // Current state of the clock (HIGH or LOW)
    Bit previous;    // Previous state of the clock (HIGH or LOW)
    void (*update)(Clock * clk); // User-defined function to update the clock
};

// Function to initialize the clock
void Clock_init(Clock * clk, Bit current);

// Function to update the clock state
void Clock_update(Clock * clk);

// Function to check if the clock is on positive edge
[[nodiscard("Clock_posedge: return value is not used")]]
inline bool Clock_posedge(Clock const * clk) {
    return (clk->initialized) ?  
        (isHIGH(clk->current) && isLOW(clk->previous)) :
        false;
}

// Function to check if the clock is on negative edge
[[nodiscard("Clock_negedge: return value is not used")]]
inline bool Clock_negedge(Clock const * clk) {
    return (clk->initialized) ?
        (isLOW(clk->current) && isHIGH(clk->previous)) :
        false;
}

#endif