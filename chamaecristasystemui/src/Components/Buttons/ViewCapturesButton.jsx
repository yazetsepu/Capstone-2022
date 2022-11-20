import React, { useEffect, useState } from 'react';
import { useNavigate } from "react-router-dom";
import Button from 'react-bootstrap/Button';

function simulateNetworkRequest() {
  this.props.history.push("/c");
}

function ViewCapturesButton() {
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
      className='but'
      variant="primary"
      size="lg"
      disabled={isLoading}
      onClick={() => navigate("/c")}
    >
      {isLoading ? 'Loading…' : 'View Captures'}
    </Button>
  );
}

export default ViewCapturesButton