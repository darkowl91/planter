import React from 'react'
import CircularProgress from '@material-ui/core/CircularProgress'
import Grid from '@material-ui/core/Grid'

export default function Loading() {
    return (
        <Grid
            container
            direction="column"
            justify="center"
            alignItems="center"
        >
            <Grid item xs>
                <CircularProgress color="secondary" />
            </Grid>
        </Grid>
    )
}
