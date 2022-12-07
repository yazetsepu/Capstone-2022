import React from 'react';
import Button from 'react-bootstrap/Button';
import Modal from 'react-bootstrap/Modal';
import CalibrateSensorModalRange from './CalibrateSensorModalRange';
import 'react-bootstrap-range-slider/dist/react-bootstrap-range-slider.css';
import './modal-styles/CalibrateSensorModal.css'

function CalibrateSensorModalContainer(props){
    return(
    <Modal show={props.isLoading} onHide={props.handleClose}>
        <Modal.Header closeButton>
            <Modal.Title>Calibrate Moisture Levels</Modal.Title>
        </Modal.Header>
        <Modal.Body>
            <div className='dropdowns'>
                <div>
                    <CalibrateSensorModalRange number={1} handleModal={props.handleModal}/>
                    <CalibrateSensorModalRange  number={2} handleModal={props.handleModal}/>
                    <CalibrateSensorModalRange  number={3} handleModal={props.handleModal}/>
                    <CalibrateSensorModalRange  number={4} handleModal={props.handleModal}/>
                </div>
                <div>
                    <CalibrateSensorModalRange  number={5} handleModal={props.handleModal}/>
                    <CalibrateSensorModalRange  number={6} handleModal={props.handleModal}/>
                    <CalibrateSensorModalRange  number={7} handleModal={props.handleModal}/>
                    <CalibrateSensorModalRange  number={8} handleModal={props.handleModal}/>
                </div>
            </div>
        </Modal.Body>
        <Modal.Footer>
            <Button variant="secondary" onClick={props.handleClose}>
                Close
            </Button>
            <Button variant="primary" onClick={props.handleSubmit}>
                Save Changes
            </Button>
        </Modal.Footer>
    </Modal>
    );
}
export default CalibrateSensorModalContainer