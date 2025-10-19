<h1> ADAS with V2V Wireless Communication </h1>

  This project demonstrates an **Advanced Driver Assistance System (ADAS)**, utilizing **Vehicle-to-Vehicle (V2V) wireless communication** to enhance safety, navigation, and driver assistance.  
  The system uses **STM32 microcontrollers**, **ESP8266 Wi-Fi modules**, and **Raspberry Pi** to exchange real-time data, detect traffic signs, monitor drowsiness, and assist with lane detection.


<hr />

<h2>📌 Project Overview</h2>

  - The project aims to create an embedded system with **Vehicle-to-Vehicle (V2V)** communication for data exchange and **advanced safety features**.  
  - The system supports **traffic sign recognition**, **driver drowsiness detection**, **lane departure warnings**, and **adaptive cruise control**.
<hr />

<h3>📌 Key Objectives</h3>

 - Implement **Vehicle-to-Vehicle (V2V)** communication using **ESP8266 Wi-Fi modules** for data transfer.
 - Develop **machine learning-based traffic sign recognition** for real-time vehicle feedback.
 - Implement **driver drowsiness detection** through facial expression monitoring.
 - Use **Raspberry Pi** for real-time monitoring and GUI visualization of the system's status.
 - Deploy **STM32 microcontrollers** to manage communication and control systems.


<hr />

<h2>📌 System Architecture</h2>
<pre><code>        ┌──────────────────────────────────────┐         ┌────────────────────────────────────────┐
        │          Vehicle 1 (Rx)               │                     Vehicle 2 (Tx)         
        │ ───────────────────────────────────── │         │ ───────────────────────────────────── │
        │  STM32 (Sensors, Control)             │         │  STM32 (CAN-ESP Gateway)              │
        │  ESP8266 (ESP-NOW Protocol)           │         │  ESP8266 (ESP-NOW Protocol)           │
        │  Vehicle Sensors                      │         └──────────────────┬────────────────────┘
        │  (Speed,Ultrasonic,Lane detect)       │                            ▲
        └────────────────────────┬──────────────┘                            │
                                 │                                     [Raspberry Pi GUI, Camera]      
                                 ▼                                           
             [Real-time Traffic Data Display]                 
                                 
                                 
                     
</code></pre>

<hr />

<h2>🧩 Features</h2>
<ul>
  <li><strong>Vehicle-to-Vehicle (V2V) Communication:</strong> ESP8266 Wi-Fi modules enable data exchange (speed, lane status, drowsiness detection) between two vehicles in real time.</li>
  <li><strong>Traffic Sign Recognition:</strong> Machine learning-based recognition of traffic signs through camera images processed on **Raspberry Pi** and communicated between vehicles.</li>
  <li><strong>Driver Drowsiness Detection:</strong> Detects facial expressions and eye movements using a camera to monitor driver drowsiness. Alerts are triggered if prolonged drowsiness is detected.</li>
  <li><strong>Lane Departure Warning:</strong> Monitors lane markings and provides alerts if the driver drifts from the lane.</li>
  <li><strong>Adaptive Cruise Control:</strong> Automatically adjusts vehicle speed based on proximity to other vehicles using V2V data.</li>
  <li><strong>Raspberry Pi GUI:</strong> Real-time visualization of sensor data (speed, lane status, drowsiness) displayed on a user-friendly interface.</li>
</ul>

<hr />

<h2>🧱 Project Structure</h2>
<pre><code>ADAS-V2V-Communication/
├── vehicle1/             # Sender vehicle code (STM32 + ESP8266)
│   ├── src/              # Source files for STM32 (sensors, control)
│   ├── inc/              # Header files
│   ├── communication/    # V2V communication (ESP8266)
├── vehicle2/             # Receiver vehicle code (STM32 + ESP8266)
│   ├── src/              # Source files for STM32 (sensors, control)
│   ├── inc/              # Header files
│   ├── communication/    # V2V communication (ESP8266)
├── raspberrypi/          # Raspberry Pi GUI and data processing
│   ├── gui/              # Graphical user interface (Python/GTK)
│   ├── processing/       # Real-time data processing (drowsiness, lane detection)
├── README.md
└── .gitignore
</code></pre>

<hr />

<h2>🔧 Technical Specifications</h2>
<table>
  <thead>
    <tr><th>Component</th><th>Details</th></tr>
  </thead>
  <tbody>
    <tr><td><strong>Microcontrollers</strong></td><td>STM32F4, STM32F103</td></tr>
    <tr><td><strong>Wireless Module</strong></td><td>ESP8266 (Wi-Fi)</td></tr>
    <tr><td><strong>Camera</strong></td><td>Raspberry Pi Camera Module (for drowsiness detection)</td></tr>
    <tr><td><strong>Operating System</strong></td><td>Raspberry Pi OS (for GUI)</td></tr>
    <tr><td><strong>Programming Languages</strong></td><td>Embedded C (STM32), Python (Raspberry Pi)</td></tr>
    <tr><td><strong>Communication Protocol</strong></td><td>Wi-Fi (ESP8266)</td></tr>
    <tr><td><strong>Tools</strong></td><td>STM32CubeIDE, Atmel Studio, Raspberry Pi, OpenCV (for lane detection), TensorFlow (for drowsiness detection)</td></tr>
  </tbody>
