#有序的纸牌
import collections

Card = collections.namedtuple('Card',['rank','suit'])

class FrenchDeck(object):
    """docstring for FrenchDeck."""
    ranks = [str(n) for n in range(2, 11)] + list('JQKA')
    suits = 'spades diamonds clubs hearts'.split()
    def __init__(self):
        super(FrenchDeck, self).__init__()
        self._cards = [Card(rank, suit)for rank in ranks
                                       for rank in ranks]

    def __len__(self):
        return len(self._cards)

    def __getitem__(self, position):
        return self._cards[position]
