import random
import matplotlib.pyplot as plt
import numpy as np
train_data = np.genfromtxt(r"C:\Users\Vivek Muskan\Desktop\ML\mnist_train.csv",delimiter = ",")
test_data = np.genfromtxt(r"C:\Users\Vivek Muskan\Desktop\ML\mnist_test.csv",delimiter = ",")
answerfile = "answer.csv"

def Back_Prop(X, y, w, b, eta, Num_Layers):
    # Every variable has been stored layer wise
    # Random Initialisation
    del_w = [np.zeros(i.shape) for i in w]
    del_b = [np.zeros(i.shape) for i in b]
    
    # Step1 -> V[0] = X
    V = [X]
    H = []
    # Step 2 -> Feed Forward
    for i in range(Num_Layers-1):
        h = ( np.add( np.dot(w[i], V[i]), b[i]))
        H.append(h)
        v = sigmoid(h)
        V.append(v)
    
    # Step 3 -> Calculating Error at Output Layer
    delta = np.multiply(sigmoid_Der(H[-1]), np.subtract(y, V[-1]))
    Err = [delta]
    
    # Step 4 -> Backward Error propagation 
    for i in range(2,Num_Layers):
        temp = np.multiply(sigmoid_Der(H[-i]), np.dot(w[-i+1].transpose(), Err[-i+1]))
        Err.insert(0,temp)
    
    # Step 5 -> Calculation of changes in weights
    for i in range(Num_Layers-1):
        delta = np.array(Err[i]).reshape(len(Err[i]),1)
        v = np.array(V[i]).reshape(1,len(V[i]))
        del_w[i] = eta*np.matmul(delta, v)
    
    del_b = Err
    return (del_w, del_b)


def sigmoid_scalar(x):
    return (1.0/(1+np.exp(-x)))
sigmoid = np.vectorize(sigmoid_scalar)

# def sigmoid_scalar(x):
#     return (np.tanh(x))
# sigmoid = np.vectorize(sigmoid_scalar)

def sigmoid_Der_scalar(x):
    p = sigmoid_scalar(x)
    return p*(1-p)
sigmoid_Der = np.vectorize(sigmoid_Der_scalar)

# def sigmoid_Der_scalar(x):
#     p = sigmoid_scalar(x)
#     return (1-p*p)
# sigmoid_Der = np.vectorize(sigmoid_Der_scalar)

def predict(X,w,b):
    for i in range(len(w)):
        h = ( np.add( np.dot(w[i], X), b[i])).transpose()
        X = sigmoid(h)
    return X


def batch_update(batch, weights, biases, eta, Num_Layers):
    del_w = [np.zeros(i.shape) for i in weights]
    del_b = [np.zeros(i.shape) for i in biases]
    for i in range(len(batch)):
        # Vectorisation of label
        y = np.zeros(10)
        y[int(batch[i][0])] = 1 
        dw, db = Back_Prop(batch[i][1:]/255, y, weights, biases, eta, Num_Layers)
        # Update Summation over batch
        del_w = [a+b for a, b in zip(del_w, dw)]
        del_b = [a+b for a, b in zip(del_b, db)]
    temp_w = [w+(1.0/len(batch))*dw for w, dw in zip(weights, del_w)]
    temp_b = [b+(1.0/len(batch))*db for b, db in zip(biases, del_b)]
    return (temp_w, temp_b)


def Neural_Network(train_data, test_data, Layer_details, epoch_no, batch_size, learning_rate):
    # Weights intialisation
    M = len(Layer_details)
    weights = [np.random.randn(Layer_details[i+1], Layer_details[i])*(0.1) for i in range(M-1)]
    biases = [np.random.randn(1, Layer_details[i+1]).ravel()*(0.1) for i in range(M-1)]
    
    Accuracy = []
    x_cord = []
    
    print("Learning Rate = {0},    Epoch no = {1},    Batch Size = {2} ".format(learning_rate, epoch_no, batch_size))
    print("")
    
    for i in range(epoch_no):
        random.shuffle(train_data)
        Batch_set = [train_data[k:k+batch_size] for k in range(0, len(train_data), batch_size)]
        for batch in Batch_set:
            temp_w, temp_b = batch_update(batch, weights, biases, learning_rate, M)
            weights = temp_w
            biases = temp_b
        
        count = 0
        for t in test_data:
            temp = predict(t[1:], weights, biases)
            if t[0] == np.where(temp == np.amax(temp))[0][0]:
                count += 1
        acc_percent = 100*count/(len(test_data))
        #print("Epoch {0} / 10 : {1} / 1000 ".format(i,count))
        Accuracy.append(acc_percent)
        x_cord.append(i)
        
    plt.plot(x_cord, Accuracy, label = 'Layer Details = {0}'.format(Layer_details))
#     result = []
#     k =0
#     for t in test_data:
#         y = predict(t,weights,biases)
#         p = np.where(y == np.amax(y))[0][0]
#         result.append(p)
#         k = k+1
#     #print(result)
#     np.savetxt(answerfile, result, fmt="%d")
