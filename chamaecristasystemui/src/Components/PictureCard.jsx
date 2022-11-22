import React, { useState, useEffect } from 'react';
import '../styles/PictureCard.css';
import CardGroup from 'react-bootstrap/CardGroup';
import SingleCard from './SingleCard';
import Pagination from 'react-bootstrap/Pagination';


function PictureCard() {

    //Designates how many picture rows (of 4 pictures each) a single page will hold
    const dataPerPage = 2
    //Stores the complete picture set fetched from the API in descending order
    const [picData, setPicData] = useState([])
    //Temporarely stores the amount of pictures to be rendered on the page at any given moment
    const [limPicData, setLimPicData] = useState([])
    //Keeps track of what index of the PicData Array is being used to display the next few pictures
    const [currNum, setCurrNum] = useState(dataPerPage)
    //Whether or not the Next arrow button is clickable in the Pagination section
    const [isNextActive, setIsNextActive] = useState(false);
     //Whether or not the Previous arrow button is clickable in the Pagination section
    const [isPrevActive, setIsPrevActive] = useState(true);
    //Keeps track of what page the user is at out of the total allowed pages as per the amount of data
    const [currPage, setCurrPage] = useState(1);

    //Performs a GET Request that will return the data present in the Pictures table in the DB
    const fetchData = async () => {
        const response = await fetch("https://cssrumapi.azurewebsites.net/Pictures/desc")
        const data = await response.json()
         /*
        * The following lines act to determine how many elements shy of a full page the last rendered page
        * contains and then fills it up to that point with empty pictures. This allows the pagination to
        * always render the same of amount of elements per page and prevents bugs with number tracking.
        * Additionally, it provides styling benefits as it removes sudden changes in the amount of rows 
        * displayed.
        * */
        let amountLeftOver = data.length % dataPerPage;
            if(amountLeftOver > 0){
                for (let i = amountLeftOver ; i < dataPerPage ; i++){
                    data.push({
                        "pic_Id" : "N/A", "camera_Pic_Path_1" : "N/A", "camera_Pic_Path_2" : "N/A", 
                        "camera_Pic_Path_3" : "N/A", "camera_Pic_Path_4" : "N/A", "classification_Accuracy_1" : "N/A", 
                        "classification_Accuracy_2" : "N/A", "classification_Accuracy_3" : "N/A", "classification_Accuracy_4" : "N/A",
                        "classification_Id_1" : "N/A", "classification_Id_2" : "N/A", "classification_Id_3" : "N/A", "classification_Id_4" : "N/A", "timestamps" : "N/A"})
                }
            }
        setPicData(data)

        //Solves the edge case where the Page: 1 is rendered without the desired amount of elements
        if(data.length <= dataPerPage){
            setLimPicData(data.slice(0)) 
            setIsNextActive(true) 
        }
        else{
            setLimPicData(data.slice(0, dataPerPage));
        }
    }

    //useEffects is a React hook that triggers everytime the page is rendered (loads)
    useEffect(() => {
        fetchData()
        //If there are no pictures, create some dummy data
        if(picData.length/dataPerPage <= 0){
            let data = []
            data.push({
                "pic_Id" : "N/A", "camera_Pic_Path_1" : "N/A", "camera_Pic_Path_2" : "N/A", 
                "camera_Pic_Path_3" : "N/A", "camera_Pic_Path_4" : "N/A", "classification_Accuracy_1" : "N/A", 
                "classification_Accuracy_2" : "N/A", "classification_Accuracy_3" : "N/A", "classification_Accuracy_4" : "N/A",
                "classification_Id_1" : "N/A", "classification_Id_2" : "N/A", "classification_Id_3" : "N/A", "classification_Id_4" : "N/A", "timestamps" : "N/A"})
                data.push({
                    "pic_Id" : "N/A", "camera_Pic_Path_1" : "N/A", "camera_Pic_Path_2" : "N/A", 
                    "camera_Pic_Path_3" : "N/A", "camera_Pic_Path_4" : "N/A", "classification_Accuracy_1" : "N/A", 
                    "classification_Accuracy_2" : "N/A", "classification_Accuracy_3" : "N/A", "classification_Accuracy_4" : "N/A",
                    "classification_Id_1" : "N/A", "classification_Id_2" : "N/A", "classification_Id_3" : "N/A", "classification_Id_4" : "N/A", "timestamps" : "N/A"})
            setLimPicData(data)
        }
    }, [])

    //Handler Functions for the Pagination buttons

    //Handles the pressing of the ">" Next arrow in the pagination
    const showNextData = () => {
        if(currNum / currPage === dataPerPage && currPage < picData.length/dataPerPage){
            setCurrNum(currNum + limPicData.length)
        }

        if(picData.slice(currNum, picData.length).length > dataPerPage || currNum / currPage >= picData.length/dataPerPage){
            setLimPicData(picData.slice(currNum, currNum+dataPerPage));
            setIsPrevActive(false);
            setCurrPage(currPage+1)
        }
        else if(picData.slice(currNum, picData.length).length <= dataPerPage && picData.slice(currNum, picData.length).length > 0){
            setLimPicData(picData.slice(currNum));
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
            setCurrNum(currNum - limPicData.length)
        }

        if(picData.slice(currNum-limPicData.length, picData.length).length > dataPerPage){
            setLimPicData(picData.slice(currNum-(limPicData.length*2), currNum-limPicData.length));
            setIsNextActive(false);
            setCurrPage(currPage-1)
        }
        else if (currNum < dataPerPage){
            setLimPicData(picData.slice(currNum-limPicData.length, currNum));
            setIsPrevActive(true);
            setCurrPage(currPage-1)
            return null;
        }
        else{
            setLimPicData(picData.slice(currNum-(limPicData.length*2), currNum-limPicData.length));
            setIsNextActive(false);
            setCurrPage(currPage-1)
        }
    }

    //Handles pressing the "1" and takes the user back to the first page
    const showFirstPage = () => {
        setCurrNum(dataPerPage)
        setLimPicData(picData.slice(0, dataPerPage));
        setIsNextActive(false);
        setIsPrevActive(true)
        setCurrPage(1)
    }

    //Handles pressing the Last Page and takes the user back to the last page
    const showLastPage = () => {
        setCurrNum(picData.length)
        setLimPicData(picData.slice(picData.length-dataPerPage));
        setIsNextActive(true);
        setIsPrevActive(false)
        setCurrPage(picData.length/dataPerPage)
    }

    const handleNextClick = () => showNextData();
    const handlePrevClick = () => showPrevData();
    const handleFirstClick = () => showFirstPage();
    const handleLastClick = () => showLastPage();


    return (
        <div>
            {/* Features Pagination both on top and on the bottom to allow for easier traversal of pages */}
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
                        {Math.ceil(picData.length/dataPerPage)}
                    </Pagination.Item>
                    <Pagination.Next 
                        onClick={handleNextClick}
                        disabled={isNextActive}
                    />
                </Pagination>
            </div>
            {/* Renders a child component that represent a single picture each */}
            {limPicData.map((data, key) => (
                <div>
                    <div className='picture-row'>   
                        <CardGroup>
                            <SingleCard id={data.pic_Id} src={data.camera_Pic_Path_1} camNum={"1"} time={data.timestamps} classif_id={data.classification_Id_1} classif_acc={data.classification_Accurracy_1} />
                            <SingleCard id={data.pic_Id} src={data.camera_Pic_Path_2} camNum={"2"} time={data.timestamps} classif_id={data.classification_Id_2} classif_acc={data.classification_Accurracy_2} />
                            <SingleCard id={data.pic_Id} src={data.camera_Pic_Path_3} camNum={"3"} time={data.timestamps} classif_id={data.classification_Id_3} classif_acc={data.classification_Accurracy_3} />
                            <SingleCard id={data.pic_Id} src={data.camera_Pic_Path_3} camNum={"4"} time={data.timestamps} classif_id={data.classification_Id_4} classif_acc={data.classification_Accurracy_4} />
                        </CardGroup>
                    </div>
                </div>
            ))}
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
                        {Math.ceil(picData.length/dataPerPage)}
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

export default PictureCard;