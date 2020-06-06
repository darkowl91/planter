import React from 'react'
import useMediaQuery from '@material-ui/core/useMediaQuery';
import { createMuiTheme, ThemeProvider } from '@material-ui/core'
import CssBaseline from '@material-ui/core/CssBaseline';
import 'firebase/database';
import * as firebase from "firebase/app";
import { FirebaseDatabaseProvider } from '@react-firebase/database'
import {firebaseConfig} from './config'

import Header from './components/header'
import Planter from './components/planter'
import Footer from './components/footer'


function App() {
    let prefersDarkMode = useMediaQuery('(prefers-color-scheme: dark)');

    const theme = React.useMemo(
        () =>
            createMuiTheme({
                palette: {
                    type: prefersDarkMode ? 'dark' : 'light',
                    primary: {
                        light: '#63ccff',
                        main: '#009be5',
                        dark: '#006db3',
                    },
                },
                typography: {
                    h5: {
                        fontWeight: 500,
                        fontSize: 26,
                        letterSpacing: 0.5,
                    },
                },
                shape: {
                    borderRadius: 8,
                },
                mixins: {
                    toolbar: {
                        minHeight: 65,
                    },
                },
            }),
        [prefersDarkMode],
    );

    const styles = {
        root: {
            display: 'flex',
            minHeight: '100vh',
        },
        app: {
            flex: 1,
            display: 'flex',
            flexDirection: 'column',
        },
        main: {
            flex: 1,
            padding: theme.spacing(6, 4),
            background: '#eaeff1',
        },
    }

    return (
        <ThemeProvider theme={ theme }>
            <div className={ styles.root }>
                <CssBaseline />
                <div className={ styles.app }>
                    <Header />
                    <main className={ styles.main }>
                        <FirebaseDatabaseProvider firebase={ firebase } { ...firebaseConfig }>
                            <Planter />
                        </FirebaseDatabaseProvider>
                    </main>
                    <Footer />
                </div>
            </div>
        </ThemeProvider>
    )
}

export default App
