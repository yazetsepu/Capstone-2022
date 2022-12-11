import React, { useState } from 'react';
import Form from 'react-bootstrap/Form';
import Button from 'react-bootstrap/Button';
import RangeSlider from 'react-bootstrap-range-slider';
import Modal from 'react-bootstrap/Modal';
import Spinner from 'react-bootstrap/Spinner';
import 'react-bootstrap-range-slider/dist/react-bootstrap-range-slider.css';
import './modal-styles/CalibrateSensorModal.css'

//Handles each sesnor button and the sliders that pop up, as well as sends the data of sliders to parent
function CalibrateSensorModalRange(props) {

  //Stores and sets each individual soil sensor values
  const maxSliderVal = 100;
  //Wet
  const [soilSensorW, setSoilSensorW] = useState(100);
  //Dry
  const [soilSensorD, setSoilSensorD] = useState(0);
  //Whether or not the secondary modal is sbeing displayed
  const [isLoading, setLoading] = useState(false);

  const [isWetCalibrating, setWetIsCalibrating] = useState(false)
  const [isDryCalibrating, setDryIsCalibrating] = useState(false)

  async function calibrate(cmdString, number) {
    let sensorValues="{sensor:" + number + ", vwc:" + (cmdString === "CalibrateDry"? soilSensorD : soilSensorW) + "}";

  // Contains the necessary headers and body information that make up a POST request
    const requestOptions = {
      method: 'POST',
      headers: { 'Content-Type': 'application/json' },
      body: JSON.stringify(
      {  
        command_String: cmdString,
        command_Value: sensorValues,
        command_Read: null,
        command_Performed: null,
        logs: {
          logs_Text: null
        }
      }
    )
  };
    const response = await fetch('https://cssrumapi.azurewebsites.net//Commands/', requestOptions)
    const data = await response.json();
    cmdString === "CalibrateDry"? setDryIsCalibrating(false) : setWetIsCalibrating(false)
    return new Promise((resolve) => {});
}

  const handleClick = () => setLoading(true);
  const handleClose = () => {
    setDryIsCalibrating(false)
    setWetIsCalibrating(false)
    setLoading(false)
  }

  return (
    <div className='individual-dropdown'>
         {/* Renders the button */}
        <Button
            variant="primary"
            size="med"
            disabled={isLoading}
            onClick={!isLoading ? handleClick : null}
        >
            {isLoading ? 'Loading…' : 'Sensor ' + (props.number+1) + ' Calibration Values'}
        </Button>

        <Modal show={isLoading} onHide={handleClose} size="lg">
        <Modal.Header closeButton>
          <Modal.Title>Calibrate Moisture Levels</Modal.Title>
        </Modal.Header>
        <Modal.Body>
        Set the <b>Volumetric Water Content</b> of this sensor for both dry and wet conditions respectively.
        <hr></hr>
          <div className='dropdowns'>
                    <Form>
                        <Form.Label><b>Dry the sensor well before setting the value</b></Form.Label>
                            <RangeSlider
                                max={maxSliderVal}
                                value={soilSensorD}
                                onChange={changeEvent => setSoilSensorD(changeEvent.target.value)}
                            />
                    </Form>
                    <Form>
                        <Form.Label><b>Put the sensor in water before setting the value</b></Form.Label>
                            <RangeSlider
                                max={maxSliderVal}
                                value={soilSensorW}
                                onChange={changeEvent => setSoilSensorW(changeEvent.target.value)}
                            />
                    </Form>
          </div>
        </Modal.Body>
        <Modal.Footer>
          
          <Button variant="primary" onClick={async (event) => {
                setDryIsCalibrating(true)
                calibrate("CalibrateDry", props.number)
            }}>
            {isDryCalibrating? <Spinner animation="border" variant="secondary" size='sm'/> : 'Calibrate Sensor Dry Value'}
          </Button>
          <Button variant="primary" onClick={async (event) => {
                setWetIsCalibrating(true)
                calibrate("CalibrateWet", props.number)
            }}>
            {isWetCalibrating? <Spinner animation="border" variant="secondary" size='sm'/> : 'Calibrate Sensor Wet Value'}
          </Button>
          <Button variant="secondary" onClick={handleClose}>
            Close
          </Button>
        </Modal.Footer>
      </Modal>
    </div>
  );
}

export default CalibrateSensorModalRange