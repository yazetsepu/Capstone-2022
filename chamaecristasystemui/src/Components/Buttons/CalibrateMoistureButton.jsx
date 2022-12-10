import React, { useState, useContext } from 'react';
import Button from 'react-bootstrap/Button';
import CalibrateSensorModalContainer from '../Modals/CalibrateSensorModalContainer';
import { StateContext } from '../../App';
import './button-styles/CalibrateMoistureButton.css'

//Allows user to manually calibrate the 8 soil moisture sensors present in the system
function CalibrateMoistureButton(props) {
  //Dictates whether the button was recently pressed or if it can be pressed again
  const [isLoading, setLoading] = useState(false);

  const { isRetrainExecuting } = useContext(StateContext);

  const handleClick = () => setLoading(true);
  const handleClose = () => setLoading(false)

  return (
    <div>
      {/* Renders the button */}
      <Button
        variant="primary"
        size="lg"
        disabled={isLoading || isRetrainExecuting}
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