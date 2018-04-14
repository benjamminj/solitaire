import { createStore as reduxCreateStore } from "redux"
import enhancers from './enhancers'
import reducer from './reducer'

const createStore = () => reduxCreateStore(reducer, enhancers())
export default createStore