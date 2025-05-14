// filepath: /digit-sim/digit-sim/src/sequential.c
#include "sequential.h"
#include "bit.h"
#include "clock.h"
#include <stdio.h>

void RS_latch(Bit * pQ, Bit * pQn, Bit S, Bit R) {
    // invalid state
    if (isLOW(S) && isLOW(R)) {
        printf("[WARN] RS_latch: invalid state\n");
        *pQ = *pQn = HIGH;
        return;
    }

    // realised by logic circuit
    // Bit tempQ, tempQn;
    // tempQ = nand_gate(2, S, *pQn);
    // tempQn = nand_gate(2, R, *pQ);
    // tempQ = nand_gate(2, S, tempQn);
    // tempQn = nand_gate(2, R, tempQ);
    // *pQ = tempQ;
    // *pQn = tempQn;

    // realised by truth table
    // set Q
    if (isLOW(S) && isHIGH(R)) {
        *pQ = HIGH;
        *pQn = LOW;
    } // reset Q
    else if (isHIGH(S) && isLOW(R)) {
        *pQ = LOW;
        *pQn = HIGH;
    }

    // hold Q
    // nothing to do

    return;
}

void gated_RS_latch(Bit * pQ, Bit * pQn, Bit G, Bit S, Bit R) {
    Bit Sn = nand_gate(2, G, S);
    Bit Rn = nand_gate(2, G, R);
    RS_latch(pQ, pQn, Sn, Rn);
    return;
}

void D_latch(Bit * pQ, Bit * pQn, Bit G, Bit D) {
    gated_RS_latch(pQ, pQn, G, D, not_gate(D));
    return;
}

void D_flip_flop(Bit * pQ, Bit * pQn, Bit D, Clock const * clk, bool posedge_trigger) {
    // static Bit last_clk = LOW; // Store the last clock state

    // if (isHIGH(clk) && isLOW(last_clk)) { // Rising edge detection
    //     *pQ = D; // On the rising edge, Q takes the value of D
    //     *pQn = not_gate(D); // Qn is the inverse of Q
    // }

    // last_clk = clk; // Update the last clock state

    if (!clk->initialized) {
        fputs("[ERR] D_flip_flop: clock not initialized.\n", stderr);
        return;
    }

    if (posedge_trigger && Clock_posedge(clk)) {
        *pQ = D;
        *pQn = not_gate(D);
    }

    if (!posedge_trigger && Clock_negedge(clk)) {
        *pQ = D;
        *pQn = not_gate(D);
    }

    return;
}

void JK_flip_flop(Bit * pQ, Bit * pQn, Bit J, Bit K, Clock const * clk, bool posedge_trigger) {
    // static Bit last_clk = LOW; // Store the last clock state

    // if (isHIGH(clk) && isLOW(last_clk)) { // Rising edge detection
    //     if (isHIGH(J) && isLOW(K)) {
    //         *pQ = HIGH; // Set
    //     } else if (isLOW(J) && isHIGH(K)) {
    //         *pQ = LOW; // Reset
    //     } else if (isHIGH(J) && isHIGH(K)) {
    //         *pQ = not_gate(*pQ); // Toggle
    //     }
    //     *pQn = not_gate(*pQ); // Update Qn
    // }

    // last_clk = clk; // Update the last clock state

    if (!clk->initialized) {
        fputs("[ERR] JK_flip_flop: clock not initialized.\n", stderr);
        return;
    }

    if (posedge_trigger && Clock_posedge(clk)) {
        *pQ = or_gate(2, 
            and_gate(2, J, not_gate(*pQ)),
            and_gate(2, not_gate(K), *pQ)
        );
        *pQn = not_gate(*pQ);
    }

    if (!posedge_trigger && Clock_negedge(clk)) {
        *pQ = or_gate(2, 
            and_gate(2, J, not_gate(*pQ)),
            and_gate(2, not_gate(K), *pQ)
        );
        *pQn = not_gate(*pQ);
    }

    return;
}

void T_flip_flop(Bit * pQ, Bit * pQn, Bit T, Clock const * clk, bool posedge_trigger) {
    // static Bit last_clk = LOW; // Store the last clock state

    // if (isHIGH(clk) && isLOW(last_clk)) { // Rising edge detection
    //     if (isHIGH(T)) {
    //         *pQ = not_gate(*pQ); // Toggle
    //     }
    //     *pQn = not_gate(*pQ); // Update Qn
    // }

    // last_clk = clk; // Update the last clock state

    if (!clk->initialized) {
        fputs("[ERR] JK_flip_flop: clock not initialized.\n", stderr);
        return;
    }

    if (posedge_trigger && Clock_posedge(clk)) {
        *pQ = xor_gate(2, T, *pQ);
        *pQn = not_gate(*pQ);
    }

    if (!posedge_trigger && Clock_negedge(clk)) {
        *pQ = xor_gate(2, T, *pQ);
        *pQn = not_gate(*pQ);
    }

    return;
}

void MSI_74LS290(Bit * pQA, Bit * pQB, Bit * pQC, Bit * pQD,
                 Clock const * A, Clock const * B,
                 Bit R01, Bit R02, Bit S91, Bit S92) { 
    if (!A->initialized || !B->initialized) {
        fputs("[ERR] MSI_74LS290: clock not initialized.\n", stderr);
        return;
    }

    // 异步计数
    if (Clock_negedge(A)) {
        *pQA = not_gate(*pQA);
    }
    if (Clock_negedge(B)) {
        Bit tempQB = *pQB;
        Bit tempQC = *pQC;
        *pQB = not_gate(*pQB);
        if (isHIGH(tempQB) && isLOW(*pQB)) {
            *pQC = not_gate(*pQC);
        }
        if (isHIGH(tempQC) && isLOW(*pQC)) {
            *pQD = not_gate(*pQD);
        }
    }
    if (isHIGH(and_gate(2, *pQB, *pQD))) {
        *pQB = LOW;
        *pQC = LOW;
        *pQD = LOW;
    }

    // 异步清零
    if (isHIGH(and_gate(2, R01, R02))) {
        *pQA = LOW;
        *pQB = LOW;
        *pQC = LOW;
        *pQD = LOW;
    }
    // 异步置9
    if (isHIGH(and_gate(2, S91, S92))) {
        *pQA = HIGH;
        *pQB = LOW;
        *pQC = LOW;
        *pQD = HIGH;
    }

    return;
}