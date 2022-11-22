import React, { Component } from 'react';
import { useState, useEffect } from 'react';
//chart.js imports to render different graph types
import {Chart, ArcElement, CategoryScale} from 'chart.js/auto'
import { Line } from "react-chartjs-2";

//Chart.js necessary setup for library use
Chart.register(ArcElement);
Chart.register(CategoryScale);

//"props" is the standard way to denote a value that is pased down by a parent component
function DataGraph (props) {

    /*
    * @params yVal = The Environmental Data value that will be rendered as the Y axis in the 
    * graph with entryId as the X axis. It's parent is the ViewGraphsPage
    * */

    //Stores the complete data set fetched from the API in ascending order
    const [envData, setEnvData] = useState([]);

    //Performs a GET Request that will return the data present in the EnvironmentalData table in the DB
    const fetchData = async (filter) => {
        const response = await fetch("https://cssrumapi.azurewebsites.net/EnvironmentalDataAll")
        const Data = await response.json()
        setEnvData(Data)
    }
        
    //useEffects is a React hook that triggers everytime the page is rendered (loads)
    useEffect(() => {
        fetchData()
        }, [])

        return(
            <div>
            {/* Sets the Title of the page to that of the corresponding data that is being graphed. */}
            <h2 style={{ textAlign: "center" }}>{
                // yVal is a prop or property variable that is handed over from a parent component
                props.yVal === "temperature"? "Temperature" :
                props.yVal === "humidity"? "Humidity" :
                props.yVal === "leaf"? "Leaf Status - 0 for Open : 1 for Closed" :
                props.yVal === "resevoir"? "Resevoir Water Level" :
                props.yVal === "water"? "Water Level" : 
                props.yVal === "light"? "Light Level" :
                props.yVal === "soil1"? "Soil Moisture Sensor 1" :
                props.yVal === "soil2"? "Soil Moisture Sensor 2" :
                props.yVal === "soil3"? "Soil Moisture Sensor 3" :
                props.yVal === "soil4"? "Soil Moisture Sensor 4" :
                props.yVal === "soil5"? "Soil Moisture Sensor 5" :
                props.yVal === "soil6"? "Soil Moisture Sensor 6" :
                props.yVal === "soil7"? "Soil Moisture Sensor 7" :
                "Soil Moisture Sensor 8"
            }
            </h2>
            {/* Line is a react component provided by the chart.js library for rendering line graphs */}
            <Line
                data={
                    {   
                        // Denotes our X (Independent Variable )
                        labels: envData.map((data) => data.entry_Id),
                        datasets: [
                            {
                                label: "Amount per Data Entry",
                                // Denotes our Y (Dependant Variable) according to the parent component
                                data: envData.map((data) => 
                                    props.yVal === "temperature"? data.temperature :
                                    props.yVal === "humidity"? data.humidity :
                                    props.yVal === "leaf"? data.classification_id :
                                    props.yVal === "resevoir"? data.resevoir_water_Level :
                                    props.yVal === "water"? data.water_Level : 
                                    props.yVal === "light"? data.light :
                                    props.yVal === "soil1"? data.soil_Moisture_1 :
                                    props.yVal === "soil2"? data.soil_Moisture_2 :
                                    props.yVal === "soil3"? data.soil_Moisture_3 :
                                    props.yVal === "soil4"? data.soil_Moisture_4 :
                                    props.yVal === "soil5"? data.soil_Moisture_5 :
                                    props.yVal === "soil6"? data.soil_Moisture_6 :
                                    props.yVal === "soil7"? data.soil_Moisture_7 :
                                    data.soil_moisture_8
                                ),
                                // Color for points on the graph
                                backgroundColor: [
                                    "rgba(75,192,192,1)",
                                    "#ecf0f1",
                                    "#50AF95",
                                    "#f3ba2f",
                                    "#2a71d0"
                                ],
                                borderColor: "black",
                                borderWidth: 2
                            }
                        ]
                    }
                }
                options={{
                    plugins: {
                        title: {
                        display: true,
                        text: "Amount per Data Entry"
                        },
                        legend: {
                        display: false
                        }
                    }
                }}
                />
            </div>
        )
}
// Exprts the component with the same name stated below so that it may be imported by other components
export default DataGraph

