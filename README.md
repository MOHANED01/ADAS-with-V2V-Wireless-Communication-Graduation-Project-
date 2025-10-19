<h1> ADAS with V2V Wireless Communication </h1>

  This project demonstrates an **Advanced Driver Assistance System (ADAS)**, utilizing **Vehicle-to-Vehicle (V2V) wireless communication** to enhance safety, and driver assistance.  
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
<pre><code>        ┌───────────────────────────────────────┐         ┌───────────────────────────────────────┐
        │          Vehicle 2 (Rx)               │                     Vehicle 1 (Tx)         
        │ ───────────────────────────────────── │         │ ───────────────────────────────────── │
        │  STM32 (Sensors, Control)             │         │  STM32 (CAN-ESP Gateway)              │
        │  ESP8266 (ESP-NOW Protocol)           │         │  ESP8266 (ESP-NOW Protocol)           │
        │  Vehicle Sensors                      │         └──────────────────┬────────────────────┘
        │  (Speed,Ultrasonic,Lane detect)       │                            │ 
        │  Vehicle Actuators(DC Motors)         │                            ▲                             
        └────────────────────────┬──────────────┘                            │
                                 │                                     [Raspberry Pi GUI, Camera]      
                                 ▼                                           
             [Real-time Traffic Data Display]                 
                                 
                                 
                     
</code></pre>

<hr />

<h2>📌 Features</h2>
<ul>
  <li><strong>Vehicle-to-Vehicle (V2V) Communication:</strong> ESP8266 Wi-Fi modules enable data exchange (speed, lane status, drowsiness detection) between two vehicles in real time.</li>
  <li><strong>Traffic Sign Recognition:</strong> Machine learning-based recognition of traffic signs through camera images processed on **Raspberry Pi** and communicated between 2 vehicles.</li>
  <li><strong>Driver Drowsiness Detection:</strong> Detects facial expressions and eye movements using a camera to monitor driver drowsiness. Alerts are triggered if driver drowsiness is detected.</li>
  <li><strong>Lane Departure Warning:</strong> Monitors lane markings and provides alerts if the driver drifts from the lane.</li>
  <li><strong>Adaptive Cruise Control:</strong> Automatically adjusts vehicle speed based on proximity to other vehicles using V2V data.</li>
  <li><strong>Raspberry Pi GUI:</strong> Real-time visualization of sensor data (speed, music, lane status, drowsiness) displayed on a user-friendly interface.</li>
</ul>



<hr />

<h2>📌 Technical Specifications</h2>
<table>
  <thead>
    <tr><th>Component</th><th>Details</th></tr>
  </thead>
  <tbody>
    <tr><td><strong>Microcontrollers</strong></td><td>STM32F4, STM32F103</td></tr>
    <tr><td><strong>Wireless Module</strong></td><td>ESP8266 (Wi-Fi)</td></tr>
    <tr><td><strong>Camera</strong></td><td>Raspberry Pi Camera Module (for drowsiness detection &  traffic sign)</td></tr>
    <tr><td><strong>Operating System</strong></td><td>Costumized OS using YOCTO (for GUI)</td></tr>
    <tr><td><strong>Programming Languages</strong></td><td>Embedded C (STM32), Python (Raspberry Pi), bash (Costumization)</td></tr>
    <tr><td><strong>Communication Protocol</strong></td><td>USART, ESP-NOW (ESP8266), CAN Network</td></tr>
    <tr><td><strong>Tools</strong></td><td>STM32CubeIDE, Arduino IDE, Raspberry Pi, OpenCV (for lane detection), TensorFlow (for drowsiness detection)</td></tr>
  </tbody>
</table>

<hr />

<h2>📌 How It Works</h2>
<ol>
  <li><strong>Vehicle 1 (Sender):</strong>
    <ul>
      <li>Collects data (sign & drowsiness detection) from camera using RPI.</li>
      <li>Displays real-time camera on a user interface (sign detectiom, drowsiness alert).</li>
      <li>Enables the driver to interact with the system (Music with Bluetooth Mobile connection) and see warnings (sign detectiom, drowsiness alert).</li>
      <li>Display data using <strong>GUI Screen</strong>.</li>
      <li>Send data to STM32 via <strong>CAN</strong> network.</li>
      <li>Transmits data to Vehicle 2 via <strong>ESP8266</strong> module.</li>
    </ul>
  </li>
  <li><strong>Vehicle 2 (Receiver):</strong>
    <ul>
      <li>Receives data from Vehicle 1 via <strong>ESP8266</strong> module.</li>
      <li>Uses the data to adjust vehicle speed, trigger warnings, and control vehicle systems.</li>
    </ul>
  </li>

</ol>

<hr />

<h2>📌 Testing &amp; Validation</h2>
<ul>
  <li>Tested V2V communication for data exchange between vehicles using <strong>ESP8266 Wi-Fi modules</strong>.</li>
  <li>Validated <strong>drowsiness detection</strong> via facial recognition running on the Raspberry Pi.</li>
  <li>Checked accuracy of <strong>lane detection</strong> with various road conditions.</li>
  <li>Tested <strong>adaptive cruise control</strong> with  speed data displayed on LCD.</li>
</ul>

<hr />

<h2>📌 Build &amp; Run Instructions</h2>

<h3>Requirements</h3>
<ul>
  <li>STM32CubeIDE/Eclipse(for STM32 programming) </li>
  <li>ArduinoIDE(for ESP8266 programming) </li>
  <li>Raspberry Pi (for GUI and data processing)</li>
  <li>OpenCV / TensorFlow (for camera processing on Raspberry Pi)</li>
</ul>

<h3>Steps</h3>
<ol>
  <li>Flash the <strong>vehicle1</strong> (Tx) firmware to the first STM32 using STM32CubeIDE.</li>
   <li>Set up the <strong>Raspberry Pi</strong> with the required libraries (OpenCV, TensorFlow) and configure the GUI application.</li>
  <li>Flash the <strong>vehicle2</strong> (Rx) firmware to the second STM32 using STM32CubeIDE.</li>
  <li>flash the <strong>ESP8266 Wi-Fi modules</strong> with a new Firware for both (Tx & Rx).</li>
  <li>Test communication and interaction by running both vehicles and the Raspberry Pi system.</li>
</ol>

<hr />

<h2>📌 Future Enhancements</h2>
<ul>
  
  <li>Improve <strong>Firmware</strong>with AUTOSAR standards.</li>
  <li>Improve <strong>lane detection</strong> with AI-powered models.</li>
  <li>Implement <strong>wireless firmware</strong> update system for V2V communication updates.</li>
  <li>Integrate <strong>vehicle-to-infrastructure (V2I)</strong> communication for enhanced traffic management.</li>

</ul>

<hr />


