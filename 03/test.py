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
        print (expected_code, '(expected1) !=', code)
        return
    i = 0
    for line in out:
        try: 
            if line.rstrip() != expected_value[i]:
                print (expected_value[i], '(expected2) !=', line.rstrip())
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

test ('./main.exe e 1 2', 0, [b'1'])
test ('./main.exe r', 0, [b'5'])
test ('./main.exe c', 0, [b'3'])
test ('./main.exe !', 0, [b'1'])
test ('./main.exe =', 0, [b'0'])
test ('./main.exe m 7', 0, [b'7'])
test ('./main.exe m 9', 0, [b'9'])
test ('./main.exe', 1, [b'No argument!'])
test ('./main.exe m', 1, [b'More arguments expected (multiplier)!'])
test ('./main.exe t', 1, [b'Wrong command!'])
test ('./main.exe e 6 1', 1, [b'Index problem with rows!'])
test ('./main.exe e 1 6', 1, [b'Index problem with colomns!'])
test ('./main.exe e 1', 1, [b'More arguments expected (rows, colomns)!'])

