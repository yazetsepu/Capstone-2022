import React, { Component } from 'react';
import { useState, useEffect } from 'react';
import {Chart, ArcElement, CategoryScale, animator} from 'chart.js/auto'
import { Line } from "react-chartjs-2";

Chart.register(ArcElement);
Chart.register(CategoryScale);

function DataGraph (props) {

    const [envData, setEnvData] = useState([]);

    const fetchData = async (filter) => {
        const response = await fetch("https://cssrumapi.azurewebsites.net/EnvironmentalDataAll")
        const Data = await response.json()
        setEnvData(Data)
    }
        
    useEffect(() => {
        fetchData()
        }, [])

        return(
            <div>
            <h2 style={{ textAlign: "center" }}>{
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
            <Line
                data={
                    {
                        labels: envData.map((data) => data.entry_Id),
                        datasets: [
                            {
                                label: "Amount per Data Entry",
                                data: envData.map((data) => 
                                    props.yVal === "temperature"? data.temperature :
                                    props.yVal === "humidity"? data.humidity :
                                    props.yVal === "leaf"? data.classification_id :
                                    props.yVal === "resevoir"? data.resevoir_water_level :
                                    props.yVal === "water"? data.water_level : 
                                    props.yVal === "light"? data.light :
                                    props.yVal === "soil1"? data.soil_moisture :
                                    props.yVal === "soil2"? data.soil_moisture_2 :
                                    props.yVal === "soil3"? data.soil_moisture_3 :
                                    props.yVal === "soil4"? data.soil_moisture_4 :
                                    props.yVal === "soil5"? data.soil_moisture_5 :
                                    props.yVal === "soil6"? data.soil_moisture_6 :
                                    props.yVal === "soil7"? data.soil_moisture_7 :
                                    data.soil_moisture_8
                                ),
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
export default DataGraph

