# NeuroFuzzyControl
Software package development for assignments during the course AE51021 Neuro-Fuzzy Control.
- This repository follows [Google C++ Style Guide](https://google.github.io/styleguide/cppguide.html).
- This repository uses the `cmake` build system.

### Online Neural Network for predicting Daily Sun Spot Number
Implementation of Multilayer Feed Forward Network which is able to fit time-series Sun Spot Number using the data available at [SIDC, Belgium](www.sidc.be/silso/datafiles).

Current implementation capabilities:
- Any kind of user-defined topology definition.
- Backpropogation training.
- Windowing dataset for time-series based regression.
- Plotting using `numpy` and `matplotlib`.

Instructions:
1. Run `./configure`.
2. Finally, `./run.sh` in the parent directory.
3. Input the net topology and number of epochs.
4. The project should look like this finally on a linux system:

### Implementation of Dynamic Neural Units.
TODO:
- Recurrent Neural Net implentation.
- Inverse Dynamic Neural Adaptive Control using the DNU-4 and DNU-5 on a discrete system.

