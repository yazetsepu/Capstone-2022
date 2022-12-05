import React, { useEffect, useState } from 'react';
import Button from 'react-bootstrap/Button';
import Modal from 'react-bootstrap/Modal';
import Form from 'react-bootstrap/Form';

async function retrainModel(){

// Contains the necessary headers and body information that make up a POST request
const requestOptions = {
  method: 'POST',
  headers: { 'Content-Type': 'application/json' },
  body: JSON.stringify(
    {  
      command_String: "RetrainModel",
      command_Value: null,
      command_Read: null,
      command_Performed: null,
      logs: {
        
      }
    }
  )
};

console.log(requestOptions)
// TODO Put correct route here
const response = await fetch('https://cssrumapi.azurewebsites.net//Commands/', requestOptions)
const data = await response.json();
return new Promise((resolve) => {});
}

function RetrainModelButton(props) {
  //Dictates whether the button was recently pressed or if it can be pressed again
  const [isLoading, setLoading] = useState(false);
  const [isShowing, setShowing] = useState(false)

  const handleClick = () => setShowing(true);
  const handleClose = () => {
    setLoading(false)
    setShowing(false)
  }

  //Triggers when the internal modal submit button is pressed to execute the button
  const handleSubmit = () => {
    retrainModel();
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
        {isLoading ? 'Loading…' : 'Retrain Model'}
      </Button>
      {/* Pops up a notification to ask the user if  tehy're sure they want to retrain the model */}
      <Modal show={isShowing} onHide={handleClose} size="lg">
        <Modal.Header closeButton>
          <Modal.Title>Are you sure you want to retrain the Model with the pictures currently available in <b>ViewCaptures</b></Modal.Title>
        </Modal.Header>
        <Modal.Body><b> Please make sure to make any relevant changes to the pictures in the View Captures Page before moving on</b></Modal.Body>
        <Modal.Footer>
          <Button variant="primary" onClick={handleClose}>
            No, dont retrain the model. Close this popup
          </Button>
          <Button variant="danger" onClick={handleSubmit}>
            Yes I am very sure! Retrain the model.
          </Button>
        </Modal.Footer>
      </Modal>
    </div>
  );
}

export default RetrainModelButton