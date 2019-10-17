import subprocess
import time

def run(command):
    process = subprocess.Popen(command, shell=True, stdout=subprocess.PIPE, stderr=subprocess.STDOUT)
    out = process.stdout.readlines()
    code = process.wait()
    return code, out

def test(command, expected_code, expected_value):
    print (command)
    code, out = run(command)
    if code != expected_code:
        print (expected_code, '(expected) !=', code)
        return
    i = 0
    for line in out:
        try:
            if int(line.rstrip()) != int(expected_value[i]):
                print (expected_value[i], '(expected) !=', line.rstrip())
                return
            i += 1
        except ValueError:
            print ('invalid output')
            return
        except IndexError:
            print ('invalid output')
            return
    if i != len(expected_value):
        print ('empty output')
        return
    print ('ok')

test('./calc.exe "2"', 0,  ['2'])
test('./calc.exe "-2"', 0, [ '-2' ])
test('./calc.exe "2 + 2"', 0, [ '4' ])
test('./calc.exe "2 + 2   "', 0, [ '4' ])
test('./calc.exe "2 +- 2"', 0, [ '0' ])
test('./calc.exe "   2+-4"', 0, [ '-2' ])
test('./calc.exe "-    4- -4"', 0, [ '0' ])
test('./calc.exe "2-3*4+-5/2"', 0, [ '-12' ])
test('./calc.exe "2-3*4*2+1--2+-5/2"', 0, [ '-21' ])
