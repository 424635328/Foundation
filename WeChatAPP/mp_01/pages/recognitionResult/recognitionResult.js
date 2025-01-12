// pages/recognitionResult/recognitionResult.js
const catData = require('../../pages/common/catData.js');

Page({
  data: {
    capturedImage: '',
    recognitionResult: null, // 存储识别结果
    recognizedCat: null, // 存储识别到的猫咪信息
    isRecognizing: false // 添加一个状态标识是否正在识别
  },

  onLoad(options) {
    this.setData({
      capturedImage: options.image || '',
      isRecognizing: true // 开始识别，设置状态为 true
    });
    this.performRecognition(this.data.capturedImage);
  },

  // 模拟识别过程，实际应用中需要替换为真实的识别逻辑
  performRecognition(imageUrl) {
    setTimeout(() => {
      // 模拟识别成功
      const recognitionSuccess = Math.random() > 0.5; // 50% 概率识别成功

      if (recognitionSuccess) {
        // 从 catData 中随机选择一只猫
        const catKeys = Object.keys(catData);
        const randomCatIndex = Math.floor(Math.random() * catKeys.length);
        const randomCatKey = catKeys[randomCatIndex]; 
        const recognizedCat = catData[randomCatKey]; // 获取随机的猫数据

        this.setData({
          recognitionResult: {
            confidence: Math.random() * 0.45 + 0.55, // 置信度在 0.55 到 0.99 之间
            catName: recognizedCat.name // 存储猫的名字
          },
          recognizedCat: recognizedCat // 直接存储猫数据对象
        });
      } else {
        // 模拟识别失败
        this.setData({
          recognitionResult: {
            confidence: 0,
            catName: null
          },
          recognizedCat: null // 清空识别到的猫咪信息
        });
      }

      // 识别完成，设置状态为 false
      this.setData({ isRecognizing: false });
    }, 2000); // 模拟识别耗时 2 秒
  },

  navigateToCatDetail() {
    console.log('catName:', this.data.recognitionResult.catName);
    // 只有识别完成且成功识别到猫咪时才跳转
    if (!this.data.isRecognizing && this.data.recognizedCat) {
      // 将整个 recognizedCat 对象传递给详情页
      wx.navigateTo({
        url: `/pages/catDetail/catDetail?catName=${this.data.recognizedCat.name}` 
      });
    }
  }
});