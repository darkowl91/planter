import React, { Component } from 'react'
import useMediaQuery from '@material-ui/core/useMediaQuery';
import { createMuiTheme, ThemeProvider } from '@material-ui/core'
import CssBaseline from '@material-ui/core/CssBaseline';
import 'firebase/database';
import * as firebase from 'firebase/app';
import { FirebaseDatabaseProvider } from '@react-firebase/database'
import { firebaseConfig } from './config'

import Planter from './components/planter'


const prefersDarkMode = useMediaQuery('(prefers-color-scheme: dark)');

const theme = React.useMemo(
    () =>
        createMuiTheme({
            palette: {
                type: prefersDarkMode ? 'dark' : 'light',
            },
        }),
    [prefersDarkMode],
);


class App extends Component {

    render() {
        return (
            <div>
                <ThemeProvider theme={ theme }>
                    <CssBaseline />
                    <FirebaseDatabaseProvider firebase={ firebase } { ...firebaseConfig }>
                        <Planter />
                    </FirebaseDatabaseProvider>
                </ThemeProvider>
            </div>
        )
    }
}

export default App
