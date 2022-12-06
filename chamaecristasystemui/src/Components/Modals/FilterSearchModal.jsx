import React, { useState } from 'react';
import Button from 'react-bootstrap/Button';
import Modal from 'react-bootstrap/Modal';
import Form from 'react-bootstrap/Form';
import './modal-styles/FilterSearchModal.css'
import InputGroup from 'react-bootstrap/InputGroup';
// date-fns
import { AdapterDateFns } from '@mui/x-date-pickers/AdapterDateFns';
// or for Day.js
import { AdapterDayjs } from '@mui/x-date-pickers/AdapterDayjs';
// or for Luxon
import { AdapterLuxon } from '@mui/x-date-pickers/AdapterLuxon';
// or for Moment.js
import { AdapterMoment } from '@mui/x-date-pickers/AdapterMoment';
import Box from '@mui/material/Box';
import dayjs from 'dayjs';
import TextField from '@mui/material/TextField';
import { LocalizationProvider } from '@mui/x-date-pickers/LocalizationProvider';
import { DateTimePicker } from '@mui/x-date-pickers/DateTimePicker';
import { MobileDateRangePicker } from '@mui/x-date-pickers-pro/MobileDateRangePicker';
import { DesktopDateTimePicker } from '@mui/x-date-pickers/DesktopDateTimePicker';

function FilterSearchMoal(props) {

    const handleClose = () => props.setShowing(false);
    const [startValue, setStartValue] = React.useState(dayjs('2018-01-01T00:00:00.000Z'));
    const [endValue, setEndValue] = React.useState(dayjs('2018-01-01T00:00:00.000Z'));
    const [value, setValue] = React.useState([null, null]);


    return(
        <Modal show={props.isShowing} onHide={handleClose}>
        <Modal.Header closeButton>
          <Modal.Title>Filter Environmental Data Content</Modal.Title>
        </Modal.Header>
        <Modal.Body>
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
        </Modal.Body>
        <Modal.Footer>
          <Button variant="secondary" onClick={handleClose}>
            Close
          </Button>
          <Button variant="primary" onClick={() => {
                console.log(value)
            }}>
            Save Changes
          </Button>
        </Modal.Footer>
      </Modal>
    )
}
export default FilterSearchMoal