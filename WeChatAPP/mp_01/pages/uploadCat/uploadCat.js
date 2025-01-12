// pages/uploadCat/uploadCat.js
const util = require('../common/catData.js'); 

Page({
  data: {
    imageUrl: '',
    name: '',
    genderIndex: 0,
    genderOptions: ['公', '母'],
    age: '',
    sterilizationIndex: 0,
    sterilizationOptions: ['已绝育', '未绝育'],
    location: '',
    personality: '',
    features: ''
  },

  chooseImage: function() {
    wx.chooseMedia({
      count: 1,
      sizeType: ['original', 'compressed'],
      sourceType: ['album', 'camera'],
      success: (res) => {
        this.setData({
          imageUrl: res.tempFilePaths[0]
        });
      }
    });
  },

  bindGenderChange: function(e) {
    this.setData({
      genderIndex: e.detail.value
    });
  },

  bindSterilizationChange: function(e) {
    this.setData({
      sterilizationIndex: e.detail.value
    });
  },

  submitForm: function(e) {
    const formData = e.detail.value;
    const newCatData = {
      imageUrl: this.data.imageUrl,
      name: formData.name,
      gender: this.data.genderOptions[this.data.genderIndex],
      age: formData.age,
      sterilization: this.data.sterilizationOptions[this.data.sterilizationIndex],
      location: formData.location,
      personality: formData.personality,
      features: formData.features
    };

    // 添加新猫咪数据到本地缓存
    util.addCatData(newCatData);

    // 提示用户上传成功
    wx.showToast({
      title: '上传成功',
      icon: 'success',
      duration: 2000
    });

    // 返回猫咪列表页面
    wx.navigateBack({
      delta: 1 
    });
  }
});