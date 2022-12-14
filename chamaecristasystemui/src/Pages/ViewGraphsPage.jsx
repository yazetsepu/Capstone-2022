import React, {  useState } from 'react';
import DarkNavbar from '../Components/Navbar';
import DataGraph from '../Components/DataGraph';
import Form from 'react-bootstrap/Form';
import '../styles/ViewGraphsPage.css';

function ViewGraphsPage() {

        const [graphValue, setGraphValue] = useState("Temperature");

        return (
            <div>
                <DarkNavbar />
                <div className="graph-selector">
                    <div>
                        {/* Dropdown selector for what the user wishes to graph */}
                        <Form.Select 
                            size="lg"
                            as="select"
                            value={graphValue}
                            onChange={e => {
                                setGraphValue(e.target.value);
                            }}>
                            <option value="temperature">Temperature</option>
                            <option value="leaf1">Leaf Status - Camara 1</option>
                            <option value="leaf2">Leaf Status - Camara 2</option>
                            <option value="leaf3">Leaf Status - Camara 3</option>
                            <option value="leaf4">Leaf Status - Camara 4</option>
                            <option value="humidity">Humidity</option>
                            <option value="water">Water Level</option>
                            <option value="light">Light Level</option>
                            <option value="soil1">Soil Moisture Sensor 1</option>
                            <option value="soil2">Soil Moisture Sensor 2</option>
                            <option value="soil3">Soil Moisture Sensor 3</option>
                            <option value="soil4">Soil Moisture Sensor 4</option>
                            <option value="soil5">Soil Moisture Sensor 5</option>
                            <option value="soil6">Soil Moisture Sensor 6</option>
                            <option value="soil7">Soil Moisture Sensor 7</option>
                            <option value="soil8">Soil Moisture Sensor 8</option>
                        </Form.Select>
                    </div>
                    <hr></hr>
                    {/* Renders the Graph of what the user picks on the selector */}
                        <DataGraph yVal={graphValue}/>
                </div>
            </div>
        );
}
export default ViewGraphsPage