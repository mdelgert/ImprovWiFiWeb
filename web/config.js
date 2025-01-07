// config.js
console.log('config.js loaded');

// Dev logic: if host is "localhost", use the given IP as base, else use relative path
const BASE_URL = window.location.hostname === "localhost" 
  ? "http://demo.local" 
  : "";                      

// Export the variable for use in other scripts
export { BASE_URL };
