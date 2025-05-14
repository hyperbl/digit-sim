// src/logic_gates.c
#include "bit.h"
#include <stdarg.h>

Bit nand_gate(uint num_inputs, ...) {
    va_list inputs;
    va_start(inputs, num_inputs);

    Bit output = va_arg(inputs, Bit);
    if (output.value == 0) {
        va_end(inputs);
        output.value = 1;
        return output;
    }

    for (uint i = 1; i < num_inputs; i++) {
        Bit input = va_arg(inputs, Bit);
        if (input.value == 0) {
            output.value = 0;
            break;
        }
        output.value &= input.value;
    }
    output.value = !output.value;
    va_end(inputs);
    return output;
}

Bit not_gate(Bit a) {
    // return nand_gate(2, a, a);
    return (Bit){!a.value};
}

Bit and_gate(uint num_inputs, ...) {
    va_list inputs;
    va_start(inputs, num_inputs);

    Bit output = va_arg(inputs, Bit);
    if (output.value == 0) {
        va_end(inputs);
        return output;
    }

    for (uint i = 1; i < num_inputs; i++) {
        Bit input = va_arg(inputs, Bit);
        if (input.value == 0) {
            output.value = 0;
            break;
        }
        output.value &= input.value;
    }
    va_end(inputs);
    return output;
}

Bit or_gate(uint num_inputs, ...) {
    va_list inputs;
    va_start(inputs, num_inputs);

    Bit output = va_arg(inputs, Bit);
    if (output.value == 1) {
        va_end(inputs);
        return output;
    }

    for (uint i = 1; i < num_inputs; i++) {
        Bit input = va_arg(inputs, Bit);
        if (input.value == 1) {
            output.value = 1;
            break;
        }
        output.value |= input.value;
    }
    va_end(inputs);
    return output;
}

Bit xor_gate(uint num_inputs, ...) {
    va_list inputs;
    va_start(inputs, num_inputs);

    Bit output = va_arg(inputs, Bit);
    for (uint i = 1; i < num_inputs; i++) {
        Bit input = va_arg(inputs, Bit);
        output.value ^= input.value;
    }
    va_end(inputs);
    return output;
}

Bit nor_gate(uint num_inputs, ...) {
    va_list inputs;
    va_start(inputs, num_inputs);

    Bit output = va_arg(inputs, Bit);
    if (output.value == 1) {
        va_end(inputs);
        output.value = 0;
        return output;
    }

    for (uint i = 1; i < num_inputs; i++) {
        Bit input = va_arg(inputs, Bit);
        if (input.value == 1) {
            output.value = 1;
            break;
        }
        output.value |= input.value;
    }
    output.value = !output.value;
    va_end(inputs);
    return output;
}