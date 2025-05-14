// filepath: include/sequential.h

#ifndef SEQUENTIAL_H
#define SEQUENTIAL_H

#include "bit.h"
#include "clock.h"

// R-S 锁存器
void RS_latch(Bit * pQ, Bit * pQn, Bit S, Bit R);

// 门控 R-S 锁存器
void gated_RS_latch(Bit * pQ, Bit * pQn, Bit G, Bit S, Bit R);

// D 锁存器
void D_latch(Bit * pQ, Bit * pQn, Bit G, Bit D);

// D 触发器
void D_flip_flop(Bit * pQ, Bit * pQn, Bit D, Clock const * clk, bool posedge_trigger);

// JK 触发器
void JK_flip_flop(Bit * pQ, Bit * pQn, Bit J, Bit K, Clock const * clk, bool posedge_trigger);

// T 触发器
void T_flip_flop(Bit * pQ, Bit * pQn, Bit T, Clock const * clk, bool posedge_trigger);

/*74LS290 异步2-5-10计数器
* @param pQA, pQB, pQC, pQD: 计数器的输出位（高有效）
* @param A, B: 时钟输入（下降沿触发）
* @param R01, R02: 异步清0（高有效）
* @param S91, S92: 异步置9（高有效）
*/
void MSI_74LS290(Bit * pQA, Bit * pQB, Bit * pQC, Bit * pQD,
                 Clock const * A, Clock const * B,
                 Bit R01, Bit R02, Bit S91, Bit S92);

#endif // SEQUENTIAL_H