def shuffle(s, t):
    """returns the shuffle s||t of strings s and t. Return the result as a set of strings, that is, without duplicates."""
    if s == '':
        return {t}
    if t == '':
        return {s}
    return {s[0] + x for x in shuffle(s[1:], t)} | {t[0] + x for x in shuffle(s, t[1:])}



def shuffle_language(A, B):
    """returns the shuffle A||B of languages A and B. Return the result as a set of strings, that is, without duplicates.
    If you want to use your function from the previous question, you will need to include it as part of your answer to this question."""
    return {x for a in A for b in B for x in shuffle(a, b)}

print(sorted(shuffle_language({'ab'}, {'cd', 'e'})))