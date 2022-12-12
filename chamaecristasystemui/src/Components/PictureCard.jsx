import React, { useState, useEffect } from 'react';
import '../styles/PictureCard.css';
import CardGroup from 'react-bootstrap/CardGroup';
import SingleCard from './SingleCard';
import PicturePaginator from './PicturePaginator';

function PictureCard(props) {

    //Designates how many picture rows (of 4 pictures each) a single page will hold
    const dataPerPage = 2
    //Stores the complete picture set fetched from the API in descending order
    const [picData, setPicData] = useState([])
    //Temporarely stores the amount of pictures to be rendered on the page at any given moment
    const [limPicData, setLimPicData] = useState([])
    //Whether or not the Next arrow button is clickable in the Pagination section
    const [isNextActive, setIsNextActive] = useState(false);

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

    return (
        <div>
            {/* Features Pagination both on top and on the bottom to allow for easier traversal of pages */}
            <PicturePaginator dataPerPage={dataPerPage} picData={picData} 
                              setLimPicData={setLimPicData} limPicData={limPicData}
                              isNextActive={isNextActive}/>
                
            {/* Renders a child component that represent a single picture each */}
            {limPicData.map((data, key) => (
                <div>
                    <div className='picture-row'>   
                        <CardGroup>
                            <SingleCard id={data.pic_Id} src={data.camera_Pic_Path_1} camNum={"1"} time={data.timestamps} classif_id={data.classification_Id_1} classif_acc={data.classification_Accurracy_1} />
                            <SingleCard id={data.pic_Id} src={data.camera_Pic_Path_2} camNum={"2"} time={data.timestamps} classif_id={data.classification_Id_2} classif_acc={data.classification_Accurracy_2} />
                            <SingleCard id={data.pic_Id} src={data.camera_Pic_Path_3} camNum={"3"} time={data.timestamps} classif_id={data.classification_Id_3} classif_acc={data.classification_Accurracy_3} />
                            <SingleCard id={data.pic_Id} src={data.camera_Pic_Path_4} camNum={"4"} time={data.timestamps} classif_id={data.classification_Id_4} classif_acc={data.classification_Accurracy_4} />
                        </CardGroup>
                    </div>
                </div>
            ))}
            <PicturePaginator dataPerPage={dataPerPage} picData={picData} 
                              setLimPicData={setLimPicData} limPicData={limPicData}
                              isNextActive={isNextActive}/>
    </div>
    );
}

export default PictureCard;