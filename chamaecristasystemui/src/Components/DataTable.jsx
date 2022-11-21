import React, { useState, useEffect } from 'react';
import '../styles/DataTable.css';
import Table from 'react-bootstrap/Table';
import Pagination from 'react-bootstrap/Pagination';

function BasicTable() {
    //to store everything returned from the fetch
    const [envData, setEnvData] = useState([])
    //to store the first 12-15 elements returned from fetch and stored in envData
    const dataPerPage = 12;
    const [limEnvData, setLimEnvData] = useState([]);
    const [currNum, setCurrNum] = useState(dataPerPage);
    const [isNextActive, setIsNextActive] = useState(false);
    const [isPrevActive, setIsPrevActive] = useState(true);
    const [currPage, setCurrPage] = useState(1);
    
    //Call the API
    const fetchData = async () => {
        const response = await fetch("https://cssrumapi.azurewebsites.net/environmentaldata/classid")
        const data = await response.json()
        //Trying this out
        let amountLeftOver = data.length % dataPerPage;
        if(amountLeftOver > 0){
            for (let i = amountLeftOver ; i < dataPerPage ; i++){
                data.push({
                    "soil_moisture" : "N/A", "soil_moisture_2" : "N/A", "soil_moisture_3" : "N/A", "soil_moisture_4" : "N/A", 
                    "soil_moisture_5" : "N/A", "soil_moisture_6" : "N/A", "soil_moisture_7" : "N/A",
                    "soil_moisture_8" : "N/A"})
            }
        }
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

      //Handler Functions for buttons
      const showNextData = () => {
        if(currNum / currPage === dataPerPage && currPage < envData.length/dataPerPage){
            setCurrNum(currNum + limEnvData.length)
        }

        if(envData.slice(currNum, envData.length).length > dataPerPage){
            setLimEnvData(envData.slice(currNum, currNum+dataPerPage));
            setIsPrevActive(false);
            setCurrPage(currPage+1)
        }
        else if(envData.slice(currNum, envData.length).length <= dataPerPage && envData.slice(currNum, envData.length).length > 0){
            setLimEnvData(envData.slice(currNum));
            setIsNextActive(true);
            setCurrPage(currPage+1)
        }
        else{
            setIsNextActive(true);
            setCurrNum(currNum-dataPerPage)
        }      
      }

      const showPrevData = () => {
        if(currPage <= 2){
            setIsPrevActive(true)
            console.log("On Prev Stop: "+currNum)
        }
        
        if(currNum / currPage === dataPerPage){
            setCurrNum(currNum - limEnvData.length)
        }

        if(envData.slice(currNum-limEnvData.length, envData.length).length > dataPerPage){
            setLimEnvData(envData.slice(currNum-(limEnvData.length*2), currNum-limEnvData.length));
            setIsNextActive(false);
            setCurrPage(currPage-1)
        }
        else if (currNum < dataPerPage){
            setLimEnvData(envData.slice(currNum-limEnvData.length, currNum));
            setIsPrevActive(true);
            setCurrPage(currPage-1)
            return null;
        }
        else{
            setLimEnvData(envData.slice(currNum-(limEnvData.length*2), currNum-limEnvData.length));
            setIsNextActive(false);
            setCurrPage(currPage-1)
        }
      }

      const showFirstPage = () => {
        setCurrNum(12)
        setLimEnvData(envData.slice(0, dataPerPage));
        setIsNextActive(false);
        setIsPrevActive(true)
        setCurrPage(1)
      }

      const showLastPage = () => {
        setCurrNum(envData.length)
        setLimEnvData(envData.slice(envData.length-dataPerPage));
        setIsNextActive(true);
        setIsPrevActive(false)
        setCurrPage(envData.length/dataPerPage)
      }

      const handleNextClick = () => showNextData();
      const handlePrevClick = () => showPrevData();
      const handleFirstClick = () => showFirstPage();
      const handleLastClick = () => showLastPage();

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
                                "Empty"}</td>
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
                    <Pagination.Item
                    onClick={handleFirstClick}>
                        {1}
                    </Pagination.Item>

                    <Pagination.Ellipsis />
                    <Pagination.Item
                        active>
                            Current Page: {Math.ceil(currPage)}
                    </Pagination.Item>
                    <Pagination.Ellipsis />

                    <Pagination.Item
                        onClick={handleLastClick}
                    >
                        {envData.length/dataPerPage}
                    </Pagination.Item>
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