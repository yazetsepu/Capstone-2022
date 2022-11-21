import Card from 'react-bootstrap/Card';


function SingleCard(props) {
  return (
      <Card>{}
        <Card.Img variant="top" src={props.src}/>
        <Card.Body>
          <Card.Title>Camera Number: {props.camNum}</Card.Title>
          <Card.Text>
            Classified as: {props.classif_id === 0? "Open" :
                            props.classif_id === 1? "Closed" :
                            "Not Available"} with {props.classif_acc * 100}% accuracy.
          </Card.Text>
        </Card.Body>
        <Card.Footer>
            Day Captured: {props.time.split('T').join(' || Time Captured: ')}
        </Card.Footer>
      </Card>
  );
}

export default SingleCard;