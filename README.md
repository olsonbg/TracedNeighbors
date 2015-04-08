TracedNeighbors
=====


## Installation

```bash
$ mkdir build
$ cd build
$ cmake ..
$ make -j4
$ src/TraceHBonds
```

To cross-compile, use:
```bash
$ cmake -DCMAKE_TOOLCHAIN_FILE=<Toolchain cmake file> ..
```

## Data file format

Lines starting with a '#' are treated as comments and ignored.
As an example, a few lines from a data file follows.

```
# Current Element : 12
# Atoms in Chain : 3
# Molecules : 2
# Unique forcefields : 2
# Times chain switched between Molecules (switching) : 1
# Periodic boundary conditions applied.
  19.4613   24.7503    8.3695 [O]  Molecule46  O12  o2h
  19.1470   25.4855    8.8586 [H]  Molecule46  H46  h1o
  18.4838   26.8268    9.4373 [O]  Molecule11  O2520  o2h
# Chain end-to-end distance: 2.5313


# Current Element : 13
# Atoms in Chain : 9
# Molecules : 2
# Unique forcefields : 3
# Times chain switched between Molecules (switching) : 2
# Periodic boundary conditions applied.
  30.9381   14.5898   12.0551 [O]  Molecule30  O7312  o2h
  30.3610   14.9652   11.4027 [H]  Molecule30  H7440  h1o
  30.2690   15.6199    9.9280 [O]  Molecule30  O7311  o2h
  29.8640   15.9833    9.1749 [H]  Molecule30  H7439  h1o
  29.5535   17.0631    7.5373 [O]  Molecule25  O6072  o2h
  29.9669   17.8535    7.5743 [H]  Molecule25  H6200  h1o
  31.5896   19.0999    6.5789 [O]  Molecule25  O6071  o1=
  32.2751   19.7160    6.1825 [H]  Molecule25  H6199  h1o
  33.0222   21.8475    5.3229 [O]  Molecule30  O7215  o2h
# Chain end-to-end distance: 10.1163
```

