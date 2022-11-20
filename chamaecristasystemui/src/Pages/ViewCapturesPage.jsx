import React, { Component } from 'react';
import DarkNavbar from '../Components/Navbar';
import PictureCard from '../Components/PictureCard'

class ViewCapturesPage extends Component {
    
    render() {
        return (
            <div>
                <DarkNavbar />
                <h1>Camera Captures</h1>
                <PictureCard />
            </div>
        );
    }
}
export default ViewCapturesPage