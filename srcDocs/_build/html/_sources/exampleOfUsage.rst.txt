=================
Example of usage
=================


|graspi| is a command line tool.
To learn the set of |graspi| available settings, the user is encourages to
execute it in the command line with no arguments:

.. code-block:: bash

    ./graspi


The usage message will provide the list of parameters that can be used. |graspi|
accepts input data in two formats: graph and array. If graph is constructed
externally data can be inputted in the graph format, for example:

.. code-block:: bash

    ./graspi -g <INPUT_FILE.graphe>

If data is structured (e.g., image), the following options are available

.. code-block:: bash

    ./graspi -a <INPUT_FILE.txt> (row-major order) -s <pixelSize> (default 1) -p <{0,1}> (default 0-false) -n <{2,3}> (default 2-{D,A}) -r path where store results (default ./)



|graspi| requires one one mandatory input parameter: the name of the input file ``<INPUT_FILE>``. The remaining parameters are optional, and have the default values set up, if the parameter is not explicitly provided.

* ``-a <INPUT_FILE.txt>`` (row-major order)  this is the option to input information about structured data. With this assumption, neighborhood of each voxel/pixel can be determined as the graph is constructed.
* ``-g <INPUT_FILE.graphe>`` this is the option to input information about the unstructured data. Input file must provide all information about the graph, this means that neighborhood of each vertex in the graph needs to be determined externally. Meta-vertices and the associated edges need to be defines in the input file. When this option is called, |graspi| reads the text file and initializes the set of vertices and edges from the input file, and need to be in agreement with these defined in the package for a given usage case.
* ``-s <pixelSize>`` (default 1) this option sets the size of the pixel to compute the length of the shortest paths. If unspecified, all results will be outputted in terms of number of pixels, and need to be rescaled for dimensional analysis.
* ``-p <{0,1}>`` (default 0-false) this option specifies if periodicity on the side faces is to be applied (valid only morphology inputted as the array option ``-a``).
* ``-n <{2,3}>`` default 2 (black and white, electron-donor and electron accepting material) -- this option specifies the number of phases. For three-phase morphology (option ``-n 3``, black, white and grey vertices are read, that correspond to electron-donor, electron-accepting and mixed phase material, respectively).
* ``-r path`` -- this option specifies where store result (default ``./``). This option allows to specify where text files with results will be saved.

|graspi| computes the set of descriptors that are relevant for the morphology in organic solar cells. See
:ref:`List of Descriptors <listOfDescriptors>` section.
