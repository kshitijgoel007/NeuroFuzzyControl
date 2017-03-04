# NeuroFuzzyControl
Software package development for assignments during the course AE51021 Neuro-Fuzzy Control.
- This repository follows [Google C++ Style Guide](https://google.github.io/styleguide/cppguide.html).
- This repository uses the `make` tool.

### Online Neural Network for predicting Daily Sun Spot Number
Implementation of Multilayer Feed Forward Network which is able to fit time-series Sun Spot Number using the data available at [SIDC, Belgium](www.sidc.be/silso/datafiles).

Current implementation capabilities:
- Any kind of user-defined topology definition.
- Backpropogation training.
- Windowing dataset for time-series based regression.
- Plotting using `numpy` and `matplotlib`.

Instructions:
1. `make`
2. `chmod +x run.sh`
3. `./run.sh`
4. Input the net topology and number of epochs.

### Dynamic Neural Units based control of satellites.
TODO:
- Real-time plotting using an appropriate plotting tool.
- Recurrent Neural Net implentation.
- Dynamic Neural Net implementation for Satellite Control.
