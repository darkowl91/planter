import React, { Component } from 'react'
import { FirebaseDatabaseNode } from "@react-firebase/database"
import Loading from './loading'
import ResponsiveContainer from 'recharts/lib/component/ResponsiveContainer'
import BarChart from 'recharts/lib/chart/BarChart'
import Bar from 'recharts/lib/cartesian/Bar'
import XAxis from 'recharts/lib/cartesian/XAxis'
import Tooltip from 'recharts/lib/component/Tooltip'
import { withTheme } from '@material-ui/styles';


class Temperature extends Component {

    render() {
        const { theme } = this.props

        return (

            <FirebaseDatabaseNode path={'planters/planter-1/temperature/'} orderByKey={'yes'} limitToLast={2000} >
                {
                    data => {
                        if (data.isLoading || !data.value) return <Loading />
                        const t = Object.entries(data.value).map(([k, v]) => { return { key: k, value: v } })

                        return (
                            <ResponsiveContainer width="100%" height={225}>
                                <BarChart data={t} >
                                    <XAxis dataKey="key" />
                                    <Tooltip />
                                    <Bar dataKey="value" stackId="a" fill={theme.palette.primary.main} />
                                </BarChart>
                            </ResponsiveContainer>

                        )
                    }
                }
            </FirebaseDatabaseNode>
        )
    }
}

export default withTheme(Temperature)