import React from 'react'
import PropTypes from 'prop-types'
import AppBar from '@material-ui/core/AppBar'
import Toolbar from '@material-ui/core/Toolbar'
import Typography from '@material-ui/core/Typography'
import Paper from '@material-ui/core/Paper'
import Grid from '@material-ui/core/Grid'
import { withStyles } from '@material-ui/core/styles'

const styles = (theme) => ({
    paper: {
        maxWidth: 936,
        margin: 'auto',
        overflow: 'hidden',
        marginBottom: 40,
    },
    bar: {
        borderBottom: '1px solid rgba(0, 0, 0, 0.12)',
    },
    block: {
        display: 'block',
    },
    contentWrapper: {
        margin: '16px',
    },
})

function Card(props) {
    const {classes, icon, label, children} = props;

    return (
        <Paper className={ classes.paper }>
            <AppBar className={ classes.bar } position="static" color="default" elevation={ 0 }>
                <Toolbar>
                    <Grid container spacing={ 2 } alignItems="center">
                        <Grid item>
                            <div className={ classes.block }>
                                { icon }
                            </div>
                        </Grid>
                        <Grid item xs>
                            <Typography color="textSecondary" align="left">
                                { label }
                            </Typography>
                        </Grid>
                    </Grid>
                </Toolbar>
            </AppBar>
            <div className={ classes.contentWrapper }>
                { children }
            </div>
        </Paper>
    )
}

Card.propTypes = {
    classes: PropTypes.object.isRequired,
    icon: PropTypes.element.isRequired,
    label: PropTypes.string.isRequired,
}

export default withStyles(styles)(Card)
