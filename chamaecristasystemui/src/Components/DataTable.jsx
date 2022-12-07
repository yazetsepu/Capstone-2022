import React, { useState, useEffect } from 'react';
import '../styles/DataTable.css';
//Imports from react-bootstrap that will help beautify the page
import Table from 'react-bootstrap/Table';
import FilterSearch from './FilterSearch';
import TablePaginator from '../Components/TablePaginator';


//The DataTable or BasicTable function is invoked by the App.js page, the main landing page.
//It does not, however, inherit anything from it.
function BasicTable() {
    //Designates how many elements of EnvData (Environmental Data) a single page will hold
    const dataPerPage = 12;
    //Stores the complete data set fetched from the API in descending order
    const [envData, setEnvData] = useState([])
    //Temporarely stores the amount of elements to be rendered on the page at any given moment
    const [limEnvData, setLimEnvData] = useState([]);
    //Whether or not the Next arrow button is clickable in the Pagination section
    const [isNextActive, setIsNextActive] = useState(false);

    const [reset, setReset] = useState(false)
    const [filteredData, setFilteredData] = useState([]);
    const [limFilteredData, setLimFilteredData] = useState([])
    const [wasPressed, setWasPressed] = useState(false);

   //Performs a GET Request that will return the data present in the EnvironmentalData table in the DB
    const fetchData = async () => {
        const response = await fetch("https://cssrumapi.azurewebsites.net/environmentaldata/classid")
        const data = await response.json()

        /*
        * The following lines act to determine how many elements shy of a full page the last rendered page
        * contains and then fills it up to that point with dummy data. This allows the pagination to
        * always render the same of amount of elements per page and prevents bugs with number tracking.
        * Additionally, it provides styling benefits as it removes sudden changes in table size.
        * */
        let amountLeftOver = data.length % dataPerPage;
        if(amountLeftOver > 0){
            for (let i = amountLeftOver ; i < dataPerPage ; i++){
                data.push({
                    "soil_Moisture_1" : "N/A", "soil_Moisture_2" : "N/A", "soil_Moisture_3" : "N/A", "soil_Moisture_4" : "N/A", 
                    "soil_Moisture_5" : "N/A", "soil_Moisture_6" : "N/A", "soil_Moisture_7" : "N/A",
                    "soil_Moisture_8" : "N/A", "timestamps" : "0000-00-00T00:00:00.000000+00:00"})
            }
        }
        setEnvData(data)

        //Solves the edge case where the Page: 1 is rendered without the desired amount of elements
        if(data.length <= dataPerPage){
            setLimEnvData(data.slice(0)) 
            setIsNextActive(true) 
        }
        else{
            setLimEnvData(data.slice(0, dataPerPage));
        }
      }

      const displayFilteredData = async () => {
        const data = filteredData;
        let amountLeftOver = data.length % dataPerPage;
        if(amountLeftOver > 0){
            for (let i = amountLeftOver ; i < dataPerPage ; i++){
                data.push({
                    "soil_Moisture_1" : "N/A", "soil_Moisture_2" : "N/A", "soil_Moisture_3" : "N/A", "soil_Moisture_4" : "N/A", 
                    "soil_Moisture_5" : "N/A", "soil_Moisture_6" : "N/A", "soil_Moisture_7" : "N/A",
                    "soil_Moisture_8" : "N/A", "timestamps" : "0000-00-00T00:00:00.000000+00:00"})
            }
        }
        setEnvData(data)

        //Solves the edge case where the Page: 1 is rendered without the desired amount of elements
        if(data.length <= dataPerPage){
            setLimFilteredData(data.slice(0)) 
            setIsNextActive(true) 
        }
        else{
            setLimFilteredData(data.slice(0, dataPerPage));
        }
      }
    
      //useEffects is a React hook that triggers everytime the page is rendered (loads)
      useEffect(() => {
        if(reset){
            displayFilteredData();
            setIsNextActive(false)
        }
        else{
            fetchData()
        }
        setReset(false)
      }, [wasPressed, envData.length, filteredData])

    return (
        //Test id for handling tests on this component
        <div data-testid="datatable-1">
            <FilterSearch setFilteredData={setFilteredData} setWasPressed={setWasPressed} setReset={setReset}/>
            <Table responsive="sm" striped bordered hover variant="dark" className='table'>
                <thead className='table-head'>
                    {/* Containes the headers for the table */}
                    <tr>
                        <th>#</th>
                        <th>Timestamp</th>
                        <th colSpan={4}>Leaf Status</th>
                        <th>Resv Water Level</th>
                        <th>Water Level</th>
                        <th>Temperature (C)</th>
                        <th colSpan={8}>Soil Moisture (%)</th>
                        <th>Air Humidity (%)</th>
                        <th>Light Level (lux)</th>
                    </tr>
                </thead>
                <tbody>
                    {/* Maps each element of the data approved to be rendered to a row on the table */}
                    {(wasPressed? limFilteredData:limEnvData).map((data, key) => (
                        <tr key = {key}>
                            <td>{data.entry_Id}</td>
                            <td>{new Date(data.timestamps.replace("-", "/").replace("-", "/").split('T').join(' ').split('.')[0] + " +0000").toLocaleString("en-US", {timeZone: 'America/Grenada'})}</td>
                            <td>{data.classification_Id_1 === 0? "Open" :
                                data.classification_Id_1 === 1? "Closed" :
                                "Empty"}</td>
                            <td>{data.classification_Id_2 === 0? "Open" :
                                data.classification_Id_2 === 1? "Closed" :
                                "Empty"}</td>
                            <td>{data.classification_Id_3 === 0? "Open" :
                                data.classification_Id_3 === 1? "Closed" :
                                "Empty"}</td>
                                <td>{data.classification_Id_4 === 0? "Open" :
                                data.classification_Id_4 === 1? "Closed" :
                                "Empty"}</td>
                            <td>{data.resevoir_Water_Level}</td>
                            <td>{data.water_Level <= 100? "Low" : "High"}</td>
                            <td>{data.temperature}</td>
                            <td>{"S1 - " + Math.round(((data.soil_Moisture_1) + Number.EPSILON) * 100) / 100}</td>
                            <td>{"S2 - " + Math.round(((data.soil_Moisture_2) + Number.EPSILON) * 100) / 100}</td>
                            <td>{"S3 - " + Math.round(((data.soil_Moisture_3) + Number.EPSILON) * 100) / 100}</td>
                            <td>{"S4 - " + Math.round(((data.soil_Moisture_4) + Number.EPSILON) * 100) / 100}</td>
                            <td>{"S5 - " + Math.round(((data.soil_Moisture_5) + Number.EPSILON) * 100) / 100}</td>
                            <td>{"S6 - " + Math.round(((data.soil_Moisture_6) + Number.EPSILON) * 100) / 100}</td>
                            <td>{"S7 - " + Math.round(((data.soil_Moisture_7) + Number.EPSILON) * 100) / 100}</td>
                            <td>{"S8 - " + Math.round(((data.soil_Moisture_8) + Number.EPSILON) * 100) / 100}</td>
                            <td>{data.humidity}</td>
                            <td>{Math.round(((data.light) + Number.EPSILON) * 100) / 100}</td>
                        </tr>
                    ))}
                </tbody>
            </Table>
            {/* Controls Pagination: the movement between pages with data */}
            
            <div className='paginator'>
                <TablePaginator envData={wasPressed? filteredData : envData} isNextActive={isNextActive} 
                                limEnvData={wasPressed? limFilteredData : limEnvData} setLimEnvData={wasPressed? setLimFilteredData : setLimEnvData} 
                                dataPerPage={dataPerPage}
                />
                
            </div>
        </div>
    );
}

export default BasicTable;