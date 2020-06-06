import React from 'react';
import PropTypes from 'prop-types'
import AppBar from '@material-ui/core/AppBar'
import Toolbar from '@material-ui/core/Toolbar'
import Typography from '@material-ui/core/Typography'
import { withStyles } from '@material-ui/core/styles'
import Avatar from '@material-ui/core/Avatar'

import Logo from '../logo.svg'

const styles = (theme) => ({
    secondaryBar: {
        zIndex: 0,

    },
    icon: {
        marginRight: theme.spacing(2),
        marginBottom: theme.spacing(2),
    },
})

function Header(props) {
    const {classes} = props;

    return (
        <React.Fragment>
            <AppBar
                component="div"
                className={ classes.secondaryBar }
                color="primary"
                position="relative"
            >
                <Toolbar>
                    <Avatar src={ Logo } alt="Planter" className={ classes.icon } />
                    <Typography color="inherit" variant="h5" component="h1">
                        Planter
                    </Typography>
                </Toolbar>
            </AppBar>
        </React.Fragment>
    );
}

Header.propTypes = {
    classes: PropTypes.object.isRequired,
}

export default withStyles(styles)(Header)
