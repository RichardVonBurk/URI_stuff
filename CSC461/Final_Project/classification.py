import numpy as np
import matplotlib.pyplot as plt
import sklearn.model_selection
import sklearn.metrics
import math
import functools
import operator
import seaborn as sns

import features
import models


def split_train_test(feature_table):
    # Split our data to training and test sets
    splitter = sklearn.model_selection.StratifiedShuffleSplit(n_splits=1,
            test_size=0.3, random_state=42)
    splits = list(splitter.split(feature_table, features.metadata['target']))[0]
    train_ind, test_ind = splits

    Xtrain = np.array(feature_table[train_ind].as_array().tolist())
    Ytrain = np.array(features.metadata['target'][train_ind].tolist())

    Xtest = np.array(feature_table[test_ind].as_array().tolist())
    Ytest = np.array(features.metadata['target'][test_ind].tolist())

    return Xtrain, Xtest, Ytrain, Ytest

def to_numpy_arrays(feature_table):
    Xdata = np.array(feature_table.as_array().tolist())
    Ydata = np.array(features.metadata['target'].tolist())
    return Xdata, Ydata

def create_confusion_matrix(Ytest, Ypred):
    return sklearn.metrics.confusion_matrix(Ytest, Ypred,
            labels=features.labels)

def get_confusion_matrix_plot(cm):
    cm = cm.astype('float') / cm.sum(axis=1)[:, np.newaxis]
    annot = np.around(cm, 2)
    fig, ax = plt.subplots(figsize=(9,7))
    sns.heatmap(cm, xticklabels=features.labels, yticklabels=features.labels,
            cmap='Blues', annot=annot, lw=0.5)
    ax.set_xlabel('Predicted Label')
    ax.set_ylabel('True Label')
    ax.set_aspect('equal')
    return plt

def show_confusion_matrix(confusion_matrix):
    plt = get_confusion_matrix_plot(confusion_matrix)
    plt.show()

def save_confusion_matrix(confusion_matrix, name):
    plt = get_confusion_matrix_plot(confusion_matrix)
    plt.savefig(f"{name}.png", bbox_inches='tight')

def k_fold_cross_validate(Xdata, Ydata, k, model):
    group_kfold = sklearn.model_selection.GroupKFold(k)
    sum_accuracy = 0.0
    size = Ydata.shape[0]
    splitsize = math.floor(size/k)
    groups = functools.reduce(lambda x, y: np.concatenate((x, y)),
            [np.full(splitsize, i, dtype=np.int32) for i in range(k-1)])
    groups = np.concatenate((groups, np.full(size - len(groups),k - 1)))
    for train_index, test_index in group_kfold.split(Xdata, Ydata, groups):
        model.train(Xdata[train_index], Ydata[train_index])
        Ypred = model.test(Xdata[test_index])
        accuracy = sklearn.metrics.accuracy_score(Ydata[test_index], Ypred)
        sum_accuracy += accuracy
    return sum_accuracy / k

def k_fold_confusion_matrix(Xdata, Ydata, k, model):
    group_kfold = sklearn.model_selection.GroupKFold(k)
    sum_confusion = None
    size = Ydata.shape[0]
    splitsize = math.floor(size/k)
    groups = functools.reduce(lambda x, y: np.concatenate((x, y)),
            [np.full(splitsize, i, dtype=np.int32) for i in range(k-1)])
    groups = np.concatenate((groups, np.full(size - len(groups),k - 1)))
    for train_index, test_index in group_kfold.split(Xdata, Ydata, groups):
        model.train(Xdata[train_index], Ydata[train_index])
        Ypred = model.test(Xdata[test_index])
        confusion = sklearn.metrics.confusion_matrix(Ydata[test_index], Ypred,
                labels=features.labels)
        if sum_confusion is None:
            sum_confusion = np.zeros(confusion.shape)
        sum_confusion += confusion
    return sum_confusion / k

def select_best_model(Xdata, Ydata, models):
    avg_accuracies = [(i, k_fold_cross_validate(Xdata, Ydata, 4, model)) for
            i, model in enumerate(models)]
    print(avg_accuracies)
    return max(avg_accuracies, key=operator.itemgetter(1))


allfeatures = features.compute_or_read_features()
Xdata, Ydata = to_numpy_arrays(allfeatures)

models = [models.RandomForest(200, 'gini'), models.LogisticRegression(),
        models.SVMNonLinear('rbf'), models.SVMNonLinear('sigmoid'),
        models.NeuralNet(), models.KNN()]
#best = select_best_model(Xdata, Ydata, models)
#print(best)

for model in models:
    cm = k_fold_confusion_matrix(Xdata, Ydata, 4, model)
    save_confusion_matrix(cm, model._name)
    print(f"Confusion matrix for {model._name} saved")
