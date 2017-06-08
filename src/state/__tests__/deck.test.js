import test from 'ava'
import deck from '../deck'

test('should contain 52 cards', t => {
  t.is(deck.length, 52)
})

test('should have incrementing IDs', t => {
  deck.forEach((card, i) => {
    const next = deck[i + 1]
    if (next) {
      t.is(card.id + 1, next.id)
    }
  })
})

test('should have all cards facedown initially', t => {
  t.false(deck.includes(card => card.visible === true))
})
