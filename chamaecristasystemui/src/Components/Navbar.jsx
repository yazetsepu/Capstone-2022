import Container from 'react-bootstrap/Container';
import Navbar from 'react-bootstrap/Navbar';
import '../styles/Navbar.css'

function DarkNavbar() {
    return (
        <Navbar bg="dark" variant="dark">
            <div className='nav-container'>
            <Container>
                <Navbar.Brand href="/">Home</Navbar.Brand>
                <Navbar.Toggle />
                <Navbar.Collapse className="justify-content-end">
                    <Navbar.Text>
                    Signed in as: <a href="#login">Admin</a>
                    </Navbar.Text>
                </Navbar.Collapse>
            </Container>
            </div>
        </Navbar>
    );
}

export default DarkNavbar;