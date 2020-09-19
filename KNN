

class KNN:

    def train(self, Xtrain, Ytrain):
        self.classList = []
        self.Xmodel = [[0 for i in range(len(Xtrain[0]))] for j in range(len(self.classList))]
        self.Ymodel = [[0 for i in range(len(self.classList))] for j in range(2)]

        for classification in Ytrain:
            if classification not in self.classList:
                self.classList.append(classification)

        for i in range(len(self.classList)):
            self.Ymodel[0][i] = self.classList[i]

        for i in range(len(Xtrain)):
            exampleClass = Ytrain[i]
            model_index = self.Ymodel[0].index(exampleClass)
            for j in range(len(Xtrain[i])):
                self.Xmodel[model_index][j] += Xtrain[i][j]
            self.Ymodel[1][model_index] += 1

        for i in range(len(self.Xmodel)):
            for j in range(len(self.Xmodel[i])):
                self.Xmodel[i][j] /= self.Ymodel[1][i]

    
    def test(self, Xtest, Ytest):    
        predictions = [0 for i in range(len(Xtest))]
        for example in range(len(Xtest)):
            classifythis = Xtest[example]
            distances = [0 for l in range(len(self.Xmodel))]
            for i in range(len(self.Xmodel)):
                distance = 0
                for j in range(len(self.Xmodel[i])):
                    distance += abs((self.Xmodel[i][j] - classifythis[j])*(self.Xmodel[i][j] - classifythis[j]))
                distances[i] = distance
            shortest = min(distances)
            hypothesis_index = distances.index(shortest)
            predictions.append(self.Ymodel[0][hypothesis_index])

        return predictions
