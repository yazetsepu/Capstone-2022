import React, { useState } from 'react';
import Button from 'react-bootstrap/Button';
import Form from 'react-bootstrap/Form';
import '../styles/FilterSearch.css'
import { AdapterDayjs } from '@mui/x-date-pickers/AdapterDayjs';
import TextField from '@mui/material/TextField';
import { LocalizationProvider } from '@mui/x-date-pickers/LocalizationProvider';
import { MobileDatePicker } from '@mui/x-date-pickers/MobileDatePicker';

function FilterSearch(props) {

    const [startValue, setStartValue] = useState([null, null]);
    const [endValue, setEndValue] = useState([null, null]);

    const fetchFilteredData = async (dateRange) => {
      const response = await fetch("https://cssrumapi.azurewebsites.net/EnvironmentalData/Filter?" + dateRange);
      console.log("https://cssrumapi.azurewebsites.net/EnvironmentalData/Filter?" + dateRange)
      const data = await response.json();
      return data;
    }

    return(
      <div className='filter-date'>
        <Form.Group md="4" controlId="validationTime">
          <LocalizationProvider
            dateAdapter={AdapterDayjs}
            localeText={{ start: 'Mobile start', end: 'Mobile end' }}
          >
            <div className='date-pickers'>
              <div className='start-date'>
                <h4>Start Date:</h4>
                <MobileDatePicker
                  value={startValue}
                  onChange={(newValue) => {
                    setStartValue(newValue);
                  }}
                  renderInput={(params) => <TextField {...params} />}
                />
              </div>
              <div className='end-date'>
                <h4>End Date:</h4>
                <MobileDatePicker
                  value={endValue}
                  onChange={(newValue) => {
                    setEndValue(newValue);
                  }}
                  renderInput={(params) => <TextField {...params} />}
                />
              </div>
            </div>
          </LocalizationProvider>
        </Form.Group>
        <div className='filter-btn'>
          <Button
                      variant="warning"
                      size='lg'
                      onClick={async () => {
                        
                        await props.setFilteredData(await fetchFilteredData("start=" + (startValue.$M+1) + "%2F" + (startValue.$D <= 9? "0" + startValue.$D : startValue.$D) + "%2F" + startValue.$y + 
                                                                            "&end=" + (endValue.$M+1) + "%2F" + (endValue.$D <= 9? "0" + endValue.$D : endValue.$D) + "%2F" + endValue.$y))
                        await props.setWasPressed(true)
                        await props.setReset(true)
                      }}
                  >
                      Filter Table
            </Button>
        </div>
      </div>
    )
}
export default FilterSearch