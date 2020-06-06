import React from 'react'
import PropTypes from 'prop-types'
import { withStyles } from '@material-ui/core/styles'
import Typography from '@material-ui/core/Typography'
import Link from '@material-ui/core/Link'

const styles = (theme) => ({
    footer: {
        padding: theme.spacing(2),
        background: '#eaeff1',
    },
});

function Footer(props) {
    const {classes} = props

    return (
        <footer className={ classes.footer }>
            <Typography variant="body2" color="textSecondary" align="center">
                { 'Copyright © ' }
                <Link color="inherit" href="https://github.com/darkowl91/planter">
                    Planter
                </Link>{ ' ' }
                { new Date().getFullYear() }
                { '.' }
            </Typography>
        </footer>
    )
}

Footer.propTypes = {
    classes: PropTypes.object.isRequired,
};

export default withStyles(styles)(Footer)
