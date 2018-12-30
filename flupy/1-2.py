#熟悉使用doctest
#一个简单的二维向量类

""
%s是将变量传到str()函数中，结果是将变量转化适合人阅读的格式

%r是将变量穿到repr()函数中，结果是将变量转化成适合机器阅读的格式
"""

from math import hypot
# hypot 返回欧几里德范数 sqrt(x*x + y*y)。

class Vector:
    '''
    >>>v1 = Vector(2, 4)
    >>>v2 = Vector(2, 1)
    >>>v2 + v1
    Vector(4, 5)
    >>>v = Vector(3, 4)
    >>>abs(v)
    5.0
    >>>v * 3
    Vector(9, 12)
    >>>abs(v * 3)
    15.0
    '''

    def __init__(self, x=0, y=0):
        self.x = x
        self.y = y

    def __repr__(self):
        # 如果使用%s 就变为Vector('x', 'y') 显然不正确
        return 'Vector(%r, %r)' % (self.x, self.y)

    def __abs__(self):
        return hypot(self.x, self.y)

    def __bool__(self):
        return bool(self.x or self.y)

    def __add__(self, other):
        x = self.x + other.x
        y = self.y + other.y
        return Vector(x, y)

    def __mul__(self, scalar):
        return Vector(self.x * scalar, self.y * scalar)

if __name__ == '__main__':
    import doctest
    doctest.testmod()
