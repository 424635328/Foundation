#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

// 定义矩阵结构体
typedef struct {
  int rows;
  int cols;
  double** data;
} Matrix;

// 创建矩阵
Matrix* createMatrix(int rows, int cols) {
  Matrix* mat = (Matrix*)malloc(sizeof(Matrix));
  mat->rows = rows;
  mat->cols = cols;
  mat->data = (double**)malloc(rows * sizeof(double*));
  for (int i = 0; i < rows; i++) {
    mat->data[i] = (double*)malloc(cols * sizeof(double));
  }
  return mat;
}

// 释放矩阵内存
void freeMatrix(Matrix* mat) {
  for (int i = 0; i < mat->rows; i++) {
    free(mat->data[i]);
  }
  free(mat->data);
  free(mat);
}

// 随机初始化矩阵
void randomInit(Matrix* mat) {
  for (int i = 0; i < mat->rows; i++) {
    for (int j = 0; j < mat->cols; j++) {
      mat->data[i][j] = (double)rand() / RAND_MAX;
    }
  }
}

// 矩阵乘法
Matrix* dot(Matrix* A, Matrix* B) {
  if (A->cols != B->rows) {
    printf("Error: Matrix dimensions incompatible for multiplication.\n");
    return NULL;
  }
  Matrix* C = createMatrix(A->rows, B->cols);
  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < B->cols; j++) {
      C->data[i][j] = 0;
      for (int k = 0; k < A->cols; k++) {
        C->data[i][j] += A->data[i][k] * B->data[k][j];
      }
    }
  }
  return C;
}

// 矩阵转置
Matrix* transpose(Matrix* A) {
  Matrix* B = createMatrix(A->cols, A->rows);
  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->cols; j++) {
      B->data[j][i] = A->data[i][j];
    }
  }
  return B;
}

// 矩阵加法
void add(Matrix* A, Matrix* B) {
  if (A->rows != B->rows || A->cols != B->cols) {
    printf("Error: Matrix dimensions incompatible for addition.\n");
    return;
  }
  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->cols; j++) {
      A->data[i][j] += B->data[i][j];
    }
  }
}

// 矩阵数乘
void multiplyScalar(Matrix* A, double scalar) {
  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->cols; j++) {
      A->data[i][j] *= scalar;
    }
  }
}

// sigmoid 函数
double sigmoid(double x) {
  return 1.0 / (1.0 + exp(-x));
}

// sigmoid 函数的导数
double sigmoidDerivative(double x) {
  return x * (1 - x);
}

// 应用 sigmoid 函数到矩阵
void applySigmoid(Matrix* A) {
  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->cols; j++) {
      A->data[i][j] = sigmoid(A->data[i][j]);
    }
  }
}

// 应用 sigmoid 函数的导数到矩阵
void applySigmoidDerivative(Matrix* A) {
  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->cols; j++) {
      A->data[i][j] = sigmoidDerivative(A->data[i][j]);
    }
  }
}

