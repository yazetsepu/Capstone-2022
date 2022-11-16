import React, { useState, useEffect } from 'react';
import '../styles/DataTable.css';
import Table from 'react-bootstrap/Table';
//What Im planning to use to achieve teh scrolling through data
import Pagination from 'react-bootstrap/Pagination';

function BasicTable() {
    //to store everything returned from the fetch
    const [envData, setEnvData] = useState([])
    //to store the first 12-15 elements returned from fetch and stored in envData
    //gets replaced with a call from a button by the next 12-15
    const [limEnvData, setLimEnvData] = useState([])
    const [currNum, setCurrNum] = useState(0)
    const [isActive, setIsActive] = useState(false);
    const dataPerPage = 2;
    
    const fetchData = async () => {
        const response = await fetch("https://cssrumapi.azurewebsites.net/environmentaldata/classid")
        const data = await response.json()
        setEnvData(data)
        if(data.length <= dataPerPage){
            setLimEnvData(data.slice(0)) 
            setIsActive(true) 
        }
        else{
            setLimEnvData(data.slice(0, dataPerPage));
        }
      }
    
      useEffect(() => {
        fetchData()
      }, [])

      const showNextData = () => {
        if(limEnvData.length <= dataPerPage-1 ){
            console.log("Finished 1 ")
            setIsActive(true)
            return null;
        }
        setCurrNum(currNum + limEnvData.length)
        envData.slice(currNum, envData.length).length > dataPerPage? setLimEnvData(envData.slice(currNum, currNum+dataPerPage)) : 
        envData.slice(currNum, envData.length).length <=dataPerPage && envData.slice(currNum, envData.length).length > 0? setLimEnvData(envData.slice(currNum)) :
        setIsActive(true);        
      }

      const showPrevData = () => {
        if(limEnvData.length <= dataPerPage-1 ){
            console.log("Finished 1 ")
            setIsActive(true)
            return null;
        }
        setCurrNum(currNum - limEnvData.length)
        envData.slice(currNum, envData.length).length > dataPerPage? setLimEnvData(envData.slice(currNum, currNum+dataPerPage)) : 
        envData.slice(currNum, envData.length).length <=dataPerPage && envData.slice(currNum, envData.length).length > 0? setLimEnvData(envData.slice(currNum)) :
        setIsActive(true);        
      }

      const handleClick = () => showNextData();

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
                        <th>Light Level (lux)</th>
                    </tr>
                </thead>
                <tbody>
                    {limEnvData.map((data, key) => (
                    <tr key = {key}>
                        <td>{data.entry_Id}</td>
                        <td>{data.times_tamps}</td>
                        <td>{data.classification_id === 0? "Open" :
                            data.classification_id === 1? "Closed" :
                            "Not Available"}</td>
                        <td>{data.water_level}</td>
                        <td>{data.temperature}</td>
                        <td>{"S1 - " + data.soil_moisture}</td>
                        <td>{"S2 - " + data.soil_moisture_2}</td>
                        <td>{"S3 - " + data.soil_moisture_3}</td>
                        <td>{"S4 - " + data.soil_moisture_4}</td>
                        <td>{"S5 - " + data.soil_moisture_5}</td>
                        <td>{"S6 - " + data.soil_moisture_6}</td>
                        <td>{"S7 - " + data.soil_moisture_7}</td>
                        <td>{"S8 - " + data.soil_moisture_8}</td>
                        <td>{data.humidity}</td>
                        <td>{data.light}</td>
                    </tr>
                    ))}
                </tbody>
            </Table>
            <Pagination>
                <Pagination.First />
                <Pagination.Prev />
                <Pagination.Item>{1}</Pagination.Item>

                <Pagination.Ellipsis />

                <Pagination.Item>{envData.length/dataPerPage}</Pagination.Item>
                <Pagination.Next 
                    onClick={handleClick}
                    disabled={isActive}
                />
                <Pagination.Last />
            </Pagination>
        </div>
    );
}

export default BasicTable;