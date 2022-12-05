import Container from 'react-bootstrap/Container';
import Navbar from 'react-bootstrap/Navbar';
import '../styles/Navbar.css'

function DarkNavbar() {
    return (
        <div className='top-nav'>
            <Navbar bg="dark" variant="dark">
                <div className='nav-container'>
                <Container>
                    {/* Returns the user to the Home Page and refreshes it */}
                    <Navbar.Brand href="/">
                        <div className='nav-text'>
                            <img
                                src={require('../resources/Capstoneers.png')}
                                width="50"
                                height="50"
                                className="d-inline-block align-top"
                                alt="React Bootstrap logo"
                            />{' '}
                            {/* &nbsp; is a space character in html that forces whitespace */}
                            <h1>&nbsp;Home</h1>
                        </div>
                    </Navbar.Brand>
                    <Navbar.Toggle />
                    <Navbar.Collapse className="justify-content-end">
                        {/* Will return user to the login page once */}
                        <Navbar.Text>
                            Signed in as: <a href="/login">Admin</a>
                        </Navbar.Text>
                    </Navbar.Collapse>
                </Container>
                </div>
            </Navbar>
        </div>
    );
}

export default DarkNavbar;