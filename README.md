
# 🧠 🔢 Math Game - C++

A dynamic **Math Quiz** console game written in C++.

The player answers a selected number of math questions based on chosen difficulty levels and operation types. The program dynamically generates questions, evaluates answers, and displays results with visual feedback.

## 🎮 Features

- Choose the number of rounds (1 to 10).
- Select Difficulty Level:
  * `1` → Easy (Numbers 1 – 10)
  * `2` → Medium (Numbers 10 – 50)
  * `3` → Hard (Numbers 50 – 100)
  * `4` → Mix (Random difficulty per question)
- Select Operation Type:
  * `1` → Addition (`+`)
  * `2` → Subtraction (`-`)
  * `3` → Multiplication (`*`)
  * `4` → Division (`/`)
  * `5` → Mix (Random operation per question)
- Changes the console background color depending on answer accuracy:
  * 🟢 Green → Right Answer / PASS
  * 🔴 Red + Audio Beep → Wrong Answer / FAIL
- Displays final statistics (Right answers, Wrong answers, Level, Operation).
- Replay option to play again without restarting the executable.

## 📐 Difficulty & Operations Setup

| Setting | Options | Behavior |
| --- | --- | --- |
| **Level** | Easy / Med / Hard / Mix | Sets the range of randomly generated operands |
| **Operation** | Add / Sub / Mul / Div / Mix | Determines the arithmetic rule applied |
| **Mix Mode** | Level or Op | Randomizes selection dynamically for each round |

## 🔄 Program Algorithm

```mermaid
flowchart TD
    A([Start]) --> B[Initialize random seed: srand]
    B --> C[Reset Screen & Set Default Color]
    C --> D[Get Number of Rounds: HowManyQuestion]
    D --> E[Select Game Level: LevelQuestion]
    E --> F[Select Operation Type: OpTypeQuestion]
    F --> G[Start Round Loop]
    G --> H[Generate Question & Calculate Correct Answer]
    H --> I[Get User Answer]
    I --> J{Is Answer Correct?}

    J -->|Yes| K[RightAnswers++<br>Green Screen]
    J -->|No| L[WrongAnswers++<br>Red Screen + Beep]

    K --> M{More rounds?}
    L --> M

    M -->|Yes| G
    M -->|No| N[ShowGameOverScreen - PASS or FAIL]
    N --> O[ShowFinalGameResults]
    O --> P{Play Again?}

    P -->|Yes| C
    P -->|No| Q([End])
