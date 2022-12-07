import '../styles/FilterSearch.css';
import Button from 'react-bootstrap/Button';
import Form from 'react-bootstrap/Form';
import InputGroup from 'react-bootstrap/InputGroup';

function FilterSearch() {
  return (
    <Form className='filter'>
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
    </Form>
  );
}

export default FilterSearch;