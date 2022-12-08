import React, { useState } from 'react';
import { useNavigate } from "react-router-dom";
import Button from 'react-bootstrap/Button';
import {AES} from 'crypto-js';
import { GenerateKey } from '../../Util/GenerateKey';
import LoginModal from '../Modals/LoginModal';



function LoginAsAdminButton() {
  //Creates the navigation objectthat will handle page switching
  const navigate = useNavigate();
  const [isShowing, setShowing] = useState(false)
  const [enteredPass, setEnteredPass] = useState(null)
  const [isInvalid, setIsInvalid] = useState(false)

  const [isLogging, setIsLogging] = useState(false)

  const fetchData = async () => {
    let key="DD2CCB091346B250C927F3FD5BB1AD1872078CFE8F572A7324DA2A0981FE2E6B&"
    const response = await fetch("https://cssrumapi.azurewebsites.net/Admins/Auth?pk="+key+"password="+enteredPass)
    return response.status === 200? true : window.location.reload();
    
  }

  //handles the encryption using a randomly generated 64 bit key and AES 256 bit standard encryption algorithm
  const handleClick = async () => {
    let result = await fetchData()

    if(result){
      const key = GenerateKey()
      const envryptedString = AES.encrypt('Admin',key);
      sessionStorage.setItem('EUT', envryptedString);

      navigate('/home',
      {
        state: {
          userKey: key,
        }
      });
    }
    else{
      setIsInvalid(true);
    }
  };

  return (
    <div>
      <Button
        className='but'
        variant="primary"
        size="lg"
        // Switches pages to the designated route
        onClick={() => {setShowing(true)}}
      >
        Login as an Admin
      </Button>

      <LoginModal isShowing={isShowing} setShowing={setShowing} 
                  enteredPass={enteredPass} setEnteredPass={setEnteredPass}
                  handleClick={handleClick} isInvalid={isInvalid} isLogging={isLogging}/>
    </div>
  );
}

export default LoginAsAdminButton