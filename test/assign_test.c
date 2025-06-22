#include "bit.h"
#include "utils.h"
#include "sequential.h"

void RS_latch_with_assign(Bit * pQ, Bit * pQn, Bit S, Bit R) {
  if (isLOW(S) && isLOW(R)) {
      printf("[WARN] RS_latch: invalid state\n");
      *pQ = *pQn = HIGH;
      return;
  }
  assign_stable(*pQ, (nand_gate(2, S, (*pQn = nand_gate(2, R, *pQ)))));
}

int main() {
  uint test_seq[] = {1, 3, 2, 3};
  printf("== RS Latch with Assign Test ==\n");
  Bit Q = LOW, Qn = LOW;
  foreach_ptr(i, test_seq, sizeof(test_seq) / sizeof(test_seq[0])) {
    Bit S = (i >> 2) ? (Bit){i & 1} : (Bit){(i >> 1) & 1};
    Bit R = (i >> 2) ? (Bit){(i >> 1) & 1} : (Bit){i & 1};
    RS_latch_with_assign(&Q, &Qn, S, R);
    printf("S: %u, R: %u, Q: %u, Qn: %u\n", 
           S.value, R.value, Q.value, Qn.value);
  }
  printf("== RS Latch without Assign ==\n");
  Q = LOW, Qn = LOW;
  foreach_ptr(i, test_seq, sizeof(test_seq) / sizeof(test_seq[0])) {
    Bit S = (i >> 2) ? (Bit){i & 1} : (Bit){(i >> 1) & 1};
    Bit R = (i >> 2) ? (Bit){(i >> 1) & 1} : (Bit){i & 1};
    RS_latch(&Q, &Qn, S, R);
    printf("S: %u, R: %u, Q: %u, Qn: %u\n", 
           S.value, R.value, Q.value, Qn.value);
  }
  printf("== Test completed ==\n");
  return 0;
}