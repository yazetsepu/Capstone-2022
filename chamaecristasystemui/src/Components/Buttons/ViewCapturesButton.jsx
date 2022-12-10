import React, { useContext } from 'react';
import { useNavigate } from "react-router-dom";
import Button from 'react-bootstrap/Button';
import { StateContext } from '../../App';

function ViewCapturesButton() {
  //Creates the navigation objectthat will handle page switching
  const navigate = useNavigate();
  const { isRetrainExecuting, key } = useContext(StateContext);

  return (
    <Button
      variant="primary"
      size="lg"
      // Switches pages to the designated route
      onClick={() => navigate("/pictures",
      {
        state: {
          userKey: key,
          retrain: isRetrainExecuting,
        }
      })
    }
    >
      View Captures
    </Button>
  );
}

export default ViewCapturesButton