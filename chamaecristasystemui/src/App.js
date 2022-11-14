import React, { Component } from 'react';
import './styles/App.css';
import BasicTable from "./Components/DataTable"
import DarkNavbar from "./Components/Navbar"
import FilterSearch from './Components/FilterSearch';
// Buttons
import ViewCapturesButton from './Components/Buttons/ViewCapturesButton';
import RetrainModelButton from './Components/Buttons/RetrainModelButton';
import WaterPlantButton from './Components/Buttons/WaterPlantButton';
import ChangeLightLevelButton from './Components/Buttons/ChangeLightLevelButton';
import ExportAsCsvButton from './Components/Buttons/ExportAsCsvButton';
import ViewAsGraphButton from './Components/Buttons/ViewAsGraphButton';

export default class App extends Component {
    static displayName = App.name;

    componentDidMount(){
        document.body.style.backgroundColor = "#D9D9D9"
    }

    render() {
        return (
            <div>
                <DarkNavbar />
                <h1 id="tabelLabel" >Chamaecrista Sustainability System</h1>
                <div className='top-container'>
                    <FilterSearch />
                    <div className='top-container-btns'>
                        <ViewCapturesButton/>
                        <RetrainModelButton/>
                    </div>
                </div>
                <div className='middle-container'>
                    <BasicTable />
                </div>
                <div className='bottom-container'>
                    <div className='bottom-container-left'>
                        <div className='bottom-container-water'>
                            <WaterPlantButton/>
                        </div>
                        <div className='bottom-container-light'>
                            <ChangeLightLevelButton/>
                        </div>
                    </div>
                    <div className='bottom-container-right'>
                        <div className='bottom-container-export'>
                            <ExportAsCsvButton/>
                        </div>
                        <div className='bottom-container-graph'>
                            <ViewAsGraphButton/>
                        </div>
                    </div>
                </div>
            </div>
        );
    }
}
