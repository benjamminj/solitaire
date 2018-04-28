import { Tableau, TableauRow, CardRefArray } from './types';

export const shuffleArray = (originalArray: any[]) => {
  // a little higher on memory, but small cost to pay for guaranteed immutability
  let arr = [...originalArray];
  let current = arr.length;
  let temp;
  let i;

  while (current) {
    i = Math.floor(Math.random() * current--)

    temp = arr[current]
    arr[current] = arr[i]
    arr[i] = temp
  }

  return arr;
}

const getNonFilledRow = (tableau: Tableau): string | null => {
  const keys = Object.keys(tableau).sort((a, b) => +a - +b);
  const rowNumber = keys.find((key: TableauRow) => tableau[key].length < +key);
  return rowNumber ? `${rowNumber}` : null;
};

type DealTableauCards = (cards: CardRefArray, tableau: Tableau) => Tableau;
export const dealTableauCards: DealTableauCards = (cards, originalTableau) => {
  const { tableau: dealtTableau } = cards.reduce(
    (acc: { row: TableauRow; tableau: Tableau }, card, i) => {
      const { row, tableau } = acc;

      if (row) {
        tableau[row].push(card);
      }

      return {
        row:
          row === '7' || row === null
            ? getNonFilledRow(acc.tableau)
            : `${+row + 1}`,
        tableau: acc.tableau,
      };
    },
    {
      row: getNonFilledRow(originalTableau),
      tableau: originalTableau,
    },
  );

  return dealtTableau;
};
