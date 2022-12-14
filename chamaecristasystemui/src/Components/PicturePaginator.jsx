import React, { useState, useEffect } from 'react';
import '../styles/PictureCard.css';
import Pagination from 'react-bootstrap/Pagination';
import Form from 'react-bootstrap/Form';
import InputGroup from 'react-bootstrap/InputGroup';
import Modal from 'react-bootstrap/Modal';
import Button from 'react-bootstrap/Button';

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

    //Sets to show page change modal
    const [show, setShow] = useState(false)
    const [pageToGo, setPageToGo] = useState(1)
    const [validationBool, setValidationBool] = useState(false)

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

    const jumpToPage = () => {
        setCurrNum(parseInt(pageToGo*2))
        props.setLimPicData(props.picData.slice((pageToGo*2-2), pageToGo*2));
        if(parseInt(pageToGo) === 1){
            setIsPrevActive(true)
            setIsNextActive(false)
        }
        else if(parseInt(pageToGo) === props.picData.length/dataPerPage){
            setIsPrevActive(false)
            setIsNextActive(true)
        }
        else{
            setIsPrevActive(false)
            setIsNextActive(false)
        }
        setCurrPage(parseInt(pageToGo))
    }

    useEffect(() => {
        let pageToGoParsed = parseInt(pageToGo)
        if(pageToGoParsed <= 0 || pageToGoParsed > props.picData.length/dataPerPage || !(/[0-9]/.test(pageToGoParsed))){
            setValidationBool(true)
        }
        else{
            setValidationBool(false)
        }
        
      }, [pageToGo]);

    const handleNextClick = () => showNextData();
    const handlePrevClick = () => showPrevData();
    const handleFirstClick = () => showFirstPage();
    const handleLastClick = () => showLastPage();
    const handlePageJump = () => jumpToPage();
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
                        onClick={() => setShow(true)}
                        >
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
                {/* Handles showing the modal to change pages */}
                <Modal show={show} onHide={() => {setShow(false)}}>
                    <Modal.Header closeButton>
                        <Modal.Title>Jump to a different page</Modal.Title>
                    </Modal.Header>
                    <Modal.Body>
                        <Form.Group controlId="validationTime">
                            <InputGroup hasValidation >
                                <Form.Control
                                    as='input'
                                    type="number"
                                    placeholder="Please enter a page to jump to"
                                    onChange={changeEvent => {setPageToGo(changeEvent.target.value)}}
                                    isInvalid={validationBool}
                                />
                                <Form.Control.Feedback type="invalid">
                                    Please enter a valid number if you wish to jump pages
                                </Form.Control.Feedback>
                            </InputGroup>
                        </Form.Group>
                    </Modal.Body>
                    <Modal.Footer>
                        <Button variant="secondary" onClick={() => {setShow(false)}}>
                            Close
                        </Button>
                        <Button disabled={validationBool} variant="primary" onClick={() => {
                            handlePageJump()
                            setShow(false)
                        }}>
                            Go to page
                        </Button>
                    </Modal.Footer>
                </Modal>
            </div>
        </div>
    );

}

export default PicturePaginator