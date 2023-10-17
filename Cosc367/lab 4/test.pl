word(astante, a,s,t,a,n,t,e). 
word(astoria, a,s,t,o,r,i,a). 
word(baratto, b,a,r,a,t,t,o). 
word(cobalto, c,o,b,a,l,t,o). 
word(pistola, p,i,s,t,o,l,a). 
word(statale, s,t,a,t,a,l,e).

test_answer :-
    findall((V1,V2,V3,H1,H2,H3), solution(V1,V2,V3,H1,H2,H3), L),
    sort(L,S), 
    foreach(member(X,S), (write(X), nl)).

test_answer :- write('Wrong answer!').