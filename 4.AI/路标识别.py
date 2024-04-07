import numpy as np
import matplotlib.pyplot as plt
from tensorflow.keras.models import Sequential
from tensorflow.keras.layers import Dense
from tensorflow.keras.optimizers import Adam
from tensorflow.python.keras.utils.np_utils import to_categorical
from tensorflow.keras.layers import Dropout, Flatten
from tensorflow.keras.layers import Conv2D, MaxPooling2D
import cv2
from sklearn.model_selection import train_test_split
import pickle
import os
import pandas as pd
import random
from tensorflow.keras.preprocessing.image import ImageDataGenerator
################# Parameters #####################

path = "./data/myData"  # 包含所有类文件夹的文件夹
labelFile = './data/labels.csv'  # 包含所有类名的文件
batch_size_val = 50  # 要一起处理多少
steps_per_epoch_val = 446  # 迭代次数
epochs_val = 10  # 整个训练集训练次数
imageDimesions = (32, 32, 3)  # 32*32的彩色图
testRatio = 0.2  # 如果分割1000个图像，将分割200个用于测试 测试集占比
validationRatio = 0.2  # 如果1000张图像，其余800张的20%将是160张用于验证 验证机占比
###################################################


############################### 导入图像
count = 0
images = []
classNo = []
myList = os.listdir(path)
print("Total Classes Detected:", len(myList))
noOfClasses = len(myList)
print("Importing Classes.....")
for x in range(0, len(myList)):
    myPicList = os.listdir(path + "/" + str(count))
    for y in myPicList:
        curImg = cv2.imread(path + "/" + str(count) + "/" + y)
        images.append(curImg)
        classNo.append(count)
    print(count, end=" ")
    count += 1
print(" ")
# 存着对应的图片信息和标签
images = np.array(images)
classNo = np.array(classNo)

############################### 分割数据 分割test集和验证集
X_train, X_test, y_train, y_test = train_test_split(images, classNo, test_size=testRatio)
X_train, X_validation, y_train, y_validation = train_test_split(X_train, y_train, test_size=validationRatio)

# X_train =要训练的图像数组
# y_train =对应的类别ID

############################### 检查每个数据集的图像数量是否与标签数量匹配
print("Data Shapes")
print("Train", end="");
print(X_train.shape, y_train.shape)
print("Validation", end="");
print(X_validation.shape, y_validation.shape)
print("Test", end="");
print(X_test.shape, y_test.shape)
assert (X_train.shape[0] == y_train.shape[
    0]), "训练集中的图像个数不等于训练集中的标签个数"
assert (X_validation.shape[0] == y_validation.shape[
    0]), "图像的数量不等于验证集中标签的数量"
assert (X_test.shape[0] == y_test.shape[0]), "图像的数量不等于测试集中标签的数量"
assert (X_train.shape[1:] == (imageDimesions)), " 训练图像的尺寸不对 "
assert (X_validation.shape[1:] == (imageDimesions)), " 验证图像的尺寸错误 "
assert (X_test.shape[1:] == (imageDimesions)), " 测试图像的尺寸是错误的"

############################### 读取CSV文件
data = pd.read_csv(labelFile)
print("data shape ", data.shape, type(data))

############################### 显示所有类的一些示例图像
# 可视化部分图标及类别
num_of_samples = []
cols = 5
num_classes = noOfClasses
fig, axs = plt.subplots(nrows=num_classes, ncols=cols, figsize=(5, 300))
fig.tight_layout()
for i in range(cols):
    for j, row in data.iterrows():
        x_selected = X_train[y_train == j]
        axs[j][i].imshow(x_selected[random.randint(0, len(x_selected) - 1), :, :], cmap=plt.get_cmap("gray"))
        axs[j][i].axis("off")
        if i == 2:
            axs[j][i].set_title(str(j) + "-" + row["Name"])
            num_of_samples.append(len(x_selected))

############################### 显示一个条形图，显示每个类别没有样本
# 对类别分布做一个统计 饼图
print(num_of_samples)
plt.figure(figsize=(12, 4))
plt.bar(range(0, num_classes), num_of_samples)
plt.title("Distribution of the training dataset")
plt.xlabel("Class number")
plt.ylabel("Number of images")
plt.show()


############################### 图像预处理
# 灰度
def grayscale(img):
    img = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
    return img


# 直方图均衡化
def equalize(img):
    img = cv2.equalizeHist(img)
    return img


def preprocessing(img):
    img = grayscale(img)  # 转换为灰度
    img = equalize(img)  # 标准化图像中的照明
    img = img / 255  # 将0到1之间的值规范化，而不是0到255
    return img


# 对所有数据进行预处理
X_train = np.array(list(map(preprocessing, X_train)))  # 对所有图像进行刺激和预处理
X_validation = np.array(list(map(preprocessing, X_validation)))
X_test = np.array(list(map(preprocessing, X_test)))
#cv2.imshow("GrayScale Images",
           #X_train[random.randint(0, len(X_train) - 1)])  # 检查训练是否正确完成

