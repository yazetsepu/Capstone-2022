import React, { useEffect, useState } from 'react';
import Button from 'react-bootstrap/Button';
import Modal from 'react-bootstrap/Modal';
import Form from 'react-bootstrap/Form';
import RangeSlider from 'react-bootstrap-range-slider';
import 'react-bootstrap-range-slider/dist/react-bootstrap-range-slider.css';
// import './button-styles/CalibrateMoistureButton.css';

async function simulateNetworkRequest() {
  const requestOptions = {
    method: 'POST',
    headers: { 'Content-Type': 'application/json' },
    body: JSON.stringify({ command_string: "Water Plant"})
  };

  const response = await fetch('https://cssrumapi.azurewebsites.net//Commands/', requestOptions)
  const data = await response.json();
  return new Promise((resolve) => setTimeout(resolve, 2000));
}

function CalibrateMoistureButton(props) {
  const [isLoading, setLoading] = useState(false);

  const [rValue, setRValue] = useState(0);
  const [gValue, setGValue] = useState(0);
  const [bValue, setBValue] = useState(0);
  const [nWValue, setNWValue] = useState(0);
  const [wWValue, setWWValue] = useState(0);

  useEffect(() => {
    // if (isLoading) {
    //   simulateNetworkRequest().then(() => {
    //     setLoading(false);
    //   });
    // }
  }, [isLoading]);

  const handleClick = () => setLoading(true);
  const handleClose = () => setLoading(false)

  const handleChange = (newVal) => setRValue(newVal)

  return (
    <div>
      <Button
        variant="primary"
        size="lg"
        disabled={isLoading}
        onClick={!isLoading ? handleClick : null}
      >
        {isLoading ? 'Loading…' : 'Calibrate Moisture Levels'}
      </Button>
      
      <Modal show={isLoading} onHide={handleClose}>
        <Modal.Header closeButton>
          <Modal.Title>Change Moisture Levels</Modal.Title>
        </Modal.Header>
        <Modal.Body>
          <Form>
            <Form.Label>Wet</Form.Label>
            <RangeSlider
              max={1023}
              value={rValue}
              onChange={changeEvent => setRValue(changeEvent.target.value)}
            />
            <Form.Label>Dry</Form.Label>
            <RangeSlider
              max={1023}
              value={gValue}
              onChange={changeEvent => setGValue(changeEvent.target.value)}
            />
            <hr></hr>
            <div>
              <Form.Check
              inline
              label="Sensor - 1: Resevoir"
              name="group1"
              type='radio'
              id={`inline-$'radio'-1`}
              />
              <Form.Check
                inline
                label="Sensor - 2: Plant Container"
                name="group1"
                type='radio'
                id={`inline-$'radio'-2`}
              />
            </div>
          </Form>
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