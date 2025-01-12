// pages/catDetail/catDetail.js
Page({
  data: {
    catData: {}
  },

  onLoad(options) {
    const catName = options.catName; // 从 URL 参数获取 catName
    const catData = require('../../pages/common/catData.js');

    // 遍历所有猫数据，找到与 catName 相匹配的猫
    for (const key in catData) {
      if (catData[key].name === catName) {
        this.setData({
          catData: catData[key]
        });
        break;
      }
    }
  }
});