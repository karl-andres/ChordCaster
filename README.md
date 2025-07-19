# About the Project

ChordCaster is an Arduino-based assistive device designed to help visually and hearing-impaired individuals play guitar independently. Originally created for Kimberly, a woman with Usher Syndrome, ChordCaster allows real-time chord progression playback using tactile buttons and audio feedback — removing the need for visual interfaces or multiple apps.

---

## Problem Statement

Kimberly, who experiences tunnel vision, limited color perception, and hearing difficulties due to Usher Syndrome, wanted to enjoy playing the guitar without relying on visual cues. Our goal was to enhance her ability to play music in a safe, independent, and joyful way.

---

## Features

- **Real-time audio chord playback** via DFPlayer Mini
- **Illuminated tactile buttons** with unique shapes for accessibility
- **Adjustable tempo & volume** in real-time
- **Physical feedback** (MP3 prompts for song name, chord name, and strumming pattern)
- **Restart and next song controls**
- **Compact & safe 3D printed enclosure**

---

## Hardware Components

- Arduino UNO
- DFPlayer Mini MP3 Module
- Breadboard & jumper wires
- Speaker
- 1000 Ohm Resistor
- 6 Push Buttons
- Custom 3D Printed Case

---

## Code Features

- Function pointer array for song modularity
- Debounced button handling (tempo, volume, restart, next)
- Dynamic tempo & volume control
- Song restart capability
- MP3 track mapping using predefined constants

---

## Song Playback Logic

Each song is a separate function containing:

- Audio prompts for song name and strumming pattern
- Strumming pattern playback
- Chord progression (notes)
- Track playback with debounce-safe interrupt checks

---
