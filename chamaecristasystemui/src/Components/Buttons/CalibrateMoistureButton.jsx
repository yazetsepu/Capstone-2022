import React, { useEffect, useState } from 'react';
import Button from 'react-bootstrap/Button';
import Modal from 'react-bootstrap/Modal';
import Form from 'react-bootstrap/Form';
import RangeSlider from 'react-bootstrap-range-slider';
import 'react-bootstrap-range-slider/dist/react-bootstrap-range-slider.css';

//TODO

//Handles sending the POST request to the Commands table in the DB
async function simulateNetworkRequest() {
  // Contains the necessary headers and body information that make up a POST request
  const requestOptions = {
    method: 'POST',
    headers: { 'Content-Type': 'application/json' },
    body: JSON.stringify({ command_String: "ChangeMoisture"})
  };

  // const response = await fetch('https://cssrumapi.azurewebsites.net//Commands/', requestOptions)
  // const data = await response.json();
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

  //Triggers when the state of isLoading changes to allow for the button press to g through
  useEffect(() => {
    if (isLoading) {
      simulateNetworkRequest().then(() => {
        setLoading(false);
      });
    }
  }, [isLoading]);

  const handleClick = () => setLoading(true);
  const handleClose = () => setLoading(false)

  // const handleChange = (newVal) => setRValue(newVal)

  return (
    <div>
      {/* Renders the button */}
      <Button
        variant="warning"
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
          <div>
            <div>
              <Form>
                <Form.Label>Soil Sensor 1 - Wet</Form.Label>
                <RangeSlider
                  max={1023}
                  value={soilSensorOneW}
                  onChange={changeEvent => setSoilSensorOneW(changeEvent.target.value)}
                />
                <Form.Label>Soil Sensor 1 - Dry</Form.Label>
                <RangeSlider
                  max={1023}
                  value={soilSensorOneD}
                  onChange={changeEvent => setSoilSensorOneD(changeEvent.target.value)}
                />
              </Form>
              <Form>
                <Form.Label>Soil Sensor 2 - Wet</Form.Label>
                <RangeSlider
                  max={1023}
                  value={soilSensorTwoW}
                  onChange={changeEvent => setSoilSensorTwoW(changeEvent.target.value)}
                />
                <Form.Label>Soil Sensor 2 - Dry</Form.Label>
                <RangeSlider
                  max={1023}
                  value={soilSensorTwoD}
                  onChange={changeEvent => setSoilSensorTwoD(changeEvent.target.value)}
                />
              </Form>
              <Form>
                <Form.Label>Soil Sensor 3 - Wet</Form.Label>
                <RangeSlider
                  max={1023}
                  value={soilSensorThreeW}
                  onChange={changeEvent => setSoilSensorThreeW(changeEvent.target.value)}
                />
                <Form.Label>Soil Sensor 3 - Dry</Form.Label>
                <RangeSlider
                  max={1023}
                  value={soilSensorThreeD}
                  onChange={changeEvent => setSoilSensorThreeD(changeEvent.target.value)}
                />
              </Form>
              <Form>
                <Form.Label>Soil Sensor 4 - Wet</Form.Label>
                <RangeSlider
                  max={1023}
                  value={soilSensorFourW}
                  onChange={changeEvent => setSoilSensorFourW(changeEvent.target.value)}
                />
                <Form.Label>Soil Sensor 4 - Dry</Form.Label>
                <RangeSlider
                  max={1023}
                  value={soilSensorFourD}
                  onChange={changeEvent => setSoilSensorFourD(changeEvent.target.value)}
                />
              </Form>
            </div>
            <div>
              <Form>
                <Form.Label>Soil Sensor 5 - Wet</Form.Label>
                <RangeSlider
                  max={1023}
                  value={soilSensorFiveW}
                  onChange={changeEvent => setSoilSensorFiveW(changeEvent.target.value)}
                />
                <Form.Label>Soil Sensor 5 - Dry</Form.Label>
                <RangeSlider
                  max={1023}
                  value={soilSensorFiveD}
                  onChange={changeEvent => setSoilSensorFiveD(changeEvent.target.value)}
                />
              </Form>
              <Form>
                <Form.Label>Soil Sensor 6 - Wet</Form.Label>
                <RangeSlider
                  max={1023}
                  value={soilSensorSixW}
                  onChange={changeEvent => setSoilSensorSixW(changeEvent.target.value)}
                />
                <Form.Label>Soil Sensor 6 - Dry</Form.Label>
                <RangeSlider
                  max={1023}
                  value={soilSensorSixD}
                  onChange={changeEvent => setSoilSensorSixD(changeEvent.target.value)}
                />
              </Form>
              <Form>
                <Form.Label>Soil Sensor 7 - Wet</Form.Label>
                <RangeSlider
                  max={1023}
                  value={soilSensorSevenW}
                  onChange={changeEvent => setSoilSensorSevenW(changeEvent.target.value)}
                />
                <Form.Label>Soil Sensor 7 - Dry</Form.Label>
                <RangeSlider
                  max={1023}
                  value={soilSensorSevenD}
                  onChange={changeEvent => setSoilSensorSevenD(changeEvent.target.value)}
                />
              </Form>
              <Form>
                <Form.Label>Soil Sensor 8 - Wet</Form.Label>
                <RangeSlider
                  max={1023}
                  value={soilSensorEightW}
                  onChange={changeEvent => setSoilSensorEightW(changeEvent.target.value)}
                />
                <Form.Label>Soil Sensor 8 - Dry</Form.Label>
                <RangeSlider
                  max={1023}
                  value={soilSensorEightD}
                  onChange={changeEvent => setSoilSensorEightD(changeEvent.target.value)}
                />
              </Form>
            </div>
          </div>
        </Modal.Body>
        <Modal.Footer>
          <Button variant="secondary" onClick={handleClose}>
            Close
          </Button>
          <Button variant="primary" onClick={handleClose}>
            Save Changes
          </Button>
        </Modal.Footer>
      </Modal>
    </div>
  );
}

export default CalibrateMoistureButton