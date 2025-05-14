// src/combinational.c
#include "combinational.h"

void MSI_74LS148(Bit * pA2, Bit * pA1, Bit * pA0, Bit * pGS, Bit * pEO, 
                 Bit EI, Bit IN0, Bit IN1, Bit IN2, Bit IN3, 
                 Bit IN4, Bit IN5, Bit IN6, Bit IN7) {
    *pA2 = and_gate(4,
        or_gate(2, EI, IN7),
        or_gate(2, EI, IN6),
        or_gate(2, EI, IN5),
        or_gate(2, EI, IN4)
    );
    *pA1 = and_gate(4,
        or_gate(2, EI, IN7),
        or_gate(2, EI, IN6),
        or_gate(4, 
            EI,
            not_gate(IN5),
            not_gate(IN4),
            IN3
        ),
        or_gate(4,
            EI,
            not_gate(IN5),
            not_gate(IN4),
            IN2
        )
    );
    *pA0 = and_gate(4,
        or_gate(2, EI, IN7),
        or_gate(3,
            EI, IN5,
            not_gate(IN6)
            
        ),
        or_gate(4,
            EI, IN3,
            not_gate(IN6),
            not_gate(IN4)
        ),
        or_gate(5,
            EI, IN1, 
            not_gate(IN6), 
            not_gate(IN4), 
            not_gate(IN2)
        )
    );
    *pEO = nand_gate(9,
        not_gate(EI),
        IN0, IN1, IN2, IN3,
        IN4, IN5, IN6, IN7
    );
    *pGS = nand_gate(2,
        not_gate(EI), 
        *pEO
    );
    return;
}

void MSI_74LS138(Bit * pY0, Bit * pY1, Bit * pY2, Bit * pY3, 
    Bit * pY4, Bit * pY5, Bit * pY6, Bit * pY7,
    Bit G1, Bit G2A, Bit G2B,
    Bit A, Bit B, Bit C) {
    Bit G = or_gate(3,
        not_gate(G1),
        G2A, G2B
    );
    *pY0 = or_gate(4,
        G, 
        C, B, A
    );
    *pY1 = or_gate(4,
        G,
        C, B, not_gate(A)
    );
    *pY2 = or_gate(4,
        G,
        C, not_gate(B), A
    );
    *pY3 = or_gate(4,
        G,
        C, not_gate(B), not_gate(A)
    );
    *pY4 = or_gate(4,
        G,
        not_gate(C), B, A
    );
    *pY5 = or_gate(4,
        G,
        not_gate(C), B, not_gate(A)
    );
    *pY6 = or_gate(4,
        G,
        not_gate(C), not_gate(B), A
    );
    *pY7 = or_gate(4,
        G,
        not_gate(C), not_gate(B), not_gate(A)
    );
    return;
}

void half_adder(Bit * pS, Bit * pC, Bit A, Bit B) {
    *pS = xor_gate(2, A, B);
    *pC = and_gate(2, A, B);
    return;
}

void full_adder(Bit * pS, Bit * pCout, Bit A, Bit B, Bit Cin) {
    Bit S1, C1, C2;
    half_adder(&S1, &C1, A, B);
    half_adder(pS, &C2, S1, Cin);
    *pCout = or_gate(2, C1, C2);
    return;
}

void MSI_74LS283(Bit * pS3, Bit * pS2, Bit * pS1, Bit * pS0, 
    Bit * pC3, Bit A3, Bit A2, Bit A1, Bit A0,
    Bit B3, Bit B2, Bit B1, Bit B0, Bit C0) {
    Bit G0, G1, G2, G3;
    Bit P0, P1, P2, P3;
    G0 = nand_gate(2, A0, B0);
    G1 = nand_gate(2, A1, B1);
    G2 = nand_gate(2, A2, B2);
    G3 = nand_gate(2, A3, B3);
    P0 = nor_gate(2, A0, B0);
    P1 = nor_gate(2, A1, B1);
    P2 = nor_gate(2, A2, B2);
    P3 = nor_gate(2, A3, B3);
    Bit Cin1, Cin2, Cin3;
    Cin1 = nor_gate(2, P0, 
            and_gate(2, G0,
                not_gate(C0)));
    Cin2 = nor_gate(3, P1,
            and_gate(2, G1, P0),
            and_gate(3, G1, G0, 
                not_gate(C0)));
    Cin3 = nor_gate(4, P2,
            and_gate(2, G2, P1),
            and_gate(3, G2, G1, P0),
            and_gate(4, G2, G1, G0,
                not_gate(C0)));
    *pC3 = nor_gate(5, P3,
            and_gate(2, G3, P2),
            and_gate(3, G3, G2, P1),
            and_gate(4, G3, G2, G1, P0),
            and_gate(5, G3, G2, G1, G0,
                not_gate(C0)));
    *pS0 = xor_gate(2, C0,
            and_gate(2, G0, not_gate(P0)));
    *pS1 = xor_gate(2, Cin1,
            and_gate(2, G1, not_gate(P1)));
    *pS2 = xor_gate(2, Cin2,
            and_gate(2, G2, not_gate(P2)));
    *pS3 = xor_gate(2, Cin3,
            and_gate(2, G3, not_gate(P3)));
    return;
}

