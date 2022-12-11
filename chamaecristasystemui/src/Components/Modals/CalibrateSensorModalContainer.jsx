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
                    <CalibrateSensorModalRange  number={0} />
                    <CalibrateSensorModalRange  number={1} />
                    <CalibrateSensorModalRange  number={2} />
                    <CalibrateSensorModalRange  number={3} />
                </div>
                <div>
                    <CalibrateSensorModalRange  number={4} />
                    <CalibrateSensorModalRange  number={5} />
                    <CalibrateSensorModalRange  number={6} />
                    <CalibrateSensorModalRange  number={7} />
                </div>
            </div>
        </Modal.Body>
        <Modal.Footer>
            <Button variant="secondary" onClick={props.handleClose}>
                Close
            </Button>
        </Modal.Footer>
    </Modal>
    );
}
export default CalibrateSensorModalContainer