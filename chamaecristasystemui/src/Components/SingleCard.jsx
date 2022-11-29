import Card from 'react-bootstrap/Card';

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
 * @param `time` denotes the time in which the picture was taken in Unix Time
 */

function SingleCard(props) {
  return (
      <Card>
        <Card.Img variant="top" src={props.src? props.src : "https://cdn.shopify.com/s/files/1/0082/7339/5794/products/dahua-analog-dome-5-mp-2-8-to-12mm-lens-dh-hac-hdbw1500-rp-z-2712-s2-dh-hac-hdbw1500rp-z-2712-s2-29173595832402_1024x1024.jpg?v=1660641051"}/>
        <Card.Body>
          <Card.Title>Camera Number: {props.src? props.camNum : props.camNum + " - No Image Available" }</Card.Title>
          <Card.Text>
            PictureId: {props.id} - Classified as: {props.classif_id === 0? "Open" :
                            props.classif_id === 1? "Closed" :
                            "Not Available"} with {Math.round(((props.classif_acc * 100) + Number.EPSILON) * 100) / 100}% accuracy.
          </Card.Text>
        </Card.Body>
        <Card.Footer>
          {/* Formats the timestamp string into a readable format for the user */}
            Day Captured: {props.time.split('T').join(' || Time Captured: ')}
        </Card.Footer>
      </Card>
  );
}

export default SingleCard;