import React, { useEffect, useState } from 'react';
import Button from 'react-bootstrap/Button';
import Modal from 'react-bootstrap/Modal';
import Form from 'react-bootstrap/Form';
import RangeSlider from 'react-bootstrap-range-slider';
import 'react-bootstrap-range-slider/dist/react-bootstrap-range-slider.css';

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

function ChangeLightLevelButton(props) {
  const [isLoading, setLoading] = useState(false);

  const [rValue, setRValue] = useState(0);
  const [gValue, setGValue] = useState(0);
  const [bValue, setBValue] = useState(0);
  const [wValue, setWValue] = useState(0);

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
        {isLoading ? 'Loading…' : 'Change Light Level'}
      </Button>
      
      <Modal show={isLoading} onHide={handleClose}>
        <Modal.Header closeButton>
          <Modal.Title>Change Light Output Colors</Modal.Title>
        </Modal.Header>
        <Modal.Body>
          <Form>
            <Form.Label>Red</Form.Label>
            <RangeSlider
              max={255}
              value={rValue}
              onChange={changeEvent => setRValue(changeEvent.target.value)}
            />
            <Form.Label>Green</Form.Label>
            <RangeSlider
              max={255}
              value={gValue}
              onChange={changeEvent => setGValue(changeEvent.target.value)}
            />
            <Form.Label>Blue</Form.Label>
            <RangeSlider
              max={255}
              value={bValue}
              onChange={changeEvent => setBValue(changeEvent.target.value)}
            />
            <Form.Label>White</Form.Label>
            <RangeSlider
              max={255}
              value={wValue}
              onChange={changeEvent => setWValue(changeEvent.target.value)}
            />
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

export default ChangeLightLevelButton