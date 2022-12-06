import React, { useEffect, useState } from 'react';
import Form from 'react-bootstrap/Form';
import Button from 'react-bootstrap/Button';
import RangeSlider from 'react-bootstrap-range-slider';
import Modal from 'react-bootstrap/Modal';
import 'react-bootstrap-range-slider/dist/react-bootstrap-range-slider.css';
import './modal-styles/calibratesensormodal.css'

//Handles each sesnor button and the sliders that pop up, as well as sends the data of sliders to parent
function CalibrateSensorModal(props) {

  //Stores and sets each individual soil sensor values
  const maxSliderVal = 1023;
  //Wet
  const [soilSensorW, setSoilSensorW] = useState(500);
  //Dry
  const [soilSensorD, setSoilSensorD] = useState(0);
  //Whether or not the secondary modal is sbeing displayed
  const [isLoading, setLoading] = useState(false);

  const handleClick = () => setLoading(true);
  const handleClose = () => setLoading(false)

  return (
    <div className='individual-dropdown'>
         {/* Renders the button */}
        <Button
            variant="primary"
            size="med"
            disabled={isLoading}
            onClick={!isLoading ? handleClick : null}
        >
            {isLoading ? 'Loading…' : 'Sensor ' + props.number + ' Calibration Values'}
        </Button>

        <Modal show={isLoading} onHide={handleClose} size="lg">
        <Modal.Header closeButton>
          <Modal.Title>Calibrate Moisture Levels</Modal.Title>
        </Modal.Header>
        <Modal.Body>
        V.Low:0-250<b>|</b>Low:251-499<b>|</b>Med:500<b>|</b>High:501-750<b>|</b>V.High:751-1023
        <hr></hr>
          <div className='dropdowns'>
                    <Form>
                        <Form.Label>Soil Sensor {props.number} - Dry - Value that is considered <b>Dry</b></Form.Label>
                            <RangeSlider
                                max={maxSliderVal}
                                value={soilSensorD}
                                onChange={changeEvent => setSoilSensorD(changeEvent.target.value)}
                            />
                    </Form>
                    <Form>
                        <Form.Label>Soil Sensor {props.number} - Wet - Value that is considered <b>Wet</b></Form.Label>
                            <RangeSlider
                                max={maxSliderVal}
                                value={soilSensorW}
                                onChange={changeEvent => setSoilSensorW(changeEvent.target.value)}
                            />
                    </Form>
          </div>
        </Modal.Body>
        <Modal.Footer>
          <Button variant="secondary" onClick={handleClose}>
            Close
          </Button>
          <Button variant="primary" onClick={(event) => {
                props.handleModal(soilSensorD, soilSensorW, props.number);
                handleClose()
            }}>
            Save Changes
          </Button>
        </Modal.Footer>
      </Modal>
    </div>
  );
}

export default CalibrateSensorModal