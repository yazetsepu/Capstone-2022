import React from 'react';
import DarkNavbar from '../Components/Navbar';
import PictureCard from '../Components/PictureCard'
import { useLocation } from "react-router-dom";


function ViewCapturesPage() {
    
    const loc = useLocation();
    let encKey = loc.state.userKey; 

    return (
        <div>
            <DarkNavbar />
            <h1>Camera Captures</h1>
            <PictureCard encKey={encKey}/>
        </div>
    );
}
export default ViewCapturesPage