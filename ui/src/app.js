import React, { Component } from 'react'
import { createMuiTheme } from '@material-ui/core/styles'
import { blue, indigo } from '@material-ui/core/colors'
import { ThemeProvider } from '@material-ui/core'
import 'firebase/database';
import * as firebase from 'firebase/app';
import { FirebaseDatabaseProvider } from '@react-firebase/database'
import Main from './components/main'
import { firebaseConfig } from './config'

const theme = createMuiTheme({
    palette: {
        secondary: {
            main: blue[900],
        },
        primary: {
            main: indigo[700],
        },
    },
    typography: {
        // Use the system font instead of the default Roboto font.
        fontFamily: [
            'Lato',
            'sans-serif',
        ].join(','),
    },
})

class App extends Component {
    render() {
        return (
            <div>
                <ThemeProvider theme={ theme }>
                    <FirebaseDatabaseProvider firebase={ firebase } { ...firebaseConfig }>
                        <Main />
                    </FirebaseDatabaseProvider>
                </ThemeProvider>
            </div>
        )
    }
}

export default App
