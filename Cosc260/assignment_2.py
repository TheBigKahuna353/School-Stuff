
def lcs(s1, s2):
    """lcs(s1, s2) -> longest common subsequence of s1 and s2"""
    table = [[0 for i in range(len(s2)+1)] for j in range(len(s1)+1)]
    for i in range(len(s1)+1):
        for j in range(len(s2)+1):
            if i == 0 or j == 0:
                table[i][j] = 0
            elif s1[i-1] == s2[j-1]:
                table[i][j] = table[i-1][j-1] + 1
            else:
                table[i][j] = max(table[i-1][j], table[i][j-1])

    best = ""
    i, j = len(s1), len(s2)
    while i > 0 and j > 0:
        if s1[i-1] == s2[j-1]:
            best = s1[i-1] + best
            i -= 1
            j -= 1
        elif table[i-1][j] > table[i][j-1]:
            i -= 1
        else:
            j -= 1
    return best

def line_edits(s1, s2):
    """line_edits(s1, s2) -> number of line edits required to transform s1 into s2"""
    s1 = s1.splitlines()
    s2 = s2.splitlines()
    if len(s1) == 0:
        return [("I", "", s2[i]) for i in range(len(s2))]
    if len(s2) == 0:
        return [("D", s1[i], "") for i in range(len(s1))]
    table = [[0 for i in range(len(s2)+1)] for j in range(len(s1)+1)]
    for i in range(len(s1)+1):
        for j in range(len(s2)+1):
            if i == 0 and j == 0:
                table[i][j] = 0
            elif i == 0:
                table[i][j] = j
            elif j == 0:
                table[i][j] = i
            elif s1[i-1] == s2[j-1]:
                table[i][j] = table[i-1][j-1]
            else:
                table[i][j] = min(table[i-1][j], table[i][j-1], table[i-1][j-1]) + 1

    return backtrack(table, s1, s2)

def backtrack(table, s1, s2):
    """backtrack(table, s1, s2) -> list of line edits required to transform s1 into s2"""
    results = []
    i, j = len(s1), len(s2)
    while i > 0 or j > 0:
        if s1[max(i-1, 0)] == s2[max(j-1, 0)]:
            i -= 1
            j -= 1
            results.append(("C", s1[i], s2[j]))
        else:
            minn = min((table[i-1][j-1], "S"), (table[i-1][j], "D"), (table[i][j-1], "I"), key=lambda x: x[0])
            if minn[1] == "D":
                results.append(("D", s1[i-1], ""))
                i -= 1
            elif minn[1] == "I":
                results.append(("I", "", s2[j-1]))
                j -= 1
            else:
                r1, r2 = highlight_line(s1[i-1], s2[j-1])
                results.append(("S", r1, r2))
                i -= 1
                j -= 1
    results.reverse()
    return results

def highlight_line(s1, s2):
    """highlight_line(s1, s2) -> shows differences in lines"""
    extras = lcs(s1, s2)
    result1 = ""
    for i in range(len(s1)):
        if s1[i] in extras:
            result1 += s1[i]
        else:
            result1 += "[[%s]]" % s1[i]
    result2 = ""
    for i in range(len(s2)):
        if s2[i] in extras:
            result2 += s2[i]
        else:
            result2 += "[[%s]]" % s2[i]
    return result1, result2


s1 = "Line1\nLine 2a\nLine3\nLine4\n"
s2 = "Line5\nline2\nLine3\n"
table = line_edits(s1, s2)
for row in table:
    print(row)

