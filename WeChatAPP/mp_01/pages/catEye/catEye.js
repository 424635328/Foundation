// pages/catEye/catEye.js
Page({
  data: {
    randomCat: {}, // 保存随机猫咪数据
    catDataList: [] 
  },
  onLoad() {
    const catData = require('../../pages/common/catData.js');
    this.setData({
      catDataList: Object.values(catData) 
    });
  },
  onShow() { 
    // 在页面每次显示时执行，获取随机猫咪数据
    const randomCatIndex = Math.floor(Math.random() * this.data.catDataList.length);
    this.setData({
      randomCat: this.data.catDataList[randomCatIndex] 
    });
  },
  takePhoto: function () {
    wx.chooseMedia({
      count: 1, // 只允许选择一张图片
      type: 'image', // 选择图片类型
      sourceType: ['album', 'camera'], // 从相机、相册中选择
      success: (res) => {
        this.setData({
          capturedImage: res.tempFiles[0].tempFilePath
        });
        // 跳转到识别结果页面
        wx.navigateTo({
          url: `/pages/recognitionResult/recognitionResult?image=${res.tempFiles[0].tempFilePath}`
        });
      }
    })
  },
  // 点击猫咪图片跳转到详情页
  navigateToCatDetail(e) {
    // 获取点击的猫咪 name
    const catName = e.currentTarget.dataset.name; // 确保在wxml中设置了data-name属性
    console.log('catName:', catName); // 添加日志输出
    // 使用 wx.navigateTo 跳转到 catDetail 页面，并传递 catName 参数
    wx.navigateTo({
      url: `/pages/catDetail/catDetail?catName=${catName}`
    });
  },
});