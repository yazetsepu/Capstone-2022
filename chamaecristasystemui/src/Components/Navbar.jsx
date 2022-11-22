import Container from 'react-bootstrap/Container';
import Navbar from 'react-bootstrap/Navbar';
import '../styles/Navbar.css'

function DarkNavbar() {
    return (
        <div className='top-nav'>
            <Navbar bg="dark" variant="dark">
                <div className='nav-container'>
                <Container>
                    {/* Returns the user to teh Home Page and refreshes it */}
                    <Navbar.Brand href="/">Home</Navbar.Brand>
                    <Navbar.Toggle />
                    <Navbar.Collapse className="justify-content-end">
                        {/* Will return user to the login page once */}
                        <Navbar.Text>
                            Signed in as: <a href="#login">Admin</a>
                        </Navbar.Text>
                    </Navbar.Collapse>
                </Container>
                </div>
            </Navbar>
        </div>
    );
}

export default DarkNavbar;