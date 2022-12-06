import Container from 'react-bootstrap/Container';
import Navbar from 'react-bootstrap/Navbar';
import Button from 'react-bootstrap/Button';
import { useNavigate } from "react-router-dom";
import { useLocation } from "react-router-dom";
import '../styles/Navbar.css'

function DarkNavbar() {
    const loc = useLocation();
    let key = 0; 
    try {
        key = loc.state.userKey;
    } 
    catch (err) {
        key = 0
    }
    const navigate = useNavigate();

    const handleClick = () => {
        navigate('/home',
      {
        state: {
          userKey: key,
        }
      })
    }
    
    return (
        <div className='top-nav'>
            <Navbar bg="dark" variant="dark" className='top-nav'>
                <div className=''>
                <Container>
                    {/* Returns the user to the Home Page and refreshes it */}
                    <Navbar.Brand>
                        <div className='nav-container'>
                            <Button variant="dark" onClick={handleClick}>
                                <img
                                    src={require('../resources/Capstoneers.png')}
                                    width="50"
                                    height="50"
                                    alt="React Bootstrap logo"
                                />
                            </Button>
                            {/* &nbsp; is a space character in html that forces whitespace */}
                            <div className='nav-text'>
                                <Button 
                                    variant="dark" 
                                    size='sm'
                                    onClick={handleClick}
                                >
                                    <h1>&nbsp;Home</h1>
                                </Button>
                                Signed in as:&nbsp; <a href="/">{key !== 0? 'Admin' : 'Guest'}</a>
                            </div>
                        </div>
                    </Navbar.Brand>
                    <Navbar.Toggle />
                </Container>
                </div>
            </Navbar>
        </div>
    );
}

export default DarkNavbar;