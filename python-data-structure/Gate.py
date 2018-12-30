class logicGate:
    """门电路的父类,仅实现标签"""

    def __init__(self, n):
        self.lable = n
        self.output = None

    def getLable(self):
        return self.lable

    def getOutput(self):
        self.output = self.performGateLogic()  #先不实现performGateLogic(),
                                               #子类中决定如何实现
        return self.output


class BinaryGate(logicGate):
    """两个输入端的门电路,作为与门和或门的父类"""

    def __init__(self, n):
        logicGate.__init__(self, n)

        self.pinA = None
        self.pinB = None

    def getPinA(self):
        if self.pinA == None:
            return int(input("Enter Pin A input for gate" + self.getLable()+
                         "-->"))
        else:
            return self.pinA.getFrom().getOutput()

    def getPinB(self):
        if self.pinB == None:
            return int(input("Enter Pin B input for gate" + self.getLable()+
                         "-->"))
        else:
            return self.pinB.getFrom().getOutput()

    def setNextPin(self, source):
        '''选择一条pin与source连接

        source -- a gate, the end of
        '''
        if self.pinA == None:
            self.pinA = source
        else:
            if self.pinB == None:
                self.pinB = source
            else:
                raise RuntimeError("Error: NO EMPTY PINS")


class UnaryGate(logicGate):
    """单个输入的门电路,作为非门的父类"""

    def __init__(self, n):
        logicGate.__init__(self, n)

        self.pin = None

    def getPin(self):
        if self.pin == None:
            return int(input("Enter Pin input for gate" + self.getLable()+
                         "-->"))
        else:
            return self.pin.getFrom().getOutput()

    def setNextPin(self, source):
        '''选择一条pin与source连接

        source -- a gate, the end of
        '''
        if self.pin == None:
            self.pin = source
        else:
            raise RuntimeError("Error: NO EMPTY PINS")


class AndGate(BinaryGate):
    """与门,做与运算,return 0/1."""

    def __init__(self, n):
        BinaryGate.__init__(self, n)

    def performGateLogic(self):
        a = self.getPinA()
        b = self.getPinB()
        if a==1 and b==1:
            return 1
        else:
            return 0


class OrGate(BinaryGate):
    """或门,做或运算,return 0/1."""

    def __init__(self, n):
        BinaryGate.__init__(self, n)

    def performGateLogic(self):
        a = self.getPinA()
        b = self.getPinB()
        if a==1 or b==1:
            return 1
        else:
            return 0


class NoGate(UnaryGate):
    """非门,非运算,return 0/1."""

    def __init__(self, n):
        UnaryGate.__init__(self, n)

    def performGateLogic(self):
        a = self.getPin()
        if a==1:
            return 0
        else:
            return 1


class Connector:
    """门电路的连接器,将前门的输出端连接到后门的输入端"""

    def __init__(self, fgate, tgate):
        self.fromgate = fgate
        self.togate = tgate

        tgate.setNextPin(self)  #门类实现

    def getFrom(self):
        return self.fromgate

    def getTo(self):
        return self.togate




if __name__ == "__main__":
    g1 = AndGate("G1")
    g2 = AndGate("G2")
    g3 = OrGate("G3")
    g4 = NoGate("G4")
    c1 = Connector(g1, g3)
    c2 = Connector(g2, g3)
    c3 = Connector(g3, g4)
    print(g4.getOutput())
