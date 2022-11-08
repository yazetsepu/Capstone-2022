import React, { Component } from 'react';
import './styles/App.css';
import BasicTable from "./Components/DataTable"
import DarkNavbar from "./Components/Navbar"
import LoadingButton from "./Components/Button"
import ViewCapturesButton from './Components/ViewCapturesButton';
import FilterSearch from './Components/FilterSearch';

export default class App extends Component {
    static displayName = App.name;

    render() {
        return (
            <div>
                <DarkNavbar />
                <h1 id="tabelLabel" >Chamaecrista Sustainability System</h1>
                <div className='top-container'>
                    <FilterSearch />
                    <div className='top-container-btns'>
                        <ViewCapturesButton/>
                        <LoadingButton text="Retrain Model"/>
                    </div>
                </div>
                <div className='middle-container'>
                    <BasicTable />
                </div>
                <div>
                    <LoadingButton text="Water Plant"/>
                    <LoadingButton text="Change Light Level"/>
                    <LoadingButton text="Export as CSV"/>
                    <LoadingButton text="View as Graph"/>
                </div>
            </div>
        );
    }
}