</table>

<hr />

<h2>🧠 How It Works</h2>
<ol>
  <li><strong>Vehicle 1 (Sender):</strong>
    <ul>
      <li>Collects sensor data (lane, speed, drowsiness detection) from cameras and other sensors.</li>
      <li>Transmits data to Vehicle 2 via **ESP8266 Wi-Fi** module.</li>
    </ul>
  </li>
  <li><strong>Vehicle 2 (Receiver):</strong>
    <ul>
      <li>Receives data from Vehicle 1 via **Wi-Fi communication**.</li>
      <li>Uses the data to adjust vehicle speed, trigger warnings, and control vehicle systems.</li>
    </ul>
  </li>
  <li><strong>Raspberry Pi GUI:</strong>
    <ul>
      <li>Displays real-time sensor data on a user interface (e.g., speed, lane detection, drowsiness alert).</li>
      <li>Enables the driver to interact with the system and see warnings (lane departure, drowsiness).</li>
    </ul>
  </li>
</ol>

<hr />

<h2>🧪 Testing &amp; Validation</h2>
<ul>
  <li>Tested V2V communication for data exchange between vehicles using **ESP8266 Wi-Fi modules**.</li>
  <li>Validated **drowsiness detection** via facial recognition running on the Raspberry Pi.</li>
  <li>Checked accuracy of **lane detection** with various road conditions.</li>
  <li>Tested **adaptive cruise control** with real-time speed data from V2V communication.</li>
</ul>

<hr />

<h2>🧰 Build &amp; Run Instructions</h2>

<h3>Requirements</h3>
<ul>
  <li>STM32CubeIDE / Atmel Studio (for STM32 programming)</li>
  <li>Raspberry Pi (for GUI and data processing)</li>
  <li>ESP8266 Wi-Fi modules</li>
  <li>OpenCV / TensorFlow (for camera processing on Raspberry Pi)</li>
</ul>

<h3>Steps</h3>
<ol>
  <li>Flash the **vehicle1** (Sender) firmware to the first STM32 using STM32CubeIDE.</li>
  <li>Flash the **vehicle2** (Receiver) firmware to the second STM32 using STM32CubeIDE.</li>
  <li>Set up the **ESP8266 Wi-Fi modules** for communication between vehicles.</li>
  <li>Set up the **Raspberry Pi** with the required libraries (OpenCV, TensorFlow) and configure the GUI application.</li>
  <li>Test communication and interaction by running both vehicles and the Raspberry Pi system.</li>
</ol>

<hr />

<h2>📁 Example Run</h2>
<pre><code>Vehicle 1: "Sending data: Speed: 60 km/h, Lane: Left, Drowsiness: Alert"
Vehicle 2: "Received data from Vehicle 1: Speed: 60 km/h, Lane: Left, Drowsiness: Alert"
Vehicle 2: "Adjusting speed and enabling lane-keeping assistance"
Raspberry Pi: "Displaying data: Speed: 60 km/h, Lane: Left, Drowsiness Alert"
</code></pre>

<hr />

<h2>🚀 Future Enhancements</h2>
<ul>
  <li>Improve **lane detection** with AI-powered models.</li>
  <li>Implement **wireless firmware update** system for V2V communication updates.</li>
  <li>Integrate **vehicle-to-infrastructure (V2I)** communication for enhanced traffic management.</li>
  <li>Develop **cross-vehicle communication protocols** for seamless data transfer across various platforms.</li>
</ul>

<hr />

<h2>📚 References</h2>
<ul>
  <li>STM32 Reference Manual</li>
  <li>ESP8266 Datasheet</li>
  <li>OpenCV Documentation (Lane Detection)</li>
  <li>TensorFlow Documentation (Drowsiness Detection)</li>
</ul>

<hr />

<h2>👨‍💻 Author</h2>
<p>
  <strong>Mohaned Hossam</strong><br />
  Embedded Software Engineer<br />
  📧 <a href="mailto:mohanedtohamy444@gmail.com">mohanedtohamy444@gmail.com</a><br />
  🔗 <a href="https://www.linkedin.com/in/mohaned-hossam-8593041b3">LinkedIn</a><br />
  💻 <a href="https://github.com/MOHANED01">GitHub</a>
</p>

<hr />

<p><strong>⭐ “Enhancing driver safety through intelligent communication and real-time control.”</strong></p>
