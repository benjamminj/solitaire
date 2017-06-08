import { app, h } from 'hyperapp'
import state from './state'

// Initialize / render hyperapp app
app({
  state,
  view: state => <div>{state}</div>
})
