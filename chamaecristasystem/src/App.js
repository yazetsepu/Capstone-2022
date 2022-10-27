import React, { Component } from 'react';
import BasicTable from "./Components/DataTable"

export default class App extends Component {
    static displayName = App.name;

    constructor(props) {
        super(props);
        this.state = { forecasts: [], loading: true };
    }

    render() {
        return (
            <div>
                <h1 id="tabelLabel" >Chamaecrista Sustainability System</h1>
                <p>This component demonstrates fetching data from the server.</p>
                <BasicTable />
            </div>
        );
    }
}
