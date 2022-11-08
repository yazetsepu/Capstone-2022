import '../styles/DataTable.css';
import Table from 'react-bootstrap/Table';
import { envData } from '../Util/dummyData'

function BasicTable() {
    return (
        <Table striped bordered hover className='table'>
            <thead>
                <tr>
                    <th>#</th>
                    <th>Timestamp</th>
                    <th>Leaf Status</th>
                    <th>Temperature (C)</th>
                    <th>Soil Moisture (%)</th>
                    <th>Air Humidity (%)</th>
                </tr>
            </thead>
            <tbody>
                {envData.map((data, key) => (
                <tr key = {key}>
                    <td>{data.id}</td>
                    <td>{data.timestamp}</td>
                    <td>{data.leafstatus}</td>
                    <td>{data.temperature}</td>
                    <td>{data.soilmoisture}</td>
                    <td>{data.airhumidity}</td>
                </tr>
                ))}
            </tbody>
        </Table>
    );
}

export default BasicTable;