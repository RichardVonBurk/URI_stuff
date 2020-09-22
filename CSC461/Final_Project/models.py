import sklearn.linear_model
import sklearn.neural_network
import sklearn.ensemble
import sklearn.svm
import numpy as np

class Model:

    def train(self, Xtrain, Ytrain):
        pass

    def test(self, Xtest):
        if self._classifier is not None:
            return self._classifier.predict(Xtest)
        else:
            raise Exception("test() called without training")


class RandomForest(Model):

    def __init__(self, n_estimators, criterion):
        self._n_estimators = n_estimators
        self._criterion = criterion
        self._classifier = None
        self._name = "random_forest"

    def train(self, Xtrain, Ytrain):
        self._classifier = sklearn.ensemble.RandomForestClassifier(
                n_estimators=self._n_estimators, criterion=self._criterion,
                oob_score=True, n_jobs=-1, random_state=42, verbose=1,
                class_weight='balanced', max_features='sqrt')
        self._classifier.fit(Xtrain, Ytrain)


class LogisticRegression(Model):

    def __init__(self):
        self._name = "logistic_regression"

    def train(self, Xtrain, Ytrain):
        self._classifier = sklearn.linear_model.LogisticRegression(
                random_state=0)
        self._classifier.fit(Xtrain, Ytrain)


class SVMNonLinear(Model):

    def __init__(self, kernel='poly'):
        self._kernel = kernel
        self._name = f"svm_{kernel}"

    def train(self, Xtrain, Ytrain):
        self._classifier = sklearn.svm.SVC(kernel=self._kernel, degree=2)
        self._classifier.fit(Xtrain, Ytrain)


class NeuralNet(Model):

    def __init__(self):
        self._name = "neuralnet"

    def train(self, Xtrain, Ytrain):
        #self._classifier = sklearn.neural_network.MLPClassifier((100,40),
        #        activation='logistic')
        self._classifier = sklearn.neural_network.MLPClassifier()
        self._classifier.fit(Xtrain, Ytrain)

    def test(self, Xtest):
        return self._classifier.predict(Xtest)

class KNN(Model):

    def __init__(self):
        self._name = "knn"

    def train(self, Xtrain, Ytrain):
        self.classList = list(set(Ytrain))
        self.classCount = len(self.classList)

        self.Xmodel = np.zeros((self.classCount, Xtrain.shape[1]))
        self.Ymodel = np.zeros((self.classCount, 2))

        self.Ymodel[:,0] = self.classList

        for i in range(len(Xtrain)):
            exampleClass = Ytrain[i]
            model_index = self.classList.index(exampleClass)
            for j in range(len(Xtrain[i])):
                self.Xmodel[model_index,j] += Xtrain[i,j]
            self.Ymodel[model_index, 1] += 1

        for i in range(len(self.Xmodel)):
            self.Xmodel[i, :] /= self.Ymodel[i, 1]


    def test(self, Xtest):
        predictions = np.zeros((Xtest.shape[0],))
        for example in range(len(Xtest)):
            classifythis = Xtest[example, :]
            distances = np.zeros((self.classCount,))
            for i in range(self.classCount):
                distance = np.sum((self.Xmodel[i, :] - classifythis) ** 2)
                distances[i] = distance
            hypothesis_index = np.argmin(distances)
            predictions[example] = self.Ymodel[hypothesis_index, 0]
        return predictions
