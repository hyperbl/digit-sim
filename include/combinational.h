// filepath: include/combinational.h

#ifndef COMBINATIONAL_H
#define COMBINATIONAL_H

#include "bit.h"

// 74LS148 优先编码器
void MSI_74LS148(Bit * pA2, Bit * pA1, Bit * pA0, Bit * pGS, Bit * pEO, 
                 Bit EI, Bit IN0, Bit IN1, Bit IN2, Bit IN3, 
                 Bit IN4, Bit IN5, Bit IN6, Bit IN7);

// 74LS138 3-8译码器
void MSI_74LS138(Bit * pY0, Bit * pY1, Bit * pY2, Bit * pY3, 
                 Bit * pY4, Bit * pY5, Bit * pY6, Bit * pY7,
                 Bit G1, Bit G2A, Bit G2B,
                 Bit A, Bit B, Bit C);

// 半加器
void half_adder(Bit * pS, Bit * pC, Bit A, Bit B);

// 全加器
void full_adder(Bit * pS, Bit * pCout, Bit A, Bit B, Bit Cin);

// MSI_74LS283 超前进位 4 位全加器
void MSI_74LS283(Bit * pS3, Bit * pS2, Bit * pS1, Bit * pS0, 
                 Bit * pC3, Bit A3, Bit A2, Bit A1, Bit A0,
                 Bit B3, Bit B2, Bit B1, Bit B0, Bit C0);

// MSI_74LS85 4 位比较器
void MSI_74LS85(Bit * pOG, Bit * pOE, Bit * pOL, 
                 Bit A3, Bit A2, Bit A1, Bit A0,
                 Bit B3, Bit B2, Bit B1, Bit B0,
                 Bit IG, Bit IE, Bit IL);

// MSI_74LS153 4 位多路选择器
void MSI_74LS153(Bit * pYa, Bit * pYb, Bit S1, Bit S0,
                 Bit Ea, Bit D3a, Bit D2a, Bit D1a, Bit D0a,
                 Bit Eb, Bit D3b, Bit D2b, Bit D1b, Bit D0b);

// MSI_74LS151 8 位多路选择器
void MSI_74LS151(Bit * pY, Bit S2, Bit S1, Bit S0,
                 Bit E, Bit D7, Bit D6, Bit D5, Bit D4,
                 Bit D3, Bit D2, Bit D1, Bit D0);


#endif // COMBINATIONAL_H