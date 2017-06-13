import { SUITS } from '../constants'

const foundation = SUITS.reduce((acc, suit) => {
  acc[suit] = []
  return acc
}, {})

export default foundation
