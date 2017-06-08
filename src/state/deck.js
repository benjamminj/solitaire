import { SUITS } from '../constants'

const genCards = (suit, prevId) => Array.from(new Array(13)).map((card, i) => ({
  id: prevId + i,
  visible: false,
  rank: i + 1,
  suit,
}))

const genDeck = suits => suits.reduce((acc, suit, i) => acc.concat([...genCards(suit, i * 13)]), [])

// exports an unshuffled deck containing all of the cards
export default genDeck(SUITS)
