import React, { useState, useEffect } from 'react';
import '../styles/DataTable.css';
import Table from 'react-bootstrap/Table';
import { envData } from '../Util/dummyData'

function BasicTable() {

    const [envData, setEnvData] = useState([])
    const [picture, setPicture] = useState([])
    
    const fetchData = async () => {
        const response = await fetch("https://cssrumapi.azurewebsites.net/EnvironmentalDataAll")
        const data = await response.json()
        setEnvData(data)
        
        // const picId = envData.picturesId
        // const picResponse = await fetch("https://cssrumapi.azurewebsites.net/Pictures/" + picId)
        // const picData = await response.json()
        // setPicture(picData)
      }
    
      useEffect(() => {
        fetchData()

      }, [])

    return (
        <Table striped bordered hover className='table'>
            <thead>
                <tr>
                    <th>#</th>
                    <th>Timestamp</th>
                    {/* <th>Leaf Status</th> */}
                    <th>Water Level</th>
                    <th>Temperature (C)</th>
                    <th>Soil Moisture (%)</th>
                    <th>Air Humidity (%)</th>
                </tr>
            </thead>
            <tbody>
                {envData.map((data, key) => (
                <tr key = {key}>
                    <td>{data.entry_Id}</td>
                    <td>{data.times_tamps}</td>
                    {/* <td>{data.pictures.classification_id}</td> */}
                    <td>{data.water_level}</td>
                    <td>{data.temperature}</td>
                    <td>{data.soil_moisture}</td>
                    <td>{data.humidity}</td>
                </tr>
                ))}
            </tbody>
        </Table>
    );
}

export default BasicTable;