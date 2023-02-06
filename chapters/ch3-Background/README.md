# Chapter 3 | Background

***Disclaimer:*** *This page offers supporting material for an Interaction Design course held at [KISD](https://kisd.de) in the winter term 2022/23. Visit the [landing page](https://github.com/KISDinteractive/fundamentals22w) of this course for more information.*

# 3 Background

Some historical background to AI helps to understand the current state of the art, and how and why certain areas have developed as they have.

## 3.1 A Brief History of AI

The history of speculation about robots is a long one. Consider this quote from **Aristoteles in 300 B.C.**

> "If every tool, when ordered, or even of its own accord, could do the work that befits it[...] then there would be no need of apprentices for the master workers, or of slaves for the lords."

The industrial Revolution and electricity fired the imagination even more. See the 3 laws of robotics by **Isaac Asimov in 1942**:

1. > A robot may not injure a human being or, through inaction, allow a human being to come to harm.

2. > A robot must obey orders given it by human beings except where such orders would conflict with the First Law.

3. > A robot must protect its own existence as long as such protection does not conflict with the First or Second Law.



We then discussed the main important events and phases in the history of AI from its emergence to the (still ongoing) so-called "Deep Learning Revolution", which has a completely new dynamic compared to the five decades before.

This is intended to give an overview of the subject and cannot reflect the entire picture of the development. Neither on a technical nor on a humanistic, societal level does this listing claim to be complete. The lower part of the timeline contains links to the previous course ["Interactive Systems [Fundamentals]"](https://github.com/KISDinteractive/fundamentals22w). Details of the main points are given below.

![rough_timeline](img/rough_timeline.jpg)



### Turing Machine

- Theoretical concept of the modern computer by the mathematician Alan Turing.
- Foundation of the research field of computer science. 
- See also ["Interactive Systems [Fundamentals]"](https://github.com/KISDinteractive/fundamentals22w) for details.

### Turing Test

- Paper in 1950 
- Alan Turing asked the question "Can machines think?" 
- proposed a test to tell human beings and computers apart
- Back in time: intellectual exploration of the topic of AI before it was even called "AI". 
- Today: a much debated topic
  - some claim to have fulfilled the (loosely described) aspects of the test
  - others propose updated, better definitions and consider it not yet satisfied. 
- 
- See also ["Interactive Systems [Fundamentals]"](https://github.com/KISDinteractive/fundamentals22w) for details.



### Dartmouth Conference

- in 1956: Dartmouth Conference (Dartmouth Summer Research Project on Artificial Intelligence)
- - Leading computer scientists, mathematicians and linguists met for an **8 week research project** on **solving tasks with computers**.
- Founded term: **Artificial Intelligence**
- Later they said, they were not happy with the term, but needed a name to distinguish "AI" from the concept of cybernetics...
- "The study is to proceed on the basis of the conjecture that every aspect of learning or any other feature of intelligence can, in principle, be described so precisely that a machine can be made to simulate it."
- "Lots of big words, terms were defined, goals were set, "AI" was founded as a research discipline**-
- (Of course) **no big breakthroughs**

→ beginning of the 1st Summer

### 1st Summer

- Dreams of the "General Problem Solver" → throw in difficult, wicked problems in; get a solution out

- Even general purpose robots were discussed
- Many different methods of AI at the same time
  - Predominant was the **Symbolic** AI paradigm: just plug in all the logics and conditions needed to solve problem
  - Only some research on **Subsymbolic AI** (non-human-readable). Inspired by the brain; build out of neurons that make up an abstract network.
- Some claimed: human intelligence in 3-8 years
- Great expectations, but by mid-1960s nothing of the promised was there.
- **Funding stopped. AI winter began**.

#### Shakey

See [video of "Shakey"](https://youtu.be/GmU7SimFkpU?t=105),  a mobile all-purpose robot that interacts (partially) autonomously with its environment.

#### Eliza

See [video of "Eliza"](https://youtu.be/GmU7SimFkpU?t=105), a chatbot that was able to use natural language to communicate with human beings.

### 2nd Summer

- Again: **great interest, funding, hype**

- This time the focus was on solving **practical problems**.

- Main topic: **domain-specific expert systems** (see below)
- **But:** systems were too expensive; difficult to keep up to date; no trust in the systems (e.g. by doctors)

- Failed again → **2nd AI Winter** started

- Difference to 1st summer: 1st was mainly about research, 2nd about business

#### Expert Systems

- Expert knowledge fed into databases
- Enter input -> get answer on complex topics
- e.g. medical treatments, travel booking chatbots

### Deep Blue vs. Kasparov

For a long time, the AI scene was quiet. Then, in 1997, came the big shock: a computer program won a chess game against world champion Garry Kasparov. A game that had been seen as something computers couldn't do or win due to their lack of creativity.

See [raw footage of Kasparov](https://www.youtube.com/watch?v=aNpv3LfCUa4), who obviously has a hard time believing that he just lost to an AI system.

### 3.2 Install Dependencies

We then installed some components and applications that we will be working with in the following sessions:

- **Python**: download from https://www.python.org/downloads/ (for windows choose the “installer”) and run the installer. **Note:** make sure the checkbox with "Add Python X.X to PATH" at the beginning of the installer is checked! If you missed that step and the check if python is installed (next section) fails, see ma post in spaces.
- **Arduino**: Download and run installer: https://www.arduino.cc/en/software 
- **Visual Studio Code** (not Visual Studio!): Download from [https://code.visualstudio.com](https://code.visualstudio.com/) and run installer
  (OR VSCodium from [https://vscodium.com](https://vscodium.com/) which is 100% Open Source and should work just as good)
  - install the extensions in VS Code :
    - Name: **Python**
      Id: ms-python.python
      Publisher: Microsoft
      [VS Marketplace Link](https://marketplace.visualstudio.com/items?itemName=ms-python.python)
    - Name: **Jupyter**
      Id: ms-toolsai.jupyter
      Publisher: Microsoft
      [VS Marketplace Link](https://marketplace.visualstudio.com/items?itemName=ms-toolsai.jupyter)

### Check if Python is installed locally

- Open a command-line interface.
  - **Mac:** open app "Terminal"
  - **Win:** open app "CMD", sometimes called "Command Line Prompt"
- Type `python --version` in the command line and hit the "Enter" key. 
- In case you see `Python` and some version number like `3.11.0`,  you now know that Python has been successfully installed.

### Accessing to Jupyter on the Server Cluster

For the duration of the course the participants were also given access (username and password) to the server cluster of the research project on jupyter.kitegg.de.

For learning Jupyter and doing some basic stuff, we can choose the "No GPU" option at the startup which saves a lot of energy!

## 3.3 Recap Python in Jupyter (in VSCode)

We have now learned the Jupyter interface step by step. This is an overview of the most important elements and shortcuts:

![Jupyter-UI](img/Jupyter-UI.png)



We then went through the basics of the programming language python by using a Jupyter. [Here you can find a Jupyter Notebook](src/Jupyter_Basics.ipynb) containing all the steps with detailed comments and explanations.
