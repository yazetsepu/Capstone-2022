import React, { Component } from 'react';

export default class App extends Component {
    static displayName = App.name;

    constructor(props) {
        super(props);
        this.state = { forecasts: [], loading: true };
    }

    render() {
        return (
            <div>
                <div className="navigation">
                <nav className="navbar navbar-default">
                    <div className="container-fluid">
                        <div className="navbar-header">
                            <a className="navbar-brand" href="#">WebSiteName</a>
                        </div>
                    </div>
                </nav>
                <h1 id="tabelLabel" >Chamaecrista Sustainability System</h1>
                    <p>This component demonstrates fetching data from the server.</p>
                </div>
            </div>
        );
    }
}
