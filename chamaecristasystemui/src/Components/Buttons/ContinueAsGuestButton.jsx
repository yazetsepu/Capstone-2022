import React from 'react';
import { useNavigate } from "react-router-dom";
import Button from 'react-bootstrap/Button';

function ContinueAsGuestButton() {
  //Creates the navigation objectthat will handle page switching
  const navigate = useNavigate();

  const handleClick = () => {
    navigate('/home',
    {
      state: {
        userKey: 0,
      }
    });
  };

  return (
    <Button
      className='but'
      variant="primary"
      size="lg"
      // Switches pages to the designated route
      onClick={handleClick}
    >
      Continue as Guest
    </Button>
  );
}

export default ContinueAsGuestButton