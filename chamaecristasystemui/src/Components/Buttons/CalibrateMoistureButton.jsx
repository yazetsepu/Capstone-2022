import React, { useEffect, useState } from 'react';
import Button from 'react-bootstrap/Button';
import Modal from 'react-bootstrap/Modal';
import Form from 'react-bootstrap/Form';
import CalibrateSensorModal from '../Modals/CalibrateSensorModal';
import RangeSlider from 'react-bootstrap-range-slider';
import 'react-bootstrap-range-slider/dist/react-bootstrap-range-slider.css';
import './button-styles/calibratemoisturebutton.css'

//TODO

//Handles sending the POST request to the Commands table in the DB
async function calibrateMoistureSensors(S1D, S2D, S3D, S4D, S5D, S6D, S7D, S8D, 
                                      S1W, S2W, S3W, S4W, S5W, S6W, S7W, S8W) 
{

  let sensorValues="{S1D:"+S1D+","+"S2D:"+S2D+","+"S3D:"+S3D+","+"S4D:"+S4D+","+ 
                    "S5D:"+S6D+","+"S6D:"+S6D+","+"S7D:"+S7D+","+"S8D:"+S8D+","+
                    "S1W:"+S1W+","+"S2W:"+S2W+","+"S3W:"+S3W+","+"S4W:"+S4W+","+
                    "S5W:"+S5W+","+"S6W:"+S6W+","+"S7W:"+S7W+","+"S8W:"+S8W+"}";

  // Contains the necessary headers and body information that make up a POST request
  const requestOptions = {
    method: 'POST',
    headers: { 'Content-Type': 'application/json' },
    body: JSON.stringify(
    {  
      command_String: "ChangeMoisture",
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
  return new Promise((resolve) => {});
}

//Allows user to manually calibrate the 8 soil moisture sensors present in the system
function CalibrateMoistureButton(props) {
  //Dictates whether the button was recently pressed or if it can be pressed again
  const [isLoading, setLoading] = useState(false);
  //Stores and sets each individual soil sensor values
  //Wet
  const [soilSensorOneW, setSoilSensorOneW] = useState(500);
  const [soilSensorTwoW, setSoilSensorTwoW] = useState(500);
  const [soilSensorThreeW, setSoilSensorThreeW] = useState(500);
  const [soilSensorFourW, setSoilSensorFourW] = useState(500);
  const [soilSensorFiveW, setSoilSensorFiveW] = useState(500);
  const [soilSensorSixW, setSoilSensorSixW] = useState(500);
  const [soilSensorSevenW, setSoilSensorSevenW] = useState(500);
  const [soilSensorEightW, setSoilSensorEightW] = useState(500);
  //Dry
  const [soilSensorOneD, setSoilSensorOneD] = useState(0);
  const [soilSensorTwoD, setSoilSensorTwoD] = useState(0);
  const [soilSensorThreeD, setSoilSensorThreeD] = useState(0);
  const [soilSensorFourD, setSoilSensorFourD] = useState(0);
  const [soilSensorFiveD, setSoilSensorFiveD] = useState(0);
  const [soilSensorSixD, setSoilSensorSixD] = useState(0);
  const [soilSensorSevenD, setSoilSensorSevenD] = useState(0);
  const [soilSensorEightD, setSoilSensorEightD] = useState(0);

  const handleClick = () => setLoading(true);
  const handleClose = () => setLoading(false)

  // const handleChange = (newVal) => setRValue(newVal)

  const handleModal = (dry, wet, number) => {
    switch(number){
      case 1:
        setSoilSensorOneW(wet);
        setSoilSensorOneD(dry)
        break;
      case 2:
        setSoilSensorTwoW(wet);
        setSoilSensorTwoD(dry)
        break;
      case 3:
        setSoilSensorThreeW(wet);
        setSoilSensorThreeD(dry)
        break;
      case 4:
        setSoilSensorFourW(wet);
        setSoilSensorFourD(dry)
        break;
      case 5:
        setSoilSensorFiveW(wet);
        setSoilSensorFiveD(dry)
        break;
      case 6:
        setSoilSensorSixW(wet);
        setSoilSensorSixD(dry)
        break;
      case 7:
        setSoilSensorSevenW(wet);
        setSoilSensorSevenD(dry)
        break;
      default:
        setSoilSensorEightW(wet);
        setSoilSensorEightD(dry)
    }
  }

  const handleSubmit = () => {
    calibrateMoistureSensors(soilSensorOneD, soilSensorTwoD, soilSensorThreeD, soilSensorFourD,
                           soilSensorFiveD, soilSensorSixD, soilSensorSevenD, soilSensorEightD,
                           soilSensorOneW, soilSensorTwoW, soilSensorThreeW, soilSensorFourW,
                           soilSensorFiveW, soilSensorSixW, soilSensorSevenW, soilSensorEightW);
    handleClose();
  }

  return (
    <div>
      {/* Renders the button */}
      <Button
        variant="primary"
        size="lg"
        disabled={isLoading}
        onClick={!isLoading ? handleClick : null}
      >
        {isLoading ? 'Loading…' : 'Calibrate Moisture Levels'}
      </Button>
      
      {/* A Modal is a mini screen that pops up when an event happens and that contains elements inside */}
      <Modal show={isLoading} onHide={handleClose}>
        <Modal.Header closeButton>
          <Modal.Title>Calibrate Moisture Levels</Modal.Title>
        </Modal.Header>
        <Modal.Body>
          <div className='dropdowns'>
            <div>
              <CalibrateSensorModal number={1} handleModal={handleModal}/>
              <CalibrateSensorModal number={2} handleModal={handleModal}/>
              <CalibrateSensorModal number={3} handleModal={handleModal}/>
              <CalibrateSensorModal number={4} handleModal={handleModal}/>
            </div>
            <div>
              <CalibrateSensorModal number={5} handleModal={handleModal}/>
              <CalibrateSensorModal number={6} handleModal={handleModal}/>
              <CalibrateSensorModal number={7} handleModal={handleModal}/>
              <CalibrateSensorModal number={8} handleModal={handleModal}/>
            </div>
          </div>
        </Modal.Body>
        <Modal.Footer>
          <Button variant="secondary" onClick={handleClose}>
            Close
          </Button>
          <Button variant="primary" onClick={handleSubmit}>
            Save Changes
          </Button>
        </Modal.Footer>
      </Modal>
    </div>
  );
}

export default CalibrateMoistureButton