// Get all the elements we need
const timeDisplay = document.querySelector('.time-display');
const startButton = document.getElementById('start');
const pauseButton = document.getElementById('pause');
const resetButton = document.getElementById('reset');
const lapButton = document.getElementById('lap');
const lapTimes = document.getElementById('lap-times');

// Variables to keep track of time
let startTime;
let elapsedTime = 0;
let timerInterval;
let isRunning = false;

// Format time as HH:MM:SS
function formatTime(milliseconds) {
    let date = new Date(milliseconds);
    let hours = date.getUTCHours().toString().padStart(2, '0');
    let minutes = date.getUTCMinutes().toString().padStart(2, '0');
    let seconds = date.getUTCSeconds().toString().padStart(2, '0');
    
    return `${hours}:${minutes}:${seconds}`;
}

// Update the time display
function updateDisplay() {
    timeDisplay.textContent = formatTime(elapsedTime);
}

// Start the stopwatch
function start() {
    if (!isRunning) {
        startTime = Date.now() - elapsedTime;
        timerInterval = setInterval(function() {
            elapsedTime = Date.now() - startTime;
            updateDisplay();
        }, 1000); // Update every second
        
        isRunning = true;
        
        // Enable/disable buttons
        startButton.disabled = true;
        pauseButton.disabled = false;
        resetButton.disabled = false;
        lapButton.disabled = false;
    }
}

// Pause the stopwatch
function pause() {
    if (isRunning) {
        clearInterval(timerInterval);
        isRunning = false;
        
        // Enable/disable buttons
        startButton.disabled = false;
        pauseButton.disabled = true;
    }
}

// Reset the stopwatch
function reset() {
    clearInterval(timerInterval);
    isRunning = false;
    elapsedTime = 0;
    updateDisplay();
    lapTimes.innerHTML = '';
    
    // Enable/disable buttons
    startButton.disabled = false;
    pauseButton.disabled = true;
    resetButton.disabled = true;
    lapButton.disabled = true;
}

// Record a lap time
function lap() {
    if (isRunning) {
        const lapTime = document.createElement('div');
        lapTime.textContent = formatTime(elapsedTime);
        lapTimes.prepend(lapTime);
    }
}

// Add event listeners to buttons
startButton.addEventListener('click', start);
pauseButton.addEventListener('click', pause);
resetButton.addEventListener('click', reset);
lapButton.addEventListener('click', lap);

// Initialize the display
updateDisplay();

// Set initial button states
pauseButton.disabled = true;
resetButton.disabled = true;
lapButton.disabled = true;