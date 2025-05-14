// filepath: include/bit.h

#ifndef BIT_H
#define BIT_H

typedef struct {
    unsigned char value : 1; // 1 bit
} Bit;

#define HIGH ((Bit){.value = 1})
#define LOW ((Bit){.value = 0})

// 判断位是否为高电平
#define isHIGH(a) (((Bit) a).value == HIGH.value)

// 判断位是否为低电平
#define isLOW(a) (((Bit) a).value == LOW.value)

typedef unsigned int uint;

// nand 与非门
Bit nand_gate(uint num_inputs, ...);
// not 非门
Bit not_gate(Bit a);
// and 与门
Bit and_gate(uint num_inputs, ...);
// or 或门
Bit or_gate(uint num_inputs, ...);
// xor 异或门
Bit xor_gate(uint num_inputs, ...);
// nor 或非门
Bit nor_gate(uint num_inputs, ...);

#endif // BIT_H