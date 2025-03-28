# ListStepper Plugin

## Overview

The ListStepper is a flexible software plugin for sequentially stepping through user-defined numerical values. Each time the plugin is triggered, it outputs the next value in a defined list. This provides a powerful mechanism for generating predictable sequences of values in your experimental workflow.

## Key Features

- **Sequential Value Output**: Step through a list of values one by one with each trigger
- **Customizable Value Lists**: Define your list through direct text input or automated generation
- **Equally Spaced Value Generation**: Create linearly spaced values between a start and end point
- **Line Randomization**: Shuffle the order of lines in your list while keeping each line intact
- **Adjustable Stepping Rate**: Configure how many triggers are needed to advance to the next value
- **Delayed Output**: Add a time delay between receiving a trigger and outputting the value

## User Interface

The plugin interface consists of the following components:

### Main Controls
- **Trigger Input Bucket**: Connect a parameter to trigger the stepper
- **Output Bucket**: Provides the current value in the sequence
- **Delay (s)**: Time delay between receiving a trigger and outputting the next value
- **Trig / N**: Number of triggers required to advance to the next value
- **Index**: Current index in the list (read-only)
- **Num Values**: Total number of values in the list (read-only)
- **Reset Button**: Resets the sequence to the beginning
- **Enable Checkbox**: Enable/disable the stepper

### Sequence Generator Section
- **Start**: Start value for equally spaced sequence generation
- **End**: End value for equally spaced sequence generation
- **Num Points**: Number of points to generate in the sequence
- **Generate Button**: Click to generate an equally spaced sequence
- **Shuffle Button**: Click to randomize the order of lines in the list

### Value List
- Text editor for viewing and manually editing the list of values

## Usage Instructions

### Basic Operation

1. Define a list of values in the text editor (bottom section)
   - Values can be separated by commas, spaces, or newlines
   - Invalid entries (non-numeric) are automatically ignored
2. Connect a parameter to the "Trigger" bucket
3. Each time the trigger parameter updates, the plugin will output the next value in the sequence

### Generating Equally Spaced Values

1. Set the desired "Start" and "End" values
2. Specify the number of points in "Num Points"
3. Click the "Generate" button
4. The plugin will generate equally spaced values with one value per line

### Randomizing the List

1. Populate the list with values (either manually or using the generator)
2. Click the "Shuffle" button
3. The lines in the list will be shuffled, keeping each line intact

## Advanced Features

### Multiple Triggers Per Step

The "Trig / N" parameter lets you define how many trigger events are required to advance to the next value. This is useful for:
- Synchronizing with multi-cycle processes
- Creating sub-step sequences
- Implementing divider functionality

### Delayed Output

The "Delay" parameter adds a time delay between receiving a trigger and outputting the next value, useful for:
- Compensating for system delays
- Creating time-dependent sequences
- Adding pause intervals in automated sequences

## Notes

- The plugin handles invalid entries gracefully, ignoring any text that cannot be converted to a number
- When the end of the list is reached, the sequence wraps around to the beginning
- The "Reset" button allows you to start over from the beginning of the sequence
- The list values are preserved when the experiment is saved

## Examples

1. **Stepped Calibration**: Create a sequence of calibration values that progress with each trigger
2. **Experimental Conditions**: Define different experimental parameters to cycle through
3. **Scan Points**: Generate scan coordinates or setpoints for automated measurement procedures
4. **Random Testing**: Define test points and then randomize their order to reduce systematic errors 