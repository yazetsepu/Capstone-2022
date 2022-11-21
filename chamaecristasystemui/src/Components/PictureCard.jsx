import React, { useState, useEffect } from 'react';
import '../styles/PictureCard.css';
import CardGroup from 'react-bootstrap/CardGroup';
import SingleCard from './SingleCard';
import Pagination from 'react-bootstrap/Pagination';


function PictureCard() {

const dataPerPage = 2
const [picData, setPicData] = useState([])
const picsPerPage = 2;
const [limPicData, setLimPicData] = useState([])
const [currNum, setCurrNum] = useState(picsPerPage)
const [isNextActive, setIsNextActive] = useState(false);
const [isPrevActive, setIsPrevActive] = useState(true);
const [currPage, setCurrPage] = useState(1);

const fetchData = async () => {
    const response = await fetch("https://cssrumapi.azurewebsites.net/PicturesAll")
    const data = await response.json()
    setPicData(data)
    if(data.length <= picsPerPage){
        setLimPicData(data.slice(0)) 
        setIsNextActive(true) 
    }
    else{
        setLimPicData(data.slice(0, picsPerPage));
    }
  }

  useEffect(() => {
    fetchData()
  }, [])

  //Handler Functions for buttons
  const showNextData = () => {
    if(currNum / currPage === dataPerPage && currPage < picData.length/dataPerPage){
        setCurrNum(currNum + limPicData.length)
    }

    if(picData.slice(currNum, picData.length).length > dataPerPage){
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

  const showPrevData = () => {
    if(currPage <= 2){
        setIsPrevActive(true)
        console.log("On Prev Stop: "+currNum)
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

  const showFirstPage = () => {
    setCurrNum(12)
    setLimPicData(picData.slice(0, dataPerPage));
    setIsNextActive(false);
    setIsPrevActive(true)
    setCurrPage(1)
  }

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
    {limPicData.map((data, key) => (
        <div>
            <div className='picture-row'>   
                <CardGroup>
                    <SingleCard src={data.camera_Pic_Path_1} camNum={"1"} time={data.times_tamps} classif_id={data.classification_id} classif_acc={data.classification_accurracy} />
                    <SingleCard src={data.camera_Pic_Path_2} camNum={"2"} time={data.times_tamps} classif_id={data.classification_id_2} classif_acc={data.classification_accurracy_2} />
                    <SingleCard src={data.camera_Pic_Path_3} camNum={"3"} time={data.times_tamps} classif_id={data.classification_id_3} classif_acc={data.classification_accurracy_3} />
                    <SingleCard src={data.camera_Pic_Path_3} camNum={"4"} time={data.times_tamps} classif_id={data.classification_id_4} classif_acc={data.classification_accurracy_4} />
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
            {picData.length/dataPerPage}
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