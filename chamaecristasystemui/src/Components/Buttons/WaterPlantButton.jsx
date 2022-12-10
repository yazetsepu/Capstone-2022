import React, { useEffect, useState, useContext } from 'react';
import Button from 'react-bootstrap/Button';
import Modal from 'react-bootstrap/Modal';
import { StateContext } from '../../App';

async function simulateNetworkRequest() {
  const requestOptions = {
    method: 'POST',
    headers: { 'Content-Type': 'application/json' },
    body: JSON.stringify
    (
      // JSON Body to be sent to the API
      { command_String: "Water Plant",
        command_Value: null,
        command_Read: null,
        command_Performed: null,
        logs: {
          logs_Text: null
        }
      }
    )
  };

  await fetch('https://cssrumapi.azurewebsites.net//Commands/', requestOptions)
  return new Promise((resolve) => setTimeout(resolve, 2000));
}

function WaterPlantButton(props) {
  const [isLoading, setLoading] = useState(false);

  const { isRetrainExecuting } = useContext(StateContext);

  useEffect(() => {
    if (isLoading) {
      simulateNetworkRequest().then(() => {
        setLoading(false);
      });
    }
  }, [isLoading]);

  const handleClick = () => setLoading(true);

  return (
    <div>  
      <Button
        variant="primary"
        size="lg"
        disabled={isLoading || isRetrainExecuting}
        onClick={!isLoading ? handleClick : null}
      >
        {isLoading ? 'Loading…' : 'Water Plant'}
      </Button>
      {/* Show a small modal to notify the user the request went through successfuly */}
      <Modal
        size="sm"
        centered
        show={isLoading}
        onHide={() => setLoading(false)}
        aria-labelledby="example-modal-sizes-title-sm"
      >
        <Modal.Header closeButton>
          <Modal.Title id="example-modal-sizes-title-sm">
            Watering Plant
          </Modal.Title>
        </Modal.Header>
        <Modal.Body>Please Wait while the plant is being watered</Modal.Body>
      </Modal>
    </div>
  );
}

export default WaterPlantButton