# Hopfield-Network-
Hopfield Network 

**HOPFIELD ASSOCIATIVE MEMORY**

The Hopfield Network is a single layered and recurrent network, the neurons are fully connected, i.e every neuron is connected to every other neuron. The neurons are not connected to itself.

Given two neurons I and j there is a connectivity weight Wij between them. And the connections have following restrictions:

1. Wij=Wji (Connections are symmetric)

2. Wii=0 (No unit has connection with itself)

The network input function of each neuron is the weighted sum of the outputs of all other neurons.

The connectivity Weight matrix can be calculated using following formula:

**BINARY INPUT**

When the Hopfield network takes Binary Input patterns say s(p) = s1(p),s2(p) .. and so on.

The weight matrix W={Wij} is given by,

![](RackMultipart20211215-4-117rgfn_html_c2e2e17a7b1c6411.png)

For (i !=j) and Wii=0.

**BIPOLAR INPUT**

For Bipolar Input patterns say s(p) = s1(p),s2(p) .. and so on.

The weight matrix is given by ,

![](RackMultipart20211215-4-117rgfn_html_24178198fb906ef8.png)

For (i !=j) and Wii=0.

**UPDATING**

The behaviour of a hopfield network can depend on the update order:

In **Asynchronous** updating a random node is picked and updated. Computations always converge if neurons are updated sequentially. It reaches a stable state in finite number of steps regardless of the update order.

**Synchronous** updating means that at time step (t+1) every neuron is updated based on network state at time step t. Computations can oscillate if neurons are updated in parallel. When the computations oscillate, no stable state is reached. Hence we can say that it enters a cycle and it cannot reach a stable state or it does not converge.

**Updating one unit in Hopfield network** is performed using following rule,

![](RackMultipart20211215-4-117rgfn_html_ce57391f99437b4d.png)

Where,

Wij  is the strength of the connection weight from unit j to unit i (the weight of the connection).

si is the state of unit i.

theta is the threshold of unit i.

**Steps to Use GUI:**

**Method 1** :

1. Import the data in Inputs.txt file by clicking the **IMPORT DATA** button. The Input vectors will be displayed in the list box below.

2. Click on the **TRAIN** button.

3. Enter the TESTvector in the second text box.

4. Click **SUBMIT** and you can see the **OUTPUT** below.

5. To enter the **TEST** Pattern again, simply edit the test vector text box and press the **SUBMIT** button.

6. Press **CLEAR ALL** to clear everything.

**Method 2:**

1. Enter Input Vector in the first text box. Click on **ENTER NEXT ROW** Button. Enter another Input Vector Again if you want and click on Enter Next row Button. The Input vectors will be displayed in the list box below.

2. Follow Steps 3 to 6 same as above.

**C++ Program**

1. A text file named Inputs.txt is created where input vectors are entered separated by comma in the following way:

**1,1**

**0,0**

2. In the program, **GetInputFromFile()** function is used to store the inputs from from the text file into a single vector.

3. If the inputs are Binary , it is converted into Bipolar and the weight matrix is calculated using the formula for weight matrix for Bipolar input pattern as stated above using function **CalculateWeightMatrix().**

4. The user is asked for test pattern , and the user must enter input pattern separated by comma in the following way:

**1,0**

5. The weight matrix is used to calculate the output HAM vector with synchronous update method as we need to see the oscillating behaviour of Hopfield Network. In this method, each neuron is updated simultaneously using the updating rule stated above and thus HAM output is obtained. **CalculateHAMOutput()** function is used for this method.

6. The previous two HAM outputs are stored in a vector using the function **StoreOutput()**. If the recent output matches with any of the HAM outputs stored in this vector then the output is displayed. And if there is a cycle, the output is displayed accordingly. The comparison with previous outputs is done using function **Compare()**.

7. Another test pattern can be tested by simply editing the Test pattern text box and by clicking Submit in the GUI.

8. For the example of T[1,1] and T[-1,-1], for Test input of [1,-1] the hopfield network never leads to a stable state as none can be attracted to nearby points and thus and oscillates between two states [1,-1] and [-1, 1].

Note: Excel file testing\_report.xls shows the testing inputs and outputs carried out on the program.
