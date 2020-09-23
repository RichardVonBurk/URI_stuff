import torch
import torch.nn as nn

from constants import *


class LinearSVM(nn.Module):
    """
    A torch module representing the basic linear version of a support vector
    machine
    """

    def __init__(self):
        # Call the superclass constructor
        super(LinearSVM, self).__init__()
        # Compute input size and initialize the linear layer
        in_size = WIDTH * HEIGHT * CHANNELS
        self.linear = nn.Linear(in_size, CLASSES)

    def forward(self, x):
        # Pass input through the linear layer and return
        return self.linear(x)