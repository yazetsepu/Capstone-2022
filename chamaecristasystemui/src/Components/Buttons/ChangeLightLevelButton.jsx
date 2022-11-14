import React, { useEffect, useState } from 'react';
import Button from 'react-bootstrap/Button';

function simulateNetworkRequest() {
  return new Promise((resolve) => setTimeout(resolve, 2000));
}

function ChangeLightLevelButton(props) {
  const [isLoading, setLoading] = useState(false);
  const bText = props.text;

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
      {isLoading ? 'Loading…' : 'Change Light Level'}
    </Button>
  );
}

export default ChangeLightLevelButton