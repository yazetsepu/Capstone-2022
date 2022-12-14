import React, { useEffect, useState, createContext, useContext } from 'react';
import './styles/App.css';
import BasicTable from "./Components/DataTable"
import DarkNavbar from "./Components/Navbar"
// Buttons
import ViewCapturesButton from './Components/Buttons/ViewCapturesButton';
import RetrainModelButton from './Components/Buttons/RetrainModelButton';
import WaterPlantButton from './Components/Buttons/WaterPlantButton';
import ExportAsCsvButton from './Components/Buttons/ExportAsCsvButton';
import ViewAsGraphButton from './Components/Buttons/ViewAsGraphButton';
import CalibrateMoistureButton from './Components/Buttons/CalibrateMoistureButton';
import ChangeDataCaptureRateButton from './Components/Buttons/ChangeDataCaptureRateButton';
import { useLocation } from "react-router-dom";
import {AES, enc} from 'crypto-js';

export const StateContext = createContext();

function App (){
    
    const loc = useLocation();
    let key = 0; 
    try {
        key = loc.state.userKey;
    } 
    catch (err) {
        key = 0
    }
    const [decryptedString, setDecryptedString] = useState(0)
    const [isRetrainExecuting, setIsRetrainExecuting] = useState(false)

    
    useEffect(() => {

        if(key !==0){
            const decrypted = AES.decrypt(sessionStorage.getItem('EUT'), key);
            setDecryptedString(decrypted.toString(enc.Utf8));
        }
    })

        return (
            <StateContext.Provider value={{ isRetrainExecuting, setIsRetrainExecuting, key }}>
                <div>
                    <DarkNavbar />
                    <div className='top-container-btns'>
                        <h1 id="tabelLabel" >Chamaecrista Sustainability System</h1>
                        <div className={decryptedString === 'Admin'? 'top-container-btns-admin': 'top-container-btns-guest'}>
                            <ViewCapturesButton />
                            {decryptedString === 'Admin'?
                                <RetrainModelButton/>
                                :
                                <></>
                            }
                        </div>
                    </div>
                    <div className='middle-container'>
                        <BasicTable />
                    </div>
                    <div className='bottom-container'>
                    {decryptedString === 'Admin'?
                        <div className='bottom-container-left'>
                            <div className='bottom-container-water'>
                                <WaterPlantButton/>
                            </div>
                            <div className='bottom-container-datacapture'>
                                <ChangeDataCaptureRateButton/>
                            </div>
                            <div className='bottom-container-moisture'>
                                <CalibrateMoistureButton />
                            </div>
                        </div>
                        : <></>
                    }
                        <div className='bottom-container-right'>
                            <div className='bottom-container-export'>
                                <ExportAsCsvButton/>
                            </div>
                            <div className='bottom-container-graph'>
                                <ViewAsGraphButton />
                            </div>
                        </div>
                    </div>
                </div>
            </StateContext.Provider>
        );
}
export default App