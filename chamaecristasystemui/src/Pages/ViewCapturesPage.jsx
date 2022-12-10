import React, { useState, createContext }from 'react';
import DarkNavbar from '../Components/Navbar';
import PictureCard from '../Components/PictureCard'
import { useLocation } from "react-router-dom";

export const PictureContext = createContext();

function ViewCapturesPage() {
    
    const loc = useLocation();
    const encKey = loc.state.userKey;
    const [isRetraining] = useState(loc.state.retrain) 

    return (
        <PictureContext.Provider value={{ isRetraining, encKey }}>
            <div>
                <DarkNavbar />
                <h1>Camera Captures</h1>
                <PictureCard />
            </div>
        </PictureContext.Provider>
    );
}
export default ViewCapturesPage