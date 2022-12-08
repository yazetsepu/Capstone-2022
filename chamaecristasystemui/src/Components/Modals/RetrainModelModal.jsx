import React from 'react';
import Button from 'react-bootstrap/Button';
import Modal from 'react-bootstrap/Modal';

function RetrainModelModal(props) {
  return (
    <div>
      {/* Pops up a notification to ask the user if  they're sure they want to retrain the model */}
      <Modal show={props.isShowing} onHide={props.handleClose} size="lg">
        <Modal.Header closeButton>
          <Modal.Title>Are you sure you want to retrain the Model with the pictures currently available in <b>ViewCaptures</b></Modal.Title>
        </Modal.Header>
        <Modal.Body><b> Please make sure to make any relevant changes to the pictures in the View Captures Page before moving on</b></Modal.Body>
        <Modal.Footer>
          <Button variant="primary" onClick={props.handleClose}>
            No, dont retrain the model. Close this popup
          </Button>
          <Button variant="danger" onClick={props.handleSubmit}>
            Yes I am very sure! Retrain the model.
          </Button>
        </Modal.Footer>
      </Modal>
    </div>
  );
}

export default RetrainModelModal