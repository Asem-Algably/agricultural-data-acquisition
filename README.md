# Reef Plus – Embedded Firmware

This repository contains the embedded systems firmware for **Reef Plus**, an IoT project currently under development.

I built this embedded part individually, while other teammates handled the web application, electronics, and logistics sides of the full project.

## What this is

Reef Plus uses multiple ESP32-based IoT nodes to collect sensor readings (air humidity, air temperature, and soil moisture) for agricultural monitoring.

## How it works (brief)

- Nodes communicate over a local wireless network using ESP-NOW.
- Readings move through the chain of nodes until they reach the **master node**.
- The master node has internet access and uploads the collected readings to a web application for storage and further processing.

## Demo

Video demo: https://drive.google.com/file/d/1uMhDBaZPWNIMETvrxpRy4zT_3VIhQVG0/view?usp=sharing

## Next steps

- Build a portal to access and manage each node’s settings
- Use long-range mode in the ESP-NOW communication protocol
- Add more support and flexibility to the firmware sensor interface to cover more sensors (like NPK sensor)
- Move from a line-based topology to a mesh-based network topology
