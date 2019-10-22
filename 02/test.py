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

test ('./main.exe 123 a123', 0, [b'0'])
test ('./main.exe 10 a1 a2 a3 a4', 0, [b'0',b'1',b'3',b'6'])
test ('./main.exe 100 a10 r a20 a30 r', 0, [b'0', b'0', b'20'])
test ('./main.exe 1 a-1', 1, [b'Problem in allocation'])
test ('./main.exe', 1, [b'No argument'])
test ('./main.exe a1000000000000000000000', 1, [b'Problem in allocation'])