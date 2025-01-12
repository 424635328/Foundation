// pages/catList/catList.js
const catData = require('../common/catData.js');

Page({
  data: {
    allCats: [], // 存储所有猫咪数据的数组
    cats: [] // 用于展示的猫咪数据，初始值与 allCats 相同
  },

  onLoad: function () {
    // 获取所有猫咪数据
    const allCats = Object.values(catData);
    this.setData({
      allCats: allCats,
      cats: allCats // 初始化用于展示的猫咪数据
    });
  },

  // 搜索框输入事件处理函数
  onSearchInput: function (e) {
    const searchKeyword = e.detail.value.toLowerCase(); // 获取搜索关键词并转换为小写
    const filteredCats = this.data.allCats.filter(cat => {
      return cat.name.toLowerCase().includes(searchKeyword); // 过滤猫咪名字中包含搜索关键词的猫咪
    });
    this.setData({
      cats: filteredCats // 更新用于展示的猫咪数据
    });
  },

  // 点击猫咪图片跳转到详情页
  navigateToCatDetail(e) {
    // 获取点击的猫咪 name
    const catName = e.currentTarget.dataset.name; 
    console.log('catName:', catName); // 添加日志输出
    // 使用 wx.navigateTo 跳转到 catDetail 页面，并传递 catName 参数
    wx.navigateTo({
      url: `/pages/catDetail/catDetail?catName=${catName}`
    });
  },

  // 点击猫咪名字跳转到详情页
  navigateToCatDetailByName(e) {
    // 获取点击的猫咪 name
    const catName = e.currentTarget.dataset.name; 
    // 使用 wx.navigateTo 跳转到 catDetail 页面，并传递 catName 参数
    wx.navigateTo({
      url: `/pages/catDetail/catDetail?catName=${catName}`
    });
  },
});