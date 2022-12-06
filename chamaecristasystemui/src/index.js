import React from 'react';
import ReactDOM from 'react-dom/client';
import './styles/index.css';
import 'bootstrap/dist/css/bootstrap.min.css';
import { BrowserRouter, Routes, Route } from "react-router-dom";
import App from './App';
import ViewCapturesPage from "./Pages/ViewCapturesPage";
import ViewGraphsPage from "./Pages/ViewGraphsPage";
import AdminLoginPage from './Pages/AdminLoginPage';


const root = ReactDOM.createRoot(document.getElementById('root'), document.body.style.backgroundColor = "#D9D9D9");

root.render(
  <React.StrictMode>
    <BrowserRouter>
      <Routes>
        <Route path="/" element={<AdminLoginPage />} />
        <Route path="/home" element={<App />} />
        <Route path="/pictures" element={<ViewCapturesPage />} />
        <Route path="/graph" element={<ViewGraphsPage />} />
      </Routes>
    </BrowserRouter>
  </React.StrictMode>
);

// If you want to start measuring performance in your app, pass a function
// to log results (for example: reportWebVitals(console.log))
// or send to an analytics endpoint. Learn more: https://bit.ly/CRA-vitals
