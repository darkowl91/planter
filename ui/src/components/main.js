import React, { Component } from 'react'
import withStyles from '@material-ui/core/styles/withStyles'
import { CssBaseline, Grid } from '@material-ui/core'
import Paper from '@material-ui/core/Paper'
import Temperature from './temperature'
import Humidity from './humidity'
import Moisture from './moisture'
import Typography from '@material-ui/core/Typography';

const styles = theme => ({
    root: {
        flexGrow: 1,
        overflow: 'hidden',
        padding: theme.spacing(0, 2),

    },
    paper: {
        padding: theme.spacing(2),
        margin: `${ theme.spacing(1) }px auto`,
        textAlign: 'center',
        color: theme.palette.text.secondary,
    },
})

class Main extends Component {

    render() {
        const {classes} = this.props

        return (
            <React.Fragment>
                <CssBaseline />
                <div className={ classes.root }>
                    <Grid container
                          direction="column"
                          justify="center"
                          alignItems="stretch">
                        <Grid item xs>
                            <Paper className={ classes.paper }>
                                <Typography variant="h2" gutterBottom>
                                    Temperature
                                </Typography>
                                <Temperature />
                            </Paper>
                        </Grid>
                        <Grid item xs>
                            <Paper className={ classes.paper }>
                                <Typography variant="h2" gutterBottom>
                                    Humidity
                                </Typography>
                                <Humidity />
                            </Paper>
                        </Grid>
                        <Grid item xs>
                            <Paper className={ classes.paper }>
                                <Typography variant="h2" gutterBottom>
                                    Soil Moisture
                                </Typography>
                                <Moisture />
                            </Paper>
                        </Grid>
                    </Grid>
                </div>
            </React.Fragment>
        )
    }
}

export default withStyles(styles)(Main)
