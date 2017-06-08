import { app, h } from 'hyperapp'

// Initialize / render hyperapp app
app({
  state: xdef,
  view: state => <div>{state}</div>
})
