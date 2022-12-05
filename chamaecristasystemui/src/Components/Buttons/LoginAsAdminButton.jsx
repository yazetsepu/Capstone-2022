import React, { useEffect, useState } from 'react';
import { useNavigate } from "react-router-dom";
import Button from 'react-bootstrap/Button';
import { UserContext } from '../../Util/CreateContext';


function LoginAsAdminButton() {
  //Creates the navigation objectthat will handle page switching
  const navigate = useNavigate();
  const [userType, setUserType] = useState(0)

  const handleClick = () => {
    setUserType(1);
    navigate("/");
  }

  return (
    <UserContext.Provider value={userType}>
      <Button
        className='but'
        variant="primary"
        size="lg"
        // Switches pages to the designated route
        onClick={handleClick}
      >
        Login as an Admin
      </Button>
    </UserContext.Provider>
  );
}

export default LoginAsAdminButton