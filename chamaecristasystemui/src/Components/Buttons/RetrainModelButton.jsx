import React, { useState, useContext } from 'react';
import Button from 'react-bootstrap/Button';
import './button-styles/RetrainModelButton.css'
import RetrainModelModal from '../Modals/RetrainModelModal';
import { StateContext } from '../../App';

async function retrainModel(){

  // Contains the necessary headers and body information that make up a POST request
  const requestOptions = {
    method: 'POST',
    headers: { 'Content-Type': 'application/json' },
    body: JSON.stringify(
      {  
        command_String: "RetrainModel",
        command_Value: null,
        command_Read: null,
        command_Performed: null,
        logs: {
          logs_Text: null
        }
      }
    )
  };
  await fetch('https://cssrumapi.azurewebsites.net//Commands/', requestOptions)
  return new Promise((resolve) => {});
}

function RetrainModelButton() {
  //Dictates whether the button was recently pressed or if it can be pressed again
  const [isShowing, setShowing] = useState(false);
  const [isExecuting, setIsExecuting] = useState(false);
  //Sets the context for the app page and the view captures
  const { setIsRetrainExecuting } = useContext(StateContext);

  const fetchData = async () => {
    const response = await fetch('https://cssrumapi.azurewebsites.net/Commands/RetrainModel/Command_Performed/Verify')
    const data = await response.json()

    if(data.command_Read !== null){
      //Make something happen right here that extends the wait timer or makes indefinite.
      if(data.command_Performed !== null){
        console.log("Finished Executing")
        return true
      }
    }else{
      console.log("Failed to execute")
      return false
    }
  }
  //Executes a function every x seconds until it succeeds or until y seconds pass
  const untilAsync = async (fn, time = 1000, wait = 10000) => {
    const startTime = new Date().getTime();  
    for (;;) {                               
      try {
        if (await fn()) {  
          localStorage.setItem("EXC", "0");
          setIsExecuting(false) 
          setIsRetrainExecuting(false)                 
          return true;
        }
      } catch (e) {                          
        throw e;
      }
  
      if (new Date().getTime() - startTime > wait) {
        localStorage.setItem("EXC", "0");
        setIsExecuting(false)
        setIsRetrainExecuting(false)
        throw new Error('Max wait reached'); 
      } else {                              
        await new Promise((resolve) => setTimeout(resolve, time));
      }
    }
  };


  const handleClick = () => setShowing(true);
  const handleClose = () => {
    setShowing(false)
  }

  //Triggers when the internal modal submit button is pressed to execute the button
  const handleSubmit = async () => {
      console.log(localStorage.getItem("EXC"))
    
    retrainModel();
    setShowing(false)
    console.log("Submitted")
    setIsExecuting(true)
    setIsRetrainExecuting(true)
    localStorage.setItem("EXC", "1");
    await untilAsync(fetchData)
  }

  return (
    <div>
      <div className='retrain-btn'>
        <Button
          variant="primary"
          size="lg"
          disabled={isExecuting || localStorage.getItem("EXC") === 1}
          onClick={!isExecuting ? handleClick : null}
        >
          {isExecuting ? 'Executing…' : 'Retrain Model'}
        </Button>
      </div>
      {/* Pops up a notification to ask the user if  they're sure they want to retrain the model */}
      <RetrainModelModal isShowing={isShowing} handleClose={handleClose} handleSubmit={handleSubmit} />
    </div>
  );
}

export default RetrainModelButton