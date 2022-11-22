import { render, screen } from '@testing-library/react';
import DataTable from '../DataTable'
import '@testing-library/jest-dom'

test('Should Render DataTable component', () => {
    render(<DataTable/>);
    const tableElement = screen.getByTestId('datatable-1');
    expect(tableElement).toBeInTheDocument();
    expect(tableElement).toHaveTextContent('#')
    expect(tableElement).toHaveTextContent('Timestamp')
    expect(tableElement).toHaveTextContent('Leaf Status')
    expect(tableElement).toHaveTextContent('Resv Water Level')
    expect(tableElement).toHaveTextContent('Water Level')
    expect(tableElement).toHaveTextContent('Temperature (C)')
    expect(tableElement).toHaveTextContent('Soil Moisture (%)')
    expect(tableElement).toHaveTextContent('Air Humidity (%)')
    expect(tableElement).toHaveTextContent('Light Level (lux)')
    expect(tableElement).toHaveTextContent('1')
    expect(tableElement).toHaveTextContent('Current Page:')
})