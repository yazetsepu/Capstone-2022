import React, { useState } from 'react';
import Button from 'react-bootstrap/Button';
import CalibrateSensorModalContainer from '../Modals/CalibrateSensorModalContainer';
import './button-styles/CalibrateMoistureButton.css'

//Allows user to manually calibrate the 8 soil moisture sensors present in the system
function CalibrateMoistureButton(props) {
  //Dictates whether the button was recently pressed or if it can be pressed again
  const [isLoading, setLoading] = useState(false);


  const handleClick = () => setLoading(true);
  const handleClose = () => setLoading(false)

  return (
    <div>
      {/* Renders the button */}
      <Button
        variant="primary"
        size="lg"
        disabled={isLoading}
        onClick={!isLoading ? handleClick : null}
      >
        {isLoading ? 'Calibrating...' : 'Calibrate Moisture Levels'}
      </Button>
      
      <CalibrateSensorModalContainer isLoading={isLoading} onHide={handleClose} 
                                     handleClose={handleClose} />
    </div>
  );
}

export default CalibrateMoistureButton