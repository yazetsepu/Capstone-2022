import React, { useEffect, useState } from 'react';
import Button from 'react-bootstrap/Button';
import Modal from 'react-bootstrap/Modal';
import Form from 'react-bootstrap/Form';
import RangeSlider from 'react-bootstrap-range-slider';
import 'react-bootstrap-range-slider/dist/react-bootstrap-range-slider.css';

//Handles sending the POST request to the Commands table in the DB
async function simulateNetworkRequest(WW, R, G, B) {
  //Formats received value sinto a string
  let colorString="{WW:"+WW+","+"R:"+R+","+"G:"+G+","+"B:"+B+"}";
  //WW:x,R:x,...

  // Contains the necessary headers and body information that make up a POST request
  const requestOptions = {
    method: 'POST',
    headers: { 'Content-Type': 'application/json' },
    body: JSON.stringify({ command_String: "Dim", command_Value: colorString})
  };
  console.log(requestOptions)
  const response = await fetch('https://cssrumapi.azurewebsites.net//Commands/', requestOptions)
  const data = await response.json();
  return new Promise((resolve) => {});
}

//Allows user to manually set the light level displayed by the system
function ChangeLightLevelButton(props) {
  //Dictates whether the button was recently pressed or if it can be pressed again
  const [isLoading, setLoading] = useState(false);
  const [isShowing, setShowing] = useState(false)
  //Stores and sets each individual ligth color and it's value
  const [rValue, setRValue] = useState(0);
  const [gValue, setGValue] = useState(0);
  const [bValue, setBValue] = useState(0);
  const [nWValue, setNWValue] = useState(0);
  const [wWValue, setWWValue] = useState(0);

  //Triggers when the state of isLoading changes to allow for the button press to g through
  useEffect(() => {
    if (isLoading) {
      simulateNetworkRequest().then(() => {
        setLoading(false);
      });
    }
  }, [isLoading]);

  const handleClick = () => setShowing(true);
  const handleClose = () => {
    setLoading(false)
    setShowing(false)
  }

  //Triggers when the internal modal submit button is pressed to execute the 
  const handleSubmit = () => {
    simulateNetworkRequest(wWValue, rValue, gValue, bValue);
    setLoading(false);
    setShowing(false)
  }

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
      {/* Pops up to allow the user to individually change the light level of each color */}
      <Modal show={isShowing} onHide={handleClose}>
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
            <Form.Label>Natural White</Form.Label>
            <RangeSlider
              max={255}
              value={nWValue}
              onChange={changeEvent => setNWValue(changeEvent.target.value)}
            />
            <Form.Label>Warm White</Form.Label>
            <RangeSlider
              max={255}
              value={wWValue}
              onChange={changeEvent => setWWValue(changeEvent.target.value)}
            />
          </Form>
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

export default ChangeLightLevelButton