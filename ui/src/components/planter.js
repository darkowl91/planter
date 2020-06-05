import React, { Component } from 'react'
import FirebaseDatabaseNode from '@react-firebase/database'

class Planter extends Component {

    render() {
        return (
            <FirebaseDatabaseNode path={ '/planter-1' } />

        )
    }

}

export default Planter
