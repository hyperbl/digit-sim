// 74LS290 计数器模拟，8421 输出
#include <stdio.h>
#include "digit_sim.h"

void clkB_update(Clock * clk);

int main() {
    // 初始化时钟
    Clock clk;
    Clock_init(&clk, LOW);

    Bit QA, QB, QC, QD;

    QA = QB = QC = QD = LOW;

    Bit prevQA = QA;

    Clock clkB = {.initialized = true, .current = QA, .previous = prevQA, .update = clkB_update};
    Clock stamp = {.initialized = true, .current = LOW, .previous = LOW};


    printf("74LS290 Counter Simulation\n");
    printf("Counting...\n");
    printf("QD=%d, QC=%d, QB=%d, QA=%d\n", QD.value, QC.value, QB.value, QA.value);
    // 计数器模拟
    for (uint i = 1; i < 21; i++) {
        MSI_74LS290(&QA, &QB, &QC, &QD,
                     &clk, &stamp,
                    LOW, LOW, LOW, LOW);
        // clkB.current = QA;
        // clkB.previous = prevQA;
        // prevQA = QA;
        Clock_update(&clkB);
        MSI_74LS290(&QA, &QB, &QC, &QD,
                     &stamp, &clkB,
                    LOW, LOW, LOW, LOW);
        if (i & 1)
            printf("QD=%u, QC=%u, QB=%u, QA=%u\n", QD.value, QC.value, QB.value, QA.value);
        Clock_update(&clk);
    }

    return 0;
}

void clkB_update(Clock * clk) {
    static uint count = 0;
    switch (count % 4) {
        case 0:
            clk->current = HIGH;
            clk->previous = LOW;
            break;
        case 1:
            clk->current = HIGH;
            clk->previous = HIGH;
            break;
        case 2:
            clk->current = LOW;
            clk->previous = HIGH;
            break;
        case 3:
            clk->current = LOW;
            clk->previous = LOW;
            break;
        default:
            break;
    }
    count++;
    return;
}
