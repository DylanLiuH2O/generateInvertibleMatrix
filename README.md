# generateInvertibleMatrix
随机可逆矩阵生成小工具（a tool of generating random invertible matrix）

## 算法  

本质上是一定迭代次数的随机初等行变换，由随机数决定执行何种初等行变换，最后得到可逆矩阵。  

## 用法  

编译源代码，`g++ ./genInvertibleMat.cc -o genInver`。  
命令格式: `./genInvertibaleMat <iterations> <order> <filename> [int/double]`。  
`iteration`是迭代次数，即执行初等行变换的次数，次数越多一般值变化越大。  
`order`是矩阵阶数。
`filename`是文件名，不带路径则生成于当前目录，可以使用其他位置的路径。  
`int/double`是可选项，用来决定倍加变换和倍乘变换的因子是整数还是浮点数。  

