<div align="center">
  <p><a><img width="100%" src="src/image/Banner.png"></a></p>
</div>

#### Publish Date: 2025-12-31

#### Title: SmartBio Air: AI-Driven Indoor Algae Based Air Purification System Using MYOSA Mini IoT Kit

#### Excerpt: A hybrid Edge AI and Cloud AI system that studies and supports indoor air purification using living algae, multi-sensor monitoring, and autonomous safety control on the MYOSA Mini IoT platform

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
SmartBio Air is an indoor air purification and experimental research system that combines **biological air treatment using algae** with **sensor-driven intelligence**. The system operates in two clearly defined modes:

- **Offline Edge Mode** for safety-critical and continuous operation  
- **Online Cloud Mode** for environmental correlation, monitoring, and scientific study  

The architecture separates real-time control from long-term analysis, making the system suitable for both deployment scenarios and academic investigation.

---

## Examples  
Representative use cases include:

- Indoor air quality monitoring in enclosed environments  
- Observation of algae response to light, air pollutants, and temperature  
- Motor pump fault detection using vibration-based Edge ML  
- Edge AI and Cloud AI co-execution experiments  

---

## Demo  

### Images  
_Add images of the system setup, algae chamber, sensor wiring, OLED output, and web dashboard._

### Videos  
_Add a short demonstration video showing live system operation._

---

## Features (Detailed)  

- Algae-assisted indoor air purification chamber  
- Multi-gas monitoring using MQ-series sensors  
- Motor pump health classification using MPU6050 and Edge ML  
- Autonomous offline execution on MYOSA (ESP32)  
- Cloud-based AI agents for monitoring and research study  
- Local OLED display for system status and air quality level  
- Web-based visualization using a static dashboard  

---

## Usage Instructions  

1. Power the MYOSA Mini IoT Kit and connect all sensors securely  
2. Allow MQ sensors sufficient warm-up time for stable readings  
3. Observe system state and air quality on the OLED display  
4. In offline mode, the system executes fully on-device  
5. In online mode, sensor data is transmitted to Azure for AI processing  
6. View environmental trends and system summaries through the web dashboard  

---

## Tech Stack  

### Hardware  
- MYOSA Mini IoT Kit (ESP32)  
- MPU6050  
- APDS9960  
- BMP180  
- MQ-2, MQ-3, MQ-7, MQ-135  
- SSD1306 OLED  

### Firmware  
- Arduino / ESP-IDF  
- Edge Impulse TinyML inference  

### Cloud  
- Microsoft Azure Functions  
- Azure AI services  

### Frontend  
- HTML  
- CSS  
- JavaScript (Static Web Application)  

---

## Requirements / Installation  

- MYOSA Mini IoT Kit  
- Arduino IDE or PlatformIO  
- Edge Impulse account for model deployment  
- Microsoft Azure account  
- Stable power supply for continuous operation  

Flash the firmware to the MYOSA board after configuring Wi-Fi credentials and cloud endpoints.

---

## File Structure (Optional)  

```
SmartBio-Air/
├── firmware/
│ ├── sensors/
│ ├── edge_ml/
│ └── main.ino
├── cloud/
│ └── azure-function/
├── web/
│ └── static-dashboard/
├── docs/
│ └── diagrams/
└── README.md
```

## License
This project may be released under the **MIT License** or another academic-friendly open-source license, subject to publication requirements.

---

## Contribution Notes (Optional)  
This repository is intended for research and educational use.  
Contributors are encouraged to document experimental conditions, sensor calibration steps, and data collection procedures clearly when submitting updates.
