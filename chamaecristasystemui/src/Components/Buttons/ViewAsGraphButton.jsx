import React, { useContext }  from 'react';
import { useNavigate } from "react-router-dom";
import Button from 'react-bootstrap/Button';
import { StateContext } from '../../App';

function ViewAsGraphButton() {
  //Creates the navigation objectthat will handle page switching
  const navigate = useNavigate();
  const { key } = useContext(StateContext);
  
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