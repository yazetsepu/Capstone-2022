import React, { useState, useEffect } from 'react';
import '../styles/DataTable.css';
//Imports from react-bootstrap that will help beautify the page
import Table from 'react-bootstrap/Table';
import Pagination from 'react-bootstrap/Pagination';

//The DataTable or BasicTable function is invoked by the App.js page, the main landing page.
//It does not, however, inherit anything from it.
function BasicTable() {
     //Stores the complete data set fetched from the API in descending order
    const [envData, setEnvData] = useState([])
    //Designates how many elements of EnvData (Environmental Data) a single page will hold
    const dataPerPage = 12;
    //Temporarely stores the amount of elements to be rendered on the page at any given moment
    const [limEnvData, setLimEnvData] = useState([]);
    //Keeps track of what index of the EnvData Array is being used to display the next few elements
    const [currNum, setCurrNum] = useState(dataPerPage);
    //Whether or not the Next arrow button is clickable in the Pagination section
    const [isNextActive, setIsNextActive] = useState(false);
    //Whether or not the Previous arrow button is clickable in the Pagination section
    const [isPrevActive, setIsPrevActive] = useState(true);
    //Keeps track of what page the user is at out of the total allowed pages as per the amount of data
    const [currPage, setCurrPage] = useState(1);
    
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
                    "soil_Moisture_8" : "N/A"})
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
    
      //useEffects is a React hook that triggers everytime the page is rendered (loads)
      useEffect(() => {
        fetchData()
      }, [])

      //Handler Functions for the Pagination buttons

      //Handles the pressing of the ">" Next arrow in the pagination
      const showNextData = () => {
        //Checks whether the elements on a page are the correct amount and if user is not on the final page
        if(currNum / currPage === dataPerPage && currPage < envData.length/dataPerPage){
            setCurrNum(currNum + limEnvData.length)
        }

        //Sets the elements to be rendered when clicking the next button by taking the current 
        //tracked number and shifting it the correct amount of elements forward.  
        if(envData.slice(currNum, envData.length).length > dataPerPage){
            setLimEnvData(envData.slice(currNum, currNum+dataPerPage));
            setIsPrevActive(false);
            setCurrPage(currPage+1)
        }
        //Sets the elements to be rendered when clicking the next button, but right before the last page.
        //Disables the next button to prevent bugs.
        else if(envData.slice(currNum, envData.length).length <= dataPerPage && envData.slice(currNum, envData.length).length > 0){
            setLimEnvData(envData.slice(currNum));
            setIsNextActive(true);
            setIsPrevActive(false);
            setCurrPage(currPage+1)
        }
        //Catches any other errors with the pagination by disabling the ability to move forward
        else{
            setIsNextActive(true);
            setIsPrevActive(false);
            setCurrNum(currNum-dataPerPage)
        }      
      }

      //Handles the pressing of the "<" Previous arrow in the pagination
      const showPrevData = () => {
        //Disables the ability to go backwards in pages if there are 2 or less remaining pages
        if(currPage <= 2){
            setIsPrevActive(true)
        }
        
        //If the amount of elements rendered are correct, move backwards in pagination
        if(currNum / currPage === dataPerPage){
            setCurrNum(currNum - limEnvData.length)
        }

        //Sets the elements to be rendered by shifting the current number tracked by the corret amount
        if(envData.slice(currNum-limEnvData.length, envData.length).length > dataPerPage){
            setLimEnvData(envData.slice(currNum-(limEnvData.length*2), currNum-limEnvData.length));
            setIsNextActive(false);
            setCurrPage(currPage-1)
        }
        //Sets the elements to be rendered but when on the last page
        else if (currNum < dataPerPage){
            setLimEnvData(envData.slice(currNum-limEnvData.length, currNum));
            setIsPrevActive(true);
            setCurrPage(currPage-1)
            return null;
        }
        //Catches any other errors with the pagination by adjisting the shifted number and the page
        else{
            setLimEnvData(envData.slice(currNum-(limEnvData.length*2), currNum-limEnvData.length));
            setIsNextActive(false);
            setCurrPage(currPage-1)
        }
      }

      //Handles pressing the "1" and takes the user back to the first page
      const showFirstPage = () => {
        setCurrNum(12)
        setLimEnvData(envData.slice(0, dataPerPage));
        setIsNextActive(false);
        setIsPrevActive(true)
        setCurrPage(1)
      }

      //Handles pressing the Last Page and takes the user back to the last page
      const showLastPage = () => {
        setCurrNum(envData.length)
        setLimEnvData(envData.slice(envData.length-dataPerPage));
        setIsNextActive(true);
        setIsPrevActive(false)
        setCurrPage(envData.length/dataPerPage)
      }

      //Handler Pointers
      const handleNextClick = () => showNextData();
      const handlePrevClick = () => showPrevData();
      const handleFirstClick = () => showFirstPage();
      const handleLastClick = () => showLastPage();

    return (
        //Test id for handling tests on this component
        <div data-testid="datatable-1">
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
                    {limEnvData.map((data, key) => (
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