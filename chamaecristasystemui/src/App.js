import React, { Component } from 'react';
import BasicTable from "./Components/DataTable"
import DarkNavbar from "./Components/Navbar"
import LoadingButton from "./Components/Button"
import GridComplexExample from './Components/FilterSearch';

export default class App extends Component {
    static displayName = App.name;

    render() {
        return (
            <div>
                <DarkNavbar />
                <h1 id="tabelLabel" >Chamaecrista Sustainability System</h1>
                <p>This component demonstrates fetching data from the server.</p>
                <div>
                    <GridComplexExample />
                    <LoadingButton text="View Captures"/>
                    <LoadingButton text="Retrain Model"/>
                </div>
                <BasicTable />
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
