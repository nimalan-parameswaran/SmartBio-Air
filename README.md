<div align="center">
  <p><a><img width="100%" src="src/image/Banner.png"></a></p>
</div>

#### Publish Date: 2025-12-31

#### Title: SmartBio Air: AI-Driven Indoor Algae Based Air Purification System Using MYOSA Mini IoT Kit

#### An indoor air purification and research system that integrates living algae, multi-sensor environmental sensing, Edge AI–based safety control, and Cloud AI–assisted research analysis using the MYOSA Mini IoT Kit.


---

## Contributors  

- **Nimalan P** - [@nimalan-parameswaran](https://github.com/nimalan-parameswaran)  
- **Dhakshatha M K** - [@DhakshathaMylsamy](https://github.com/DhakshathaMylsamy)
  
---

## Acknowledgement 
We express our sincere thanks and profound gratitude to the **IEEE International MYOSA 4.0 Committee Members** for shortlisting our project from a large number of submitted proposals and for supporting this work through the provision of a **USD 250 MYOSA Mini IoT Kit**.

We are grateful to the **IEEE Sensors Council** for its continued encouragement and support of student-led research and applied engineering initiatives.

We extend our special thanks to **Dr. Dinesh Chellappan**, Centre for Research and Development, for his valuable guidance, technical direction, and mentorship throughout the course of this project.

Finally, we acknowledge **Ms. Pinki Dey**, Assistant Professor II, Department of Biomedical Engineering, for her assistance with the cultivation and maintenance of the *Spirulina* culture, which forms a fundamental biological component of this work.

---

<p align="center">
  <img src="src/image/Img1.jpg" width="600">
</p>

---

## Overview  

**SmartBio Air** is an indoor air purification and experimental research system that combines biological air treatment using algae with multi-sensor environmental monitoring and intelligent control. The system is designed not only to support indoor air purification, but also to experimentally observe and document the relationship between environmental conditions, air pollutants, and algae growth behavior over time.

The platform operates using a hybrid intelligence model in which time-sensitive and safety-related decisions are executed locally on the MYOSA Mini IoT Kit, while research-oriented observation, data correlation, and long-term interpretation are performed using cloud-based AI services. This separation allows continuous and safe operation during network unavailability, while still enabling extended scientific investigation when connectivity is present.

The system architecture is bifurcated into two synchronized operational states:

- **Primary Edge Control Mode**, which prioritises autonomous operation, motor pump protection, and air quality response using on-device inference and predefined threshold logic. This mode supports uninterrupted air purification without dependence on internet connectivity.

- **Cloud AI Agent Mode**, which is primarily intended for research purposes. In this mode, full sensor data is transmitted to the cloud to study how algae growth responds to changes in air pollution levels, light conditions, temperature, and other environmental factors. Centralised data logging, AI agent–based reasoning, and web-based visualisation support long-term analysis and pattern identification.

By combining biological air treatment, Edge AI–based safety mechanisms, and cloud-assisted research workflows, SmartBio Air functions both as a practical indoor air purification system and as a research platform suitable for studies in TinyML, IoT-based environmental sensing, and sustainable bio-assisted systems.

---

## Background  
Indoor air pollution has become a growing concern due to increased time spent in enclosed environments and the presence of gaseous pollutants such as carbon monoxide, volatile organic compounds, and particulate matter. Conventional air purification systems rely mainly on mechanical filtration or chemical absorption, which often require frequent maintenance and do not contribute to long-term environmental sustainability.

Biological air treatment using microalgae has gained research interest due to its natural ability to absorb carbon dioxide and certain airborne contaminants while producing oxygen through photosynthesis. Despite this potential, most algae-based purification systems remain confined to laboratory studies and lack real-time sensing, adaptive control, and long-term observational capability.

Recent progress in Internet of Things platforms, Edge AI, and cloud-based analytics allows biological systems to be monitored continuously and studied under real environmental conditions. Integrating these technologies offers an opportunity to bridge the gap between biological air purification research and deployable indoor systems.

---

## Problem Statement  
Existing indoor air purifiers operate as isolated mechanical systems with limited environmental awareness and no capacity to study biological purification processes over time. Algae-based air purification concepts, while promising, often lack continuous monitoring, fault tolerance, and autonomous operation required for indoor deployment.

There is a lack of systems that can safely operate in real environments while simultaneously collecting structured data to study how algae growth responds to air pollution levels, light conditions, and environmental changes. Network dependence further limits reliability, as cloud-only solutions cannot guarantee uninterrupted operation.

A system is required that supports autonomous air purification, protects hardware components, and enables controlled scientific observation without compromising safety or continuity.

---

## Project Objectives  
The primary objectives of this project are:

- To design an indoor air purification system that incorporates living algae as a biological air treatment medium

- To monitor indoor air quality and environmental parameters using multiple sensors

- To implement on-device intelligence for safety-critical operation and motor pump protection

- To study the relationship between air pollution levels, environmental conditions, and algae growth behavior

- To support long-term data collection and visualization for research and analysis

---
## Solution

SmartBio Air is implemented on the MYOSA Mini IoT Kit using a hybrid on-device and cloud-assisted intelligence approach designed for safe indoor operation and research observation. The system combines gas sensors, environmental sensors, and a biologically active algae chamber to support air purification while enabling continuous monitoring of surrounding conditions.

All safety-critical and time-sensitive functions, including air quality response and motor pump health monitoring, are executed locally on the device through embedded inference and threshold-based logic. This local execution allows uninterrupted operation even during network unavailability and protects hardware components from abnormal operating conditions.

<p align="center">
  <img src="src/image/Img3.png" width="50%" /> 
</p>

For experimental and analytical purposes, sensor measurements are transmitted to cloud services when connectivity is available. These services support structured data storage, correlation, and AI-based reasoning to study relationships between air pollution levels, environmental parameters, and algae growth behaviour over extended periods.

The system operates in two modes: an autonomous Edge mode that prioritises continuous air purification and system safety, and a cloud-connected mode focused on long-term environmental analysis and biological observation.


---
## Process Flow:
<p align="center">
  <img src="src/image/SmartBio Air – Process Flow.png" width=auto>
</p>

---

## Prototype  

<h3 align="center">  Prototype Design </h3>

<p align="center">
  <img src="src/video/360.gif" width="100%">
</p>

---

<h3 align="center">  Demo video </h3>

https://github.com/user-attachments/assets/dc5e86f7-b55a-48e4-8528-622ea4c8585f

---

<h3 align="center">  GitHub Static Web App </h3>

<p align="center">
  <img src="src/video/Demo.gif" width="100%" />
</p>

<p align="center">
  <a href="https://nimalan-parameswaran.github.io/SmartBio-Air/" target="_blank">
    Click here! Web App
  </a>
</p>

---

## Novelty  

- Use of living microalgae as an active biological air treatment component  
- Dual-mode architecture separating safety-critical on-device execution from cloud-based research tasks  
- On-device TinyML inference for motor pump health monitoring using vibration data  
- Continuous environmental sensing linked with biological response observation  
- Cloud-assisted workflow dedicated to studying algae behaviour under varying air conditions  
- Autonomous operation during network unavailability  
- Modular design using the MYOSA Mini IoT Kit suitable for educational and research reuse  


---

## Scope of the Project

This project covers indoor air quality monitoring, algae-based biological treatment, autonomous motor control, and cloud-assisted data analysis within controlled indoor environments.
Clinical validation, large-scale deployment, and industrial manufacturing considerations are outside the present scope.

---

##  Outcomes 

- Functional indoor air purification prototype using algae-based treatment  
- Autonomous execution during network outages  
- Continuous air quality and environmental monitoring  
- Structured dataset linking pollution levels with algae growth behaviour  
- A reusable research platform for studies in TinyML, IoT sensing, and bio-assisted systems  

---

## Features

- Algae-assisted indoor air purification chamber  
- Multi-gas sensing using MQ-series sensors  
- Motor pump health classification using MPU6050 and embedded ML  
- Autonomous offline execution on MYOSA (ESP32)  
- Cloud-based AI agents for monitoring and research  
- Local OLED display for system status  
- Web-based static dashboard for visualisation  

---

## Usage Instructions  

1. Power the MYOSA Mini IoT Kit and connect all sensors  
2. Allow MQ sensors adequate warm-up time  
3. Monitor air quality and system state on the OLED display  
4. Offline mode executes entirely on-device  
5. Online mode transmits data to Azure services  
6. View trends and summaries through the web dashboard  

---

## Tech Stack  

### Hardware  
- MYOSA Motherboard (ESP32)  
- MPU6050  
- APDS9960  
- BMP180
- SSD1306 OLED
- L298N
- 3.3V Mini Fan
- MQ-2, MQ-3, MQ-7, MQ-135
- 6V DC Motor Air Pump
- 4 Channel 12V Relay Board
- 12V Plant Grow LED


### Firmware  
- Arduino 
- Edge Impulse TinyML inference  

### Cloud  
- Microsoft Azure Functions  
- Azure OpenAI services

### Frontend  
- HTML  
- CSS  
- JavaScript
- GitHub Page

---

## Requirements / Installation  

## Installation and setup

This repository does not include automated installation or flashing scripts. The available setup steps are limited to the repository contents:

1. Clone the repository:
   ```sh
   git clone https://github.com/nimalan-parameswaran/SmartBio-Air.git

2. Open the static project page:

- Launch index.html in a web browser to view the project overview and visuals.

3. Review embedded inference assets:

- Inspect the TinyML_MotorPumpFaultDetection directory for TinyML model files and headers intended for embedded use.

Hardware deployment and firmware flashing require external tools and are not documented in this repository.

---

## File Structure

```
SmartBio-Air/
├── index.html — Static web-based project overview
│
├── Data/ — Project data folder
│ ├── DataCollectionScript/
│ ├── Datasets/
│ ├── Data_Preprocessing_and_EDA.ipynb
│ └── EdgeImpulse_Final_dataset.csv
│
├── Main/ — Main project resources
│ ├── AGENT_MAIN/
│ ├── MYOSA-MAIN/
│ └── WEBAPP_MAIN/
│
├── TinyML_MotorPumpFaultDetection/ — TinyML model files and related artefacts
│ ├── FaultDetection_Inferencing/
│ ├── FaultDetection_ModelFile/
│ ├── src/
│ └── README.md/
│
├── src/ — Assets used by the static web interface
├── LICENSE — MIT License
└── README.md — Project documentation

```

## License

This project is licensed under the MIT License. Refer to the LICENSE file for details.

---

## Contribution Notes

This repository is intended for research and educational use. Contributors are encouraged to document experimental conditions, sensor calibration steps, and data collection procedures clearly when submitting updates.
