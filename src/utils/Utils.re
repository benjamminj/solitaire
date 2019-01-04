let isCardSelected = (selectedCardId, cardId) => {
  switch (selectedCardId) {
    | None => false
    | Some(id) => id == cardId
  }
}