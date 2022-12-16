# Exercise Manager

A basic CLI program to manage programming exercises, written in C.

## Motivation

Back when I learnt C, near the end of the year 2021, I wanted to implement almost every algorithm every algorithm, every exercise's solution, every basic function that I knew of — just about everything — in it. The language felt so powerful that I wanted to spend a lot of my time working in it.

That's when I felt the need of an exercise-managing application.

One that could simply hold a collection of many exercises along with some related information such as the exercises's difficulty level and the concepts used in it. In this way, I knew that if ever I wanted to practice C again in the future, I'd be able to quickly search for an exercise with a given difficulty level or one implementing a given concept.

And so enumerating amongst my choices of a language to use, i.e. PHP, JavaScript, Python and even C, I eventually came to the conclusion of using C. _What could've been better than creating an application in C? Clearly nothing._ 😊

## How it works?

The way this application works is pretty elementary. The main commands are `add`, `update`, `show`, and `search`. Each can be called with either an `e` (for 'exercise') or a `c` (for 'concept') following it.

Here are the descriptions of these commands:

- `add` is used to add a given exercise or concept.
- `update` is used to update a given exercise or a given concept.
- `show` is used to show a given concept or exercise.
- `search` is the cornerstone of the application — it allows us to perform the most important function of the application, i.e. searching.

For example, `show e` serves to show a given exercise. Similarly, `add c` serves to add a new concept.

When the application is first compiled, and there's no `data.bin` file, we start off with an absolutely empty list of exercises and concepts. Then, based on what concepts/exercises we want, we add them using the `add` command.


