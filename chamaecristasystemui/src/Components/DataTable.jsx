import React, { useState, useEffect } from 'react';
import '../styles/DataTable.css';
import Table from 'react-bootstrap/Table';
//What Im planning to use to achieve teh scrolling through data
// import Pagination from 'react-bootstrap/Pagination';

function BasicTable() {
    //to store everything returned from teh fetch
    const [envData, setEnvData] = useState([])
    //to store the first 12-15 elements returned from fetch and stored in envData
    //gets replaced with a call from a button by the next 12-15
    const [limEnvData, setLimEnvData] = useState([])
    
    const fetchData = async () => {
        const response = await fetch("https://cssrumapi.azurewebsites.net/environmentaldata/classid")
        const data = await response.json()
        setEnvData(data)

        console.log(data)
      }
    
      useEffect(() => {
        fetchData()
      }, [])

    return (
        <div>
            <Table responsive="sm" striped bordered hover variant="dark" className='table'>
                <thead>
                    <tr>
                        <th>#</th>
                        <th>Timestamp</th>
                        <th>Leaf Status</th>
                        <th>Water Level</th>
                        <th>Temperature (C)</th>
                        <th colSpan={8}>Soil Moisture (%)</th>
                        <th>Air Humidity (%)</th>
                    </tr>
                </thead>
                <tbody>
                    {envData.map((data, key) => (
                    <tr key = {key}>
                        <td>{data.entry_Id}</td>
                        <td>{data.times_tamps}</td>
                        <td>{data.classification_id === 0? "Open" :
                            data.classification_id === 1? "Closed" :
                            "Not Available"}</td>
                        <td>{data.water_level}</td>
                        <td>{data.temperature}</td>
                        <td>{"S1 - " + data.soil_moisture}</td>
                        <td>{"S2 - " + data.soil_moisture}</td>
                        <td>{"S3 - " + data.soil_moisture}</td>
                        <td>{"S4 - " + data.soil_moisture}</td>
                        <td>{"S5 - " + data.soil_moisture}</td>
                        <td>{"S6 - " + data.soil_moisture}</td>
                        <td>{"S7 - " + data.soil_moisture}</td>
                        <td>{"S8 - " + data.soil_moisture}</td>
                        <td>{data.humidity}</td>
                    </tr>
                    ))}
                </tbody>
            </Table>
            {/* <Pagination>
                <Pagination.First />
                <Pagination.Prev />
                <Pagination.Item>{1}</Pagination.Item>

                <Pagination.Ellipsis />

                <Pagination.Item>{20}</Pagination.Item>
                <Pagination.Next />
                <Pagination.Last />
            </Pagination> */}
        </div>
    );
}

export default BasicTable;