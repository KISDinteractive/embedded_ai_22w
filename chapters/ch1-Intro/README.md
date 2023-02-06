# Chapter 1 | Intro

***Disclaimer:*** *This page offers supporting material for an Interaction Design course held at [KISD](https://kisd.de) in the winter term 2022/23. Visit the [landing page](https://github.com/KISDinteractive/fundamentals22w) of this course for more information.*

# 1.1 Intro & Formalities

## Who is in?

We have agreed on nine participants according to the course selection list.

## Who am I (the teacher)?

- [Jakob Kilian](https://www.th-koeln.de/personen/jakob.kilian/) | he/his
- Research Fellow in KITeGG / "AI and Design" project since 02/2022
- Living Objects Lab (F02) at KISD

## Formalities

- Meetings on Mondays from 10:00 – 12:00 
- 15 min break at 11:00
- 11 meetings (today, 14.11 – 30.01)

## Ground Rules

- pls send a mail if you cannot come
- pls study material on GitHub if you miss a session
- pls be in time (solidarity) – we agreed on 5 mins "on-time"-tolerance
- We want to achieve a space of **psychological safety**
  - We treat each other with kindness and respect
  - We consider our different backgrounds / we don't judge people if they don't know sth.
  - We help each other
  - We give constructive feedback
- We try to speak English whenever non-native speakers can join in the conversation
- We ask questions when we don't understand something. Better early than late

# 1.2 Course Content

In a short introduction round we discussed the particpant's expectations of the course and understanding of "AI". We noted some of the statements on the whiteboard for a later review.

## What does "Artificial Intelligence" ("AI") mean?

- No is no such "thing" as "THE AI"

- Always a set of tools for solving specific tasks – but sometimes even with "superhuman" performance → **Narrow AIs**
- We are not even close to "AI" with human level of "intelligence" (General AI / AGI):
  - Generalisation
  - Transfer
  - Integration
- Discourse should be about both current and future AI systems

→ *Be vigilant and critical, but do not fall into euphoria or panic!*

## What Exactly is This Course About?

We discussed the difference between the **cloud** and its so-called **edge**, where laptops, smartphones but also smaller devices such as the "Internet of Things" and various end devices are located.

![cloud-edge](img/cloud-edge.jpg)

This course is about implementing AI on the **edge** side, whereas many AI applications run on big servers in the **cloud**. Sometimes we may fake things and still use the cloud anyway to test prototypes.

### Some Terms we will use:

- **Machine Learning / ML =** AI variant | Use of data to improve a machine's performance on tasks

- **Deep Learning / DL =** Family of ML methods using artificial neural networks

- **Edge AI =** not running on servers (the cloud)

- **Embedded AI =** AI that runs on »embedded« systems such as microcontrollers

- **TinyML =** ML for tiny computers / microcontrollers

- **AIoT, TinyAI, ...** 

## What is a Microcontroller / MCU?

Small computer on a single chip that has some special characteristics:

- small, cheap, easy to get

- (very) little memory (kilobytes)

- less computing resources

- **Interfaces to control:** 
- peripherals
  
- electrical & electronic parts (e.g. Sensors)
  
- mechanical parts

*Note: There are in-between / hybrid cases, that are actually computers but with some capabilities of MCUs such as e.g. the Raspberry Pi or the powerful NVIDIA Jetson Orin

# Example ML with an ESP32

We then showed how easy it actually is to train a network when using tools. This time we used ["Teachable Machine" from Google.](https://teachablemachine.withgoogle.com/train/image) 

- [Link to the code file in the author's repository](https://github.com/fustyles/Arduino/blob/master/ESP32-CAM_Tensorflow.js/ESP32-CAM_teachablemachine/ESP32-CAM_teachablemachine.ino)
- [Short tutorial by the author showing the functionality](https://www.youtube.com/watch?v=Sn7AwpGFXLw)
