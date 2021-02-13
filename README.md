# MNIST Classification in C
This tool allows the training and testing of a simple MLP (Multilayer Perceptron) network. The specific network is trained, using the MNIST dataset, to be able to classify hand-written digits.

## Compilation
```
$ make
```

## Usage
The `dataset` folder is required to run the program. This folder contains all the MNIST images and has to be placed into the root folder of the project:
```
.
├── dataset
│   ├── training
│   │   ├── 0
│   │   ├── 1
│   │   ├── 2
│   │   ├── 3
│   │   ├── 4
│   │   ├── 5
│   │   ├── 6
│   │   ├── 7
│   │   ├── 8
│   │   └── 9
│   └── testing
│       ├── 0
│       ├── 1
│       ├── 2
│       ├── 3
│       ├── 4
│       ├── 5
│       ├── 6
│       ├── 7
│       ├── 8
│       └── 9
├── main.c
├── images_handler.h
├── images_handler.c
├── neural_network_handler.h
├── neural_network_handler.c
├── stb_image.h
└── Makefile
```

Run the program with:
```
$ ./MNIST_classification_in_C -l 1 -n 64 -e 10 -lr 0.001
```
where:
* The `-l` argument sets the number of hidden layers.
* The `-n` argument sets the number of neurons of each hidden layer.
* The `-e` argument sets the number of training epochs.
* The `-lr` argument sets the specific learning rate used during training.

## Output
```
Reading ./dataset/training/0/ files.
Reading ./dataset/training/1/ files.
Reading ./dataset/training/2/ files.
Reading ./dataset/training/3/ files.
Reading ./dataset/training/4/ files.
Reading ./dataset/training/5/ files.
Reading ./dataset/training/6/ files.
Reading ./dataset/training/7/ files.
Reading ./dataset/training/8/ files.
Reading ./dataset/training/9/ files.
Reading ./dataset/testing/0/ files.
Reading ./dataset/testing/1/ files.
Reading ./dataset/testing/2/ files.
Reading ./dataset/testing/3/ files.
Reading ./dataset/testing/4/ files.
Reading ./dataset/testing/5/ files.
Reading ./dataset/testing/6/ files.
Reading ./dataset/testing/7/ files.
Reading ./dataset/testing/8/ files.
Reading ./dataset/testing/9/ files.
Shuffling samples.
Training.
Epoch: 1/10, accuracy: 0.759783, loss: 1.746183
Epoch: 2/10, accuracy: 0.861150, loss: 0.689133
Epoch: 3/10, accuracy: 0.883467, loss: 0.566282
Epoch: 4/10, accuracy: 0.896183, loss: 0.498846
Epoch: 5/10, accuracy: 0.905183, loss: 0.453839
Epoch: 6/10, accuracy: 0.912250, loss: 0.420292
Epoch: 7/10, accuracy: 0.917500, loss: 0.393635
Epoch: 8/10, accuracy: 0.922050, loss: 0.371836
Epoch: 9/10, accuracy: 0.925733, loss: 0.353492
Epoch: 10/10, accuracy: 0.929567, loss: 0.337611
Testing.
Accuracy: 0.926500, loss: 0.354491
```
