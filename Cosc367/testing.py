from lab11 import *

class GetPrint:
    def __init__(self):
        self.output = []
    
    def write(self, *txt):
        txt = [str(i) for i in txt]
        txt = " ".join(txt)
        if txt != " " or txt != "":
            self.output.append(txt)

    def get(self):
        return self.output

    def clear(self):
        self.output = []

filename = "tester.txt"

with open(filename, 'r') as f:
    lines = f.readlines()

for i in range(len(lines)-1, -1, -1):
    lines[i] = lines[i].strip()
    if "student_answer" in lines[i]:
        lines[i] = "end of output"
    # get rid of blank lines and tabs
    if lines[i] == '': 
        # if 2 or 3 blank lines in a row, answers is next line
        if lines[i-1].strip() == '' and lines[i-2].strip() == '':
            lines[i-2] = "end of code"
        del lines[i]
    if lines[i] == 'print()':
        del lines[i]
            

del lines[0]
lines.append("end of output")
# States
ANSWERS = 0
TESTS = 1

tests = []
answers = []

code = ""
output = []
state = TESTS

for line in lines:
    if state == ANSWERS:
        if line == "end of output":
            answers.append(output)
            output = []
            state = TESTS
            continue
        output.append(line)
    if state == TESTS:
        if line == "end of code":
            tests.append(code)
            code = ""
            state = ANSWERS
            continue
        code += line + "\n"

# run tests
log = GetPrint()
stdout = print

def run_code(code):
    print = log.write
    err = False
    try:
        exec(code)
    except Exception as e:
        print(e)
        err = True
    print = stdout
    if err:
        print("Error in code")
        print("Code:")
        print(code)

# for test in tests:
#     print("Code:")
#     print(test)
#     run_code(test)
#     print("Your output:")
#     output = log.get()
#     log.clear()
#     print(output)


for i in range(len(tests)):
    print("Test", i+1)
    run_code(tests[i])
    output = log.get()
    if output == answers[i]:
        print("Correct!")
    else:
        print("Incorrect")
        print("Your output:")
        for line in output:
            print(line)
        print("Correct output:")
        for line in answers[i]:
            print(line)
    log.clear()
    print()

    

