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
