document.addEventListener("DOMContentLoaded", () => {
    const zoneSelect = document.getElementById("zone");
    const addScheduleForm = document.getElementById("add-schedule-form");
    const addScheduleBtn = document.getElementById("add-schedule-btn");
    const clearScheduleBtn = document.getElementById("clear-schedule-btn");

    // Fetch zones and populate the dropdown
    fetch("/zones")
        .then(response => response.json())
        .then(zones => {
            zones.forEach(zone => {
                const option = document.createElement("option");
                option.value = zone - 1; // Adjust for zero-indexed zones
                option.textContent = `Zone ${zone}`;
                zoneSelect.appendChild(option);
            });

            if (zones.length > 0) {
                zoneSelect.value = zones[0] - 1;
                zoneSelect.dispatchEvent(new Event("change")); // Fetch schedule for the first zone
            }
        })
        .catch(error => console.error("Error fetching zones:", error));

    // Fetch current schedule for selected zone
    zoneSelect.addEventListener("change", () => {
        const zone = zoneSelect.value;
        fetch(`/get_schedule?zone=${zone}`)
            .then(response => response.json())
            .then(schedules => {
                const scheduleSection = document.getElementById(`schedule-list-${zone}`);
                
                if (!scheduleSection) {
                    // Create a new section if it doesn't exist
                    const newScheduleSection = document.createElement("div");
                    newScheduleSection.id = `schedule-list-${zone}`;
                    newScheduleSection.innerHTML = `<h3>Schedule for Zone ${parseInt(zone) + 1}</h3><ul></ul>`;
                    document.body.appendChild(newScheduleSection);
                }

                const scheduleList = document.getElementById(`schedule-list-${zone}`).querySelector("ul");
                scheduleList.innerHTML = ""; // Clear existing schedule
                if (schedules.length > 0) {
                    schedules.forEach(schedule => {
                        const listItem = document.createElement("li");
                        listItem.textContent = `Days: ${schedule.days.join(", ")}, Start: ${schedule.startHour}:${schedule.startMinute}, Duration: ${schedule.duration} mins`;
                        scheduleList.appendChild(listItem);
                    });
                } else {
                    const listItem = document.createElement("li");
                    listItem.textContent = "No schedule available.";
                    scheduleList.appendChild(listItem);
                }
            })
            .catch(error => console.error("Error fetching schedule:", error));
    });

    // Add a new schedule
    addScheduleBtn.addEventListener("click", () => {
        const zone = zoneSelect.value;
        const formData = new FormData(addScheduleForm);
        const days = Array.from(formData.getAll("days")).map(Number);

        const schedule = {
            startHour: parseInt(formData.get("startHour")),
            startMinute: parseInt(formData.get("startMinute")),
            duration: parseInt(formData.get("duration")),
            days: days
        };

        fetch(`/add_schedule?zone=${zone}`, {
            method: "POST",
            headers: { "Content-Type": "application/json" },
            body: JSON.stringify(schedule)
        })
            .then(response => {
                if (response.ok) {
                    alert("Schedule added!");
                    zoneSelect.dispatchEvent(new Event("change")); // Refresh schedule
                } else {
                    alert("Failed to add schedule.");
                }
            })
            .catch(error => console.error("Error adding schedule:", error));
    });

    // Clear the schedule for the selected zone
    clearScheduleBtn.addEventListener("click", () => {
        const zone = zoneSelect.value;
        fetch(`/clear_schedule?zone=${zone}`, { method: "POST" })
            .then(response => {
                if (response.ok) {
                    alert("Schedule cleared!");
                    zoneSelect.dispatchEvent(new Event("change")); // Refresh schedule
                } else {
                    alert("Failed to clear schedule.");
                }
            })
            .catch(error => console.error("Error clearing schedule:", error));
    });
});
