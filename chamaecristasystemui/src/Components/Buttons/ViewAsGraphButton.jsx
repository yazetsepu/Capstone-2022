import React, { useEffect, useState } from 'react';
import { useNavigate } from "react-router-dom";
import Button from 'react-bootstrap/Button';

function simulateNetworkRequest() {
  this.props.history.push("/c");
}

function ViewAsGraphButton(props) {
  //Creates the navigation objectthat will handle page switching
  const navigate = useNavigate();
  const [isLoading, setLoading] = useState(false);
  
  useEffect(() => {
    if (isLoading) {
      simulateNetworkRequest().then(() => {
        setLoading(false);
      });
    }
  }, [isLoading]);

  const handleClick = () => setLoading(true);

  return (
    <Button
      variant="primary"
      size="lg"
      disabled={isLoading}
      // Switches pages to the designated route
      onClick={() => navigate("/graph")}
    >
      {isLoading ? 'Loading…' : 'View as Graph'}
    </Button>
  );
}

export default ViewAsGraphButton