import React, { useState } from 'react';
import Button from 'react-bootstrap/Button';
import './button-styles/RetrainModelButton.css'
import RetrainModelModal from '../Modals/RetrainModelModal';

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

// TODO Put correct route here
await fetch('https://cssrumapi.azurewebsites.net//Commands/', requestOptions)
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
      <div className='retrain-btn'>
        <Button
          variant="primary"
          size="lg"
          disabled={isLoading}
          onClick={!isLoading ? handleClick : null}
        >
          {isLoading ? 'Loading…' : 'Retrain Model'}
        </Button>
      </div>
      {/* Pops up a notification to ask the user if  they're sure they want to retrain the model */}
      <RetrainModelModal isShowing={isShowing} handleClose={handleClose} handleSubmit={handleSubmit} />
    </div>
  );
}

export default RetrainModelButton