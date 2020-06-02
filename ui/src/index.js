import React from 'react'
import ReactDOM from 'react-dom'
import App from './views/planterAppView'
import * as serviceWorker from './serviceWorker'

ReactDOM.render(
  <React.StrictMode>
    <App />
  </React.StrictMode>,
  document.getElementById('root')
)

serviceWorker.unregister()
