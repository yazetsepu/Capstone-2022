import React, { useEffect, useState } from 'react';
import Button from 'react-bootstrap/Button';

function simulateNetworkRequest() {
  return new Promise(
    // API Calls 
  );
}

function ExportAsCsvButton(props) {
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
      onClick={!isLoading ? handleClick : null}
    >
      {isLoading ? 'Loading…' : 'Export as CSV'}
    </Button>
  );
}

export default ExportAsCsvButton