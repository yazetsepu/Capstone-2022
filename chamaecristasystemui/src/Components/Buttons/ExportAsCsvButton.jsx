import React from 'react';
import Button from 'react-bootstrap/Button';

function ExportAsCsvButton() {

  //Performs the GET request
  const fetchData = async () => {
    const response = await fetch('https://cssrumapi.azurewebsites.net/EnvironmentalDataAll')
    const data = await response.json()
    return data;
  }

  //Sets the background code and necessary event triggers for a download
  const downloadFile = ({data, fileName, fileType}) => {
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

  //Handles the conversion of data to csv with the appropriate headers and their mappings
  const handleClick = async e =>{
    let envData = await fetchData()
    console.log(envData)

    // Headers for each column
    let headers = ['Entry Id,Timestamp (UTC),Temperature,Humidity,Light,Resevoir Water Level,Water Level,Soil Moisture S1,Soil Moisture S2,Soil Moisture S3,Soil Moisture S4,Soil Moisture S5,Soil Moisture S6,Soil Moisture S7,Soil Moisture S8']

    //Convert data to csv
    let envCsv = envData.reduce((data, key) => {
      const { entry_Id,timestamps,temperature,humidity,light,reservoir_Water_Level,water_Level,soil_Moisture_1,soil_Moisture_2,
              soil_Moisture_3,soil_Moisture_4,soil_Moisture_5,soil_Moisture_6,soil_Moisture_7,soil_Moisture_8 } = key
      data.push([entry_Id,(timestamps.replace("-", "/").replace("-", "/").split('T').join(' ').split('.')[0] + " +0000").toLocaleString("en-US", {timeZone: 'America/Grenada'}),temperature,humidity,light,reservoir_Water_Level,water_Level,soil_Moisture_1,soil_Moisture_2,
                soil_Moisture_3,soil_Moisture_4,soil_Moisture_5,soil_Moisture_6,soil_Moisture_7,soil_Moisture_8].join(','))
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
      onClick={handleClick}
    >
      Export as CSV
    </Button>
  );
}

export default ExportAsCsvButton