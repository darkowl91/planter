import React, { Component } from 'react'
import { createMuiTheme } from '@material-ui/core/styles'
import { blue, indigo } from '@material-ui/core/colors'
import { ThemeProvider } from '@material-ui/core'
import "firebase/database";
import * as firebase from "firebase/app";
import { FirebaseDatabaseProvider } from '@react-firebase/database'
import Main from '../components/main'

const theme = createMuiTheme({
    palette: {
        secondary: {
            main: blue[900]
        },
        primary: {
            main: indigo[700]
        }
    },
    typography: {
        // Use the system font instead of the default Roboto font.
        fontFamily: [
            'Lato',
            'sans-serif'
        ].join(',')
    }
})

const firebaseConfig = {
    apiKey: "AIzaSyCCK6qYz8_5WMp6Dz4trdZBrq3pj9H6KSc",
    authDomain: "planter-7c69c.firebaseapp.com",
    databaseURL: "https://planter-7c69c.firebaseio.com",
    projectId: "planter-7c69c",
    storageBucket: "planter-7c69c.appspot.com",
    messagingSenderId: "628484140467",
    appId: "1:628484140467:web:c0dbcba5a1ba67b6062fc6",
    measurementId: "G-GV4383Z0X4"
};

class App extends Component {
    render() {
        return (
            <div>
                <ThemeProvider theme={theme}>
                    <FirebaseDatabaseProvider firebase={firebase} {...firebaseConfig}>
                        <Main />
                    </FirebaseDatabaseProvider>
                </ThemeProvider>
            </div>
        )
    }
}

export default App