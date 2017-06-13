import test from 'ava'
import foundation from '../foundation'
import { SUITS } from '../../constants'

test.only('should have keys as suits and empty arrays for values', t => {
  t.is(typeof foundation, 'object')

  SUITS.forEach(suit => {
    t.true(Array.isArray(foundation[suit]))
  })
})
