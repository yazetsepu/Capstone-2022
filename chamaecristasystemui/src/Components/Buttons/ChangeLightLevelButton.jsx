import React, { useState } from 'react';
import Button from 'react-bootstrap/Button';
import Modal from 'react-bootstrap/Modal';
import Form from 'react-bootstrap/Form';
import InputGroup from 'react-bootstrap/InputGroup';
import RangeSlider from 'react-bootstrap-range-slider';
import 'react-bootstrap-range-slider/dist/react-bootstrap-range-slider.css';

//Handles sending the POST request to the Commands table in the DB to schedule a light dimming
async function scheduleDimPlantLight(hour, min, WW, R, G, B, isScheduled) {
  //Formats received value sinto a string
  let changeString = !isScheduled? "Schedule Dim" : "Dim"
  let changeValue = !isScheduled? "{hour: "+hour+", minute:"+min+" W:"+WW+", "+"R:"+R+", "+"G:"+G+", "+"B:"+B+"}" :
                                  "{W:"+WW+", "+"R:"+R+", "+"G:"+G+", "+"B:"+B+"}"

  // Contains the necessary headers and body information that make up a POST request
  const requestOptions = {
    method: 'POST',
    headers: { 'Content-Type': 'application/json' },
    body: JSON.stringify(
      { 
        command_String: changeString,
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
  //Stores time for scheduling dimming
  const [timeOfDay, setTimeOfDay] = useState("00:00");
  const [enableSched, setEnableSched] = useState(true);

  //handles Showing and closing the modal
  const handleClick = () => setShowing(true);
  const handleClose = () => {
    setLoading(false)
    setShowing(false)
  }

  //Triggers when the internal modal submit button is pressed to execute the 
  const handleSubmit = () => {
    scheduleDimPlantLight(timeOfDay.split(':')[0], timeOfDay.split(':')[1], wWValue, rValue, gValue, bValue, enableSched)
    setLoading(false);
    setShowing(false);
    setEnableSched(true);
  }

  //Uses RegEx to validate that whatever is entered is done so in 24 hour format correctly like so: XX:XX
  const validationBool = (/[a-zA-Z]/.test(timeOfDay)) || timeOfDay.length !== 5 || 
                        !(/[\u003A]/.test(timeOfDay[2])) || !(/[0-2]/.test(timeOfDay[0])) || 
                        (/[2]/.test(timeOfDay[0]) && !(/[0-3]/.test(timeOfDay[1]))) || 
                        !(/[0-5]/.test(timeOfDay[3])) || !(/[0-9]/.test(timeOfDay[4]));

  const handleEnable = () => {
    setEnableSched(!enableSched);
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
          <h4>Modify the current light output colors</h4>
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
          {/* Schedule a light change */}
          </Form>
          <hr></hr>
          <h4>Schedule a change for light output color</h4>
          <Form.Group md="4" controlId="validationTime">
            <Form.Label>Schedule a time to dim the lights (24 hr format - Ex: <b>23:45</b>)</Form.Label>
            <InputGroup hasValidation >
                <Button 
                  variant="primary" 
                  id="button-addon2"
                  onClick={handleEnable}
                  >
                  {enableSched? "Disabled" : "Enabled"}
                </Button>
              <Form.Control
                as='input'
                type="text"
                placeholder="Leave empty to change now"
                aria-describedby="inputGroupPrepend"
                required
                onChange={changeEvent => {setTimeOfDay(changeEvent.target.value)}}
                isInvalid={validationBool}
                disabled={enableSched}
              />
              <Form.Control.Feedback type="invalid">
                Enter the time you wish the lights to change color. Example - 22:05
              </Form.Control.Feedback>
            </InputGroup>
            <Form.Label>When disabled, will dim the light at the current time</Form.Label>
          </Form.Group>
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