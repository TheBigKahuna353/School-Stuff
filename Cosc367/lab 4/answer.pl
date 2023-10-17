
solution(V1,V2,V3,H1,H2,H3) :- 
    word(V1,_,V1H1,_,V1H2,_,V1H3,_),
    word(V2,_,V2H1,_,V2H2,_,V2H3,_),
    word(V3,_,V3H1,_,V3H2,_,V3H3,_),
    word(H1,_,V1H1,_,V2H1,_,V3H1,_),
    word(H2,_,V1H2,_,V2H2,_,V3H2,_),
    word(H3,_,V1H3,_,V2H3,_,V3H3,_),
    V1 \= V2, V1 \= V3, V1 \= H1, V1 \= H2, V1 \= H3,
    V2 \= V3, V2 \= H1, V2 \= H2, V2 \= H3,
    V3 \= H1, V3 \= H2, V3 \= H3,
    H1 \= H2, H1 \= H3,
    H2 \= H3.