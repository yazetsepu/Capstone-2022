import React, { useState } from 'react';
import Button from 'react-bootstrap/Button';
import Modal from 'react-bootstrap/Modal';
import Form from 'react-bootstrap/Form';
import InputGroup from 'react-bootstrap/InputGroup';

function LoginModal(props) {

    //handles Showing and closing the modal
    const handleClose = () => props.setShowing(false)
  
    return (
      <div>
        <Modal show={props.isShowing} onHide={handleClose}>
          <Modal.Header closeButton>
            <Modal.Title>Enter admin credentials</Modal.Title>
          </Modal.Header>
          <Modal.Body>
            <Form.Group md="4" controlId="validationTime">
              <InputGroup hasValidation >
                  
                <Form.Control
                    as='input'
                    type="password"
                    placeholder="Password"
                    aria-describedby="inputGroupPrepend"
                    isInvalid={props.Invalid}
                    required
                    onChange={changeEvent => {props.setEnteredPass(changeEvent.target.value)}}/>
                        <Button 
                            variant="primary" 
                            id="button-addon2"
                            onClick={props.handleClick}
                            >
                            Login
                        </Button>
              </InputGroup>
            </Form.Group>
          </Modal.Body>
        </Modal>
      </div>
    );
  }
  
  export default LoginModal