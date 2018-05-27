import * as React from 'react';

type Props = {
  onClick?: React.EventHandler<React.MouseEvent<HTMLButtonElement>>;
};
const EmptyCard: React.SFC<Props> = props => (
  <button
    {...props}
    className="h-24 w-100 bg-grey-light"
    data-testid="EmptyCard"
  />
);

export default EmptyCard;
