// pages/cat/cat.js
const catDataUtil = require('../common/catData.js');

Page({
  data: {
    userInfo: null 
  },
  onLoad: function() {
    // 从本地缓存获取用户信息
    const userInfoFromStorage = wx.getStorageSync('userInfo');
    if (userInfoFromStorage) {
      this.setData({
        userInfo: userInfoFromStorage 
      });
    } else {
      // 用户未登录，显示登录按钮
      this.setData({
        userInfo: null
      });
    }
  },
  navigateToSponsor: function() {
    wx.navigateTo({
      url: '/pages/sponsor/sponsor' // 跳转到赞助页面
    });
  },

  // 登录按钮点击事件
  onLogin: function() {
    // 获取用户信息，可以使用 wx.getUserProfile 获取
    wx.getUserProfile({
      desc: '用于展示您的个人信息',
      success: (res) => {
        console.log('用户信息获取成功：', res.userInfo);
        // 更新页面数据，直接显示用户信息
        this.setData({
          userInfo: res.userInfo
        });
        // 将用户信息保存到本地缓存
        wx.setStorageSync('userInfo', res.userInfo);
      },
      fail: (err) => {
        console.error('用户信息获取失败：', err);
        // 处理错误信息，例如提示用户
      }
    });
  },

  // 上传猫咪信息
  uploadCatInfo: function() {
    // 跳转到上传猫咪信息页面，可以使用 wx.navigateTo
    wx.navigateTo({
      url: '/pages/uploadCat/uploadCat' 
    });
  },

  // 查看所有猫咪
  viewAllCats: function() {
    // 跳转到查看所有猫咪页面，可以使用 wx.navigateTo
    wx.navigateTo({
      url: '/pages/catList/catList' 
    });
  }
});