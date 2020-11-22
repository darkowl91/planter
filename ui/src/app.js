import React from 'react'
import PropTypes from 'prop-types'
import { createMuiTheme, ThemeProvider, withStyles } from '@material-ui/core/styles'
import CssBaseline from '@material-ui/core/CssBaseline'

import 'firebase/database';
import firebase from 'firebase/app'
import { FirebaseDatabaseProvider } from '@react-firebase/database'
import { firebaseConfig } from './config'

import Header from './components/header'
import Planter from './components/planter'
import Footer from './components/footer'


const theme = createMuiTheme({
    palette: {
        type: 'light',
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
})


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


function App(props) {

    const {classes} = props

    return (
        <ThemeProvider theme={ theme }>
            <div className={ classes.root }>
                <CssBaseline />
                <div className={ classes.app }>
                    <Header />
                    <main className={ classes.main }>
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

App.propTypes = {
    classes: PropTypes.object.isRequired,
}

export default withStyles(styles)(App)
