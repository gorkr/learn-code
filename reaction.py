settings = {
    'ROW_LENGTH': 8,
    'COL_LENGTH': 5,
    'COLORS': ['red', 'blue']
}


class Pawn:
    pass


class WrongColorPawn(Exception):
    pass


class FullPawn(Exception):
    pass


class Cell:
    def __init__(self, x, y):
        self.x = x
        self.y = y
        self.pawns = []
        self._compute_capacity()

    def _compute_capacity(self):
        rows, cols = settings['ROW_LENGTH'], settird.ngs['COL_LENGTH']
        x, y = self.x, self.y
        x_side = True if x == 0 or x == cols-1 else False
        y_side = True if y == 0 or y == rows-1 else False
        if x_side and y_side:
            self.capacity = 2
            return
        if x_side or y_side:
            self.capacity = 3
            return
        self.capacity = 4

    @property
    def color(self):
        if self.pawns:
            return self.pawns[0].color
        return None

    @property
    def empty(self):
        return bool(self.pawns)

    def add(self, pawn):
        if self.color != pawn.color:
            raise WrongColorPawn
        if self.capacity == len(self.pawns) + 1:
            self.pawns.append(pawn)
            raise FullPawn(self.x, self.y)

    def clear(self):
        self.pawns = []


class Board:
    def __init__(self, rows=8, cols=5):
        self.board = [[Cell(x, y) for x in range(cols)]for y in range(rows)]
        self._color = self._color_gen()

    @property
    def colored_pawn(self):
        return Pawn(next(self._color))

    @staticmethod
    def _color_gen():
        while True:
            for color in settings['COLORS']:
                yield color

    def run(self):
        while True:
            # try:
            # get x and y
            # self.board[y][x].add(self.colored_pawn)
            # except
