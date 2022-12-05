import React, { useEffect, useState } from 'react';
import { useNavigate } from "react-router-dom";
import Button from 'react-bootstrap/Button';

function ViewCapturesButton() {
  //Creates the navigation objectthat will handle page switching
  const navigate = useNavigate();

  return (
    <Button
      className='but'
      variant="primary"
      size="lg"
      // Switches pages to the designated route
      onClick={() => navigate("/pictures")}
    >
      View Captures
    </Button>
  );
}

export default ViewCapturesButton