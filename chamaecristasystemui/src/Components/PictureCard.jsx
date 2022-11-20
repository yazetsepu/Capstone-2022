import React, { useState, useEffect } from 'react';
import '../styles/PictureCard.css';
import CardGroup from 'react-bootstrap/CardGroup';
import SingleCard from './SingleCard';
import Pagination from 'react-bootstrap/Pagination';


function PictureCard() {

const [picData, setPicData] = useState([])
const picsPerPage = 1;
const [limPicData, setLimPicData] = useState([])
const [currNum, setCurrNum] = useState(picsPerPage)
const [isNextActive, setIsNextActive] = useState(false);
const [isPrevActive, setIsPrevActive] = useState(true);

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

  const showNextData = () => {
    if(limPicData.length <= picsPerPage-1 ){
        setIsNextActive(true)
        return null;
    }
    setCurrNum(currNum + limPicData.length)

    if(picData.slice(currNum, picData.length).length > picsPerPage){
        setLimPicData(picData.slice(currNum, currNum+picsPerPage));
        setIsPrevActive(false);
    }
    else if(picData.slice(currNum, picData.length).length <=picsPerPage && picData.slice(currNum, picData.length).length > 0){
        setLimPicData(picData.slice(currNum));
        setIsNextActive(true);
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
    
    setCurrNum(currNum - limPicData.length)
    
    if(picData.slice(currNum-limPicData.length, picData.length).length >= picsPerPage){
        setLimPicData(picData.slice(currNum-limPicData.length, currNum));
        setIsNextActive(false);
    }
    else if (currNum <= picsPerPage){
        setLimPicData(picData.slice(currNum-limPicData.length, currNum));
        setIsPrevActive(true);
    }
    else {
        setIsPrevActive(true);
    }
               
  }

  const handleNextClick = () => showNextData();
  const handlePrevClick = () => showPrevData();


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
            <div className='paginator'>
                    <Pagination>
                        <Pagination.Prev 
                            onClick={handlePrevClick}
                            disabled={isPrevActive}/>
                        <Pagination.Item>{1}</Pagination.Item>

                        <Pagination.Ellipsis />

                        <Pagination.Item>{picData.length/picsPerPage}</Pagination.Item>
                        <Pagination.Next 
                            onClick={handleNextClick}
                            disabled={isNextActive}
                        />
                    </Pagination>
            </div>
        </div>
    ))}
   </div>
  );
}

export default PictureCard;