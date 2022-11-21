import React, { useEffect, useState } from 'react';
import Button from 'react-bootstrap/Button';

function ExportAsCsvButton(props) {
  const [isLoading, setLoading] = useState(false);
  const [envData, setEnvData] = useState([])

  const fetchData = async () => {
    const response = await fetch("https://cssrumapi.azurewebsites.net/EnvironmentalDataAll")
    const data = await response.json()
    setEnvData(data)
    return new Promise((resolve) => setTimeout(resolve, 2000));
  }

  const downloadFile = ({data, fileName, fileType}) => {
    setLoading(true)
    const blob = new Blob([data], { type: fileType })
    const a = document.createElement('a')
    a.download = fileName
    a.href = window.URL.createObjectURL(blob)
    const clickEvt = new MouseEvent('click', {
      view: window,
      bubbles: true,
      cancelable: true,
    })
    a.dispatchEvent(clickEvt)
    a.remove()
  }

  useEffect(() => {
    if (isLoading) {
      fetchData().then(() => {
        setLoading(false);

      });
    }
  }, [isLoading]);

  const handleClick = e =>{
    e.preventDefault()

    // Headers for each column
    let headers = ['Entry Id,Timestamp,Temperature,Humidity,Light,Resevoir Water Level,Water Level,Soil Moisture S1,Soil Moisture S2,Soil Moisture S3,Soil Moisture S4,Soil Moisture S5,Soil Moisture S6,Soil Moisture S7,Soil Moisture S8']

    //Convert data to csv
    let envCsv = envData.reduce((data, key) => {
      const { entry_Id,times_tamps,temperature,humidity,light,resevoir_water_level,water_level,soil_moisture,soil_moisture_2,soil_moisture_3,soil_moisture_4,soil_moisture_5,soil_moisture_6,soil_moisture_7,soil_moisture_8 } = key
      data.push([entry_Id,times_tamps,temperature,humidity,light,resevoir_water_level,water_level,soil_moisture,soil_moisture_2,soil_moisture_3,soil_moisture_4,soil_moisture_5,soil_moisture_6,soil_moisture_7,soil_moisture_8].join(','))
      return data
    }, [])

    //Perform Download
    downloadFile({
      data: [...headers, ...envCsv].join('\n'),
      fileName: 'EnvironmentalData.csv',
      fileType: 'text/csv',
    })
  }
     

  return (
    <Button
      variant="primary"
      size="lg"
      disabled={isLoading}
      onClick={!isLoading ? handleClick : null}
    >
      {isLoading ? 'Loading…' : 'Export as CSV'}
    </Button>
  );
}

export default ExportAsCsvButton