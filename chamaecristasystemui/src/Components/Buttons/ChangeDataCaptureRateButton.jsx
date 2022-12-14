import React, { useState } from 'react';
import Button from 'react-bootstrap/Button';
import Modal from 'react-bootstrap/Modal';
import Form from 'react-bootstrap/Form';
import InputGroup from 'react-bootstrap/InputGroup';
import RangeSlider from 'react-bootstrap-range-slider';
import 'react-bootstrap-range-slider/dist/react-bootstrap-range-slider.css';

//Handles sending the POST request to the Commands table in the DB to schedule a light dimming
async function changeDataCaptureRate(minutes) {
  //Formats received value sinto a string
  let changeValue ="{minutes:"+ minutes +"}"

  // Contains the necessary headers and body information that make up a POST request
  const requestOptions = {
    method: 'POST',
    headers: { 'Content-Type': 'application/json' },
    body: JSON.stringify(
      { 
        command_String: "CaptureTime",
        command_Value: changeValue,
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

//Allows user to manually set the light level displayed by the system
function ChangeDataCaptureRateButton(props) {
  //Dictates whether the button was recently pressed or if it can be pressed again
  const [isLoading, setLoading] = useState(false);
  const [isShowing, setShowing] = useState(false)
  //Stores time for scheduling dimming
  const [minutes, setMinutes] = useState(1);

  //handles Showing and closing the modal
  const handleClick = () => setShowing(true);
  const handleClose = () => {
    setLoading(false)
    setShowing(false)
  }

  //Triggers when the internal modal submit button is pressed to execute the 
  const handleSubmit = () => {
    changeDataCaptureRate(minutes)   
    setLoading(false);
    setShowing(false);
  }

  //Uses RegEx to validate that whatever is entered is done so in 24 hour format correctly like so: XX:XX
  const validationBool = minutes.length > 2 || parseInt(minutes) <= 0 || !(/[0-9]/.test(minutes))

  return (
    <div>
      <Button
        variant="primary"
        size="lg"
        disabled={isLoading}
        onClick={!isLoading ? handleClick : null}
      >
        {isLoading ? 'Loading…' : 'Change Data Capture Rate'}
      </Button>
      {/* Pops up to allow the user to individually change the light level of each color */}
      <Modal show={isShowing} onHide={handleClose}>
        <Modal.Header closeButton>
          <Modal.Title>Change the rate at which the system sends new data</Modal.Title>
        </Modal.Header>
        <Modal.Body>
          <Form.Group md="4" controlId="validationTime">
            <InputGroup hasValidation >
              <Form.Control
                as='input'
                type="text"
                placeholder="Please Enter a valid amount of minutes"
                aria-describedby="inputGroupPrepend"
                required
                onChange={changeEvent => {setMinutes(changeEvent.target.value)}}
                isInvalid={validationBool}
              />
              <Form.Control.Feedback type="invalid">
                Please enter a valid amount of minutes
              </Form.Control.Feedback>
            </InputGroup>
          </Form.Group>
        </Modal.Body>
        <Modal.Footer>
          <Button variant="secondary" onClick={handleClose}>
            Close
          </Button>
          <Button disabled={validationBool} variant="primary" onClick={handleSubmit}>
            Save Changes
          </Button>
        </Modal.Footer>
      </Modal>
    </div>
  );
}

export default ChangeDataCaptureRateButton