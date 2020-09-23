import torch
import torchvision
import torchvision.transforms as transforms
import torch.optim as optim
import sys

from linear_svm import LinearSVM
from constants import *

# Normalize data
transform = transforms.Compose(
        [transforms.ToTensor(),
            transforms.Normalize((0.4914, 0.4822, 0.4465),
                (0.247, 0.243, 0.261))])


# Load training data
trainset = torchvision.datasets.CIFAR10(root='./data', train=True,
        download=True, transform=transform)
trainloader = torch.utils.data.DataLoader(trainset, batch_size=4, shuffle=True,
        num_workers=2)

# Load test data
testset = torchvision.datasets.CIFAR10(root='./data', train=False,
        download=True, transform=transform)
testloader = torch.utils.data.DataLoader(testset, batch_size=4, shuffle=False,
        num_workers=2)

import matplotlib.pyplot as plt
import numpy as np

if len(sys.argv) > 1:
    # First argument is the learning rate
    DEFAULT_LEARNING_RATE = float(sys.argv[1])
if len(sys.argv) > 2:
    # Second argument is the number of epochs
    EPOCHS = int(sys.argv[2])


def multiclass_hinge_loss(outputs, actuals):
    delta = 1
    N = len(actuals)

    # Turn y from a one-dimensional (N) tensor to a two-dimensional (N * 1)
    # tensor.
    y_column = actuals.view(-1, 1)
    # Stack the y's such that it is of size (N * CLASSES), with every row
    # containing the same element (the index of the correct class).
    y_allclasses = torch.gather(y_column, 1, torch.zeros(N, CLASSES,
        dtype=torch.long))
    # Now, from the model's outputs create a tensor containing only the
    # predicted score for the correct output class in every class' position (we
    # use this in the next step of calculating loss).
    correct_class_outputs = torch.gather(outputs, 1, y_allclasses)

    # Subtract the correct_class_outputs from outputs, which essentially
    # computes the hinge loss for every class. For multi-class hinge loss we
    # need to subtract the score for the correct class from the score for each
    # class (and add the margin size delta). We clamp that with a zero minimum
    # to get the actual 'hinge' part of the loss. Note that even the correct
    # class for each instance will have a loss of delta, but we'll fix that
    # later.
    losses = torch.clamp(outputs - correct_class_outputs + delta, min=0)
    # Sum all those losses to get a grand total across all classes and
    # instances.
    total_loss = torch.sum(losses)
    # Remove the delta added to the loss for the correct class for each instance
    # by subtracting the necessary amount.
    total_loss -= N * delta
    return total_loss

def train_batch(X, y, model, optimizer, c=DEFAULT_C):
    # Convert to float tensors
    # X = torch.FloatTensor(X)
    # y = torch.FloatTensor(y)

    # Set the model to "training mode".
    model.train()

    # Set the initial gadients to zero.
    optimizer.zero_grad()
    # Make a forward-pass to obtain an output.
    outputs = model(X)

    # Get the loss for these predictions
    loss = multiclass_hinge_loss(outputs, y)
    # Add the l2 regularization term
    loss +=  c * torch.mean(model.linear.weight ** 2)
    # Do the backpropagation step
    loss.backward()
    # Update weights
    optimizer.step()
    return loss

# Initialize our model
model = LinearSVM()

l = DEFAULT_LEARNING_RATE
# Create a Stochastic Gradient Descent optimizer to optimize the model's
# parameters using the given learning rate.
optimizer = optim.SGD(model.parameters(), l)

# Initialize the 'scheduler' which dynamically updates our learning rate
scheduler = torch.optim.lr_scheduler.ReduceLROnPlateau(optimizer)

print("Starting training with learning rate {} and {} epochs".format(
    DEFAULT_LEARNING_RATE, EPOCHS))

for epoch in range(EPOCHS):
    print("Epoch", epoch)
    total_loss = 0
    # Loop through the mini-batches, training the SVM on each of them.
    for i, data in enumerate(trainloader, 0):
        # Separate the input data from their labels.
        inputs, labels = data
        # Get the mini-batch size, the first dimension of our input tensor.
        N = inputs.size()[0]
        # The 'inputs' tensor is 4 dimensional right now (BATCH_SIZE * CHANNELS
        # * WIDTH * HEIGHT). We flatten out all dimensions after the first so
        # that each data instance is a 1-dimensional array.
        inputs = inputs.view(N, -1)
        total_loss += train_batch(inputs, labels, model, optimizer)
    scheduler.step(total_loss)

print("Evaluating trained model on test data")

correct = 0
total = 0
with torch.no_grad():
    for data in testloader:
        # Separate the input data from their labels.
        images, labels = data
        # Get the mini-batch size, the first dimension of our input tensor.
        N = inputs.size()[0]
        # The 'inputs' tensor is 4 dimensional right now (BATCH_SIZE * CHANNELS
        # * WIDTH * HEIGHT). We flatten out all dimensions after the first so
        # that each data instance is a 1-dimensional array.
        images = images.view(N, -1)
        # Make a forward pass (predict).
        outputs = model(images)
        # Get the prediction with the highest score.
        _, predicted = torch.max(outputs.data, 1)
        # Update the total and the correct counts
        total += labels.size(0)
        correct += (predicted == labels).sum().item()

print('Accuracy of the network on the 10000 test images: %d%%' % (
    100 * correct / total))