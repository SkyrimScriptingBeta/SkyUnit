![SkyUnit](resources/images/SkyUnit.png)

# SkyUnit

~ **_Skyrim Acceptance Testing Framework_** ~

## TODO

- [ ] xxx

## Priorities

My immediate priority is a tool which can assert that:

> _Scenario: the game runs without crashing_

**Given** Skyrim is launched with a specific set of mods  
**When** the game launches  
**Then** the game does not crash

> _Scenario: a mod or SKSE plugin successfully returns a value_

**Given** Skyrim is launched with a specific set of mods  
**When** a certain Papyrus function is called  
**Then** the function returns the expected value

## Why?

I want this as part of build pipelines on GitHub
for my distributions of CommonLibSSE/VR and my own plugins.

e.g. I want Jenkins setup on a computer to execute this and integrate it with GitHub Actions.

# Design (_thinking out loud..._)

## Declaring tests

SkyUnit needs to know if there are any tests to run.

If none, it should not run.

### Ideas

1. Implicit discovery based on SKSE plugin and Papyrus script names
2. Explicit declaration in a file like JSON or YAML or INI
