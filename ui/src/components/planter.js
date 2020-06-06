import React from 'react'
import BarChartIcon from '@material-ui/icons/BarChart'
import { FirebaseDatabaseNode } from '@react-firebase/database'

import Card from './card'
import Loading from './loading'
import SimpleLineChart from './simplelineChart'


function Planter() {

    return (
        <FirebaseDatabaseNode path={ 'planters/planter-1' } orderByKey={ 'yes' } limitToLast={ 25 }>
            {
                data => {
                    if (data.isLoading || !data.value) return <Loading />

                    const values = Object.values(data.value)

                    return (
                        <React.Fragment>
                            <Card label={ 'Moisture' } icon={ <BarChartIcon /> }>
                                <SimpleLineChart data={ values } dataXAxisKey="epoch"
                                                 dataYAxisKey="moisture" />
                            </Card>

                            <Card label={ 'Temperature' } icon={ <BarChartIcon /> }>
                                <SimpleLineChart data={ values } dataXAxisKey="epoch"
                                                 dataYAxisKey="temperature" />
                            </Card>

                            <Card label={ 'Humidity' } icon={ <BarChartIcon /> }>
                                <SimpleLineChart data={ values } dataXAxisKey="epoch"
                                                 dataYAxisKey="humidity" />
                            </Card>
                        </React.Fragment>
                    )
                }
            }
        </FirebaseDatabaseNode>
    )
}

export default (Planter)
