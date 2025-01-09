// settings.js
console.log("settings.js loaded");

import { httpGet, httpPost, showMessage } from "./global.js";

// Load settings from the server
async function loadSettings() {
  try {
    console.log("Fetching settings from /settings/get...");
    const response = await httpGet("/settings/get");
    const { data } = response; // Extract the data object from the response
    console.log("Received settings:", data); // Debugging: log received settings

    const networkInput = document.getElementById("wifi-network");
    const passwordInput = document.getElementById("wifi-password");

    if (data.wifi_ssid !== undefined) {
      networkInput.value = data.wifi_ssid;
      console.log("Populated Wi-Fi Network:", data.wifi_ssid); // Debugging
    } else {
      console.warn("Wi-Fi SSID is undefined in the response.");
    }

    if (data.wifi_password !== undefined) {
      passwordInput.value = data.wifi_password;
      console.log("Populated Wi-Fi Password:", data.wifi_password); // Debugging
    } else {
      console.warn("Wi-Fi Password is undefined in the response.");
    }

    showMessage("Settings loaded successfully!", "success");
  } catch (error) {
    showMessage("Failed to load settings.", "error");
    console.error("Error loading settings:", error);
  }
}

// Save settings to the server
async function saveSettings() {
  const wifiSsid = document.getElementById("wifi-network").value.trim();
  const wifiPassword = document.getElementById("wifi-password").value.trim();

  if (!wifiSsid || !wifiPassword) {
    showMessage("Please fill in both fields.", "error");
    console.error("Validation failed: Both fields are required.");
    return;
  }

  try {
    console.log("Saving settings to /settings/save...");
    const body = { wifi_ssid: wifiSsid, wifi_password: wifiPassword };
    console.log("Payload being sent:", body); // Debugging

    await httpPost("/settings/set", body);
    showMessage("Settings saved successfully!", "success");
  } catch (error) {
    showMessage("Failed to save settings.", "error");
    console.error("Error saving settings:", error);
  }
}

// Attach event listeners
document.addEventListener("DOMContentLoaded", () => {
  // Load existing settings on page load
  console.log("Page loaded. Initializing settings load...");
  loadSettings();

  // Attach save button event
  const saveButton = document.querySelector(".settings-form button");
  if (saveButton) {
    saveButton.addEventListener("click", saveSettings);
    console.log("Save button event listener attached.");
  } else {
    console.error("Save button not found.");
  }
});
