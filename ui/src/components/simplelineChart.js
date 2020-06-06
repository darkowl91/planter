import { CartesianGrid, Legend, Line, LineChart, ResponsiveContainer, Tooltip, XAxis, YAxis } from 'recharts'
import { toDate, toDateTime } from '../service/dateFormat'
import React from 'react'
import withTheme from '@material-ui/styles/withTheme'
import PropTypes from 'prop-types'

function SimpleLineChart(props) {

    const {theme, data, dataXAxisKey, dataYAxisKey} = props

    return (
        <ResponsiveContainer width="100%" height={ 225 }>
            <LineChart data={ data } margin={ {right: 32} }>
                <CartesianGrid strokeDasharray="3 3" />
                <XAxis dataKey={ dataXAxisKey } tickFormatter={ toDate } />
                <YAxis />
                <Tooltip labelFormatter={ toDateTime } />
                <Legend />
                <Line type="monotone" dataKey={ dataYAxisKey } stroke={ theme.palette.primary.main } />
            </LineChart>
        </ResponsiveContainer>
    )
}

SimpleLineChart.propTypes = {
    theme: PropTypes.object.isRequired,
    data: PropTypes.arrayOf(PropTypes.object).isRequired,
    dataXAxisKey: PropTypes.string.isRequired,
    dataYAxisKey: PropTypes.string.isRequired,
}

export default withTheme(SimpleLineChart)

