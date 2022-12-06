import React, { useState } from 'react';
import Card from 'react-bootstrap/Card';
import Button from 'react-bootstrap/Button';


async function changeClassification(pid, camNum, classfId) {
  let correctClassfId = classfId === 0? 1 : 0 
  // Contains the necessary headers and body information that make up a POST request
  const requestOptions = {
    method: 'PUT',
    headers: { 'Content-Type': 'application/json' },
    // A -1 in classification accuracy indicates that the value was manually changed
    body: camNum === "1" ? JSON.stringify({ classification_Id_1 : correctClassfId, classification_Accurracy_1: -1}) : 
          camNum === "2" ? JSON.stringify({ classification_Id_2 : correctClassfId, classification_Accurracy_2: -1}) :
          camNum === "3" ? JSON.stringify({ classification_Id_3 : correctClassfId, classification_Accurracy_3: -1}) :
          JSON.stringify({ classification_Id_4 : correctClassfId, classification_Accurracy_4: -1})
  };
  console.log(requestOptions)
  console.log(pid)
  const response = await fetch('https://cssrumapi.azurewebsites.net/Pictures/' + pid, requestOptions)
  const data = await response.json();
  return new Promise((resolve) => {});
}

/**
 * @param `src` denotes the image source URL and is responsible for showing the actual picture
 * 
 * @param `camNum` denotes the number of the camera that took the picture from 1 to 4
 * 
 * @param `id` denotes the id of the picture it is currently displaying so the user may refer to it anywhere else.
 * 
 * @param `classif_id` denotes the classification_id found in the Pictures table and originating from the Machine Learning Algorithm: 0 for Open, 1 for Closed, and Not Available for everything else
 * 
 * @param `classif_acc` denotes the accuracy or certanty the model returns for the classification_id mentioned above
 * 
 * @param `time` denotes the time in which the picture was taken in Unix Time transformed to UTC -4:00
 */
function SingleCard(props) {

const [classifId, setClassifId] = useState(0)
const [classifAcc, setClassifAcc] = useState(0)
const [wasClicked, setWasClicked] = useState(false)

const handleClick = () => {
  setClassifId(props.classif_id === 0? 1 : 0)
  setClassifAcc(-1)
  changeClassification(props.id, props.camNum, props.classif_id);
  setWasClicked(true);
}

  return (
      <Card>
        <Card.Img variant="top" src={props.src && props.src !== "string"? props.src : "https://cdn.shopify.com/s/files/1/0082/7339/5794/products/dahua-analog-dome-5-mp-2-8-to-12mm-lens-dh-hac-hdbw1500-rp-z-2712-s2-dh-hac-hdbw1500rp-z-2712-s2-29173595832402_1024x1024.jpg?v=1660641051"}/>
        <Card.Body>
          <Card.Title>Camera Number: {props.src && props.src !== "string"? props.camNum : props.camNum + " - No Image Available" }</Card.Title>
          <Card.Text>
            PictureId: <b>{props.id + " - Cam " + props.camNum}</b> - Classified as:&nbsp; 
            <b>
              {
              !wasClicked? (props.classif_id === 0? "Open" : props.classif_id === 1? "Closed" : "Not Available")
                :
                           (classifId === 0? "Open" : classifId === 1? "Closed" : "Not Available")
              }
            </b> 
            &nbsp;with&nbsp; 
            <b>
              {
              !wasClicked?(props.classif_acc >= 0 ? Math.round(((props.classif_acc * 100) + Number.EPSILON) * 100) / 100 + "% accuracy." : " Manually Changed.")
                :
                          (classifAcc === 0? "Open" : classifAcc === 1? "Closed" : "Manually Changed")
              }
            </b> 
          </Card.Text>
          {/* Renders the button */}
          { props.encKey !==0?
            <Button
                variant="danger"
                size="med"
                onClick={handleClick}
            >
              Change Classification
            </Button>
            :
            <></>
            }
            { props.encKey !==0?
            <Card.Text>
              <i>If you wish to change the classification again, please refresh and click once more.</i>
            </Card.Text>
            :
            <></>
            }
            
          
        </Card.Body>
        <Card.Footer>
          {/* Formats the timestamp string into a readable format for the user */}
            Day and Time Captured: {new Date(props.time.replace("-", "/").replace("-", "/").split('T').join(' ').split('.')[0] + " +0000").toLocaleString("en-US", {timeZone: 'America/Grenada'})}
        </Card.Footer>
      </Card>
  );
}

export default SingleCard;