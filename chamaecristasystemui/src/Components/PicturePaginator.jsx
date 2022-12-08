import React, { useState } from 'react';
import '../styles/PictureCard.css';
import Pagination from 'react-bootstrap/Pagination';

function PicturePaginator(props){
        
    //Designates how many picture rows (of 4 pictures each) a single page will hold
    const dataPerPage = props.dataPerPage
    //Keeps track of what index of the PicData Array is being used to display the next few pictures
    const [currNum, setCurrNum] = useState(dataPerPage)
    //Whether or not the Next arrow button is clickable in the Pagination section
    const [isNextActive, setIsNextActive] = useState(false);
     //Whether or not the Previous arrow button is clickable in the Pagination section
    const [isPrevActive, setIsPrevActive] = useState(true);
    //Keeps track of what page the user is at out of the total allowed pages as per the amount of data
    const [currPage, setCurrPage] = useState(1);

    //Handler Functions for the Pagination buttons

    //Handles the pressing of the ">" Next arrow in the pagination
    const showNextData = () => {
        if(currNum / currPage === dataPerPage && currPage < props.picData.length/dataPerPage){
            setCurrNum(currNum + props.limPicData.length)
        }

        if(props.picData.slice(currNum, props.picData.length).length > dataPerPage || currNum / currPage >= props.picData.length/dataPerPage){
            props.setLimPicData(props.picData.slice(currNum, currNum+dataPerPage));
            setIsPrevActive(false);
            setCurrPage(currPage+1)
        }
        else if(props.picData.slice(currNum, props.picData.length).length <= dataPerPage && props.picData.slice(currNum, props.picData.length).length > 0){
            props.setLimPicData(props.picData.slice(currNum));
            setIsNextActive(true);
            setCurrPage(currPage+1)
        }
        else{
            setIsNextActive(true);
            setCurrNum(currNum-dataPerPage)
        }      
    }

    //Handles the pressing of the "<" Previous arrow in the pagination
    const showPrevData = () => {
        if(currPage <= 2){
            setIsPrevActive(true)
        }
        
        if(currNum / currPage === dataPerPage){
            setCurrNum(currNum - props.limPicData.length)
        }

        if(props.picData.slice(currNum-props.limPicData.length, props.picData.length).length > dataPerPage){
            props.setLimPicData(props.picData.slice(currNum-(props.limPicData.length*2), currNum-props.limPicData.length));
            setIsNextActive(false);
            setCurrPage(currPage-1)
        }
        else if (currNum < dataPerPage){
            props.setLimPicData(props.picData.slice(currNum-props.limPicData.length, currNum));
            setIsPrevActive(true);
            setCurrPage(currPage-1)
            return null;
        }
        else{
            props.setLimPicData(props.picData.slice(currNum-(props.limPicData.length*2), currNum-props.limPicData.length));
            setIsNextActive(false);
            setCurrPage(currPage-1)
        }
    }

    //Handles pressing the "1" and takes the user back to the first page
    const showFirstPage = () => {
        setCurrNum(dataPerPage)
        props.setLimPicData(props.picData.slice(0, dataPerPage));
        setIsNextActive(false);
        setIsPrevActive(true)
        setCurrPage(1)
    }

    //Handles pressing the Last Page and takes the user back to the last page
    const showLastPage = () => {
        setCurrNum(props.picData.length)
        props.setLimPicData(props.picData.slice(props.picData.length-dataPerPage));
        setIsNextActive(true);
        setIsPrevActive(false)
        setCurrPage(props.picData.length/dataPerPage)
    }

    const handleNextClick = () => showNextData();
    const handlePrevClick = () => showPrevData();
    const handleFirstClick = () => showFirstPage();
    const handleLastClick = () => showLastPage();
    return (
        <div>
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
                        {Math.ceil(props.picData.length/dataPerPage)}
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

export default PicturePaginator