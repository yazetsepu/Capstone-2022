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
    const dataPerPage = 2;
    const [limEnvData, setLimEnvData] = useState([])
    const [currNum, setCurrNum] = useState(dataPerPage)
    const [isNextActive, setIsNextActive] = useState(false);
    const [isPrevActive, setIsPrevActive] = useState(true);
    
    
    const fetchData = async () => {
        const response = await fetch("https://cssrumapi.azurewebsites.net/environmentaldata/classid")
        const data = await response.json()
        setEnvData(data)
        if(data.length <= dataPerPage){
            setLimEnvData(data.slice(0)) 
            setIsNextActive(true) 
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
            setIsNextActive(true)
            return null;
        }
        setCurrNum(currNum + limEnvData.length)

        if(envData.slice(currNum, envData.length).length > dataPerPage){
            setLimEnvData(envData.slice(currNum, currNum+dataPerPage));
            setIsPrevActive(false);
        }
        else if(envData.slice(currNum, envData.length).length <=dataPerPage && envData.slice(currNum, envData.length).length > 0){
            setLimEnvData(envData.slice(currNum));
            setIsNextActive(true);
            // setCurrNum(currNum - dataPerPage)
        }
        else{
            setIsNextActive(true);
        }      
      }

      const showPrevData = () => {
        if(currNum <= 0){
            setIsPrevActive(true)
            return null;
        }
        
        setCurrNum(currNum - limEnvData.length)
        
        if(envData.slice(currNum-limEnvData.length, envData.length).length >= dataPerPage){
            setLimEnvData(envData.slice(currNum-limEnvData.length, currNum));
            setIsNextActive(false);
        }
        else if (currNum <= dataPerPage){
            setLimEnvData(envData.slice(currNum-limEnvData.length, currNum));
            setIsPrevActive(true);
            // setCurrNum(currNum + limEnvData.length)
        }
        else {
            setIsPrevActive(true);
        }
                   
      }

      const handleNextClick = () => showNextData();
      const handlePrevClick = () => showPrevData();

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
            <div className='paginator'>
                <Pagination>
                    <Pagination.Prev 
                        onClick={handlePrevClick}
                        disabled={isPrevActive}/>
                    <Pagination.Item>{1}</Pagination.Item>

                    <Pagination.Ellipsis />

                    <Pagination.Item>{envData.length/dataPerPage}</Pagination.Item>
                    <Pagination.Next 
                        onClick={handleNextClick}
                        disabled={isNextActive}
                    />
                </Pagination>
            </div>
        </div>
    );
}

export default BasicTable;