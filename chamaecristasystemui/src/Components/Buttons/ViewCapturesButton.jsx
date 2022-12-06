import React, { useEffect, useState } from 'react';
import { useNavigate } from "react-router-dom";
import Button from 'react-bootstrap/Button';

function ViewCapturesButton(props) {
  //Creates the navigation objectthat will handle page switching
  const navigate = useNavigate();
  let key = props.encKey;

  return (
    <Button
      variant="primary"
      size="lg"
      // Switches pages to the designated route
      onClick={() => navigate("/pictures",
      {
        state: {
          userKey: key,
        }
      })
    }
    >
      View Captures
    </Button>
  );
}

export default ViewCapturesButton