int main() {
  srand(time(NULL)); // 初始化随机数生成器

  // 输入数据
  double X_data[4][2] = {{0, 0}, {0, 1}, {1, 0}, {1, 1}};
  Matrix* X = createMatrix(4, 2);
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 2; j++) {
      X->data[i][j] = X_data[i][j];
    }
  }

  // 目标输出
  double y_data[4][1] = {{0}, {1}, {1}, {0}};
  Matrix* y = createMatrix(4, 1);
  for (int i = 0; i < 4; i++) {
    y->data[i][0] = y_data[i][0];
  }

  // 初始化权重
  Matrix* hidden_weights = createMatrix(2, 3);
  randomInit(hidden_weights);
  Matrix* output_weights = createMatrix(3, 1);
  randomInit(output_weights);

  // 初始化学习率
  double learning_rate = 0.5;

  // 学习率衰减因子
  double decay_rate = 0.9999;

  // 训练循环
  for (int epoch = 0; epoch < 10000; epoch++) {
    // 前向传播
    Matrix* hidden_layer_input = dot(X, hidden_weights);
    Matrix* hidden_layer_output = createMatrix(hidden_layer_input->rows, hidden_layer_input->cols);
    for (int i = 0; i < hidden_layer_input->rows; i++) {
      for (int j = 0; j < hidden_layer_input->cols; j++) {
        hidden_layer_output->data[i][j] = hidden_layer_input->data[i][j];
      }
    }
    applySigmoid(hidden_layer_output);
    Matrix* output_layer_input = dot(hidden_layer_output, output_weights);
    Matrix* output_layer_output = createMatrix(output_layer_input->rows, output_layer_input->cols);
    for (int i = 0; i < output_layer_input->rows; i++) {
      for (int j = 0; j < output_layer_input->cols; j++) {
        output_layer_output->data[i][j] = output_layer_input->data[i][j];
      }
    }
    applySigmoid(output_layer_output);

    // 计算误差
    Matrix* error = createMatrix(y->rows, y->cols);
    for (int i = 0; i < y->rows; i++) {
      for (int j = 0; j < y->cols; j++) {
        error->data[i][j] = y->data[i][j] - output_layer_output->data[i][j];
      }
    }

    // 反向传播
    Matrix* d_output = createMatrix(output_layer_output->rows, output_layer_output->cols);
    for (int i = 0; i < output_layer_output->rows; i++) {
      for (int j = 0; j < output_layer_output->cols; j++) {
        d_output->data[i][j] = output_layer_output->data[i][j];
      }
    }
    applySigmoidDerivative(d_output);
    for (int i = 0; i < d_output->rows; i++) {
      for (int j = 0; j < d_output->cols; j++) {
        d_output->data[i][j] *= error->data[i][j];
      }
    }

    Matrix* error_hidden_layer = dot(d_output, transpose(output_weights));
    Matrix* d_hidden_layer = createMatrix(hidden_layer_output->rows, hidden_layer_output->cols);
    for (int i = 0; i < hidden_layer_output->rows; i++) {
      for (int j = 0; j < hidden_layer_output->cols; j++) {
        d_hidden_layer->data[i][j] = hidden_layer_output->data[i][j];
      }
    }
    applySigmoidDerivative(d_hidden_layer);
    for (int i = 0; i < d_hidden_layer->rows; i++) {
      for (int j = 0; j < d_hidden_layer->cols; j++) {
        d_hidden_layer->data[i][j] *= error_hidden_layer->data[i][j];
      }
    }

    // 更新权重
    Matrix* temp1 = dot(transpose(hidden_layer_output), d_output);
    multiplyScalar(temp1, learning_rate);
    add(output_weights, temp1);
    freeMatrix(temp1);
    
    Matrix* temp2 = dot(transpose(X), d_hidden_layer);
    multiplyScalar(temp2, learning_rate);
    add(hidden_weights, temp2);
    freeMatrix(temp2);

    // 动态调整学习率
    learning_rate *= decay_rate;
    
    // 释放内存
    freeMatrix(hidden_layer_input);
    freeMatrix(hidden_layer_output);
    freeMatrix(output_layer_input);
    freeMatrix(output_layer_output);
    freeMatrix(error);
    freeMatrix(d_output);
    freeMatrix(error_hidden_layer);
    freeMatrix(d_hidden_layer);
  }

  // 测试训练后的模型
  Matrix* hidden_layer_input = dot(X, hidden_weights);
  Matrix* hidden_layer_output = createMatrix(hidden_layer_input->rows, hidden_layer_input->cols);
  for (int i = 0; i < hidden_layer_input->rows; i++) {
    for (int j = 0; j < hidden_layer_input->cols; j++) {
      hidden_layer_output->data[i][j] = hidden_layer_input->data[i][j];
    }
  }
  applySigmoid(hidden_layer_output);
  Matrix* output_layer_input = dot(hidden_layer_output, output_weights);
  Matrix* output_layer_output = createMatrix(output_layer_input->rows, output_layer_input->cols);
  for (int i = 0; i < output_layer_input->rows; i++) {
    for (int j = 0; j < output_layer_input->cols; j++) {
      output_layer_output->data[i][j] = output_layer_input->data[i][j];
    }
  }
  applySigmoid(output_layer_output);

  // 打印预测结果
  printf("预测结果:\n");
  for (int i = 0; i < output_layer_output->rows; i++) {
    for (int j = 0; j < output_layer_output->cols; j++) {
      printf("%f ", output_layer_output->data[i][j]);
    }
    printf("\n");
  }

  // 释放内存
  freeMatrix(X);
  freeMatrix(y);
  freeMatrix(hidden_weights);
  freeMatrix(output_weights);
  freeMatrix(hidden_layer_input);
  freeMatrix(hidden_layer_output);
  freeMatrix(output_layer_input);
  freeMatrix(output_layer_output);

  return 0;
}