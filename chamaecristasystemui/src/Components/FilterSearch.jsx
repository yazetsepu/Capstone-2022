import React, { useState } from 'react';
import Button from 'react-bootstrap/Button';
import Form from 'react-bootstrap/Form';
import '../styles/FilterSearch.css'
import { AdapterDayjs } from '@mui/x-date-pickers/AdapterDayjs';
import Box from '@mui/material/Box';
import TextField from '@mui/material/TextField';
import { LocalizationProvider } from '@mui/x-date-pickers/LocalizationProvider';
import { MobileDateRangePicker } from '@mui/x-date-pickers-pro/MobileDateRangePicker';

function FilterSearch(props) {

    const handleClose = () => props.setShowing(false);
    const [value, setValue] = React.useState([null, null]);

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
            <MobileDateRangePicker
              value={value}
              onChange={(newValue) => {
                setValue(newValue);
              }}
              renderInput={(startProps, endProps) => (
                <React.Fragment>
                  <TextField {...startProps} />
                  <Box sx={{ mx: 2 }}> to </Box>
                  <TextField {...endProps} />
                </React.Fragment>
              )}
            />
          </LocalizationProvider>
        </Form.Group>
        <div className='filter-btn'>
          <Button
                      variant="warning"
                      size='lg'
                      onClick={async () => {
                        await props.setFilteredData(await fetchFilteredData("start=" + (value[0].$M+1) + "%2F" + (value[0].$D <= 9? "0" + value[0].$D : value[0].$D) + "%2F" + value[0].$y + 
                                                                            "&end=" + (value[1].$M+1) + "%2F" + (value[1].$D <= 9? "0" + value[1].$D : value[1].$D) + "%2F" + value[1].$y))
                        await props.setWasPressed(true)
                        await props.setReset(true)
                        handleClose()
                      }}
                  >
                      Filter Table
            </Button>
        </div>
      </div>
    )
}
export default FilterSearch