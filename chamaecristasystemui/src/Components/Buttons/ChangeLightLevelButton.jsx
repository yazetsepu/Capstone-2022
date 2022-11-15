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

  const [rvalue, setrValue] = useState(0);

  useEffect(() => {
    // if (isLoading) {
    //   simulateNetworkRequest().then(() => {
    //     setLoading(false);
    //   });
    // }
  }, [isLoading]);

  const handleClick = () => setLoading(true);
  const handleClose = () => setLoading(false)

  const handleChange = (newVal) => setrValue(newVal)

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
          <Modal.Title>Modal heading</Modal.Title>
        </Modal.Header>
        <Modal.Body>
          <Form>
            <Form.Group className="mb-3" controlId="exampleForm.ControlInput1">
              <Form.Label>Email address</Form.Label>
              <Form.Control
                type="email"
                placeholder="name@example.com"
                autoFocus
              />
            </Form.Group>
            <Form.Group
              className="mb-3"
              controlId="exampleForm.ControlTextarea1"
            >
              <Form.Label>Example textarea</Form.Label>
              <Form.Control as="textarea" rows={3} />
            </Form.Group>
            <RangeSlider
              value={rvalue}
              onChange={changeEvent => setrValue(changeEvent.target.value)}
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