void MSI_74LS85(Bit * pOG, Bit * pOE, Bit * pOL, 
    Bit A3, Bit A2, Bit A1, Bit A0,
    Bit B3, Bit B2, Bit B1, Bit B0,
    Bit IG, Bit IE, Bit IL) {
    Bit P0, P1, P2, P3;
    Bit E0, E1, E2, E3;
    P0 = nand_gate(2, A0, B0);
    P1 = nand_gate(2, A1, B1);
    P2 = nand_gate(2, A2, B2);
    P3 = nand_gate(2, A3, B3);
    E0 = not_gate(xor_gate(2, A0, B0));
    E1 = not_gate(xor_gate(2, A1, B1));
    E2 = not_gate(xor_gate(2, A2, B2));
    E3 = not_gate(xor_gate(2, A3, B3));
    *pOG = and_gate(6,
        nand_gate(2, B3, P3),
        nand_gate(3, B2, P2, E3),
        nand_gate(4, B1, P1, E2, E3),
        nand_gate(5, B0, P0, E1, E2, E3),
        nand_gate(5, E0, E1, E2, E3, IL),
        nand_gate(5, E0, E1, E2, E3, IE)
    );
    *pOE = and_gate(5, E0, E1, E2, E3, IE);
    *pOL = and_gate(6,
        nand_gate(5, E0, E1, E2, E3, IE),
        nand_gate(5, E0, E1, E2, E3, IG),
        nand_gate(5, A0, P0, E1, E2, E3),
        nand_gate(4, A1, P1, E2, E3),
        nand_gate(3, A2, P2, E3),
        nand_gate(2, A3, P3)
    ); 
    return;
}

void MSI_74LS153(Bit * pYa, Bit * pYb, Bit S1, Bit S0,
    Bit Ea, Bit D3a, Bit D2a, Bit D1a, Bit D0a,
    Bit Eb, Bit D3b, Bit D2b, Bit D1b, Bit D0b) {
    *pYa = nor_gate(2, Ea,
        nor_gate(4,
            and_gate(3, S1, S0, D3a),
            and_gate(3, S1, not_gate(S0), D2a),
            and_gate(3, not_gate(S1), S0, D1a),
            and_gate(3, not_gate(S1), not_gate(S0), D0a)
        )
    );
    *pYb = nor_gate(2, Eb,
        nor_gate(4,
            and_gate(3, not_gate(S1), not_gate(S0), D0b),
            and_gate(3, not_gate(S1), S0, D1b),
            and_gate(3, S1, not_gate(S0), D2b),
            and_gate(3, S1, S0, D3b)
        )
    );
    return;
}

void MSI_74LS151(Bit * pY, Bit S2, Bit S1, Bit S0,
    Bit E, Bit D7, Bit D6, Bit D5, Bit D4,
    Bit D3, Bit D2, Bit D1, Bit D0) {
    *pY = nor_gate(2, E,
        nor_gate(8,
            and_gate(4, S2, S1, S0, D7),
            and_gate(4, S2, S1, not_gate(S0), D6),
            and_gate(4, S2, not_gate(S1), S0, D5),
            and_gate(4, S2, not_gate(S1), not_gate(S0), D4),
            and_gate(4, not_gate(S2), S1, S0, D3),
            and_gate(4, not_gate(S2), S1, not_gate(S0), D2),
            and_gate(4, not_gate(S2), not_gate(S1), S0, D1),
            and_gate(4, not_gate(S2), not_gate(S1), not_gate(S0), D0)
        )
    );
    return;
}