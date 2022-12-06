import React, { useEffect, useState } from 'react';
import { useNavigate } from "react-router-dom";
import Button from 'react-bootstrap/Button';

function ViewAsGraphButton(props) {
  //Creates the navigation objectthat will handle page switching
  const navigate = useNavigate();
  let key = props.encKey;
  
  return (
    <Button
      variant="primary"
      size="lg"
      // Switches pages to the designated route
      onClick={() => navigate("/graph",
      {
        state: {
          userKey: key,
        }
      })}
    >
      View as Graph
    </Button>
  );
}

export default ViewAsGraphButton