// app.js
const util = require('./utils/util.js'); // 导入 util.js


App({
  onLaunch() {
    // 登录
    wx.login({
      success: res => {
        // 发送 res.code 到后台换取 openId, sessionKey, unionId
        // 你可以在此处调用自己的服务器 API，将 res.code 传递给服务器，
        // 服务器会使用 res.code 获取用户的信息，并返回给小程序
        console.log('登录成功：', res.code);
      },
      fail: err => {
        console.error('登录失败：', err);
      }
    });
  }
  
});

