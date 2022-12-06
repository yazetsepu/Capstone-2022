import React, { useState, useEffect } from 'react';
import Pagination from 'react-bootstrap/Pagination';

function TablePaginator(props) {
    //Designates how many elements of EnvData (Environmental Data) a single page will hold
    const dataPerPage = props.dataPerPage;
    //Keeps track of what index of the EnvData Array is being used to display the next few elements
    const [currNum, setCurrNum] = useState(dataPerPage);
    //Whether or not the Next arrow button is clickable in the Pagination section
    const [isNextActive, setIsNextActive] = useState(false);
    //Whether or not the Previous arrow button is clickable in the Pagination section
    const [isPrevActive, setIsPrevActive] = useState(true);
    //Keeps track of what page the user is at out of the total allowed pages as per the amount of data
    const [currPage, setCurrPage] = useState(1);

    useEffect(() => {
        if(props.isNextActive){
            setIsNextActive(true)
        }
      }, [])

     //Handler Functions for the Pagination buttons

      //Handles the pressing of the ">" Next arrow in the pagination
      const showNextData = () => {
        //Checks whether the elements on a page are the correct amount and if user is not on the final page
        if(currNum / currPage === dataPerPage && currPage < props.envData.length/dataPerPage){
            setCurrNum(currNum + props.limEnvData.length)
        }

        //Sets the elements to be rendered when clicking the next button by taking the current 
        //tracked number and shifting it the correct amount of elements forward.  
        if(props.envData.slice(currNum, props.envData.length).length > dataPerPage){
            props.setLimEnvData(props.envData.slice(currNum, currNum+dataPerPage));
            setIsPrevActive(false);
            setCurrPage(currPage+1)
        }
        //Sets the elements to be rendered when clicking the next button, but right before the last page.
        //Disables the next button to prevent bugs.
        else if(props.envData.slice(currNum, props.envData.length).length <= dataPerPage && props.envData.slice(currNum, props.envData.length).length > 0){
            props.setLimEnvData(props.envData.slice(currNum));
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
            setCurrNum(currNum - props.limEnvData.length)
        }

        //Sets the elements to be rendered by shifting the current number tracked by the corret amount
        if(props.envData.slice(currNum-props.limEnvData.length, props.envData.length).length > dataPerPage){
            props.setLimEnvData(props.envData.slice(currNum-(props.limEnvData.length*2), currNum-props.limEnvData.length));
            setIsNextActive(false);
            setCurrPage(currPage-1)
        }
        //Sets the elements to be rendered but when on the last page
        else if (currNum < dataPerPage){
            props.setLimEnvData(props.envData.slice(currNum-props.limEnvData.length, currNum));
            setIsPrevActive(true);
            setCurrPage(currPage-1)
            return null;
        }
        //Catches any other errors with the pagination by adjisting the shifted number and the page
        else{
            props.setLimEnvData(props.envData.slice(currNum-(props.limEnvData.length*2), currNum-props.limEnvData.length));
            setIsNextActive(false);
            setCurrPage(currPage-1)
        }
      }

      //Handles pressing the "1" and takes the user back to the first page
      const showFirstPage = () => {
        setCurrNum(dataPerPage)
        props.setLimEnvData(props.envData.slice(0, dataPerPage));
        setIsNextActive(false);
        setIsPrevActive(true)
        setCurrPage(1)
      }

      //Handles pressing the Last Page and takes the user back to the last page
      const showLastPage = () => {
        setCurrNum(props.envData.length)
        props.setLimEnvData(props.envData.slice(props.envData.length-dataPerPage));
        setIsNextActive(true);
        setIsPrevActive(false)
        setCurrPage(props.envData.length/dataPerPage)
      }

      //Handler Pointers
      const handleNextClick = () => showNextData();
      const handlePrevClick = () => showPrevData();
      const handleFirstClick = () => showFirstPage();
      const handleLastClick = () => showLastPage();

    return (
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
                {props.envData.length/dataPerPage}
            </Pagination.Item>
            <Pagination.Next 
                onClick={handleNextClick}
                disabled={isNextActive}
            />
        </Pagination>
    )
}
export default TablePaginator