// settings.js
console.log("settings.js loaded");

import { httpGet, httpPost, showMessage } from "./global.js";

// Load Wi-Fi settings from the server
async function loadWifiSettings() {
  try {
    console.log("Fetching Wi-Fi settings from /wifi/get...");
    const settings = await httpGet("/wifi/get");
    console.log("Received settings:", settings); // Debugging: log received settings

    const networkInput = document.getElementById("wifi-network");
    const passwordInput = document.getElementById("wifi-password");

    if (settings.wifi_ssid !== undefined) {
      networkInput.value = settings.wifi_ssid;
      console.log("Populated Wifi Network:", settings.wifi_ssid); // Debugging
    } else {
      console.warn("Wifi SSID is undefined in the response.");
    }

    if (settings.wifi_password !== undefined) {
      passwordInput.value = settings.wifi_password;
      console.log("Populated Wifi Password:", settings.wifi_password); // Debugging
    } else {
      console.warn("Wifi Password is undefined in the response.");
    }

    //showMessage("Wi-Fi settings loaded successfully!", "success");
  } catch (error) {
    showMessage("Failed to load Wi-Fi settings.", "error");
    console.error("Error loading Wi-Fi settings:", error);
  }
}

// Save Wi-Fi settings to the server
async function saveWifiSettings() {
  const wifiSsid = document.getElementById("wifi-network").value.trim();
  const wifiPassword = document.getElementById("wifi-password").value.trim();

  if (!wifiSsid || !wifiPassword) {
    showMessage("Please fill in both fields.", "error");
    console.error("Validation failed: Both fields are required.");
    return;
  }

  try {
    console.log("Saving Wi-Fi settings to /wifi/save...");
    const body = { wifi_ssid: wifiSsid, wifi_password: wifiPassword };
    console.log("Payload being sent:", body); // Debugging

    await httpPost("/wifi/save", body);
    showMessage("Wi-Fi settings saved successfully!", "success");
  } catch (error) {
    showMessage("Failed to save Wi-Fi settings.", "error");
    console.error("Error saving Wi-Fi settings:", error);
  }
}

// Attach event listeners
document.addEventListener("DOMContentLoaded", () => {
  // Load existing Wi-Fi settings on page load
  console.log("Page loaded. Initializing Wi-Fi settings load...");
  loadWifiSettings();

  // Attach save button event
  const saveButton = document.querySelector(".settings-form button");
  if (saveButton) {
    saveButton.addEventListener("click", saveWifiSettings);
    console.log("Save button event listener attached.");
  } else {
    console.error("Save button not found.");
  }
});
