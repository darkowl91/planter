import React from 'react';
import PropTypes from 'prop-types';
import AppBar from '@material-ui/core/AppBar';
import Grid from '@material-ui/core/Grid';
import Toolbar from '@material-ui/core/Toolbar';
import Typography from '@material-ui/core/Typography';
import { withStyles } from '@material-ui/core/styles';
import Avatar from '@material-ui/core/Avatar'
import Logo from '../logo.svg'

const styles = (theme) => ({
    secondaryBar: {
        zIndex: 0,
    },
});

function Header(props) {
    const {classes} = props;

    return (
        <React.Fragment>

            <AppBar
                component="div"
                className={ classes.secondaryBar }
                color="primary"
                position="static"
                elevation={ 0 }
            >
                <Toolbar>
                    <Grid container alignItems="center" spacing={ 1 }>
                        <Grid item xs>
                            <Avatar src={Logo} alt="Planter" />
                        </Grid>
                        <Grid item xs>
                            <Typography color="inherit" variant="h5" component="h1">
                                Planter
                            </Typography>
                        </Grid>
                    </Grid>
                </Toolbar>
            </AppBar>

        </React.Fragment>
    );
}

Header.propTypes = {
    classes: PropTypes.object.isRequired,
};

export default withStyles(styles)(Header);
