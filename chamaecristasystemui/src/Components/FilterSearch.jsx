import Button from 'react-bootstrap/Button';
import Col from 'react-bootstrap/Col';
import Form from 'react-bootstrap/Form';
import Row from 'react-bootstrap/Row';
import InputGroup from 'react-bootstrap/InputGroup';

function GridComplexExample() {
  return (
    <Form>
      <Row className="mb-3">
        <Form.Group as={Col} controlId="formGridEmail">
            <InputGroup className="mb-3">
                <Form.Control
                    placeholder="Filter Text"
                    aria-label="Filter"
                    aria-describedby="basic-addon2"
                    />
                        <Button variant="warning" id="button-addon2" type="submit">
                            Filter
                        </Button>
            </InputGroup>
        </Form.Group>
      </Row>
    </Form>
  );
}

export default GridComplexExample;