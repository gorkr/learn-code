from base import Stack

def parChecker(symbolString):
    """检查括弧是否匹配, stack实现

    symbolString -- string 括弧字符串
    """

    s = Stack()
    balanced = True  #括弧数量不匹配时为False.
    index = 0  #迭代所有字符.
    while index < len(symbolString) and balanced:
        symbol = symbolString[index]
        if symbol in "([{":
            s.push(symbol)
        else:
            if s.isEmpty():
                balanced = False
            else:
                if not matches(s.pop(), symbol):
                    balanced = False

        index +=1

    if balanced and s.isEmpty():
        return True
    else:
        return False

def matches(open, close):
    opens = "([{"
    closes = ")]}"
    return opens.index(open) == closes.index(close)


print(parChecker("{()({[[][[]{}]]})}"))
print(parChecker("{}{}{}{}[((()]"))