############################### 添加深度为1
# 增加一维
X_train = X_train.reshape(X_train.shape[0], X_train.shape[1], X_train.shape[2], 1)
X_validation = X_validation.reshape(X_validation.shape[0], X_validation.shape[1], X_validation.shape[2], 1)
X_test = X_test.reshape(X_test.shape[0], X_test.shape[1], X_test.shape[2], 1)

############################### 增强图像:使其更通用
# width_shift_range 图像偏移 width_shift_range*width
# height_shift_range  height_shift_range*height
# zoom_range: Float or [lower, upper]. Range for random zoom. 随机缩放范围
# shear_range: Float. Shear Intensity (Shear angle in counter-clockwise direction in degrees) # 剪切-剪切角度-逆时针剪切
# rotation_range: Int. Degree range for random rotations. 随机旋转的角度范围
dataGen = ImageDataGenerator(width_shift_range=0.1,
                             # 0.1 = 10%     如果超过1，例如10，则表示没有。像素(如10像素)
                             height_shift_range=0.1,
                             zoom_range=0.2,  # 0.2表示从0.8到1.2
                             shear_range=0.1,  # 剪切角大小
                             rotation_range=10)  # 度
dataGen.fit(X_train)
batches = dataGen.flow(X_train, y_train,
                       batch_size=20)  # 请求数据生成器生成图像批处理大小= no。每次调用时创建的图像
X_batch, y_batch = next(batches)

# 显示放大的图像样本
fig, axs = plt.subplots(1, 15, figsize=(20, 5))
fig.tight_layout()

for i in range(15):
    axs[i].imshow(X_batch[i].reshape(imageDimesions[0], imageDimesions[1]))
    axs[i].axis('off')
plt.show()

# one-hot
y_train = to_categorical(y_train, noOfClasses)
y_validation = to_categorical(y_validation, noOfClasses)
y_test = to_categorical(y_test, noOfClasses)


############################### 卷积神经网络模型 定义模型
# 卷积-卷积-池化 卷积-卷积-池化  drop
def myModel():
    no_Of_Filters = 60
    size_of_Filter = (5, 5)  # 这是在图像周围移动以获取特征的内核。
    # 当使用3232的图像时，这将从每个边界移除2个像素
    size_of_Filter2 = (3, 3)
    size_of_pool = (2, 2)  # 缩小所有的特征映射，以泛化更多，以减少过拟合
    no_Of_Nodes = 500  # 不。隐藏层中的节点
    model = Sequential()
    model.add((Conv2D(no_Of_Filters, size_of_Filter, input_shape=(imageDimesions[0], imageDimesions[1], 1),
                      activation='relu')))  # 增加更多的卷积层=更少的特征，但可能会提高精度
    model.add((Conv2D(no_Of_Filters, size_of_Filter, activation='relu')))
    model.add(MaxPooling2D(pool_size=size_of_pool))  # 不影响过滤器的深度/数量

    model.add((Conv2D(no_Of_Filters // 2, size_of_Filter2, activation='relu')))
    model.add((Conv2D(no_Of_Filters // 2, size_of_Filter2, activation='relu')))
    model.add(MaxPooling2D(pool_size=size_of_pool))
    model.add(Dropout(0.5))

    model.add(Flatten())
    model.add(Dense(no_Of_Nodes, activation='relu'))
    model.add(Dropout(0.5))  # 输入节点随着每次更新1所有0无
    model.add(Dense(noOfClasses, activation='softmax'))  # 输出层
    # 编译模型
    model.compile(Adam(lr=0.001), loss='categorical_crossentropy', metrics=['accuracy'])
    return model


############################### TRAIN
model = myModel()
print(model.summary())
# 开始训练
history = model.fit_generator(dataGen.flow(X_train, y_train, batch_size=batch_size_val),
                              steps_per_epoch=steps_per_epoch_val, epochs=epochs_val,
                              validation_data=(X_validation, y_validation), shuffle=1)

############################### PLOT
plt.figure(1)
plt.plot(history.history['loss'])
plt.plot(history.history['val_loss'])
plt.legend(['training', 'validation'])
plt.title('loss')
plt.xlabel('epoch')
plt.figure(2)
plt.plot(history.history['accuracy'])
plt.plot(history.history['val_accuracy'])
plt.legend(['training', 'validation'])
plt.title('Acurracy')
plt.xlabel('epoch')
plt.show()
# 开始评估模型
score = model.evaluate(X_test, y_test, verbose=0)
print('Test Score:', score[0])
print('Test Accuracy:', score[1])

#保持模型
model.save('traffic.h5')
# 将模型存储为pickle对象
# pickle_out = open("model_trained.p", "wb")  # wb = WRITE BYTE
# pickle.dump(model, pickle_out)
# pickle_out.close()
# cv2.waitKey(0)
