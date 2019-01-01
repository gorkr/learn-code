from base import Stack
from timeit import Timer

def divideBy2(decNumber):
    remstack = Stack()

    while decNumber > 0:
        remstack.push(decNumber % 2)
        decNumber //= 2

    binString = ""
    while not remstack.isEmpty():
        binString += str(remstack.pop())
        #binString = binString.join(str(remstack.pop()))  #join方法反而耗时更长

    return binString

print(divideBy2(42))
t = Timer("divideBy2(42)", "from __main__ import divideBy2")
print(t.timeit(number=1000))
