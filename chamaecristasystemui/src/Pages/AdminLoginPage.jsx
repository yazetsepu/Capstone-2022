import React, { Component } from 'react';
import Button from '../Components/Buttons/Button';
import ContinueAsGuestButton from '../Components/Buttons/ContinueAsGuestButton';
import LoginAsAdminButton from '../Components/Buttons/LoginAsAdminButton';
import '../styles/AdminLoginPage.css';

class AdminLoginPage extends Component {
    
    render() {
        return (
            <div className='login-center'>
                <img
                    src={require('../resources/Capstoneers.png')}
                    alt="Capstoneers logo"
                    width="400"
                    height="400"
                />
                <div className='login-button-center'>
                    <div className='top-btn'>
                        <ContinueAsGuestButton/>
                    </div>
                    <LoginAsAdminButton/>
                </div>
            </div>
        );
    }
}
export default AdminLoginPage