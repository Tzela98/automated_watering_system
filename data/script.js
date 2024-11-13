function populateZones() {
    // Fetch the list of available zones from the server
    fetch('/zones')
        .then(response => response.json())  // Parse the JSON response
        .then(zones => {
            const zoneSelect = document.getElementById('zone');  // Get the <select> element
            zoneSelect.innerHTML = '';  // Clear existing options

            // Dynamically create <option> elements for each zone
            zones.forEach(zone => {
                const option = document.createElement('option');
                option.value = zone;  // Set the value of the option (zone number)
                option.textContent = 'Zone ' + zone;  // Display name (e.g., Zone 1)
                zoneSelect.appendChild(option);  // Add the option to the select element
            });
        })
        .catch(error => {
            console.error('Error fetching zones:', error);
        });
}

function updateStatus() {
    fetch('/status')
        .then(response => response.text())
        .then(data => {
            document.getElementById('status').innerText = 'System status: ' + data;
        });
}

// Update status every 5 seconds
setInterval(updateStatus, 5000);

// Populate the zones when the page loads
document.addEventListener('DOMContentLoaded', populateZones);
